// DSPIC30F2010 Configuration Bit Settings

// 'C' source line config statements

#include "def.h"

//d�claration des variables
const unsigned int StateLoTable[] = {0x0000, 0x0210, 0x2004, 0x0204, 0x0801, 0x0810, 0x2001, 0x0000};
unsigned int HallValue = 0, Current = 0, Freq = 0;
unsigned char Vitesse = 0, Validation = 0, CptRampe = 0;
state State = Idle;
stateComp Rampe = ComparateursOff;

int test = 0;

int main(int argc, char** argv) {
    Init();                         //Initialisation des diff�rents modules
    START_MOTOR();                  //Activation des PWMs
    LED_OFF();                      //Extinction de la LEDs utilisateur
    while(1) {                      //Boucle infini
        if(State == ErrCur) {       //clignotement rapide si le courant est trop �lev�
            STOP_MOTOR();           //On arr�te le moteur
            __delay_ms(100);
            LED_ON();
            __delay_ms(100);
            LED_OFF();
        } else if(State == ErrRec) { //allum� si on ne recoit rien
            LED_ON();
        } else {
            START_MOTOR();          //On d�marre le moteur (Cas si on a eu une sur int�nsit�e)
            __delay_ms(500);        //clignotement lent si tout vas bien
            LED_ON();
            __delay_ms(500);
            LED_OFF();
        }
    }
    return (EXIT_SUCCESS);
}

void __attribute__((__interrupt__, __auto_psv__)) _CNInterrupt(void) { //Gestion d'interruption des capteurs de retour FEM
    IFS0bits.CNIF = 0;              //On efface le bit d'interruption
    if(Rampe) {                     //Si on a fini la rampe
        HallValue = PORTB & 0x0038; //Masque du port B pour r�cup�rer les valeurs de RB3, 4 et 5
        HallValue = HallValue >> 3; //D�calage au bit 0 de RB3
        OVDCON = StateLoTable[HallValue]; //Affection d'uin tableau liant l'ordre des PWMs � alimenter en fonction des capteurs
    }
    Freq++;                         //Incr�ment d'une variable de "mesure" de al vitesse du moteur
}

void __attribute__((__interrupt__, __auto_psv__)) _ADCInterrupt(void) { //Gestion d'interruption de la lecture analogique du courant
    IFS0bits.ADIF = 0;              //On efface le bit d'interruption
    Current = ADCBUF0;              //lecture du resultat
}

void __attribute__((__interrupt__, __auto_psv__)) _T3Interrupt(void) { //Gestion d'interruption du Timer 3
	IFS0bits.T3IF = 0;              //On efface le bit d'interruption
    /*                       gestion des �tats                                     */
    if(Current > LIM_CUR) {         //Si on a une surintensit�
        PDC1 = 0;                   //On �teint le moteur
        PDC3 = 0;
        PDC3 = 0;
        State = ErrCur;             //On se met dans l'�tat correspondant pour mettre � jour la lED
    } else {
        if(Validation) {            //Si on n'a eu un message en I2C il y a moins de 100 ms
            unsigned char V;
            if(Vitesse > LIM_VIT) { //Si la vitesse de commande recu est suffisante pour lancer le moteur
                if(Freq > LIM_FREQ) {//Si la fr�quence moteur permet d'exploiter les comparateurs
                    V = Vitesse;    //On affecte la vitesse sur les PWMs
                    Rampe = ComparateursOn;//On passe en mode comparateurs
                } else {
                    Rampe = ComparateursOff;//On ne regarde plus les comparateurs
                    V = PDC1+PAS_RAMPE;//On cr�e une rampe de vitesse
                    OVDCON = StateLoTable[CptRampe];//On r�&alise le mode pas � pas
                    CptRampe++;     //On incr�mente le pas
                    if(CptRampe > 9) {//On ne d�passe pas la taille de la s�quence
                        CptRampe = 0;
                    }
                }
            } else {
                V = 0;              //Si on n'a pas une assez grande valeur sur la vitesse de commade, le moteur ne tourne pas
            }
            Validation--;           //Validation est remis � 4 � chaque message soit 4*20ms => Validation = 0
                                    //Au bout de 100 ms si on n'a pas eu de nouveau messages, on ne retourne pas dans cette partie du code
            State = Idle;
            PDC1 = V;
            PDC3 = V;
            PDC3 = V;
        } else {
            PDC1 = 0;               //Si validation = 0, on eteint le moteur et on effecte l'�tat sur la LED
            PDC3 = 0;
            PDC3 = 0;
            State = ErrRec;
        }
    }
    Freq = 0;                       //On remet � 0 le comptage de la vitesse moteur
}

void __attribute__((__interrupt__, __auto_psv__)) _SI2CInterrupt(void) { //Gestion d'interruption  de la r�c�ption en I2C
    IFS0bits.SI2CIF = 0;             //On efface le bit d'interruption
    unsigned char temp = I2CRCV;     //Lecture du message
    if(temp < 102 && temp > 0) {     //r�c�ption des messages et d�codage
        if(temp == 101) {            //Commande d'arr�t du moteur
            Vitesse = 0;
        } else {
            Vitesse = (100-temp)<<1; //Adaptation de la valeur du moteur
        }
        Validation = 4;              //Nouveau message re�u, T3 fonctionne normalement pour 100 ms
    }
}
