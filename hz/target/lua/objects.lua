-- objects.lua
-- object definitions


-- default object type..
function hz_register_objtype(name, obj) 
	if (obj ~= nil) then
		add_parent(obj,world_object);
		obj.obj_type_name = name;
		
		if (object_types[name] ~= nil) then
			print("Object type [".. name .."] exists, redifining.");
		else
			print("Object type [".. name .."] defined.");
		end;

		object_types[name] = obj;
		srvobj_types[name] = obj;
		C_sprite_addtype(name,obj);
	end;
end


-- keyboard handling stuff

a_key_map = {
-- Windows key codes
	[32] = "space",
	[37] = "left",
	[38] = "up",
	[39] = "right",
	[40] = "down",
	[79] = "o",
	[80] = "p",
-- X11 key codes
	[65361] = "left",
	[65362] = "up",
	[65363] = "right",
	[65364] = "down",
	[111] = "o",
	[112] = "p",
-- SDL key codes
        [273] = "up",
	[274] = "down",
	[275] = "right",
	[276] = "left"
};

-- cos/sin tables
Dirx = {
	[0] =	  0.000000,[1] =	 0.156434,[2] =   0.309017,[3] =	  0.453991,
	[4] =     0.587785,[5] =     0.707107,[6] =   0.809017,[7] =      0.891007,
	[8] =     0.951057,[9] =     0.987688,[10] =  1.000000,[11] =     0.987688,
	[12] =     0.951057,[13] =   0.891007,[14] =  0.809017,[15] =     0.707107,
	[16] =     0.587785,[17] =   0.453990,[18] =  0.309017,[19] =     0.156434,
	[20] =     0.000000,[21] =   -0.156435,[22] = -0.309017,[23] =    -0.453991,
	[24] =     -0.587785,[25] =  -0.707107,[26] = -0.809017,[27] =    -0.891007,
	[28] =     -0.951057,[29] =  -0.987688,[30] = -1.000000,[31] =    -0.987688,
	[32] =     -0.951056,[33] =  -0.891006,[34] = -0.809017,[35] =    -0.707107,
	[36] =     -0.587785,[37] =  -0.453990,[38] = -0.309017,[39] =    -0.156434
};


Diry = {
	[0] =     -1.000000,[1] =     -0.987688,[2] =     -0.951057,[3] =     -0.891007,
	[4] =     -0.809017,[5] =     -0.707107,[6] =     -0.587785,[7] =     -0.453990,
	[8] =     -0.309017,[9] =     -0.156434,[10] =     0.000000,[11] =     0.156434,
	[12] =     0.309017,[13] =     0.453991,[14] =     0.587785,[15] =     0.707107,
	[16] =     0.809017,[17] =     0.891007,[18] =     0.951057,[19] =     0.987688,
	[20] =     1.000000,[21] =     0.987688,[22] =     0.951057,[23] =     0.891006,
	[24] =     0.809017,[25] =     0.707107,[26] =     0.587785,[27] =     0.453990,
	[28] =     0.309017,[29] =     0.156434,[30] =     0.000000,[31] =     -0.156435,
	[32] =     -0.309017,[33] =     -0.453991,[34] =     -0.587785,[35] =     -0.707107,
	[36] =     -0.809017,[37] =     -0.891007,[38] =     -0.951057,[39] =     -0.987688
};



dofile("visrep.lua"); -- load visual rep definitions
dofile("traits.lua"); -- load traits!

dofile("obj_tnk.lua");		-- this really has the tank, dropship, and heli
dofile("obj_bse.lua");		-- mainbase and minibase defined

dofile("obj_flg.lua");		-- flag
dofile("obj_expl.lua");		-- explosions
dofile("obj_proj.lua");		-- projectiles

dofile("initobj.lua");

function makeRandomBases()
	if 1 then
		local x = 0
		while (x < 10) do
			local y = 0
			while y < 10 do
				C_addsprite("Base",250 + (x * 100),500 + (y * 100));
				y = y + 1;
			end
			x = x + 1;
		end
	end
end

function setupGameSprites()
        print("setup UI elements");
        mainUnitDamageBar = C_newHorizBarView(25,10,150,12,100);
        mainUnitFuelBar   = C_newHorizBarView(_SCREEN_X - (150 + 25),10,150,12,100);
        
	print("setup game sprites");
	printTable(objects);
        -- this is our second unit...
	C_addsprite("heli",200,30);

        -- give me one base
        C_addsprite("Base",100,100);

        -- make one enemy
	a_tnk = C_addsprite("tank",500,200);
        a_tnk:ai_moveToXY(100,100);

	-- C_addsprite("hovercraft", 50,150);
	-- C_addsprite("litetank",100,100);

	-- the test objects for Daniel's fighter images
	-- C_addsprite("hd_mainship",250,180); -- can't be controlled
	-- C_addsprite("hd_mainship_c",250,250); -- CAN be controlled

        -- place a bunch of random flags on the map..
	local i = 0;
	while (i < 30) do
		C_addsprite("flag",random() * 1500, random() * 1500);
		i = i + 1;
	end
	-- printTable(objects);
end
