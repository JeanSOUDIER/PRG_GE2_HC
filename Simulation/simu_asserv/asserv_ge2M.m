clear

%Hélice

Vit = 10000/60;                     %vitesse du BLDC [tr/min]
D = 0.230;                          %Diamètre hélice en [m]
theta = 0.8;                        %Angle de la pale [rad]
H = 2*pi*0.7*D/2*tan(theta);        %Pas géométrique
h = H/D;                            %Pas de l'hélice
Sgouv = 0.008262;                   %Surface maxiamle du gouvernail en regard avec la poussée [m^2]
Ghelice = 28.35*h*D^3*10^-10*Sgouv; %Gain de l'hélice

Gfrot = 1;                          %Gain des frottement du système

P = 1.5;                            %Poids [Kg]
DecGcenter = 0;                     %Décalage du centre de gravité [m]
Ggrav = DecGcenter*9.81*P           %Gain lié au décalague du centre de gravité [N*m]

%Servo
L = 2.2e-3;                         %Inductance moteur [H]
R = 1.52;                           %Résistance moteur [Ohm]
J = 8.3e-5;                         %Inertie moteur [rad/s]
C0 = 0.024;                         %Coeff de frottement sec [N*m]
f = 5.06e-5;                        %Coeff de frottement visqeux [N*m]
Kphi = 0.127;                       %Coeff moteur

KpS = 1;                            %Correcteur P
KiS = 0.000001;                     %Correctuer I
Gservo = 1;                         %Coeff du cpateur du servo

Gredu = 1;                          %Coeff du reducteur moteur

%Asserv
Ti = 1;                             %Gain intégrateur capteur
Kp = 0.63;                            %Correcteur P
Ki = 0.01;                             %Correctuer I
Step = pi;                          %Step valeur finale
Te = 0.04;                          %Temps d'échantillonage [s]
Gcapt = 1;                          %Gain capteur
T = 0.5;                             %Temps de simulation

Vit^2*Ghelice*Step

%Simulation
sim('asserv_ge2',T);
%sim('servo',T);

figure(1);
plot(StepF);
figure(2);
plot(Pos);
figure(3);
plot(Vitesse);
figure(4);
plot(Courant);
figure(5);
plot(Erreur);
figure(6);
plot(Cmd);
figure(7);
plot(Gyro);
figure(8);
plot(Angle);


