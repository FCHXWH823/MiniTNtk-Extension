// Path statistics: !a: 16; !b: 12; !c: 8; !d: 16; a: 24; b: 12; c: 8; d: 16; 
.subckt P27031_DepthLimited GND VCC Y a b c d 
.model nmos NMOS level=1 VTO=0.4 KP=120u
.model pmos PMOS level=1 VTO=-0.4 KP=40u

M0 Y d pN6 VCC PMOS W=2u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M1 pN4 b pN3 VCC PMOS W=2u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M2 pN5 c VCC VCC PMOS W=2u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M3 pN2 a pN1 VCC PMOS W=2u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M4 pN3 !a pN1 VCC PMOS W=2u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M5 pN7 !b pN2 VCC PMOS W=2u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M6 pN1 !c VCC VCC PMOS W=2u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M7 Y d pN6 VCC PMOS W=2u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M8 pN6 !b pN3 VCC PMOS W=2u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M9 pN2 !a pN5 VCC PMOS W=2u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M10 Y !d pN4 VCC PMOS W=2u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M11 Y !d pN7 VCC PMOS W=2u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M12 pN6 b pN2 VCC PMOS W=2u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M13 Y a pN4 VCC PMOS W=2u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M14 pN3 a pN5 VCC PMOS W=2u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M15 !a a VCC VCC PMOS W=0.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M16 !b b VCC VCC PMOS W=0.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M17 !c c VCC VCC PMOS W=0.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M18 !d d VCC VCC PMOS W=0.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M19 nN1 a GND GND NMOS W=1u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M20 nN3 b nN2 GND NMOS W=1u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M21 !d d GND GND NMOS W=0.25u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M22 nN6 d nN5 GND NMOS W=1u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M23 nN5 !a GND GND NMOS W=1u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M24 nN3 !b nN6 GND NMOS W=1u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M25 nN3 !c GND GND NMOS W=1u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M26 nN6 !d nN1 GND NMOS W=1u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M27 nN2 d nN4 GND NMOS W=1u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M28 nN5 !d nN2 GND NMOS W=1u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M29 Y c nN3 GND NMOS W=1u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M30 nN4 a GND GND NMOS W=1u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M31 Y a nN5 GND NMOS W=1u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M32 !a a GND GND NMOS W=0.25u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M33 !b b GND GND NMOS W=0.25u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M34 !c c GND GND NMOS W=0.25u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M35 Y !a nN4 GND NMOS W=1u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
.end
