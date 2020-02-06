#include "ADC.h"
int activo;
void adc (int activo){
    switch (activo){
        case 1:
            ADCON0 = 0x57;
            break;
            
        default:
            ADCON0 = 0x57;
            break;
            
    }
}
