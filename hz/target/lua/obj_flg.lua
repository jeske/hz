--
-- ****************************
--
--  Flag, obj_flg.lua
--
-- ****************************
--

hz_register_objtype("flag", {
	flagimg = 1.0,
	nocollide = 1,
	VisualRep = VisualReps.Flag,
	-- methods

	new = function (self,a_list) 
		if (type(a_list) ~= "table") then
			print("missile:new() called with non-table" .. tostring(a_list));
		else
			a_list._parents = {self};
			a_list.objtype = "flag";
			a_list.counter = 0.0;
			a_list.frame_time = 80.0;
			a_list.flagimg = 1.0;
			C_obj_setLayer(a_list.objnum,-1);
		end
		return (a_list);
	end,

	-- this is a dummy ai_event to prevent slowdown!
	
	ai_event = function(self)
	end,

	-- to do the animation

	doTick = function (self,tick_diff)
		local counter = self.counter;
		local flagimg = self.flagimg;
		local FLAG_IMG_MAX = 4;

		counter = counter + tick_diff;

		if (counter > self.frame_time) then
			counter = 0;
			flagimg = flagimg + 1;
			if (flagimg > FLAG_IMG_MAX) then
				flagimg = 1;
			end
		
		end

		self.flagimg = flagimg;
		self.counter = counter;
	end
}); 
