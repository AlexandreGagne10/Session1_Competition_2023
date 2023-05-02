/*
    Nom du projet : Robot suiveur de ligne - Competition 2023 - CEGEP de Maisonneuve
    Auteur : Alexandre Gagne
    Date : 2023-04-30

    Processeur : PIC18F25K80
    Compilateur : XC8
    IDE : MPLAB X 2.40
    Description : Ce programme permet de faire fonctionner le robot suiveur de ligne pour la competition de 2023.
*/

#include <stdio.h>
#include "prog211.h"
#include "mcc_generated_files/mcc.h"

//-----------------------------------------------------------//
//                                                           //
//                  REDEFINITION DES BROCHES                 //
//                                                           //
//-----------------------------------------------------------//

//---------------------- MOTEUR GAUCHE ----------------------//
#define IN1 PIN_A0  // Broche IN1 du moteur gauche
#define IN2 PIN_A1  // Broche IN2 du moteur gauche
//---------------------- MOTEUR DROIT -----------------------//
#define IN3 PIN_A2  // Broche IN3 du moteur droit
#define IN4 PIN_A3  // Broche IN4 du moteur droit
//----------------- ACTIVATION DES MOTEURS ------------------//
#define ENA PIN_C1  // Broche ENA pour activer le moteur gauche
#define ENB PIN_C2  // Broche ENB pour activer le moteur droit
//------------------------ CAPTEURS -------------------------//
#define LED PIN_A5  // Broche LED  
//------------------- CAPTEURS OBSTACLE ---------------------//
#define COG PIN_B2  // Broche CAPTEUR OBSTACLE GAUCHE
#define COD PIN_B3  // Broche CAPTEUR OBSTACLE DROIT
//-------------------- CAPTEURS LIGNE -----------------------//
#define CLD PIN_B0  // Broche CAPTEUR LIGNE DROIT
#define CLG PIN_B7  // Broche CAPTEUR LIGNE GAUCHE

//-----------------------------------------------------------//
//                                                           //
//                  PROTOTYPES DES FONCTIONS                 //
//                                                           //
//-----------------------------------------------------------//
void avancer_250ms(void);   // Fonction pour avancer pendant 250ms
void avancer(void);         // Fonction pour avancer
void TDB(void);             // Fonction pour tourner brusquement a droite
void TGB(void);             // Fonction pour tourner brusquement a gauche
void arret(void);           // Fonction pour arreter le robot

//-----------------------------------------------------------//
//                                                           //
//                    PROGRAMME PRINCIPAL                    //
//                                                           //
//-----------------------------------------------------------//
void main(void)
{
    SYSTEM_Initialize();    // Fonction pour initialiser le systeme

    while(1)    // Boucle infinie
    {
        bool CLD_STATE = input(CLD);    // On lit l'etat du capteur de ligne droit
        bool CLG_STATE = input(CLG);    // On lit l'etat du capteur de ligne gauche

        if (!CLD_STATE && !CLG_STATE)   // Si les deux capteurs de ligne sont hors ligne
        {
            avancer();  // On avance
        }
        
        if (CLD_STATE && !CLG_STATE)    // Si le capteur de ligne droit est sur la ligne
        {
            TGB();  // On tourne brusquement a gauche
        }
        
        if (!CLD_STATE && CLG_STATE)    // Si le capteur de ligne gauche est sur la ligne
        {
            TDB();  // On tourne brusquement a droite
        }
        
        if (CLD_STATE && CLG_STATE)    // Si les deux capteurs de ligne sont sur la ligne
        {
            for (int i = 0; i < 2; i++) // On avance pendant 250ms deux fois
            {
                avancer_250ms();    // On avance pendant 250ms
            }
            arret();    // On arrete le robot
        }
    }
}

//-----------------------------------------------------------//
//                                                           //
//                       LES FONCTIONS                       //
//                                                           //
//-----------------------------------------------------------//

//-----------------------------------------------------------//
//                                                           //
//                        Avance 250ms                       //
//     Le robot avance pendant 250ms a une vitesse de 44%    //
//     de sa vitesse max. Apr?s 250ms, le robot s'arrete.    //
//                                                           //
//-----------------------------------------------------------//
void avancer_250ms(void) {
    // On choisi la direction des moteurs
    output_high(IN1);   // Moteur gauche vers l'avant (HIGH)
    output_low(IN2);    // Moteur gauche vers l'avant (LOW)
    output_high(IN3);   // Moteur droit vers l'avant (HIGH)
    output_low(IN4);    // Moteur droit vers l'avant (LOW)

    //-------------------------------------------//
    //                                           //
    //     Nbrs de boucle:                       //
    //     250ms / 500 us = 500 boucles          //
    //                                           //
    //-------------------------------------------//
    for (int i = 0; i < 500; i++) 
    {
        //-------------------------------------------//
        //                                           //
        //            Puissance: 44%                 //
        //    Time High    220us   =   44 %          //
        //    Time TOT     500us   =  100 %          //
        //                                           //
        //-------------------------------------------//
        output_high(ENA);   // On active le moteur gauche
        output_high(ENB);   // On active le moteur droit
        __delay_us(250);      // On attend 220us
        output_low(ENA);    // On desactive le moteur gauche
        output_low(ENB);    // On desactive le moteur droit
        __delay_us(250);      // On attend 280us
    }
    arret();    // On arrete le robot
}

//-----------------------------------------------------------//
//                                                           //
//                          Avancer                          //
//  Le robot avance a une vitesse de 44% de sa vitesse max   //
//  tant que les deux capteurs de ligne sont hors ligne.     //
//                                                           //
//-----------------------------------------------------------//
void avancer(void) {
    // On choisi la direction des moteurs
    output_high(IN1);   // Moteur gauche vers l'avant (HIGH)
    output_low(IN2);    // Moteur gauche vers l'avant (LOW)
    output_high(IN3);   // Moteur droit vers l'avant (HIGH)
    output_low(IN4);    // Moteur droit vers l'avant (LOW)

    // Tant que les deux capteurs de ligne sont hors ligne
    while ((!input(CLD)) && (!input(CLG)))
    {
        //-------------------------------------------//
        //                                           //
        //            Puissance: 44%                 //
        //    Time High    220us   =   44 %          //
        //    Time TOT     500us   =  100 %          //
        //                                           //
        //-------------------------------------------//
        output_high(ENA);   // On active le moteur gauche
        output_high(ENB);   // On active le moteur droit
        __delay_us(250);      // On attend 220us
        output_low(ENA);    // On desactive le moteur gauche
        output_low(ENB);    // On desactive le moteur droit
        __delay_us(250);      // On attend 280us
    }
    arret();    // On arrete le robot
}

//-----------------------------------------------------------//
//                                                           //
//                Tourner a gauche brusquement               //
//  Le robot tourne a gauche brusquement a une vitesse de    //
//  40% de sa vitesse max tant que le capteur de ligne       //
//  droit est sur la ligne.                                 //
//                                                           //
//-----------------------------------------------------------//
void TGB(void) {
    // On choisi la direction des moteurs
    output_low(IN1);    // Moteur gauche vers l'arriere (LOW)
    output_high(IN2);   // Moteur gauche vers l'arriere (HIGH)
    output_high(IN3);    // Moteur droit vers l'arriere (LOW)
    output_low(IN4);   // Moteur droit vers l'arriere (HIGH)

    // Tant que le capteur de ligne gauche est sur la ligne
    while ((input(CLD)) && (!input(CLG))) 
    {
        //-------------------------------------------//
        //                                           //
        //            Puissance: 40%                 //
        //    Time High    200us   =   40 %          //
        //    Time TOT     500us   =  100 %          //
        //                                           //
        //-------------------------------------------//
        output_high(ENA);   // Activation du moteur A
        output_high(ENB);   // Activation du moteur B
        __delay_us(250);    // Delai de 200 microsecondes

        output_low(ENA);    // Desactivation du moteur A
        output_low(ENB);    // Desactivation du moteur B
        __delay_us(250);    // Delai de 300 microsecondes
    }
    arret();    // On arrete le robot
}

//-----------------------------------------------------------//
//                                                           //
//                Tourner a droite brusquement               //
//  Le robot tourne a droite brusquement a une vitesse de    //
//  40% de sa vitesse max tant que le capteur de ligne       //
//  gauche est sur la ligne.                                 //
//                                                           //
//-----------------------------------------------------------//
void TDB(void) {
    // On choisi la direction des moteurs
    output_high(IN1);    // Moteur gauche vers l'arriere (LOW)
    output_low(IN2);   // Moteur gauche vers l'arriere (HIGH)
    output_low(IN3);    // Moteur droit vers l'arriere (LOW)
    output_high(IN4);   // Moteur droit vers l'arriere (HIGH)

    // Tant que le capteur de ligne gauche est sur la ligne
    while ((!input(CLD)) && (input(CLG))) 
    {
        //-------------------------------------------//
        //                                           //
        //            Puissance: 40%                 //
        //    Time High    200us   =   40 %          //
        //    Time TOT     500us   =  100 %          //
        //                                           //
        //-------------------------------------------//
        output_high(ENA);   // Activation du moteur A
        output_high(ENB);   // Activation du moteur B
        __delay_us(250);    // Delai de 200 microsecondes

        output_low(ENA);    // Desactivation du moteur A
        output_low(ENB);    // Desactivation du moteur B
        __delay_us(250);    // Delai de 300 microsecondes
    }
    arret();    // On arrete le robot
}

//-----------------------------------------------------------//
//                                                           //
//                     Arreter le robot                      //
//  Le robot s'arrete en coupant l'alimentation des moteurs  //
//                                                           //
//-----------------------------------------------------------//
void arret(void) {
    output_low(ENA);    // Desactivation du moteur A
    output_low(ENB);    // Desactivation du moteur B
    __delay_ms(250);    // Delai de 250 millisecondes
}
