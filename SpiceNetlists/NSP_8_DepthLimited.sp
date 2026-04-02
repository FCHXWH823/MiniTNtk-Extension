// Path statistics: a: 9; b: 8; c: 9; d: 9; e: 6; 
.subckt NSP_8_DepthLimited GND VCC Y a b c d e 
.model nmos NMOS level=1 VTO=0.4 KP=120u
.model pmos PMOS level=1 VTO=-0.4 KP=40u

M0 Y b pN1 VCC PMOS W=1u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M1 pN2 b VCC VCC PMOS W=1.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M2 pN3 c pN2 VCC PMOS W=1.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M3 pN1 a VCC VCC PMOS W=1.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M4 Y d pN3 VCC PMOS W=1.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M5 pN4 d pN1 VCC PMOS W=1.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M6 Y e pN4 VCC PMOS W=1.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M7 pN4 c pN1 VCC PMOS W=1.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M8 nN2 a GND GND NMOS W=0.75u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M9 Y a nN1 GND NMOS W=0.75u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M10 nN2 c nN1 GND NMOS W=0.75u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M11 nN1 d GND GND NMOS W=0.75u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M12 nN2 e GND GND NMOS W=0.75u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M13 Y b nN2 GND NMOS W=0.75u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
.end
