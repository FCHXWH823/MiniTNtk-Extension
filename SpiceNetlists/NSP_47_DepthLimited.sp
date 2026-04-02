// Path statistics: a: 12; b: 8; c: 8; d: 8; e: 8; f: 8; 
.subckt NSP_47_DepthLimited GND VCC Y a b c d e f 
.model nmos NMOS level=1 VTO=0.4 KP=120u
.model pmos PMOS level=1 VTO=-0.4 KP=40u

M0 Y a pN2 VCC PMOS W=1.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M1 pN2 b VCC VCC PMOS W=1.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M2 pN1 a VCC VCC PMOS W=1.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M3 pN2 d pN1 VCC PMOS W=1.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M4 pN2 e VCC VCC PMOS W=1.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M5 pN1 f pN2 VCC PMOS W=1.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M6 Y c pN1 VCC PMOS W=1.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M7 nN4 a GND GND NMOS W=0.75u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M8 nN3 b GND GND NMOS W=1.25u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M9 nN4 c nN2 GND NMOS W=1.25u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M10 Y a nN2 GND NMOS W=0.75u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M11 nN2 e nN3 GND NMOS W=1.25u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M12 nN1 f nN4 GND NMOS W=1.25u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M13 Y d nN1 GND NMOS W=1.25u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
.end
