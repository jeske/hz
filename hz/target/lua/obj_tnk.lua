$debug

-- mainship object type...

hz_register_objtype("mainship", {
	_parents = { damageable, air_physics, controllable, collidable },

	Condition = "Healthy",
	imgdir = 2.0,   -- the image index

	rimgdir = 1.0,
	direction = 0.0, -- in degrees
	bullet_type = "bullet",
	objtype = "mainship",
	exp_timer = 0.0,
	frame_time = 70,
	layer = 1,
        show_my_damage = 1,

	damage_max = 100,
	recharge_rate = 0.1,
	
	VisualRep = VisualReps.newDropShip,

	-- called to navigate...
	ai_event = function(self)
          if not self.signaled_ai_event then
            self.signaled_ai_event = 1;
            print("******** AI EVENT".. tostring(self));
          end
	end,

        ai_moveToXY = function(self,target_x, target_y)
          self.ai_target_x = target_x;
          self.ai_target_y = target_y;
        end,

	-- constructor
	new = function (self,a_list) -- constructor
			if (type(a_list) ~= "table") then
			print("mainship:new() called with non-table "..tostring(a_list));
		else 
			a_list._parents = { self };
			a_list.key = {}; -- make our private keydown list
			a_list.ctrl_centered = 1.0;
			a_list.dest_dir = 0.0;
		end
		return a_list
	end,

	recharge = function (self,byWhom) -- recharge method
		local damage = self.damage;
		if (damage > 0) then
			damage = max(0,damage - recharge_rate);
			self.damage = damage;
		end
	end


}); -- register done

hz_register_objtype("hd_mainship", {
	_parents = { mainship_physics, controllable, collidable },

	Condition = "Healthy",
	imgdir_max = 24,
	imgdir = 2.0,   -- the image index

	rimgdir = 1.0,
	direction = 0.0, -- in degrees
	bullet_type = "bullet",
	objtype = "hd_mainship",
	exp_timer = 0.0,
	frame_time = 70,
	layer = 1,
	Mode = "Flying", -- Flying, Standing, Transforming, Walking 

	damage = 0,
	damage_max = 10,
	recharge_rate = 0.1,
	
	VisualRep = VisualReps.hdFighter,

	-- dummy ai_event
	ai_event = function(self)
	end,

	-- constructor
	new = function (self,a_list) -- constructor
			if (type(a_list) ~= "table") then
			print("mainship:new() called with non-table "..tostring(a_list));
		else 
			a_list._parents = { self };
			a_list.key = {}; -- make our private keydown list
			a_list.ctrl_centered = 1.0;
			a_list.dest_dir = 0.0;
		end
		return a_list
	end,

	recharge = function (self,byWhom) -- recharge method
		local damage = self.damage;
		if (damage > 0) then
			damage = max(0,damage - recharge_rate);
			self.damage = damage;
		end
	end


}); -- register done

hz_register_objtype("hd_mainship_c", {
	_parents = { air_physics, controllable, collidable },

	Condition = "Healthy",
	imgdir_max = 24,
	imgdir = 2.0,   -- the image index

	rimgdir = 1.0,
	direction = 0.0, -- in degrees
	bullet_type = "bullet",
	objtype = "hd_mainship",
	exp_timer = 0.0,
	frame_time = 70,
	layer = 1,
	Mode = "Flying", -- Flying, Standing, Transforming, Walking 

	damage = 0,
	damage_max = 10,
	recharge_rate = 0.1,
	
	VisualRep = VisualReps.hdFighter,

	-- dummy ai_event
	ai_event = function(self)
	end,

	-- constructor
	new = function (self,a_list) -- constructor
			if (type(a_list) ~= "table") then
			print("mainship:new() called with non-table "..tostring(a_list));
		else 
			a_list._parents = { self };
			a_list.key = {}; -- make our private keydown list
			a_list.ctrl_centered = 1.0;
			a_list.dest_dir = 0.0;
		end
		return a_list
	end,

	recharge = function (self,byWhom) -- recharge method
		local damage = self.damage;
		if (damage > 0) then
			damage = max(0,damage - recharge_rate);
			self.damage = damage;
		end
	end


}); -- register done



hz_register_objtype("heli", {
	_parents = { air_physics, controllable, collidable },
	imgdir = 2.0, -- image index
	rimgdir = 1.0, -- rotor image index
	direction = 0.0, 
	bullet_type = "bullet",
	objtype = "heli",
	exp_timer = 0.0,
	frame_time = 30,
	layer = 1,
	VisualRep = VisualReps.Heli,

	-- dummy ai_event
	ai_event = function(self)
	end,

	new = function (self,a_list) -- constructor
		if (type(a_list) ~= 'table') then
			print("heli:new() called with non-table "..tostring(a_list));
		else
			a_list._parents = { self };
			a_list.key = {}; -- make our private keydown list
			a_list.ctrl_centered = 1.0;
			a_list.dest_dir = 0.0;
		end
		return (a_list);
	end
}); -- register done

hz_register_objtype("hovercraft", {
	_parents = { air_physics, controllable, collidable },
	imgdir = 2.0, -- image index
	rimgdir = 1.0, -- rotor image index
	direction = 0.0, 
	bullet_type = "bullet",
	objtype = "hovercraft",
	exp_timer = 0.0,
	frame_time = 70,
	layer = 1,
	VisualRep = VisualReps.Hovercraft,

	-- dummy ai_event
	ai_event = function(self)
	end,

	new = function (self,a_list) -- constructor
		if (type(a_list) ~= 'table') then
			print("heli:new() called with non-table "..tostring(a_list));
		else
			a_list._parents = { self };
			a_list.key = {}; -- make our private keydown list
			a_list.ctrl_centered = 1.0;
			a_list.dest_dir = 0.0;
		end
		return (a_list);
	end
}); -- register done

hz_register_objtype("litetank", {
	_parents = { air_physics, controllable, collidable },
	imgdir = 2.0, -- image index
	rimgdir = 1.0, -- rotor image index
	direction = 0.0, 
	bullet_type = "bullet",
	objtype = "litetank",
	exp_timer = 0.0,
	frame_time = 70,
	layer = 1,
	VisualRep = VisualReps.NLiteTank,

	-- dummy ai_event
	ai_event = function(self)
	end,

	new = function (self,a_list) -- constructor
		if (type(a_list) ~= 'table') then
			print("heli:new() called with non-table "..tostring(a_list));
		else
			a_list._parents = { self };
			a_list.key = {}; -- make our private keydown list
			a_list.ctrl_centered = 1.0;
			a_list.dest_dir = 0.0;
		end
		return (a_list);
	end
}); -- register done


--
--
--
--  Setup New Tank!
--
--


hz_register_objtype("tank",{
	_parents = { ground_physics, controllable, collidable },
	timgdir = 1.0, -- turret image index
	VisualRep = VisualReps.Tank,
	objtype = "tank",
	bullet_type = "bullet",
	layer = 0,
	
	new = function (self,a_list) -- constructor
		if (type(a_list) ~= 'table') then
			print("tank:new() called with non-table "..tostring(a_list));
		else
			a_list._parents = { self };
			a_list.key = {}; -- make our private keydown list
			a_list.ctrl_centered = 1.0;
			a_list.dest_dir = 0.0;
		end
		return (a_list);
	end

}); -- register done


--
-- FOLLOWER
--  

follower = {
	-- state
	follow_count = 0,
	follow = 0,
	-- methods
	
	ai_event = function(self,evt,x,y)
		self.x = x;
		self.y = y;
	
		if (self.follow) then
			if (self.follow_count > 2000) then
				-- follow someone else 
				self.follow = 0;
				local new_follow = random() * 10;
				if ((objects[new_follow]) ~= nil) then
					objects[new_follow]:viewFollow();
				end
			else
				self.follow_count = self.follow_count + 1;
			end
		end
	
		if (self.count == nil) then
			self.count = 0;
		else
			self.count = self.count + 1;
		end
		
		if (self.gotox == nil) then
			-- choose a random destination
			-- print("Donut choosing random destination");
			if (numdecisions == nil) then
				numdecisions = 1;
			else 
				numdecisions = numdecisions + 1;
			end
	 
	
			self.gotox = (random() * 2000);
			self.gotoy = (random() * 2000);
			
			self:goTo(self.gotox, self.gotoy);
	
		elseif ((self.gotox - self.x) < 10 and (self.gotoy - self.y) < 10) then
			-- we reached our destination
			-- print("Donut destination reached!");
			self.gotox = nil;
			self.gotoy = nil;
	
	
		-- hand off the view follow to someone else...
			
		
		elseif (self.count > 100) then
			-- we need to "Revector!"
			-- print("Donut revectoring from (".. x ..",".. y ..") to (".. self.gotox ..",".. self.gotoy ..")");
			--		self:goTo(self.gotox, self.gotoy);
			self.count = 0;
		end
	
	end -- end ai_event
	
}; -- end follower
	
--
-- add an ai_event and make an automated tank!!!
--
hz_register_objtype("atank",{
	_parents = { controllable, collidable, ground_physics, follower },
	VisualRep = VisualReps.Tank,
	objtype = "atank",
	bullet_type = "bullet",
	layer = 0,

	new = function (self,a_list) -- constructor
		if (type(a_list) ~= 'table') then
			print("atank:new() called with non-table "..tostring(a_list));
		else
			a_list._parents = { self };
			a_list.key = {}; -- make our private keydown list
			a_list.ctrl_centered = 1.0;
			a_list.dest_dir = 0.0;
		end
		return (a_list);
	end

}); -- register done

