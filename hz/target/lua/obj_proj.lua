-- obj_proj.lua
--
-- Projectiles!
--

-- bullet object type...

hz_register_objtype("bullet",{
	VisualRep = { "std\\bullet.bmp" },
	countdown = 550,
	layer = 1,

	new = function(self,a_list)
		if (type(a_list) ~= "table") then
			print("donut:new() called with non-table "..tostring(a_list));
		else 
			a_list._parents = {self};
			a_list.objtype = "bullet";
		end
		return a_list
	end,

	ai_event = function()
	end,
	
	-- apply damage!
	ge_collision = function(self,x,y,whoIhit)
		if (whoIhit.applyDamage and (self.creator ~= whoIhit) and (self.layer == whoIhit.layer)) then
			if (collisions_active < MAX_COLLISIONS) then
				C_addsprite("explosion",x,y);
				collisions_active = collisions_active + 1;
			end
			whoIhit:applyDamage(1);
			C_obj_delete(self.objnum);
		end
	end,

	doTick = function(self,tick_diff)
		local countdown = self.countdown;

		if (countdown > 0) then
			countdown = countdown - tick_diff;
			self.countdown = countdown;
		else 
			C_obj_delete(self.objnum);
		end
	end
}); -- register done

--
-- ****************************
--
--  Missile!
--
-- ****************************
--

hz_register_objtype("missile",{
	flight_time = 600, -- number of ticks to live
	VisualRep = VisualReps.Missile,


	new = function(self,a_list)
		if (type(a_list) ~= "table") then
			print("missile:new() called with non-table" .. tostring(a_list));
		else
			a_list._parents = {self};
			a_list.objtype = "missile";
			a_list.flight_time = 600;
		end
		return (a_list);
	end,

	doTick = function(self,tick_diff)
		self.flight_time = self.flight_time - tick_diff;
	
		if (self.flight_time < 0) then
			C_obj_delete(self.objnum);
		end
	end
}); -- register done
