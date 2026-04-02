// Path statistics: a: 14; b: 8; c: 7; d: 8; e: 8; f: 8; 
.subckt NSP_29 GND VCC Y a b c d e f 
.model nmos NMOS level=1 VTO=0.4 KP=120u
.model pmos PMOS level=1 VTO=-0.4 KP=40u

M0 Y b pN3 VCC PMOS W=2u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M1 Y a pN2 VCC PMOS W=2u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M2 pN3 c pN2 VCC PMOS W=1.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M3 pN2 d VCC VCC PMOS W=2u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M4 pN1 e pN2 VCC PMOS W=2u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M5 pN3 f pN1 VCC PMOS W=2u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M6 pN3 a VCC VCC PMOS W=2u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M7 nN1 a GND GND NMOS W=0.75u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M8 nN2 b GND GND NMOS W=1u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M9 Y a nN2 GND NMOS W=0.75u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M10 nN1 d nN2 GND NMOS W=1u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M11 nN3 e nN1 GND NMOS W=1u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M12 nN3 f nN1 GND NMOS W=1u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M13 Y c nN3 GND NMOS W=1u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
.end
