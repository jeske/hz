-- ***********
-- game.lua
-- ***********
-- Server game definition file
-- ***************************

-- object definitions

-- default object type..

if (srvobj_types.lua == nil) then
	srvobj_types.lua = { _parents = { world_srvobj }}
else
	print("srvobj_types.lua already loaded, redefining...");
end

function srvobj_types.lua:new(a_list)
	a_list._parents = { self };
	a_list.objtype = "lua";
	return a_list;
end

if (srvobj_types.default == nil) then
	srvobj_types.default = {_parents = { world_srvobj }}
else 
	print("srvobj_types.default already loaded, redefining...");
end

function srvobj_types.default:new(a_list) 
	a_list._parents = { self };
	a_list.objtype = "default"
	return a_list
end


-- donut object type...
if (srvobj_types.donut == nil) then
	srvobj_types.donut = {parent = world_srvobj}
else
	print("object_types.donut already loaded, redefining...");
end

function srvobj_types.donut:new(a_list)
	if (type(a_list) ~= "table") then
		print("donut:new() called with non-table "..tostring(a_list));
	else 
		a_list._parents = { self };
		a_list.objtype = "donut";
		a_list.maxdamage = 20;
		a_list.curdamage = 0;
	end
	return a_list
end

function srvobj_types.donut:ge_collision(x,y,hisnumber) 

	-- self.curdamage = self.curdamage + 1;
	
	if (self.curdamage > self.maxdamage) then
		print("I've been killed!");
		self.curdamage = 0;
		self:delete();
	end	
end

-- mainship object type...
if (srvobj_types.mainship == nil) then
	srvobj_types.mainship = {_parents = { world_srvobj } }
else
	print("object_types.mainship already loaded, redefining...");
end


function srvobj_types.mainship:new(a_list)
	if (type(a_list) ~= "table") then
		print("donut:new() called with non-table "..tostring(a_list));
	else
		a_list._parents = { self };
		a_list.objtype = "mainship";
		a_list.maxdamage = 200;
		a_list.curdamage = 0;
	end
	return a_list
end

-- bullet object type...
if (srvobj_types.bullet == nil) then
	srvobj_types.bullet = {_parents = { world_srvobj}}
else
	print("object_types.bullet already loaded, redefining...");
end


function srvobj_types.bullet:new(a_list)
	if (type(a_list) ~= "table") then
		print("donut:new() called with non-table "..tostring(a_list));
	else
		a_list._parents = { self };
		a_list.objtype = "mainship";
		a_list.maxdamage = 200;
		a_list.curdamage = 0;
	end
	return a_list;
end

function srvobj_types.bullet:ge_collision(x,y,whowehit)
	-- I need to delete myself!
	if (whowehit.objtype ~= "mainship") then
		whowehit.curdamage = whowehit.curdamage + 1;
		self:delete();
	end
end

-- srvobj_types.default.ai_event = object_types.donut.ai_event;


-- base object type
if (srvobj_types.base == nil) then
	srvobj_types.base = { _parents = {world_srvobj} }
else
    print("object_types.base already loaded, redinining...");
end

function srvobj_types.base:new(a_list)
	if (type(a_list) ~= "table") then
		printf("base:new() called with non-table"..tostring(a_list));
	else
		a_list._parents = {self};
		a_list.objtype = "base";
		a_list.maxdamage = 200;
		a_list.curdamage = 0;
		printf("constructed base..");
	end;
	return a_list;
end

function srvobj_types.base:ge_collision(x,y,WhoWeHit)
	-- weird, we're a base! 
	printf("base collision...");
end;

-- end of base definition

