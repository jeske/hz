controllable = {
key_maps = a_key_map, -- we need the key map!
firing_frequency = 200.0,

keyUp = function (self,vk_code)
	local map = self.key_maps[vk_code];
	if (map ~= nil) then
		self.key[map] = nil;
		self:handleKeys();
	end
end,

keyDown = function(self, vk_code) 
	local map = self.key_maps[vk_code];
	if (map ~= nil) then
		self.key[map] = 1;
		self:handleKeys();
	end
end,

inputEvent = function(self,ev) 
    print(format("keydown = (%d)'%s'",ev,tostring(ev)));

	if (ev == 9) then  -- tab
		-- switch active objects!
		local nextobji, nextobj;
		local first_obj;

		nextobji, nextobj = next(srvobjs,nil);
		first_obj = nextobj;

		repeat
			while ((nextobji) and (nextobj ~= self)) do
				nextobji, nextobj = next(srvobjs,nextobji);
			end

			nextobji,nextobj = next(srvobjs,nextobji);
		until ((nextobj == nil) or (nextobj.inputEvent));

		if (nextobj == nil) then
			nextobj = first_obj;
		end

		if (nextobj ~= nil) then
			C_obj_followsprite(nextobj.objnum);
		end
	
	elseif (ev == 32) then
		-- try to pickup the unit under us!
		self.attempt_pickup_drop_timer = 200;
	elseif (ev == 1000032) then -- space 
		-- fire!
		local xpos,ypos;
		local dir;
		
		if (self.timgdir) then
			dir = self.timgdir;
		else
			dir = self.imgdir;
		end

		xpos,ypos = C_obj_getPos(self.objnum);

		C_addsprite(self.bullet_type,
				xpos + 32 + (Dirx[dir] * 80), ypos + 32 + (Diry[dir-1] * 80), 
				Dirx[dir-1] * 500.0/1000.0,
				Diry[dir-1] * 500.0/1000.0);

--		new_obj = new Sprite( defaultSpriteList, OBJ_BULLET, 
--					Dirx[(int)shipSprite->frame]*6.0 + 32.0 + shipSprite->posx,
--                    Diry[(int)shipSprite->frame]*6.0 + 32.0 + shipSprite->posy,
--                    Dirx[(int)shipSprite->frame]*500.0/1000.0,
--                    Diry[(int)shipSprite->frame]*500.0/1000.0 );


	end
end,

handleKeys = function (self)
	local key = self.key;
	local dest_dir = self.dest_dir;
	local centered = 0;

	printTable(key);

	if (key.o) then
		self.timgdir = self.timgdir + 1;
		if (self.timgdir > 40) then
			self.timgdir = self.timgdir - 40.0;
		end
	end

	if (key.space) then
		self.firing = 1;
	else
		self.firing = nil;
	end

	if (key.p) then
		self.timgdir = self.timgdir - 1;
		if (self.timgdir < 0) then
			self.timgdir = self.timgdir + 40.0;
		end
	end

	if (key.up) then
		if (key.right) then
			dest_dir = 5;  -- up/right
		elseif (key.left) then
			dest_dir = 35; -- up/left
		else 
			dest_dir = 0;  -- up
		end
	elseif (key.down) then
		if (key.right) then
			dest_dir = 15; -- down/right
		elseif (key.left) then
			dest_dir = 25; -- down/left
		else
			dest_dir = 20; -- down
		end
	elseif (key.right) then
		dest_dir = 10;     -- right
	elseif (key.left) then
		dest_dir = 30;     -- left
	else
		centered = 1;
	end
	
	self.ctrl_centered = centered;

	self.dest_dir = dest_dir;

	print(format("handlekeys() dest_dir = %d, centered = %d, centered = %s",
		dest_dir,centered, tostring(self.ctrl_centered)));
end

}; -- end controllable


collisions_active = 0;
MAX_COLLISIONS = 5;

collidable = {
ge_collision = function(self,x,y,whoIhit)

	if self.attempt_pickup_drop_timer then
		if not self.carrying_unit then
			print("trying to carry unit! " .. whoIhit.obj_type_name);
			self.carrying_unit = whoIhit;
			self.attempt_pickup_drop_timer = nil; -- don't pickup anymore
		end

	end

	if ((collisions_active < MAX_COLLISIONS) and (self.layer == whoIhit.layer)) then
		C_addsprite("explosion",x,y);
		collisions_active = collisions_active + 1;
	end
end

}; -- end collidable

air_physics = {
	
-- properties...
vx = 0, vy = 0, rot = 0,

	-- methods....

doTick = function(self,tick_diff)

  	-- handle carrying a unit
	
	if self.attempt_pickup_drop_timer then
		if self.carrying_unit then
			-- we need to try and drop it!!
			print("dropping unit ".. self.carrying_unit.obj_type_name);
			self.carrying_unit = nil;
			self.attempt_pickup_drop_timer = nil; -- reset the timer!
		else 
			self.attempt_pickup_drop_timer = self.attempt_pickup_drop_timer - tick_diff;
			if self.attempt_pickup_drop_timer <= 0 then
				self.attempt_pickup_drop_timer = nil;
			end	
		end
	end

	if self.carrying_unit then
		x,y = C_obj_getPos(self.objnum);
		C_obj_setPos(self.carrying_unit.objnum,x,y);	
 	end


	-- if we need to fire a bullet, fire one!

	handle_firing(self,tick_diff);

	-- on to physics calculations

	local vx, vy, rot;
	local dest_dir = self.dest_dir;
	local ax, ay; -- acceleration vectors

	local exp_timer = self.exp_timer;
	local frame_time = self.frame_time; -- 70 seconds? frames? what is this?
	local exp_img_num = self.rimgdir;
	local EXP_IMG_COUNT = 10;
	local MAX_SHIP_FRAME = 40;

	exp_timer = exp_timer + tick_diff;

	while (exp_timer > frame_time) do
		exp_timer = exp_timer - frame_time;
		exp_img_num = exp_img_num + 1;

		if (exp_img_num > EXP_IMG_COUNT) then
			exp_img_num = 1;
		end
	end

	self.exp_timer = exp_timer;
	self.rimgdir = floor(exp_img_num);

	vx, vy = C_obj_getVelocity(self.objnum);
	rot = self.rot;

	if (self.ctrl_centered == 1.0) then
		ax = 0.0;
		ay = 0.0;
	else -- (not self.ctrl_centered)
		-- accelerate in that direction!
		ax = Dirx[floor(dest_dir)];
		ay = Diry[floor(dest_dir)];
		-- print(format("accelerate at (%f,%f)",ax,ay));
	end
	
	if (ax == 0.0) then	
		-- coast!
		if (vx > tick_diff/2000.0) then
			vx = vx - tick_diff/2000.0;
		elseif (vx < -tick_diff/2000.0) then
			vx = vx + tick_diff/2000.0;
		else
			vx = 0;
		end
	else
		-- apply the acceleration!
		vx = vx + (ax * tick_diff/4000.0);
	end

	if (ay == 0.0) then
		-- coast!
		if (vy > tick_diff/2000.0) then
			vy = vy - tick_diff/2000.0;
		elseif (vy < -tick_diff/2000.0) then
			vy = vy + tick_diff/2000.0;
		else
			vy = 0;
		end	
	else
		-- apply the acceleration!
		vy = vy + (ay * tick_diff/4000.0);
	end

	if (self.ctrl_centered == 1.0) then
		C_obj_setVelocity(self.objnum,vx,vy);
		return;
	end

	local i_rot = floor(rot);

	if (i_rot == dest_dir) then
		-- we're facing, so given an acceleration boost!
		vx = vx + (ax * tick_diff/2000.0);
		vy = vy + (ay * tick_diff/2000.0);
	else
		-- we need to turn "into the wind"
		local turn_vec;
		local cw_distance;
		local ccw_distance;

		-- first, figur out what direction to turn
		if (i_rot > dest_dir) then
			ccw_distance = i_rot - dest_dir;
			cw_distance  = MAX_SHIP_FRAME - (ccw_distance);
		else
			cw_distance = dest_dir - i_rot;
			ccw_distance = MAX_SHIP_FRAME - (cw_distance);
		end

		local TURN_RATE = 1.0;

		if (cw_distance < ccw_distance) then
			if (cw_distance < TURN_RATE) then
				turn_vec = cw_distance;
			else
				turn_vec = TURN_RATE; -- cw
			end
		else
			if (ccw_distance < TURN_RATE) then
				turn_vec = 0.0 - ccw_distance;
			else
				turn_vec = 0.0 - TURN_RATE; -- ccw
			end
		end

		i_rot = i_rot + turn_vec;
		if (i_rot < 0.0) then
			i_rot = i_rot + MAX_SHIP_FRAME;
		end
		if (i_rot >= MAX_SHIP_FRAME) then
			i_rot = i_rot - MAX_SHIP_FRAME;
		end
	end 

	if self.imgdir_max then	
		self.imgdir = floor((i_rot / MAX_SHIP_FRAME) * self.imgdir_max) + 1;
	else
		self.imgdir = i_rot + 1;
	end
	self.rot = i_rot;
	C_obj_setVelocity(self.objnum,vx,vy);

end -- function end

}; -- end air_physics



ground_physics = {
 vx = 0, vy = 0, rot = 0,
doTick = function(self,tick_diff)
	local vx, vy, rot;
	local dest_dir = self.dest_dir;
	local ax, ay; -- acceleration vectors
	local speed_scale = 2000;
		
	vx, vy = C_obj_getVelocity(self.objnum);
	rot = self.rot;

	if (self.ctrl_centered == 1.0) then
		ax = 0.0;
		ay = 0.0;

		-- coast!
		if (vx > tick_diff/speed_scale) then
			vx = vx - tick_diff/speed_scale;
		elseif (vx < -tick_diff/speed_scale) then
			vx = vx + tick_diff/speed_scale;
		else
			vx = 0;
		end

		-- coast!
		if (vy > tick_diff/speed_scale) then
			vy = vy - tick_diff/speed_scale;
		elseif (vy < -tick_diff/speed_scale) then
			vy = vy + tick_diff/speed_scale;
		else
			vy = 0;
		end	

		C_obj_setVelocity(self.objnum,vx,vy);
		return; -- dirty return

	else 

		-- figure out if we are facing the right direction	

		if (floor(rot) == dest_dir) then
			ax = Dirx[floor(rot)];
			ay = Diry[floor(rot)];
	
			-- print(format("accelerate at (%f,%f)",ax,ay));
	
			-- we're facing, so given an acceleration boost!
			vx = vx + (ax * tick_diff/speed_scale);
			vy = vy + (ay * tick_diff/speed_scale);
		else
			-- we need to turn "into the wind"
			local turn_vec;
			local cw_distance;
			local ccw_distance;
			local MAX_SHIP_FRAME = 40;


			if ((vx == 0.0) and (vy == 0.0)) then
				-- first, figur out what direction to turn
				if (rot > dest_dir) then
					ccw_distance = rot - dest_dir;
					cw_distance  = MAX_SHIP_FRAME - (ccw_distance);
				else
					cw_distance = dest_dir - rot;
					ccw_distance = MAX_SHIP_FRAME - (cw_distance);
				end
		
				local TURN_RATE = 0.4;
		
				if (cw_distance < ccw_distance) then
					if (cw_distance < TURN_RATE) then
						turn_vec = cw_distance;
					else
						turn_vec = TURN_RATE; -- cw
					end
				else
					if (ccw_distance < TURN_RATE) then
						turn_vec = 0.0 - cw_distance;
					else
						turn_vec = 0.0 - TURN_RATE; -- ccw
					end
				end
		
				rot = rot + turn_vec;
				if (rot < 0.0) then
					rot = rot + MAX_SHIP_FRAME;
				end
				if (rot >= MAX_SHIP_FRAME) then
					rot = rot - MAX_SHIP_FRAME;
				end
			else
			
				-- coast!
				if (vx > 50.0/1000.0) then
					vx = vx - 50.0/1000.0;
				elseif (vx < -50.0/1000.0) then
					vx = vx + 50.0/1000.0;
				else
					vx = 0;
				end
		
				-- coast!
				if (vy > 50.0/1000.0) then
					vy = vy - 50.0/1000.0;
				elseif (vy < -50.0/1000.0) then
					vy = vy + 50.0/1000.0;
				else
					vy = 0;
				end
			end
		end
	end

	
	vx = max(-0.15,min(0.15,vx));
	vy = max(-0.15,min(0.15,vy));


	self.imgdir = floor(rot) + 1;
	self.rot = rot;
	C_obj_setVelocity(self.objnum,vx,vy);
	
end
}; -- end groud_physics


function cycle(inval,low,high)
  inval = inval + 1;
  if inval > high then
    inval = low
  end
  return inval
end

mainship_physics = {
vx = 0, vy = 0, rot = 0, reqMode = "Flying",
imgdir = 1, walk_step = 1, walk_dir = 1, trans_img = 1, tick_count = 0, tick_count2 = 0, tick_count3 = 0,
doTick = function(self,tick_diff)
  self.tick_count = self.tick_count + tick_diff;
  self.tick_count2 = self.tick_count2 + tick_diff;
  self.tick_count3 = self.tick_count3 + tick_diff;
  local TIMER = 50;
  local TURN_TIMER = 600;
  local NEXT_MODE_TIMER = 10000;

  if self.tick_count > TIMER then
    self.imgdir = cycle(self.imgdir,1,24)
    self.trans_img = cycle(self.trans_img,1,20)
    self.walk_step = cycle(self.walk_step,1,7)
    self.tick_count = self.tick_count - TIMER;
  end

  if self.tick_count3 > TURN_TIMER then
    self.tick_count3 = self.tick_count3 - TURN_TIMER;
    self.walk_dir = cycle(self.walk_dir,1,8);
  end

  if self.tick_count2 > NEXT_MODE_TIMER then
    self.tick_count2 = 0;


    if self.Mode == "Flying" then
      self.Mode = "Transforming"
    elseif self.Mode == "Transforming" then
      self.Mode = "Standing"
    elseif self.Mode == "Standing" then
      self.Mode = "Walking"
    elseif self.Mode == "Walking" then
      self.Mode = "Flying"
    end

  end

end,
doTick2 = function(self,tick_diff)
  if self.reqMode == "Flying" then
    self.Mode = "Flying";
    air_physics.doTick(self,tick_diff)
  elseif self.reqMode == "Walking" then
    self.Mode = "Walking";
    ground_physics.doTick(self,tick_diff)
  elseif self.reqMode == "Standing" then
    self.reqMode = "Walking";
  elseif self.reqMode == "Transforming" then
    self.doTransform(self,tick_diff)
  end
end,

doTransform = function(self,tick_diff)
   if self.Mode ~= "Transforming" then 
     if self.Mode == "Flying" then
       self.trans_img = 20;
       self.trans_dir = -1;
     else
       self.trans_img = 1;
       self.trans_dir = 1;
     end
     self.trans_tick_wait = 0;
     self.Mode = "Transforming";
   end

   self.trans_tick_wait = self.trans_tick_wait + tick_diff;
   local TRANSFORM_SPEED = 200;

   if self.trans_tick_wait > TRANSFORM_SPEED then
     self.trans_tick_wait = self.trans_tick_wait - TRANSFORM_SPEED;
     self.trans_img = self.trans_img + self.trans_dir;
     if (self.trans_img <= 0) then
       self.Mode = "Walking";
       self.reqMode = "Walking";
     end
     if (self.trans_img >= 20) then
       self.Mode = "Flying";
       self.reqMode = "Flying";
     end
   end

end
}; -- end mainship_physics


function handle_firing(self, tick_diff)
	if self.firing then
		local xpos,ypos;
		local dir;

		if self.ticks_til_next_shot then
			self.ticks_til_next_shot = self.ticks_til_next_shot - tick_diff;
		else
			self.ticks_til_next_shot = 0;
		end

		if self.ticks_til_next_shot <= 0 then
			self.ticks_til_next_shot = self.ticks_til_next_shot + self.firing_frequency;
			if (self.timgdir) then
				dir = self.timgdir;
			else
				dir = self.rot + 1;
			end

			xpos,ypos = C_obj_getPos(self.objnum);

			local offset = 30;

			new_bullet = C_addsprite(self.bullet_type,
				xpos + 32 + (Dirx[dir] * offset), ypos + 32 + (Diry[dir-1] * offset), 
				Dirx[dir-1] * 500.0/1000.0,
				Diry[dir-1] * 500.0/1000.0);
			if new_bullet then
				print(new_bullet);
				new_bullet.creator = self;
			end

		end
	else
		self.ticks_til_next_shot = nil;
	end
end
