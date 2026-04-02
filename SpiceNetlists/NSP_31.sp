// Path statistics: a: 16; b: 7; c: 8; d: 7; e: 8; f: 8; 
.subckt NSP_31 GND VCC Y a b c d e f 
.model nmos NMOS level=1 VTO=0.4 KP=120u
.model pmos PMOS level=1 VTO=-0.4 KP=40u

M0 Y f pN2 VCC PMOS W=1.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M1 pN2 b pN1 VCC PMOS W=1.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M2 Y a pN1 VCC PMOS W=1.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M3 pN1 d VCC VCC PMOS W=1.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M4 Y c pN2 VCC PMOS W=1.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M5 Y e pN1 VCC PMOS W=1.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M6 pN2 a VCC VCC PMOS W=1.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M7 nN3 a nN1 GND NMOS W=1.25u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M8 Y a nN2 GND NMOS W=1.25u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M9 nN2 c nN4 GND NMOS W=1.25u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M10 nN2 d GND GND NMOS W=1u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M11 nN1 e GND GND NMOS W=1.25u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M12 nN4 f nN3 GND NMOS W=1.25u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M13 Y b nN3 GND NMOS W=1u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
.end
