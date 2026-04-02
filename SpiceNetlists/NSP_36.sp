// Path statistics: a: 16; b: 7; c: 7; d: 8; e: 8; f: 8; 
.subckt NSP_36 GND VCC Y a b c d e f 
.model nmos NMOS level=1 VTO=0.4 KP=120u
.model pmos PMOS level=1 VTO=-0.4 KP=40u

M0 Y e pN3 VCC PMOS W=2u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M1 pN2 b VCC VCC PMOS W=1.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M2 pN1 a VCC VCC PMOS W=2u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M3 pN1 d pN2 VCC PMOS W=2u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M4 Y c pN1 VCC PMOS W=1.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M5 pN2 f pN1 VCC PMOS W=2u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M6 pN3 a pN2 VCC PMOS W=2u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M7 nN3 a GND GND NMOS W=1u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M8 nN1 b GND GND NMOS W=1u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M9 Y a nN1 GND NMOS W=1u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M10 nN2 d nN3 GND NMOS W=1u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M11 nN3 e GND GND NMOS W=1u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M12 nN2 f nN1 GND NMOS W=1u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M13 Y c nN3 GND NMOS W=1u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
.end
