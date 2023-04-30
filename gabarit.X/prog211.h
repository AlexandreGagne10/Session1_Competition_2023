/**
    Header File pour le module prog211.c

   Luc Vermette

  File Name:
    prog211.h

  Summary:
 Prototypes des fonctiones utilisees dans le cours Programmation appliquée


*/

#include <xc.h>

#define _XTAL_FREQ 20000000

// assignation de nombres arbitraires pour les broches

#define PIN_A0 50   
#define PIN_A1 51  
#define PIN_A2 52  
#define PIN_A3 53  
// PIN_A4 non disponible
//#define PIN_A5 PORTAbits.RA5   temporairement
#define PIN_A5 55
// PIN_A6 non disponible
// PIN_A7 non disponible

#define PIN_B0 60  
#define PIN_B1 61  
#define PIN_B2 62  
#define PIN_B3 63  
#define PIN_B4 64  
#define PIN_B5 65  
#define PIN_B6 66  
#define PIN_B7 67  

#define PIN_C0 70      
#define PIN_C1 71  
#define PIN_C2 72  
#define PIN_C3 73  
#define PIN_C4 74  
#define PIN_C5 75  
#define PIN_C6 76  
#define PIN_C7 77  


void output_high(unsigned pin);
void output_low(unsigned pin);
int input(unsigned pin);