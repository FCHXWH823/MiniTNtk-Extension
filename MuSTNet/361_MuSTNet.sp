// Path statistics: : 0; !a: 0; !b: 0; !c: 0; a: 1; b: 1; c: 1; d: 0; 
.subckt 361_MuSTNet GND VCC Y a b c d 
.model nmos NMOS level=1 VTO=0.4 KP=120u
.model pmos PMOS level=1 VTO=-0.4 KP=40u

M0 !a a VCC VCC PMOS W=0.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M1 !b b VCC VCC PMOS W=0.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M2 !c c VCC VCC PMOS W=0.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M3 !c c GND GND NMOS W=0.25u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M4 Y a GND GND NMOS W=0.25u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M5 Y b GND GND NMOS W=0.25u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M6      W=0u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M7      W=0u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M8      W=0u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M9      W=0u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M10 !a a GND GND NMOS W=0.25u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M11 !b b GND GND NMOS W=0.25u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M12 Y c GND GND NMOS W=0.25u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
.end
