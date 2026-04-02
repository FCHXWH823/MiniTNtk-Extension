// Path statistics: a: 14; b: 6; c: 7; d: 6; e: 7; 
.subckt NSP_5 GND VCC Y a b c d e 
.model nmos NMOS level=1 VTO=0.4 KP=120u
.model pmos PMOS level=1 VTO=-0.4 KP=40u

M0 Y a pN2 VCC PMOS W=1.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M1 pN2 b VCC VCC PMOS W=1.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M2 pN1 c pN2 VCC PMOS W=1.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M3 pN1 a VCC VCC PMOS W=1.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M4 pN1 e VCC VCC PMOS W=1.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M5 Y d pN1 VCC PMOS W=1.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M6 nN1 a GND GND NMOS W=1u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M7 nN2 b GND GND NMOS W=0.75u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M8 nN1 c nN2 GND NMOS W=1u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M9 nN3 a nN2 GND NMOS W=1u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M10 Y d nN1 GND NMOS W=0.75u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M11 Y e nN3 GND NMOS W=1u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
.end
