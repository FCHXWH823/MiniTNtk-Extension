// Path statistics: !a: 13; !b: 13; !c: 13; !d: 13; a: 13; b: 18; c: 17; d: 18; 
.subckt P27031 GND VCC Y a b c d 
.model nmos NMOS level=1 VTO=0.4 KP=120u
.model pmos PMOS level=1 VTO=-0.4 KP=40u

M0 Y !b pN6 VCC PMOS W=2.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M1 pN1 a pN2 VCC PMOS W=2u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M2 pN4 c pN1 VCC PMOS W=2u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M3 pN5 d VCC VCC PMOS W=2.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M4 pN1 !a pN5 VCC PMOS W=2u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M5 Y b pN4 VCC PMOS W=2.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M6 pN3 !c pN7 VCC PMOS W=2.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M7 pN2 !d VCC VCC PMOS W=2.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M8 pN6 !c pN1 VCC PMOS W=2u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M9 pN7 !a pN2 VCC PMOS W=2.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M10 pN7 d pN3 VCC PMOS W=2.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M11 pN6 c pN7 VCC PMOS W=2.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M12 pN3 a pN5 VCC PMOS W=2.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M13 pN4 b pN3 VCC PMOS W=2.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M14 !a a VCC VCC PMOS W=0.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M15 !b b VCC VCC PMOS W=0.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M16 !c c VCC VCC PMOS W=0.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M17 !d d VCC VCC PMOS W=0.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M18 nN2 a nN1 GND NMOS W=1u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M19 !d d GND GND NMOS W=0.25u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M20 nN3 c nN5 GND NMOS W=1u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M21 nN1 d nN6 GND NMOS W=1u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M22 nN6 !a GND GND NMOS W=1u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M23 Y b nN3 GND NMOS W=1u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M24 nN1 !c nN3 GND NMOS W=1u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M25 nN5 !d nN6 GND NMOS W=1u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M26 nN3 !b GND GND NMOS W=1u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M27 nN1 c nN4 GND NMOS W=1u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M28 Y !b nN4 GND NMOS W=1u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M29 nN4 b GND GND NMOS W=1u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M30 nN2 !d GND GND NMOS W=1u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M31 !a a GND GND NMOS W=0.25u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M32 !b b GND GND NMOS W=0.25u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M33 !c c GND GND NMOS W=0.25u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M34 Y d nN2 GND NMOS W=1u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
.end
