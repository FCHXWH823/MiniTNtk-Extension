// Path statistics: a: 10; b: 8; c: 10; d: 10; e: 7; f: 7; 
.subckt NSP_24_DepthLimited GND VCC Y a b c d e f 
.model nmos NMOS level=1 VTO=0.4 KP=120u
.model pmos PMOS level=1 VTO=-0.4 KP=40u

M0 Y b pN5 VCC PMOS W=1.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M1 pN1 a VCC VCC PMOS W=2u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M2 pN3 c pN1 VCC PMOS W=2u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M3 pN5 d pN4 VCC PMOS W=1.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M4 Y b pN1 VCC PMOS W=1u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M5 pN2 f pN3 VCC PMOS W=2u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M6 pN4 c VCC VCC PMOS W=1.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M7 Y e pN2 VCC PMOS W=2u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M8 pN3 d pN1 VCC PMOS W=2u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M9 nN1 a GND GND NMOS W=0.75u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M10 nN2 b GND GND NMOS W=0.75u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M11 Y a nN2 GND NMOS W=0.75u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M12 nN2 d nN1 GND NMOS W=0.75u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M13 Y c nN1 GND NMOS W=0.75u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M14 Y e nN2 GND NMOS W=0.75u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M15 Y f nN2 GND NMOS W=0.75u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
.end
