$debug
-- init.lua
-- 
-- game initialization code...
--

collectgarbage(100);

-- first comes preloaded functions

 function printGlobalVariables ()
 local i, v = nextvar(nil)
  while i do
    print("["..i..", "..type(v).."]")
    i, v = nextvar(i)
  end
end

_old_dofile = dofile;

function dofile(filename)
    local newstring = "lua/".. filename;
	print("dofile("..newstring..")");

	if (_old_dofile(newstring) == nil) then
		print("error in _old_dofile()!");
	end
end


dofile("util.lua");




dofile("game.lua");


-- ****************
-- CLIENT SIDE
-- ****************

-- object_types registry
-- just register your object with this if you want it to be
-- used...

object_types = {}

-- objects list
-- this will hold the actual objects being
-- animated in the game...

objects = {} 

-- game startup!!

dofile("init_map.lua");
dofile("objects.lua");

print("[init.lua]: loading complete");
