// Path statistics: a: 14; b: 7; c: 7; d: 7; e: 7; f: 7; 
.subckt NSP_39 GND VCC Y a b c d e f 
.model nmos NMOS level=1 VTO=0.4 KP=120u
.model pmos PMOS level=1 VTO=-0.4 KP=40u

M0 Y d pN2 VCC PMOS W=1.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M1 pN1 b VCC VCC PMOS W=1.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M2 pN2 c pN1 VCC PMOS W=1.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M3 Y a pN1 VCC PMOS W=1.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M4 pN2 e VCC VCC PMOS W=1.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M5 pN1 f VCC VCC PMOS W=1.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M6 pN2 a VCC VCC PMOS W=1.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M7 nN1 a GND GND NMOS W=1u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M8 Y a nN2 GND NMOS W=1u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M9 nN2 c nN4 GND NMOS W=1u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M10 nN2 d GND GND NMOS W=1u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M11 nN4 e nN1 GND NMOS W=1u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M12 nN3 f nN4 GND NMOS W=1u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M13 Y b nN3 GND NMOS W=1u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
.end
