-- Base object behavior and info

-- recharge items which are on my team
recharge = {
    recharge_rate = 1,
	ge_collision = function(self,x,y,whoIhit)
		if (type(whoIhit.recharge) == "function") then
			whoIhit:recharge(self);
		end
	end
}; -- end recharge

hz_register_objtype("hdmainbase", {
	nocollide = 1,
	build_unit_timer = 0,
	build_unit_type_name = "",
	VisualRep = VisualReps.hdmainbase,
	-- methods

	new = function (self,a_list) 
		if (type(a_list) ~= "table") then
			print("missile:new() called with non-table" .. tostring(a_list));
		else
			a_list._parents = {self};
			a_list.objtype = "hdmainbase";
			C_obj_setLayer(a_list.objnum,-1);
		end
		return (a_list);
	end,

	doTick = function(self,tick_diff)
		if self.build_unit_timer > 0 then
			self.build_unit_timer = max(0,self.build_unit_timer-tick_diff);

			if self.build_unit_timer == 0 then
				-- build the unit!
                		xpos,ypos = C_obj_getPos(self.objnum);
				C_addsprite(self.build_unit_type_name,xpos+200,ypos+115);
				self.build_unit_type_name = "";
			end

		end
	end,

	buildUnit = function (self,unit_type_name)
		self.build_unit_timer = 20;
		self.build_unit_type_name = unit_type_name;
	end,

	ai_event = function(self)
	end,
}); 


hz_register_objtype("Base", {
	_parents = { recharge },
	Condition = "Healthy",
	VisualRep = VisualReps.nbase,
	layer = 0,
	State = "Closed",
	opentick = 1,
	spintick = 1,
	opening_or_closing = "auto",
	spincount = 0,
	tick_delta = 0,
	frame_time = 35,
	open_timer = 0,
	new = function(self,a_list) 
		a_list._parents = {self};
		a_list.objtype = "default"
		C_obj_setLayer(a_list.objnum,-1);
		return a_list
	end,
	ge_collision = function(self,x,y,whoIhit)
		self.open_timer = 2000;
                if whoIhit.healDamage then
                  whoIhit:healDamage(1);
                end
	end,
	doTick = function(self,tick_diff)
		local State = self.State
		self.tick_delta = self.tick_delta + tick_diff;

		if self.tick_delta > self.frame_time then
			self.tick_delta = self.tick_delta - self.frame_time;
			if self.open_timer > 0 then
				self.open_timer = self.open_timer - self.frame_time;
			end
		else
			return; -- get out of here!
		end

		if self.opening_or_closing == "opening" then
			if State == "Closed" then
				self.opentick = 1;
				self.State = "Opening";
				-- print("opening: Opening");
			elseif State == "Opening" then
				self.opentick = self.opentick + 1;

				if self.opentick > 14 then
					-- start spinning
					self.spintick = 1;
					self.State = "Open";
					-- print("opening: Open");
				end
			elseif State == "Open" then
				self.spintick = self.spintick + 1;

				if self.spintick > 6 then
					self.spintick = 1;
					self.spincount = self.spincount + 1;
					-- print("opening: spin ", self.spincount);
				end

				if self.open_timer <= 0 then
					self.opening_or_closing = "closing"
				end
			end

		elseif self.opening_or_closing == "closing" then
			if self.open_timer > 0 then
				self.opening_or_closing = "opening"
			end

			if State == "Open" then
				self.spintick = self.spintick - 1;
				
				if self.spintick < 1 then
					-- stop spinning
					self.opentick = 14;
					self.State = "Opening";
				end
			elseif State == "Opening" then
				self.opentick = self.opentick - 1;
	
				if self.opentick < 1 then
					self.spintick = 1;
					self.opentick = 1;
					self.State = "Closed"
					self.opening_or_closing = "auto";
				end
			else
				-- reset
				self.spintick = 1;
				self.opentick = 1;
				self.State = "Closed";
				self.opening_or_closing = "auto";
				self.open_timer = 0;
			end
		elseif self.opening_or_closing == "auto" then
			if self.open_timer > 0 then
				self.opening_or_closing = "opening"
			end
		else
			self.spintick = self.spintick + 1;
			self.opentick = self.opentick + 1;

			if self.spintick > 6 then
				self.spintick = 1;
			end
			if self.opentick > 14 then
				self.opentick = 1;
			end


		end
	end,
	ai_event = function(self,evt,x,y) 
		self.x = x;
		self.y = y;
	--	if (self.count == nil) then
	--		self.count = 0;
	--	else
	--		self.count = self.count + 1;
	--	end
	--
	--	if (self.count > 400) then
	--		print("Default obj at loc (".. x ..",".. y ..")");
	--		self.count = 0;
	--	end
	end
}); -- register done

-- mainbase, minibase

hz_register_objtype("mainbase",	{ VisualRep = { "new\\mainbase.bmp", 0, 0, 0, 0 }});
hz_register_objtype("minibase", { VisualRep = { "new\\minibase.bmp", 0, 0, 0, 0 }});


--hz_register_objtype("SCcontrol", { 
--	VisualRep = { "stico\\buildings\\control\\ctrl.bmp",0,0,0,0 }
--
--}); -- register done
