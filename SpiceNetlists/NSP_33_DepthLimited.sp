// Path statistics: a: 14; b: 10; c: 7; d: 9; e: 10; f: 7; 
.subckt NSP_33_DepthLimited GND VCC Y a b c d e f 
.model nmos NMOS level=1 VTO=0.4 KP=120u
.model pmos PMOS level=1 VTO=-0.4 KP=40u

M0 Y e pN2 VCC PMOS W=2u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M1 Y a pN2 VCC PMOS W=2u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M2 pN1 c pN3 VCC PMOS W=2u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M3 pN2 d VCC VCC PMOS W=2u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M4 Y b pN3 VCC PMOS W=2u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M5 pN2 f pN1 VCC PMOS W=2u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M6 pN3 a VCC VCC PMOS W=2u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M7 nN1 a GND GND NMOS W=0.75u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M8 Y d nN1 GND NMOS W=0.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M9 nN4 c GND GND NMOS W=0.75u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M10 nN5 d nN4 GND NMOS W=0.75u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M11 nN3 e nN1 GND NMOS W=0.75u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M12 nN4 f GND GND NMOS W=0.75u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M13 nN2 e nN4 GND NMOS W=0.75u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M14 Y b nN3 GND NMOS W=0.75u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M15 Y b nN5 GND NMOS W=0.75u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M16 Y a nN2 GND NMOS W=0.75u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
.end
