// Path statistics: a: 16; b: 8; c: 8; d: 8; e: 6; f: 6; 
.subckt NSP_14_DepthLimited GND VCC Y a b c d e f 
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
M4 Y c pN1 VCC PMOS W=1.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M5 Y e VCC VCC PMOS W=0.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M6 Y f VCC VCC PMOS W=0.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M7 nN2 a nN1 GND NMOS W=1.25u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M8 nN3 b nN2 GND NMOS W=1.25u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M9 nN4 c nN2 GND NMOS W=1.25u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M10 nN3 d nN1 GND NMOS W=1.25u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M11 nN1 e GND GND NMOS W=1.25u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M12 nN4 a nN3 GND NMOS W=1.25u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M13 Y f nN4 GND NMOS W=1.25u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
.end
