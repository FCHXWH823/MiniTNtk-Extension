.subckt test GND VCC Y a b c d f 
M0 Y b pN3 VCC PMOS W=1.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M1 Y a pN1 VCC PMOS W=1u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M2 pN4 c VCC VCC PMOS W=1.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M3 pN3 d pN4 VCC PMOS W=1.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M4 pN1 f VCC VCC PMOS W=1u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M5 nN1 f GND GND NMOS W=0.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M6 Y a nN1 GND NMOS W=0.5u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M7 nN4 c GND GND NMOS W=0.75u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M8 nN3 d nN4 GND NMOS W=0.75u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
M9 Y b nN3 GND NMOS W=0.75u L=0.05u 
+ ad=0p pd=0u as=0p ps=0u
.ends test
