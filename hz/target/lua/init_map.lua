-- init map!!

-- tile sprites... this is just to get things rolling


C_setpalette("nimg/tile01.bmp");

C_tile_addtype("nimg/tile03.bmp"); -- tile 0 

local tile_num = 1;
while (tile_num < 30) do
  C_tile_addtype(format("nimg/tile%02d.bmp",tile_num));
  tile_num = tile_num + 1;
end


a_map = { {  0,  0,  0,  0,  4, 24, 22, 21, 23,  5, 00, 00, 00, 00 },
          { 00, 12, 00, 00,  4, 24, 22, 27, 23,  5, 00, 00, 00, 00 },
		  { 00, 00, 00, 00,  4, 24, 27, 27, 23,  5, 00, 00, 00, 00 },
		  { 00, 00, 00, 00,  4, 24, 27, 27, 23,  5, 00, 00, 00, 00 },
		  { 00, 00, 00, 00,  4, 24, 22, 27, 23,  5, 00, 00, 00, 00 },
		  { 00, 00, 00, 00,  4, 24, 27, 27, 23,  5, 00, 00, 00, 00 },
		  { 00, 00, 00, 00,  4, 24, 22, 27, 23,  5, 00, 00, 00, 00 },
		  { 00, 00, 00, 00,  4, 24, 27, 21, 23,  5, 00, 00, 00, 00 },
		  { 00, 00, 00, 00,  4, 13, 25, 25, 17,  5, 00, 00, 00, 00 },
		  { 00, 00, 00, 00,  8,  6,  6,  6,  6, 10, 00, 00, 00, 00 },
		  { 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00 }
		};

local x = 0;
local y = 0;
while (a_map[x+1]) do
  y = 0;
  while (a_map[x+1][y+1]) do
	C_setmapsquare(y,x,a_map[x+1][y+1]);
	y = y + 1;
  end
  x = x + 1;
end
