#include "7Segmentos.h"
int valor;
void sevenseg (int valor){// switch case apra cada valor del 7 segmentos 
    switch (valor){
        case 1:
            PORTC = 0x28;
            break;
        case 2:
            PORTC = 0xCD;
            break;
        case 3:
            PORTC = 0x6D;
            break;
        case 4:
            PORTC = 0x2B;
            break;
        case 5:
            PORTC = 0x67;
            break;
        case 6:
            PORTC = 0xE7;
            break;
        case 7:
            PORTC = 0x2D;
            break;
        case 8:
            PORTC = 0xEF;
            break;
        case 9:
            PORTC = 0x6F;
            break;
        case 10:
            PORTC = 0xAF;
            break;
        case 11:
            PORTC = 0xE3;
            break;
        case 12:
            PORTC = 0xC6;
            break;
        case 13:
            PORTC = 0xE9;
            break;
        case 14:
            PORTC = 0xC7;
            break;
        case 15:
            PORTC = 0x87;
            break;
        default:
            PORTC = 0xEF;
            break;
    }
            
                
}


