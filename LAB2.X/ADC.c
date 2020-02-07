#include "ADC.h"
int activo;
void adc (int activo){
    switch (activo){
        case 5:
            ADCON0 = 0x55;
            break;
            
        default:
            ADCON0 = 0x55;
            break;
            
    }
}
