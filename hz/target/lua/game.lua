-- ***********
-- game.lua
-- ***********



-- declare the base object...

world_object = {
	action = { 
		SHOOT = 0, 
		SHIELD = 1
	},

	new = function(self,alist)
		return alist;
	end,

	go = function(self,direction, velocity)
	end,

	goTo = function(self,xloc, yloc)
		local objnum = self.objnum;

		if (type(objnum) == "userdata") then
			-- good, it's a number, so ask us to 
			-- move
			C_obj_goTo(objnum,xloc,yloc);
		else
			print("Object without number asked to move");
		end
	end,

	setLayer = function(self,layer)
		C_obj_setLayer(self.objnum,layer);
	end, 

	viewFollow = function(self)
		local objnum = self.objnum;
	
		C_obj_viewFollow(objnum);
	end,


	doTick = function(self,tickDiff)
		self.tickDiff = tickDiff;
	end,

	goToTile = function(self,xloc, yloc)
	end,

	doAction = function(self,action_type)
	end,

};


-- world_map

world_map = {
	tileTypeAt = function(self,x,y)
	end,

	tileTypeAtPoint = function(self,x,y)
	end
};

-- server base object

world_srvobj = {
	delete = function(self)
		local objnum = self.objnum;
	
		if (type(objnum) == "userdata") then
			-- good, it's a number, so delete us...
			C_obj_delete(objnum);
		else
			print("SrvObj without number asked to delete");
		end
	end

};


-- ****************
-- SERVER SIDE
-- ****************

srvobj_types = {}
srvobjs = {}

-- ****************
-- should probably create game controller here!
-- ****************


