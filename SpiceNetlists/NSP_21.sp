// Path statistics: a: 16; b: 8; c: 8; d: 8; e: 8; f: 6; 
.subckt NSP_21 GND VCC Y a b c d e f 
.model nmos NMOS level=1 VTO=0.4 KP=120u
.model pmos PMOS level=1 VTO=-0.4 KP=40u

M0 Y f VCC VCC PMOS W=0.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M1 Y a pN2 VCC PMOS W=1.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M2 pN2 c VCC VCC PMOS W=1.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M3 pN1 d pN2 VCC PMOS W=1.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M4 pN2 e VCC VCC PMOS W=1.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M5 Y b pN1 VCC PMOS W=1.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M6 pN1 a VCC VCC PMOS W=1.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M7 nN1 a GND GND NMOS W=1.25u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M8 nN2 b GND GND NMOS W=1.25u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M9 nN1 c nN3 GND NMOS W=1.25u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M10 nN4 d nN1 GND NMOS W=1.25u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M11 nN2 e nN3 GND NMOS W=1.25u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M12 nN4 a nN2 GND NMOS W=1.25u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M13 Y f nN4 GND NMOS W=1.25u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
.end
