-- THIS IS AN EXAMPLE FILE
-- IT DOES NOT GET LOADED!!
-- THIS ISN'T EVEN THE RIGHT VISUAL REP FORMAT!!!

-- here is a FULLY populated sprite

addSprites{ 
	tank = { 	type = "layer",
			{ type = "direction",
			  name = "tank bottom",
				{ "tank-l0-d0.bmp" , hotspots = { {0,0,10,10} , {10,10,20,20}}  },
				{ "tank-l0-d1.bmp" , hotspots = { {1,1,11,11} , {11,11,21,21}}  }
				{ "tank-l0-d2.bmp" , hotspots = { {1,1,11,11} , {11,11,21,21}}  }
				{ "tank-l0-d3.bmp" , hotspots = { {1,1,11,11} , {11,11,21,21}}  }
			},
			{ type = "direction",
			  name = "turret",
				{ "tank-l1-d0.bmp" , hotspots = { {0,0,10,10} , {10,10,20,20}}  },
				{ "tank-l1-d1.bmp" , hotspots = { {0,0,10,10} , {10,10,20,20}}  },
				{ "tank-l1-d2.bmp" , hotspots = { {0,0,10,10} , {10,10,20,20}}  },
				{ "tank-l1-d3.bmp" , hotspots = { {0,0,10,10} , {10,10,20,20}}  },
			}
		};

addSprites{ 
	tank = { 	type = "layer",
			tank_bottom = { type = "direction",
				{ "tank-l0-d0.bmp" , hotspots = { {0,0,10,10} , {10,10,20,20}}  },
				{ "tank-l0-d1.bmp" , hotspots = { {1,1,11,11} , {11,11,21,21}}  },
				{ "tank-l0-d2.bmp" , hotspots = { {1,1,11,11} , {11,11,21,21}}  },
				{ "tank-l0-d3.bmp" , hotspots = { {1,1,11,11} , {11,11,21,21}}  }
			},
			turret = { type = "direction",
				{ "tank-l1-d0.bmp" , hotspots = { {0,0,10,10} , {10,10,20,20}}  },
				{ "tank-l1-d1.bmp" , hotspots = { {0,0,10,10} , {10,10,20,20}}  },
				{ "tank-l1-d2.bmp" , hotspots = { {0,0,10,10} , {10,10,20,20}}  },
				{ "tank-l1-d3.bmp" , hotspots = { {0,0,10,10} , {10,10,20,20}}  }
			},
	helicopter = { type = "layer",
				heli_main = { type = "direction",
					{ "heli-l0-d0.bmp" , hotspots = { {0,0,10,10} , {10,10,20,20}} },
					{ "heli-l0-d1.bmp" , hotspots = { {0,0,10,10} , {10,10,20,20}} },
					{ "heli-l0-d2.bmp" , hotspots = { {0,0,10,10} , {10,10,20,20}} },
					{ "heli-l0-d3.bmp" , hotspots = { {0,0,10,10} , {10,10,20,20}} }
				},
				heli_rotor = { type = "animation",
					{ "heli-rotor-0.bmp" , hotspots = { {0,0,10,10} , {0,0,30,30}} },
					{ "heli-rotor-1.bmp" , hotspots = { {0,0,10,10} , {0,0,30,30}} },
					{ "heli-rotor-2.bmp" , hotspots = { {0,0,10,10} , {0,0,30,30}} },
					{ "heli-rotor-3.bmp" , hotspots = { {0,0,10,10} , {0,0,30,30}} }
				}
			}
	
		};

			
			


				
		

addSprites{	name = "tank",
		layers = {	
		

addSprite{
	layers = { 	luavarname = "damage_state";
			{ <layer 0> },
			{ <layer 1> }
	         }
	}
	
{ type = "layers",
  luavarname = "damage_state",
  {  },
  {  }
}


}; -- end sprite
			