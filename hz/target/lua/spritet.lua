$debug


print("std\\dude array...");

Dude = {
  Condition="Healthy",
  Direction="North",
  Frame=0,
  VisualRep = { IndexedBy="Condition",
                Healthy  = { IndexedBy="@Direction",
                            	North    = { IndexedBy="@Layer",
                            			L1 = { 
		                                         {"std\\dude0.ppm",  0,0, 63,63},
		                                         {"std\\dude1.ppm", 64,0,127,63},
		                                         {"std\\dude2.ppm",128,0,191,63},
		                                         {"std\\dude3.ppm",192,0,254,63},
		                                         {"std\\dude4.ppm",256,0,319,63};
												 IndexedBy = "@Frame"
		                                       },
	  	                              L2        = { 
		                                         {"std\\dude5.bmp",100,0,163,63},
		                                         {"std\\dude6.ppm",164,0,227,63},
		                                         {"std\\dude7.ppm",228,0,291,63},
		                                         {"std\\dude8.ppm",292,0,354,63},
		                                         {"std\\dude9.ppm",356,0,419,63};
												 IndexedBy="@Frame"
		                                       },
		                         },
		               South    = { IndexedBy="@Layer",
		                            L1        = { 
		                                         {"std\\dude20.ppm",  0,0, 63,63},
		                                         {"std\\dude21.ppm", 64,0,127,63},
		                                         {"std\\dude22.ppm",128,0,191,63},
		                                         {"std\\dude23.ppm",192,0,254,63},
		                                         {"std\\dude24.ppm",256,0,319,63};
												 IndexedBy="@Frame"
		                                       },
		                            L2        = { 
		                                         {"std\\dude25.ppm",100,0,163,63},
		                                         {"std\\dude26.ppm",164,0,227,63},
		                                         {"std\\dude27.ppm",228,0,291,63},
		                                         {"std\\dude28.ppm",292,0,354,63},
		                                         {"std\\dude29.ppm",356,0,419,63};
												 IndexedBy="@Frame"
		                                       },
		                         }
		             },

		 Dead     = { 
            		   {"std\\dude30.ppm",  0,0, 63,63},
		               {"std\\dude31.ppm", 64,0,127,63},
		               {"std\\dude32.ppm",128,0,191,63},
		               {"std\\dude33.ppm",192,0,254,63},
		               {"std\\dude34.ppm",256,0,319,63};
					   IndexedBy="@Frame"
		             }
   
		} -- end VisualRep
	}


print("loading dude...");

C_sprite_addtype("std\\dude", Dude);

print("Done loading dude");

print("Base array...");



