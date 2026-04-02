// Path statistics: a: 14; b: 7; c: 7; d: 7; e: 5; 
.subckt NSP_4 GND VCC Y a b c d e 
.model nmos NMOS level=1 VTO=0.4 KP=120u
.model pmos PMOS level=1 VTO=-0.4 KP=40u

M0 Y e pN3 VCC PMOS W=2u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M1 pN2 b VCC VCC PMOS W=2u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M2 pN2 c pN1 VCC PMOS W=2u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M3 pN3 d pN1 VCC PMOS W=2u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M4 pN1 a VCC VCC PMOS W=2u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M5 pN3 a pN2 VCC PMOS W=2u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M6 nN2 a GND GND NMOS W=0.75u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M7 Y a nN1 GND NMOS W=0.75u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M8 nN2 c nN1 GND NMOS W=0.75u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M9 nN1 d GND GND NMOS W=0.75u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M10 Y b nN2 GND NMOS W=0.75u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M11 Y e GND GND NMOS W=0.25u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
.end
