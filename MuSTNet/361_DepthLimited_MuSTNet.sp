// Path statistics: !a: 17; !b: 15; !c: 10; a: 14; b: 16; c: 21; d: 9; 
.subckt 361_DepthLimited_MuSTNet GND VCC Y a b c d 
.model nmos NMOS level=1 VTO=0.4 KP=120u
.model pmos PMOS level=1 VTO=-0.4 KP=40u

M0 Y c pN4 VCC PMOS W=3u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M1 pN6 b pN4 VCC PMOS W=3u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M2 pN5 c VCC VCC PMOS W=2.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M3 pN6 a VCC VCC PMOS W=2u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M4 pN9 !a VCC VCC PMOS W=3u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M5 pN6 !b pN5 VCC PMOS W=2.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M6 pN5 !c pN2 VCC PMOS W=3u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M7 pN9 b pN5 VCC PMOS W=3u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M8 pN6 !a pN2 VCC PMOS W=3u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M9 Y d pN2 VCC PMOS W=2.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M10 !a a VCC VCC PMOS W=0.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M11 !b b VCC VCC PMOS W=0.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M12 !c c VCC VCC PMOS W=0.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M13 nN3 a GND GND NMOS W=1.25u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M14 nN5 b GND GND NMOS W=1u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M15 nN3 c GND GND NMOS W=1.25u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M16 nN7 d nN2 GND NMOS W=1u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M17 nN5 !a nN2 GND NMOS W=1.25u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M18 nN7 !b nN5 GND NMOS W=1.25u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M19 !c c GND GND NMOS W=0.25u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M20 Y !c nN2 GND NMOS W=1u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M21 nN3 !b nN2 GND NMOS W=1.25u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M22 nN7 a nN5 GND NMOS W=1.25u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M23 !a a GND GND NMOS W=0.25u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M24 !b b GND GND NMOS W=0.25u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M25 Y c nN7 GND NMOS W=1.25u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
.end
