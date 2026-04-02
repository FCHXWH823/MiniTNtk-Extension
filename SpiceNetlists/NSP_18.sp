// Path statistics: a: 16; b: 8; c: 8; d: 8; e: 6; f: 6; 
.subckt NSP_18 GND VCC Y a b c d e f 
.model nmos NMOS level=1 VTO=0.4 KP=120u
.model pmos PMOS level=1 VTO=-0.4 KP=40u

M0 Y f pN4 VCC PMOS W=2.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M1 pN3 b pN1 VCC PMOS W=2.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M2 pN4 c pN1 VCC PMOS W=2.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M3 pN3 d pN2 VCC PMOS W=2.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M4 pN2 e VCC VCC PMOS W=2.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M5 pN1 a pN2 VCC PMOS W=2.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M6 pN4 a pN3 VCC PMOS W=2.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M7 nN1 a GND GND NMOS W=0.75u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M8 nN2 b GND GND NMOS W=0.75u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M9 Y a nN2 GND NMOS W=0.75u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M10 nN2 d nN1 GND NMOS W=0.75u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M11 Y c nN1 GND NMOS W=0.75u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M12 Y e GND GND NMOS W=0.25u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M13 Y f GND GND NMOS W=0.25u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
.end
