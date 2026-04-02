// Path statistics: a: 14; b: 7; c: 7; d: 7; e: 6; f: 6; 
.subckt NSP_17_DepthLimited GND VCC Y a b c d e f 
.model nmos NMOS level=1 VTO=0.4 KP=120u
.model pmos PMOS level=1 VTO=-0.4 KP=40u

M0 Y c pN1 VCC PMOS W=2u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M1 pN2 b pN3 VCC PMOS W=2u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M2 Y a pN2 VCC PMOS W=2u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M3 pN1 d pN2 VCC PMOS W=2u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M4 pN3 e VCC VCC PMOS W=2u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M5 pN3 f VCC VCC PMOS W=2u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M6 pN1 a pN3 VCC PMOS W=2u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M7 nN3 a GND GND NMOS W=0.75u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M8 nN1 b GND GND NMOS W=0.75u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M9 nN1 c nN3 GND NMOS W=0.75u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M10 Y a nN1 GND NMOS W=0.75u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M11 Y d nN3 GND NMOS W=0.75u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M12 nN2 f GND GND NMOS W=0.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M13 Y e nN2 GND NMOS W=0.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
.end
