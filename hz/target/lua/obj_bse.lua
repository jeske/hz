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


hz_register_objtype("Base", {
	_parents = { recharge },
	Condition = "Healthy",
	VisualRep = { 	IndexedBy = "Condition",
					Healthy = { "std\\base0000.bmp", 0, 0, 0, 0 },
					Dead    = { "std\\dude5.bmp", 0, 0, 0, 0 }
				} ,
	layer = 0,
	new = function(self,a_list) 
		a_list._parents = {self};
		a_list.objtype = "default"
		return a_list
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
