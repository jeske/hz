--
-- ********************
--
-- Visual Reps, visrep.lua
--
-- ********************
-- 


VisualReps = {

oldBase = { 	IndexedBy = "Condition",
			Healthy = { "std\\base0000.bmp", 0, 0, 0, 0 },
			Dead    = { "std\\dude5.bmp", 0, 0, 0, 0 }
},

abase = { "nbase\\base0000.bmp", 0, 0, 0, 0},

nbase = {
	IndexedBy = "State",
      Closed = { "nbase\\base0000.bmp" , 0, 0, 0, 0},
	Opening = { { "nbase\\base0001.bmp", 0, 0, 0, 0},
			{ "nbase\\base0002.bmp" , 0, 0, 0, 0},
			{ "nbase\\base0003.bmp" , 0, 0, 0, 0},
			{ "nbase\\base0004.bmp" , 0, 0, 0, 0},
			{ "nbase\\base0005.bmp" , 0, 0, 0, 0},
			{ "nbase\\base0006.bmp" , 0, 0, 0, 0},
			{ "nbase\\base0007.bmp" , 0, 0, 0, 0},
			{ "nbase\\base0008.bmp" , 0, 0, 0, 0},
			{ "nbase\\base0009.bmp" , 0, 0, 0, 0},
			{ "nbase\\base0010.bmp" , 0, 0, 0, 0},
			{ "nbase\\base0011.bmp" , 0, 0, 0, 0},
			{ "nbase\\base0012.bmp" , 0, 0, 0, 0},
			{ "nbase\\base0013.bmp" , 0, 0, 0, 0},
			{ "nbase\\base0014.bmp" , 0, 0, 0, 0};
			IndexedBy = "opentick" },
      Open   = {	{ "nbase\\base0015.bmp" , 0, 0, 0, 0},
			{ "nbase\\base0016.bmp" , 0, 0, 0, 0},
			{ "nbase\\base0017.bmp" , 0, 0, 0, 0},
			{ "nbase\\base0018.bmp" , 0, 0, 0, 0},
			{ "nbase\\base0019.bmp" , 0, 0, 0, 0},
			{ "nbase\\base0020.bmp" , 0, 0, 0, 0},
			-- { "nbase\\base0021.bmp" , 0, 0, 0, 0}
			;
			IndexedBy = "spintick"
			},

},

newDropShip = { 
					{"newdropship\\dropship0000.bmp", 0, 0, 0, 0 },
					{"newdropship\\dropship0001.bmp", 0, 0, 0, 0 },
					{"newdropship\\dropship0002.bmp", 0, 0, 0, 0 },
					{"newdropship\\dropship0003.bmp", 0, 0, 0, 0 },
					{"newdropship\\dropship0004.bmp", 0, 0, 0, 0 },
					{"newdropship\\dropship0005.bmp", 0, 0, 0, 0 },
					{"newdropship\\dropship0006.bmp", 0, 0, 0, 0 },
					{"newdropship\\dropship0007.bmp", 0, 0, 0, 0 },
					{"newdropship\\dropship0008.bmp", 0, 0, 0, 0 },
					{"newdropship\\dropship0009.bmp", 0, 0, 0, 0 },
					{"newdropship\\dropship0010.bmp", 0, 0, 0, 0 },
					{"newdropship\\dropship0011.bmp", 0, 0, 0, 0 },
					{"newdropship\\dropship0012.bmp", 0, 0, 0, 0 },
					{"newdropship\\dropship0013.bmp", 0, 0, 0, 0 },
					{"newdropship\\dropship0014.bmp", 0, 0, 0, 0 },
					{"newdropship\\dropship0015.bmp", 0, 0, 0, 0 },
					{"newdropship\\dropship0016.bmp", 0, 0, 0, 0 },
					{"newdropship\\dropship0017.bmp", 0, 0, 0, 0 },
					{"newdropship\\dropship0018.bmp", 0, 0, 0, 0 },
					{"newdropship\\dropship0019.bmp", 0, 0, 0, 0 },
					{"newdropship\\dropship0020.bmp", 0, 0, 0, 0 },
					{"newdropship\\dropship0021.bmp", 0, 0, 0, 0 },
					{"newdropship\\dropship0022.bmp", 0, 0, 0, 0 },
					{"newdropship\\dropship0023.bmp", 0, 0, 0, 0 },
					{"newdropship\\dropship0024.bmp", 0, 0, 0, 0 },
					{"newdropship\\dropship0025.bmp", 0, 0, 0, 0 },
					{"newdropship\\dropship0026.bmp", 0, 0, 0, 0 },
					{"newdropship\\dropship0027.bmp", 0, 0, 0, 0 },
					{"newdropship\\dropship0028.bmp", 0, 0, 0, 0 },
					{"newdropship\\dropship0029.bmp", 0, 0, 0, 0 },
					{"newdropship\\dropship0030.bmp", 0, 0, 0, 0 },
					{"newdropship\\dropship0031.bmp", 0, 0, 0, 0 },
					{"newdropship\\dropship0032.bmp", 0, 0, 0, 0 },
					{"newdropship\\dropship0033.bmp", 0, 0, 0, 0 },
					{"newdropship\\dropship0034.bmp", 0, 0, 0, 0 },
					{"newdropship\\dropship0035.bmp", 0, 0, 0, 0 },
					{"newdropship\\dropship0036.bmp", 0, 0, 0, 0 },
					{"newdropship\\dropship0037.bmp", 0, 0, 0, 0 },
					{"newdropship\\dropship0038.bmp", 0, 0, 0, 0 },
					{"newdropship\\dropship0039.bmp", 0, 0, 0, 0 };
					IndexedBy="imgdir"
				},




dropShip = { 
					{"dropship\\dropship0000.bmp", 0, 0, 0, 0 },
					{"dropship\\dropship0001.bmp", 0, 0, 0, 0 },
					{"dropship\\dropship0002.bmp", 0, 0, 0, 0 },
					{"dropship\\dropship0003.bmp", 0, 0, 0, 0 },
					{"dropship\\dropship0004.bmp", 0, 0, 0, 0 },
					{"dropship\\dropship0005.bmp", 0, 0, 0, 0 },
					{"dropship\\dropship0006.bmp", 0, 0, 0, 0 },
					{"dropship\\dropship0007.bmp", 0, 0, 0, 0 },
					{"dropship\\dropship0008.bmp", 0, 0, 0, 0 },
					{"dropship\\dropship0009.bmp", 0, 0, 0, 0 },
					{"dropship\\dropship0010.bmp", 0, 0, 0, 0 },
					{"dropship\\dropship0011.bmp", 0, 0, 0, 0 },
					{"dropship\\dropship0012.bmp", 0, 0, 0, 0 },
					{"dropship\\dropship0013.bmp", 0, 0, 0, 0 },
					{"dropship\\dropship0014.bmp", 0, 0, 0, 0 },
					{"dropship\\dropship0015.bmp", 0, 0, 0, 0 },
					{"dropship\\dropship0016.bmp", 0, 0, 0, 0 },
					{"dropship\\dropship0017.bmp", 0, 0, 0, 0 },
					{"dropship\\dropship0018.bmp", 0, 0, 0, 0 },
					{"dropship\\dropship0019.bmp", 0, 0, 0, 0 },
					{"dropship\\dropship0020.bmp", 0, 0, 0, 0 },
					{"dropship\\dropship0021.bmp", 0, 0, 0, 0 },
					{"dropship\\dropship0022.bmp", 0, 0, 0, 0 },
					{"dropship\\dropship0023.bmp", 0, 0, 0, 0 },
					{"dropship\\dropship0024.bmp", 0, 0, 0, 0 },
					{"dropship\\dropship0025.bmp", 0, 0, 0, 0 },
					{"dropship\\dropship0026.bmp", 0, 0, 0, 0 },
					{"dropship\\dropship0027.bmp", 0, 0, 0, 0 },
					{"dropship\\dropship0028.bmp", 0, 0, 0, 0 },
					{"dropship\\dropship0029.bmp", 0, 0, 0, 0 },
					{"dropship\\dropship0030.bmp", 0, 0, 0, 0 },
					{"dropship\\dropship0031.bmp", 0, 0, 0, 0 },
					{"dropship\\dropship0032.bmp", 0, 0, 0, 0 },
					{"dropship\\dropship0033.bmp", 0, 0, 0, 0 },
					{"dropship\\dropship0034.bmp", 0, 0, 0, 0 },
					{"dropship\\dropship0035.bmp", 0, 0, 0, 0 },
					{"dropship\\dropship0036.bmp", 0, 0, 0, 0 },
					{"dropship\\dropship0037.bmp", 0, 0, 0, 0 },
					{"dropship\\dropship0038.bmp", 0, 0, 0, 0 },
					{"dropship\\dropship0039.bmp", 0, 0, 0, 0 };
					IndexedBy="imgdir"
				},

					

Flag = {
					{ "img\\redflag0.bmp", 0, 0, 0, 0 },
					{ "img\\redflag1.bmp", 0, 0, 0, 0 },
					{ "img\\redflag2.bmp", 0, 0, 0, 0 },
					{ "img\\redflag3.bmp", 0, 0, 0, 0 };
				IndexedBy = "flagimg"
				},
Missile = {"img\\missile.bmp", 0, 0, 0, 0 },


Explosion = {
				{ "img\\bigexp1.bmp", 0, 0, 0, 0 },
				{ "img\\bigexp2.bmp", 0, 0, 0, 0 },
				{ "img\\bigexp3.bmp", 0, 0, 0, 0 },
				{ "img\\bigexp4.bmp", 0, 0, 0, 0 },
				{ "img\\bigexp5.bmp", 0, 0, 0, 0 },
				{ "img\\bigexp6.bmp", 0, 0, 0, 0 },
				{ "img\\bigexp7.bmp", 0, 0, 0, 0 },
				{ "img\\bigexp8.bmp", 0, 0, 0, 0 },
				{ "img\\bigexp9.bmp", 0, 0, 0, 0 };
				IndexedBy = "rimgdir"
				},

OTank = {
				{ "tank\\tank000.bmp", 0, 0, 0, 0 },
				{ "tank\\tank001.bmp", 0, 0, 0, 0 },
				{ "tank\\tank002.bmp", 0, 0, 0, 0 },
				{ "tank\\tank003.bmp", 0, 0, 0, 0 },
				{ "tank\\tank004.bmp", 0, 0, 0, 0 },
				{ "tank\\tank005.bmp", 0, 0, 0, 0 },
				{ "tank\\tank006.bmp", 0, 0, 0, 0 },
				{ "tank\\tank007.bmp", 0, 0, 0, 0 },
				{ "tank\\tank008.bmp", 0, 0, 0, 0 },
				{ "tank\\tank009.bmp", 0, 0, 0, 0 },
				{ "tank\\tank010.bmp", 0, 0, 0, 0 },
				{ "tank\\tank011.bmp", 0, 0, 0, 0 },
				{ "tank\\tank012.bmp", 0, 0, 0, 0 },
				{ "tank\\tank013.bmp", 0, 0, 0, 0 },
				{ "tank\\tank014.bmp", 0, 0, 0, 0 },
				{ "tank\\tank015.bmp", 0, 0, 0, 0 },
				{ "tank\\tank016.bmp", 0, 0, 0, 0 },
				{ "tank\\tank017.bmp", 0, 0, 0, 0 },
				{ "tank\\tank018.bmp", 0, 0, 0, 0 },
				{ "tank\\tank019.bmp", 0, 0, 0, 0 },
				{ "tank\\tank020.bmp", 0, 0, 0, 0 },
				{ "tank\\tank021.bmp", 0, 0, 0, 0 },
				{ "tank\\tank022.bmp", 0, 0, 0, 0 },
				{ "tank\\tank023.bmp", 0, 0, 0, 0 },
				{ "tank\\tank024.bmp", 0, 0, 0, 0 },
				{ "tank\\tank025.bmp", 0, 0, 0, 0 },
				{ "tank\\tank026.bmp", 0, 0, 0, 0 },
				{ "tank\\tank027.bmp", 0, 0, 0, 0 },
				{ "tank\\tank028.bmp", 0, 0, 0, 0 },
				{ "tank\\tank029.bmp", 0, 0, 0, 0 },
				{ "tank\\tank030.bmp", 0, 0, 0, 0 },
				{ "tank\\tank031.bmp", 0, 0, 0, 0 },
				{ "tank\\tank032.bmp", 0, 0, 0, 0 },
				{ "tank\\tank033.bmp", 0, 0, 0, 0 },
				{ "tank\\tank034.bmp", 0, 0, 0, 0 },
				{ "tank\\tank035.bmp", 0, 0, 0, 0 },
				{ "tank\\tank036.bmp", 0, 0, 0, 0 },
				{ "tank\\tank037.bmp", 0, 0, 0, 0 },
				{ "tank\\tank038.bmp", 0, 0, 0, 0 },
				{ "tank\\tank039.bmp", 0, 0, 0, 0 };
				IndexedBy = "imgdir"
				
			}, -- end VisualRep

Heli = { L1 = { -- blades
						{ "nhelis\\rotor0000.bmp", 0, 0, 0, 0 },
						{ "nhelis\\rotor0001.bmp", 0, 0, 0, 0 },
						{ "nhelis\\rotor0002.bmp", 0, 0, 0, 0 },
						{ "nhelis\\rotor0003.bmp", 0, 0, 0, 0 },
						{ "nhelis\\rotor0004.bmp", 0, 0, 0, 0 },
						{ "nhelis\\rotor0005.bmp", 0, 0, 0, 0 },
						{ "nhelis\\rotor0006.bmp", 0, 0, 0, 0 },
						{ "nhelis\\rotor0007.bmp", 0, 0, 0, 0 },
						{ "nhelis\\rotor0008.bmp", 0, 0, 0, 0 },
						{ "nhelis\\rotor0009.bmp", 0, 0, 0, 0 };
						IndexedBy = "rimgdir"
					   },
					
					L2 = { -- tank base
						{ "nhelis\\heli20000.bmp", 0, 0, 0, 0 },
						{ "nhelis\\heli20001.bmp", 0, 0, 0, 0 },
						{ "nhelis\\heli20002.bmp", 0, 0, 0, 0 },
						{ "nhelis\\heli20003.bmp", 0, 0, 0, 0 },
						{ "nhelis\\heli20004.bmp", 0, 0, 0, 0 },
						{ "nhelis\\heli20005.bmp", 0, 0, 0, 0 },
						{ "nhelis\\heli20006.bmp", 0, 0, 0, 0 },
						{ "nhelis\\heli20007.bmp", 0, 0, 0, 0 },
						{ "nhelis\\heli20008.bmp", 0, 0, 0, 0 },
						{ "nhelis\\heli20009.bmp", 0, 0, 0, 0 },
						{ "nhelis\\heli20010.bmp", 0, 0, 0, 0 },
						{ "nhelis\\heli20011.bmp", 0, 0, 0, 0 },
						{ "nhelis\\heli20012.bmp", 0, 0, 0, 0 },
						{ "nhelis\\heli20013.bmp", 0, 0, 0, 0 },
						{ "nhelis\\heli20014.bmp", 0, 0, 0, 0 },
						{ "nhelis\\heli20015.bmp", 0, 0, 0, 0 },
						{ "nhelis\\heli20016.bmp", 0, 0, 0, 0 },
						{ "nhelis\\heli20017.bmp", 0, 0, 0, 0 },
						{ "nhelis\\heli20018.bmp", 0, 0, 0, 0 },
						{ "nhelis\\heli20019.bmp", 0, 0, 0, 0 },
						{ "nhelis\\heli20020.bmp", 0, 0, 0, 0 },
						{ "nhelis\\heli20021.bmp", 0, 0, 0, 0 },
						{ "nhelis\\heli20022.bmp", 0, 0, 0, 0 },
						{ "nhelis\\heli20023.bmp", 0, 0, 0, 0 },
						{ "nhelis\\heli20024.bmp", 0, 0, 0, 0 },
						{ "nhelis\\heli20025.bmp", 0, 0, 0, 0 },
						{ "nhelis\\heli20026.bmp", 0, 0, 0, 0 },
						{ "nhelis\\heli20027.bmp", 0, 0, 0, 0 },
						{ "nhelis\\heli20028.bmp", 0, 0, 0, 0 },
						{ "nhelis\\heli20029.bmp", 0, 0, 0, 0 },
						{ "nhelis\\heli20030.bmp", 0, 0, 0, 0 },
						{ "nhelis\\heli20031.bmp", 0, 0, 0, 0 },
						{ "nhelis\\heli20032.bmp", 0, 0, 0, 0 },
						{ "nhelis\\heli20033.bmp", 0, 0, 0, 0 },
						{ "nhelis\\heli20034.bmp", 0, 0, 0, 0 },
						{ "nhelis\\heli20035.bmp", 0, 0, 0, 0 },
						{ "nhelis\\heli20036.bmp", 0, 0, 0, 0 },
						{ "nhelis\\heli20037.bmp", 0, 0, 0, 0 },
						{ "nhelis\\heli20038.bmp", 0, 0, 0, 0 },
						{ "nhelis\\heli20039.bmp", 0, 0, 0, 0 };
						IndexedBy = "imgdir"
						},
					IndexedBy = "@Layer"
				}, -- end visual rep

	

   TankLarge = {
				{ "ntankb\\ntank0000.bmp", 0, 0, 0, 0 },
				{ "ntankb\\ntank0001.bmp", 0, 0, 0, 0 },
				{ "ntankb\\ntank0002.bmp", 0, 0, 0, 0 },
				{ "ntankb\\ntank0003.bmp", 0, 0, 0, 0 },
				{ "ntankb\\ntank0004.bmp", 0, 0, 0, 0 },
				{ "ntankb\\ntank0005.bmp", 0, 0, 0, 0 },
				{ "ntankb\\ntank0006.bmp", 0, 0, 0, 0 },
				{ "ntankb\\ntank0007.bmp", 0, 0, 0, 0 },
				{ "ntankb\\ntank0008.bmp", 0, 0, 0, 0 },
				{ "ntankb\\ntank0009.bmp", 0, 0, 0, 0 },
				{ "ntankb\\ntank0010.bmp", 0, 0, 0, 0 },
				{ "ntankb\\ntank0011.bmp", 0, 0, 0, 0 },
				{ "ntankb\\ntank0012.bmp", 0, 0, 0, 0 },
				{ "ntankb\\ntank0013.bmp", 0, 0, 0, 0 },
				{ "ntankb\\ntank0014.bmp", 0, 0, 0, 0 },
				{ "ntankb\\ntank0015.bmp", 0, 0, 0, 0 },
				{ "ntankb\\ntank0016.bmp", 0, 0, 0, 0 },
				{ "ntankb\\ntank0017.bmp", 0, 0, 0, 0 },
				{ "ntankb\\ntank0018.bmp", 0, 0, 0, 0 },
				{ "ntankb\\ntank0019.bmp", 0, 0, 0, 0 },
				{ "ntankb\\ntank0020.bmp", 0, 0, 0, 0 },
				{ "ntankb\\ntank0021.bmp", 0, 0, 0, 0 },
				{ "ntankb\\ntank0022.bmp", 0, 0, 0, 0 },
				{ "ntankb\\ntank0023.bmp", 0, 0, 0, 0 },
				{ "ntankb\\ntank0024.bmp", 0, 0, 0, 0 },
				{ "ntankb\\ntank0025.bmp", 0, 0, 0, 0 },
				{ "ntankb\\ntank0026.bmp", 0, 0, 0, 0 },
				{ "ntankb\\ntank0027.bmp", 0, 0, 0, 0 },
				{ "ntankb\\ntank0028.bmp", 0, 0, 0, 0 },
				{ "ntankb\\ntank0029.bmp", 0, 0, 0, 0 },
				{ "ntankb\\ntank0030.bmp", 0, 0, 0, 0 },
				{ "ntankb\\ntank0031.bmp", 0, 0, 0, 0 },
				{ "ntankb\\ntank0032.bmp", 0, 0, 0, 0 },
				{ "ntankb\\ntank0033.bmp", 0, 0, 0, 0 },
				{ "ntankb\\ntank0034.bmp", 0, 0, 0, 0 },
				{ "ntankb\\ntank0035.bmp", 0, 0, 0, 0 },
				{ "ntankb\\ntank0036.bmp", 0, 0, 0, 0 },
				{ "ntankb\\ntank0037.bmp", 0, 0, 0, 0 },
				{ "ntankb\\ntank0038.bmp", 0, 0, 0, 0 },
				{ "ntankb\\ntank0039.bmp", 0, 0, 0, 0 };
				IndexedBy = "imgdir"
				}, -- end visualrep

Tank = { L1 = { -- tank base
						{ "ntanks\\turret0000.bmp", 0, 0, 0, 0 },
						{ "ntanks\\turret0001.bmp", 0, 0, 0, 0 },
						{ "ntanks\\turret0002.bmp", 0, 0, 0, 0 },
						{ "ntanks\\turret0003.bmp", 0, 0, 0, 0 },
						{ "ntanks\\turret0004.bmp", 0, 0, 0, 0 },
						{ "ntanks\\turret0005.bmp", 0, 0, 0, 0 },
						{ "ntanks\\turret0006.bmp", 0, 0, 0, 0 },
						{ "ntanks\\turret0007.bmp", 0, 0, 0, 0 },
						{ "ntanks\\turret0008.bmp", 0, 0, 0, 0 },
						{ "ntanks\\turret0009.bmp", 0, 0, 0, 0 },
						{ "ntanks\\turret0010.bmp", 0, 0, 0, 0 },
						{ "ntanks\\turret0011.bmp", 0, 0, 0, 0 },
						{ "ntanks\\turret0012.bmp", 0, 0, 0, 0 },
						{ "ntanks\\turret0013.bmp", 0, 0, 0, 0 },
						{ "ntanks\\turret0014.bmp", 0, 0, 0, 0 },
						{ "ntanks\\turret0015.bmp", 0, 0, 0, 0 },
						{ "ntanks\\turret0016.bmp", 0, 0, 0, 0 },
						{ "ntanks\\turret0017.bmp", 0, 0, 0, 0 },
						{ "ntanks\\turret0018.bmp", 0, 0, 0, 0 },
						{ "ntanks\\turret0019.bmp", 0, 0, 0, 0 },
						{ "ntanks\\turret0020.bmp", 0, 0, 0, 0 },
						{ "ntanks\\turret0021.bmp", 0, 0, 0, 0 },
						{ "ntanks\\turret0022.bmp", 0, 0, 0, 0 },
						{ "ntanks\\turret0023.bmp", 0, 0, 0, 0 },
						{ "ntanks\\turret0024.bmp", 0, 0, 0, 0 },
						{ "ntanks\\turret0025.bmp", 0, 0, 0, 0 },
						{ "ntanks\\turret0026.bmp", 0, 0, 0, 0 },
						{ "ntanks\\turret0027.bmp", 0, 0, 0, 0 },
						{ "ntanks\\turret0028.bmp", 0, 0, 0, 0 },
						{ "ntanks\\turret0029.bmp", 0, 0, 0, 0 },
						{ "ntanks\\turret0030.bmp", 0, 0, 0, 0 },
						{ "ntanks\\turret0031.bmp", 0, 0, 0, 0 },
						{ "ntanks\\turret0032.bmp", 0, 0, 0, 0 },
						{ "ntanks\\turret0033.bmp", 0, 0, 0, 0 },
						{ "ntanks\\turret0034.bmp", 0, 0, 0, 0 },
						{ "ntanks\\turret0035.bmp", 0, 0, 0, 0 },
						{ "ntanks\\turret0036.bmp", 0, 0, 0, 0 },
						{ "ntanks\\turret0037.bmp", 0, 0, 0, 0 },
						{ "ntanks\\turret0038.bmp", 0, 0, 0, 0 },
						{ "ntanks\\turret0039.bmp", 0, 0, 0, 0 };
						IndexedBy = "timgdir"
					   },
					
					L2 = { -- tank turret
						{ "ntanks\\ntank0000.bmp", 0, 0, 0, 0 },
						{ "ntanks\\ntank0001.bmp", 0, 0, 0, 0 },
						{ "ntanks\\ntank0002.bmp", 0, 0, 0, 0 },
						{ "ntanks\\ntank0003.bmp", 0, 0, 0, 0 },
						{ "ntanks\\ntank0004.bmp", 0, 0, 0, 0 },
						{ "ntanks\\ntank0005.bmp", 0, 0, 0, 0 },
						{ "ntanks\\ntank0006.bmp", 0, 0, 0, 0 },
						{ "ntanks\\ntank0007.bmp", 0, 0, 0, 0 },
						{ "ntanks\\ntank0008.bmp", 0, 0, 0, 0 },
						{ "ntanks\\ntank0009.bmp", 0, 0, 0, 0 },
						{ "ntanks\\ntank0010.bmp", 0, 0, 0, 0 },
						{ "ntanks\\ntank0011.bmp", 0, 0, 0, 0 },
						{ "ntanks\\ntank0012.bmp", 0, 0, 0, 0 },
						{ "ntanks\\ntank0013.bmp", 0, 0, 0, 0 },
						{ "ntanks\\ntank0014.bmp", 0, 0, 0, 0 },
						{ "ntanks\\ntank0015.bmp", 0, 0, 0, 0 },
						{ "ntanks\\ntank0016.bmp", 0, 0, 0, 0 },
						{ "ntanks\\ntank0017.bmp", 0, 0, 0, 0 },
						{ "ntanks\\ntank0018.bmp", 0, 0, 0, 0 },
						{ "ntanks\\ntank0019.bmp", 0, 0, 0, 0 },
						{ "ntanks\\ntank0020.bmp", 0, 0, 0, 0 },
						{ "ntanks\\ntank0021.bmp", 0, 0, 0, 0 },
						{ "ntanks\\ntank0022.bmp", 0, 0, 0, 0 },
						{ "ntanks\\ntank0023.bmp", 0, 0, 0, 0 },
						{ "ntanks\\ntank0024.bmp", 0, 0, 0, 0 },
						{ "ntanks\\ntank0025.bmp", 0, 0, 0, 0 },
						{ "ntanks\\ntank0026.bmp", 0, 0, 0, 0 },
						{ "ntanks\\ntank0027.bmp", 0, 0, 0, 0 },
						{ "ntanks\\ntank0028.bmp", 0, 0, 0, 0 },
						{ "ntanks\\ntank0029.bmp", 0, 0, 0, 0 },
						{ "ntanks\\ntank0030.bmp", 0, 0, 0, 0 },
						{ "ntanks\\ntank0031.bmp", 0, 0, 0, 0 },
						{ "ntanks\\ntank0032.bmp", 0, 0, 0, 0 },
						{ "ntanks\\ntank0033.bmp", 0, 0, 0, 0 },
						{ "ntanks\\ntank0034.bmp", 0, 0, 0, 0 },
						{ "ntanks\\ntank0035.bmp", 0, 0, 0, 0 },
						{ "ntanks\\ntank0036.bmp", 0, 0, 0, 0 },
						{ "ntanks\\ntank0037.bmp", 0, 0, 0, 0 },
						{ "ntanks\\ntank0038.bmp", 0, 0, 0, 0 },
						{ "ntanks\\ntank0039.bmp", 0, 0, 0, 0 };
						IndexedBy = "imgdir"
						},
					IndexedBy = "@Layer"
				}, -- end Tank

	NLiteTank = {
						{ "nlitetnk\\tank0000.bmp", 0, 0, 0, 0 },
						{ "nlitetnk\\tank0001.bmp", 0, 0, 0, 0 },
						{ "nlitetnk\\tank0002.bmp", 0, 0, 0, 0 },
						{ "nlitetnk\\tank0003.bmp", 0, 0, 0, 0 },
						{ "nlitetnk\\tank0004.bmp", 0, 0, 0, 0 },
						{ "nlitetnk\\tank0005.bmp", 0, 0, 0, 0 },
						{ "nlitetnk\\tank0006.bmp", 0, 0, 0, 0 },
						{ "nlitetnk\\tank0007.bmp", 0, 0, 0, 0 },
						{ "nlitetnk\\tank0008.bmp", 0, 0, 0, 0 },
						{ "nlitetnk\\tank0009.bmp", 0, 0, 0, 0 },
						{ "nlitetnk\\tank0010.bmp", 0, 0, 0, 0 },
						{ "nlitetnk\\tank0011.bmp", 0, 0, 0, 0 },
						{ "nlitetnk\\tank0012.bmp", 0, 0, 0, 0 },
						{ "nlitetnk\\tank0013.bmp", 0, 0, 0, 0 },
						{ "nlitetnk\\tank0014.bmp", 0, 0, 0, 0 },
						{ "nlitetnk\\tank0015.bmp", 0, 0, 0, 0 },
						{ "nlitetnk\\tank0016.bmp", 0, 0, 0, 0 },
						{ "nlitetnk\\tank0017.bmp", 0, 0, 0, 0 },
						{ "nlitetnk\\tank0018.bmp", 0, 0, 0, 0 },
						{ "nlitetnk\\tank0019.bmp", 0, 0, 0, 0 },
						{ "nlitetnk\\tank0020.bmp", 0, 0, 0, 0 },
						{ "nlitetnk\\tank0021.bmp", 0, 0, 0, 0 },
						{ "nlitetnk\\tank0022.bmp", 0, 0, 0, 0 },
						{ "nlitetnk\\tank0023.bmp", 0, 0, 0, 0 },
						{ "nlitetnk\\tank0024.bmp", 0, 0, 0, 0 },
						{ "nlitetnk\\tank0025.bmp", 0, 0, 0, 0 },
						{ "nlitetnk\\tank0026.bmp", 0, 0, 0, 0 },
						{ "nlitetnk\\tank0027.bmp", 0, 0, 0, 0 },
						{ "nlitetnk\\tank0028.bmp", 0, 0, 0, 0 },
						{ "nlitetnk\\tank0029.bmp", 0, 0, 0, 0 },
						{ "nlitetnk\\tank0030.bmp", 0, 0, 0, 0 },
						{ "nlitetnk\\tank0031.bmp", 0, 0, 0, 0 },
						{ "nlitetnk\\tank0032.bmp", 0, 0, 0, 0 },
						{ "nlitetnk\\tank0033.bmp", 0, 0, 0, 0 },
						{ "nlitetnk\\tank0034.bmp", 0, 0, 0, 0 },
						{ "nlitetnk\\tank0035.bmp", 0, 0, 0, 0 },
						{ "nlitetnk\\tank0036.bmp", 0, 0, 0, 0 },
						{ "nlitetnk\\tank0037.bmp", 0, 0, 0, 0 },
						{ "nlitetnk\\tank0038.bmp", 0, 0, 0, 0 },
						{ "nlitetnk\\tank0039.bmp", 0, 0, 0, 0 };
						IndexedBy = "imgdir"		
	},

	Hovercraft = {
						{ "nhover\\hover0000.bmp", 0, 0, 0, 0 },
						{ "nhover\\hover0001.bmp", 0, 0, 0, 0 },
						{ "nhover\\hover0002.bmp", 0, 0, 0, 0 },
						{ "nhover\\hover0003.bmp", 0, 0, 0, 0 },
						{ "nhover\\hover0004.bmp", 0, 0, 0, 0 },
						{ "nhover\\hover0005.bmp", 0, 0, 0, 0 },
						{ "nhover\\hover0006.bmp", 0, 0, 0, 0 },
						{ "nhover\\hover0007.bmp", 0, 0, 0, 0 },
						{ "nhover\\hover0008.bmp", 0, 0, 0, 0 },
						{ "nhover\\hover0009.bmp", 0, 0, 0, 0 },
						{ "nhover\\hover0010.bmp", 0, 0, 0, 0 },
						{ "nhover\\hover0011.bmp", 0, 0, 0, 0 },
						{ "nhover\\hover0012.bmp", 0, 0, 0, 0 },
						{ "nhover\\hover0013.bmp", 0, 0, 0, 0 },
						{ "nhover\\hover0014.bmp", 0, 0, 0, 0 },
						{ "nhover\\hover0015.bmp", 0, 0, 0, 0 },
						{ "nhover\\hover0016.bmp", 0, 0, 0, 0 },
						{ "nhover\\hover0017.bmp", 0, 0, 0, 0 },
						{ "nhover\\hover0018.bmp", 0, 0, 0, 0 },
						{ "nhover\\hover0019.bmp", 0, 0, 0, 0 },
						{ "nhover\\hover0020.bmp", 0, 0, 0, 0 },
						{ "nhover\\hover0021.bmp", 0, 0, 0, 0 },
						{ "nhover\\hover0022.bmp", 0, 0, 0, 0 },
						{ "nhover\\hover0023.bmp", 0, 0, 0, 0 },
						{ "nhover\\hover0024.bmp", 0, 0, 0, 0 },
						{ "nhover\\hover0025.bmp", 0, 0, 0, 0 },
						{ "nhover\\hover0026.bmp", 0, 0, 0, 0 },
						{ "nhover\\hover0027.bmp", 0, 0, 0, 0 },
						{ "nhover\\hover0028.bmp", 0, 0, 0, 0 },
						{ "nhover\\hover0029.bmp", 0, 0, 0, 0 },
						{ "nhover\\hover0030.bmp", 0, 0, 0, 0 },
						{ "nhover\\hover0031.bmp", 0, 0, 0, 0 },
						{ "nhover\\hover0032.bmp", 0, 0, 0, 0 },
						{ "nhover\\hover0033.bmp", 0, 0, 0, 0 },
						{ "nhover\\hover0034.bmp", 0, 0, 0, 0 },
						{ "nhover\\hover0035.bmp", 0, 0, 0, 0 },
						{ "nhover\\hover0036.bmp", 0, 0, 0, 0 },
						{ "nhover\\hover0037.bmp", 0, 0, 0, 0 },
						{ "nhover\\hover0038.bmp", 0, 0, 0, 0 },
						{ "nhover\\hover0039.bmp", 0, 0, 0, 0 };
						IndexedBy = "imgdir"
	}



};
