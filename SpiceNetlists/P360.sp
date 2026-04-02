// Path statistics: !a: 12; !b: 12; !c: 7; !d: 8; a: 12; b: 7; c: 7; d: 12; 
.subckt P360 GND VCC Y a b c d 
.model nmos NMOS level=1 VTO=0.4 KP=120u
.model pmos PMOS level=1 VTO=-0.4 KP=40u

M0 Y d pN3 VCC PMOS W=2u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M1 pN3 b pN4 VCC PMOS W=2u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M2 pN3 c pN1 VCC PMOS W=2u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M3 Y a pN1 VCC PMOS W=2u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M4 pN2 !a VCC VCC PMOS W=2u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M5 pN4 !b VCC VCC PMOS W=2u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M6 pN2 !c pN4 VCC PMOS W=2u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M7 pN4 !d VCC VCC PMOS W=2u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M8 pN3 a pN2 VCC PMOS W=2u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M9 pN1 !a pN4 VCC PMOS W=2u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M10 !a a VCC VCC PMOS W=0.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M11 !b b VCC VCC PMOS W=0.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M12 !c c VCC VCC PMOS W=0.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M13 !d d VCC VCC PMOS W=0.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M14 nN2 a nN1 GND NMOS W=1u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M15 nN2 b GND GND NMOS W=0.75u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M16 !d d GND GND NMOS W=0.25u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M17 Y c nN1 GND NMOS W=0.75u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M18 nN2 !a nN4 GND NMOS W=1u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M19 Y d nN2 GND NMOS W=1u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M20 Y !b nN2 GND NMOS W=1u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M21 nN4 !d nN3 GND NMOS W=1u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M22 nN1 d nN3 GND NMOS W=1u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M23 nN3 !b GND GND NMOS W=1u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M24 !a a GND GND NMOS W=0.25u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M25 !b b GND GND NMOS W=0.25u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M26 !c c GND GND NMOS W=0.25u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M27 Y !c nN4 GND NMOS W=0.75u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
.end
