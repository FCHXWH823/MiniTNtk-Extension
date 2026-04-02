// Path statistics: a: 14; b: 7; c: 7; d: 7; e: 7; f: 7; 
.subckt NSP_42_DepthLimited GND VCC Y a b c d e f 
.model nmos NMOS level=1 VTO=0.4 KP=120u
.model pmos PMOS level=1 VTO=-0.4 KP=40u

M0 Y f pN4 VCC PMOS W=2u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M1 pN4 b pN3 VCC PMOS W=2u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M2 pN1 c pN3 VCC PMOS W=2u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M3 pN1 d VCC VCC PMOS W=2u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M4 pN2 a pN1 VCC PMOS W=2u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M5 Y e pN2 VCC PMOS W=2u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M6 pN3 a VCC VCC PMOS W=2u L=0.05u 
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
M12 nN2 f GND GND NMOS W=0.75u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M13 Y e nN2 GND NMOS W=0.75u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
.end
