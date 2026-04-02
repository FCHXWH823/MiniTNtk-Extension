// Path statistics: a: 4; b: 4; c: 3; 
.subckt AI21_MuSTNet GND VCC Y a b c 
.model nmos NMOS level=1 VTO=0.4 KP=120u
.model pmos PMOS level=1 VTO=-0.4 KP=40u

M0 Y c pN2 VCC PMOS W=1u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M1 pN2 b VCC VCC PMOS W=1u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M2 pN2 a VCC VCC PMOS W=1u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M3 nN1 a GND GND NMOS W=0.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M4 Y c GND GND NMOS W=0.25u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M5 Y b nN1 GND NMOS W=0.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
.end
