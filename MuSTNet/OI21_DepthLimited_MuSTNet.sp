// Path statistics: a: 4; b: 4; c: 3; 
.subckt OI21_DepthLimited_MuSTNet GND VCC Y a b c 
.model nmos NMOS level=1 VTO=0.4 KP=120u
.model pmos PMOS level=1 VTO=-0.4 KP=40u

M0 Y b pN1 VCC PMOS W=1u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M1 Y a pN1 VCC PMOS W=1u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M2 pN1 c VCC VCC PMOS W=1u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M3 Y c GND GND NMOS W=0.25u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M4 nN2 b GND GND NMOS W=0.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M5 Y a nN2 GND NMOS W=0.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
.end
