--
-- ****************************
--
--  Explosion 
--
-- ****************************
--



hz_register_objtype("explosion",{
	Condition = "Healthy",
	imgdir = 2.0,   -- the image index
	timgdir = 1.0,  -- the turret image index
	rimgdir = 1.0,
	exp_timer = 1.0,
	frame_time = 60,
	direction = 0.0, -- in degrees
	key_maps = a_key_map,
	nocollide = 1,

	VisualRep = VisualReps.Explosion,

	-- constructor

	new = function(self,a_list)
		if (type(a_list) ~= "table") then
			print("explosion:new() called with non-table "..tostring(a_list));
		else 
			a_list._parents = {self};
			a_list.objtype = "explosion";
			a_list.key = {}; -- make our private keydown list
			a_list.ctrl_centered = 1.0;
			a_list.dest_dir = 0.0;
		end
		return a_list
	end,


	-- animation doTick!

	doTick = function(self,tick_diff) 
		local exp_timer = self.exp_timer;
		local frame_time = self.frame_time; -- 70 seconds? frames? what is this?
		local exp_img_num = self.rimgdir;
		local EXP_IMG_COUNT = 9;
	
		exp_timer = exp_timer + tick_diff;
	
		while (exp_timer > frame_time) do
			exp_timer = exp_timer - frame_time;
			exp_img_num = exp_img_num + 1;
			if (exp_img_num > EXP_IMG_COUNT) then
				C_obj_delete(self.objnum); -- make us go away!
				collisions_active = collisions_active - 1;
				return; -- don't keep running
			end
		end
	
		self.exp_timer = exp_timer;
		self.rimgdir = floor(exp_img_num);
	end
}); -- register done

