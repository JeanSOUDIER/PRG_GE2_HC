clear

f = 25000;
T = 1/f;
Vbat = 11.4;
Pmot = 300;
Vds = Vbat;
tr = 5.2*10^-9;
tf = 3.6*10^-9;
Rds_on = 0.0026;

fprintf('calcul des puissances : ');
Id = Pmot/Vbat
Ps = 1/2*Vds*Id*(tr+tf)*f
Pc99 = (T-tr-tf)/T*Rds_on*Id^2
Pc80 = 0.8*Rds_on*Id^2
Pc20 = 0.2*Rds_on*Id^2

fprintf('calcul des puissances totales : ');
Ptot99 = Pc99+Ps
Ptot80 = Pc80+Ps
Ptot20 = Pc20+Ps

fprintf('calcul des températures : ');
Rcu = 300; %W/m/K à 20°C => 300-390
Tj = 80;
Ta = 25;
Rjs = 2.6;

Rcu/((Tj-Ta)/Ptot99-Rjs) %cm^2
