clear

Vm = 15;
Vdd = 3.3;
R1A = 40000;
R1B = 12000;
R1 = R1A*R1B/(R1A+R1B);
Vin_max = R1B/(R1A+R1B)*Vm

Vtl = 0;
Vth = 2.7;
R3 = R1*Vdd/(Vth-Vtl)

Vref = Vth*R3/(R1+R3);
R2 = 10000*(Vdd/Vref-1)

