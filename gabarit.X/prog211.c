/**
   LCD driver source file

  Company:
    Microchip Technology Inc.

  File Name:
    prog211.c

  Summary:
           fonctions utiles pour le cours Programmation appliquée


*/

/**
  Section: Included Files
*/
#include <xc.h>
#include "mcc_generated_files/pin_manager.h"
#include "prog211.h"



void output_high(unsigned pin)
{ 
   
    switch(pin)
    {          
       case 50 : IO_RA0_SetHigh();
                 break;
       case 51 : IO_RA1_SetHigh();
                 break;
       case 52 : IO_RA2_SetHigh();
                 break;
       case 53 : IO_RA3_SetHigh();
                 break;
      // RA4 non-accessible 
       case 55 : IO_RA5_SetHigh();
                 break;
     // RA6 non-accessible 
     // RA7 non-accessible
     //  case 60 : RB0 = 1;    normalement en input 
     //            break;
       case 61 : IO_RB1_SetHigh();
                 break;
       case 62 : IO_RB2_SetHigh();
                 break;
       case 63 : IO_RB3_SetHigh();
                 break;  
       case 64 : IO_RB4_SetHigh();
                 break;
       case 65 :IO_RB5_SetHigh();
                 break;
       case 66 : IO_RB6_SetHigh();
                 break;            
       case 67 : IO_RB7_SetHigh();
                 break;            
       case 70 : IO_RC0_SetHigh();
                 break;
       case 71 : IO_RC1_SetHigh();
                 break;
       case 72 : IO_RC2_SetHigh(); 
                 break;
       case 73 : IO_RC3_SetHigh(); 
                 break;  
       case 74 : IO_RC4_SetHigh();
                 break;
       case 75 : IO_RC5_SetHigh();
                 break;
       //case 76 : RC6 = 1; 
       //          break;            
       //case 77 : RC7 = 1; 
       //          break;             
              
                 
    }  
       
}


   
void output_low(unsigned pin)
{

    switch(pin)
    {          
       case 50 : IO_RA0_SetLow();
                 break;
       case 51 : IO_RA1_SetLow();
                 break;
       case 52 : IO_RA2_SetLow();
                 break;
       case 53 : IO_RA3_SetLow();
                 break;
      // RA4 non-accessible 
       case 55 : IO_RA5_SetLow();
                 break;
     // RA6 non-accessible 
     // RA7 non-accessible
     //  case 60 : RB0 = 1;    normalement en input 
     //            break;
       case 61 : IO_RB1_SetLow();
                 break;
       case 62 : IO_RB2_SetLow();
                 break;
       case 63 : IO_RB3_SetLow();
                 break;  
       case 64 : IO_RB4_SetLow();
                 break;
       case 65 : IO_RB5_SetLow();
                 break;
       case 66 : IO_RB6_SetLow();
                 break;            
       case 67 : IO_RB7_SetLow();
                 break;            
       case 70 : IO_RC0_SetLow();
                 break;
       case 71 : IO_RC1_SetLow();
                 break;
       case 72 : IO_RC2_SetLow(); 
                 break;
       case 73 : IO_RC3_SetLow(); 
                 break;  
       case 74 : IO_RC4_SetLow();
                 break;
       case 75 : IO_RC5_SetLow();
                 break;
       // case 76 : RC6 = 0; 
       //          break;            
       //case 77 : RC7 = 0; 
       //          break;             
              
                 
    }
  
}
 
int input(unsigned pin)
{
    int value;

    switch(pin)
    {  
        case 60 : value = PORTBbits.RB0;
                 break;
        case 61 : value = PORTBbits.RB1;
                 break;
        case 62 : value = PORTBbits.RB2;
                 break;
        case 63 : value = PORTBbits.RB3;
                 break;  
        case 64 : value = PORTBbits.RB4;
                 break;
        case 65 : value = PORTBbits.RB5;
                 break;
        case 66 : value = PORTBbits.RB6;
                 break;            
        case 67 : value = PORTBbits.RB7;
                 break;            
        
    }
    return value;
}

