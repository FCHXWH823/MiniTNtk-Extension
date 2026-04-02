// Path statistics: a: 14; b: 7; c: 7; d: 7; e: 5; 
.subckt NSP_3_DepthLimited GND VCC Y a b c d e 
.model nmos NMOS level=1 VTO=0.4 KP=120u
.model pmos PMOS level=1 VTO=-0.4 KP=40u

M0 Y e VCC VCC PMOS W=0.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M1 Y a pN1 VCC PMOS W=1.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M2 pN2 c pN1 VCC PMOS W=1.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M3 pN1 d VCC VCC PMOS W=1.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M4 Y b pN2 VCC PMOS W=1.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M5 pN2 a VCC VCC PMOS W=1.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M6 nN1 a GND GND NMOS W=1u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M7 nN2 b GND GND NMOS W=1u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M8 nN2 c nN1 GND NMOS W=1u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M9 nN3 d nN1 GND NMOS W=1u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M10 nN3 a nN2 GND NMOS W=1u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M11 Y e nN3 GND NMOS W=1u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
.end
