--
-- ****************************
--
--  Flag, obj_flg.lua
--
-- ****************************
--

hz_register_objtype("tree01", {
	flagimg = 1.0,
	nocollide = 1,
	VisualRep = VisualReps.Tree01,
	-- methods

	new = function (self,a_list) 
		if (type(a_list) ~= "table") then
			print("missile:new() called with non-table" .. tostring(a_list));
		else
			a_list._parents = {self};
			a_list.objtype = "tree01";
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
}); 

hz_register_objtype("tree02", {
	flagimg = 1.0,
	nocollide = 1,
	VisualRep = VisualReps.Tree02,
	-- methods

	new = function (self,a_list) 
		if (type(a_list) ~= "table") then
			print("missile:new() called with non-table" .. tostring(a_list));
		else
			a_list._parents = {self};
			a_list.objtype = "tree02";
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
}); 

hz_register_objtype("tree03", {
	flagimg = 1.0,
	nocollide = 1,
	VisualRep = VisualReps.Tree03,
	-- methods

	new = function (self,a_list) 
		if (type(a_list) ~= "table") then
			print("missile:new() called with non-table" .. tostring(a_list));
		else
			a_list._parents = {self};
			a_list.objtype = "tree03";
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
}); 

hz_register_objtype("bush01", {
	flagimg = 1.0,
	nocollide = 1,
	VisualRep = VisualReps.Bush01,
	-- methods

	new = function (self,a_list) 
		if (type(a_list) ~= "table") then
			print("missile:new() called with non-table" .. tostring(a_list));
		else
			a_list._parents = {self};
			a_list.objtype = "bush01";
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
}); 

hz_register_objtype("rock01", {
	flagimg = 1.0,
	nocollide = 1,
	VisualRep = VisualReps.Rock01,
	-- methods

	new = function (self,a_list) 
		if (type(a_list) ~= "table") then
			print("missile:new() called with non-table" .. tostring(a_list));
		else
			a_list._parents = {self};
			a_list.objtype = "rock01";
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
}); 

hz_register_objtype("rock02", {
	flagimg = 1.0,
	nocollide = 1,
	VisualRep = VisualReps.Rock02,
	-- methods

	new = function (self,a_list) 
		if (type(a_list) ~= "table") then
			print("missile:new() called with non-table" .. tostring(a_list));
		else
			a_list._parents = {self};
			a_list.objtype = "rock02";
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
}); 

hz_register_objtype("rock03", {
	flagimg = 1.0,
	nocollide = 1,
	VisualRep = VisualReps.Rock03,
	-- methods

	new = function (self,a_list) 
		if (type(a_list) ~= "table") then
			print("missile:new() called with non-table" .. tostring(a_list));
		else
			a_list._parents = {self};
			a_list.objtype = "rock03";
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
}); 

hz_register_objtype("rock04", {
	flagimg = 1.0,
	nocollide = 1,
	VisualRep = VisualReps.Rock04,
	-- methods

	new = function (self,a_list) 
		if (type(a_list) ~= "table") then
			print("missile:new() called with non-table" .. tostring(a_list));
		else
			a_list._parents = {self};
			a_list.objtype = "rock04";
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
}); 

