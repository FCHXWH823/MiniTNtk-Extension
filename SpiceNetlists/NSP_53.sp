// Path statistics: a: 14; b: 8; c: 8; d: 8; e: 8; f: 8; 
.subckt NSP_53 GND VCC Y a b c d e f 
.model nmos NMOS level=1 VTO=0.4 KP=120u
.model pmos PMOS level=1 VTO=-0.4 KP=40u

M0 Y b pN3 VCC PMOS W=2.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M1 Y a pN1 VCC PMOS W=2u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M2 pN1 c pN4 VCC PMOS W=2.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M3 pN1 d VCC VCC PMOS W=2.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M4 pN3 e pN2 VCC PMOS W=2.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M5 pN2 f pN4 VCC PMOS W=2.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M6 pN2 a VCC VCC PMOS W=2u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M7 nN2 a GND GND NMOS W=0.75u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M8 nN1 b GND GND NMOS W=0.75u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M9 nN2 c nN1 GND NMOS W=0.75u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M10 Y a nN1 GND NMOS W=0.75u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M11 nN1 e GND GND NMOS W=0.75u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M12 nN2 f nN1 GND NMOS W=0.75u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M13 Y d nN2 GND NMOS W=0.75u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
.end
