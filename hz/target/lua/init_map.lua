-- init map!!
-- tile sprites... this is just to get things rolling

if not MAP_TILES_LOADED then
  C_setpalette("nimg/tile01.bmp");
  C_tile_addtype("nimg/tile27.bmp"); -- tile 0 

  local tile_num = 1;
  while (tile_num < 30) do
    C_tile_addtype(format("nimg/tile%02d.bmp",tile_num));
    tile_num = tile_num + 1;
  end

  -- add 2000 random land variations
  local n = 0;
  while n < 2000 do
     local x = random() * 200;
     local y = random() * 200;

     if random() > 0.5 then
       C_setmapsquare(y,x,21);	
     else
       C_setmapsquare(y,x,22);	
     end

     n = n + 1;
  end

  MAP_TILES_LOADED = 1;
end

map_templates = {};

map_templates.island = { 
  {  0,  0,  0,  0,  4, 24, 22, 21, 23,  5, 00, 00, 00, 00 },
  { 00, 00, 00, 00,  4, 24, 22, 27, 23,  5, 00, 00, 00, 00 },
  { 00, 00, 00, 00,  4, 24, 27, 27, 23,  5, 00, 00, 00, 00 },
  { 00, 00, 00, 00,  4, 24, 27, 27, 23,  5, 00, 00, 00, 00 },
  { 00, 00, 00, 00,  4, 24, 22, 27, 23,  5, 00, 00, 00, 00 },
  { 00, 00, 00, 00,  4, 24, 27, 27, 23,  5, 00, 00, 00, 00 },
  { 00, 00, 00, 00,  4, 24, 22, 27, 23,  5, 00, 00, 00, 00 },
  { 00, 00, 00, 00,  4, 24, 27, 21, 23,  5, 00, 00, 00, 00 },
  { 00, 00, 00, 00,  4, 13, 25, 25, 17,  5, 00, 00, 00, 00 },
  { 00, 00, 00, 00,  8,  6,  6,  6,  6, 10, 00, 00, 00, 00 },
  { 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00 },
};

-- 01 shallow water 1
-- 02 shallow water 2
-- 03 deep water 1
-- 04 deep/shallow H-border
-- 05 shallow/deep H-border
-- 06 shallow/deep V-border
-- 07 deep/shallow V-border
-- 08 D/s corner UR
-- 09 D/s corner LR
-- 10 s/D corner UL
-- 11 s/D corner LL
-- 12 water rocks
-- 13 S/L corner UR
-- 14 


map_templates.lake = {
  { 18, 25, 25, 25, 25, 25, 25, 25, 14 },
  { 23,  2,  1,  5,  3,  3,  4,  2, 24 },
  { 23,  2, 29,  5,  3,  3,  4, 12, 24 },
  { 19, 26, 26, 26, 26, 26, 26, 26, 16 },
};

map_templates.hz_logo = { 
  {  21,  0,  0,  0, 21,  0, 21, 21, 21, 21, 21 }, 
  {  21,  0,  0,  0, 21,  0,  0,  0,  0,  0, 21 },
  {  21,  0,  0,  0, 21,  0,  0,  0,  0, 21,  0 },
  {  21, 21, 21, 21, 21,  0,  0,  0, 21,  0,  0 },
  {  21,  0,  0,  0, 21,  0,  0, 21,  0,  0,  0 },
  {  21,  0,  0,  0, 21,  0, 21,  0,  0,  0,  0 },
  {  21,  0,  0,  0, 21,  0, 21, 21, 21, 21, 21 },
};

 
function place_item(a_map, at_x, at_y)
  local x = 1;
  local y = 1;

  while (a_map[y]) do
    x = 1;
    while (a_map[y][x]) do
	local tile = a_map[y][x];
        if tile ~= -1 then
	  	C_setmapsquare(at_x + x,at_y + y,a_map[y][x]);
	end
  	x = x + 1;
    end
    y = y + 1;
  end
end

place_item(map_templates.lake,10,15);
place_item(map_templates.hz_logo,1,1);


