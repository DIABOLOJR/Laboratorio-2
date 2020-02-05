// PIC16F887 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
// Configuración del PIC
#pragma config FOSC = INTRC_CLKOUT// Oscillator Selection bits (INTOSC oscillator: CLKOUT function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown Out Reset Selection bits (BOR enabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)
 
/*
 *Bibliotecas
 */
#include <xc.h>
#include <stdint.h>
#include "7Segmentos.h"

/*
 *Variables y asignaciones previas
 */
unsigned int uint8_t a = 0;
int b = 0;
int c = 0;
int conversion = 0;
int valor1 = 0;
int valor2 = 0;
float d = 0;
/*
 *Main
 */
void main(void) {
    return;
}
/*
 * Codigo de incrementos
 */
void contador(void){
    if (b =0){
        a++;
        PORTB = a;
    } else if (c = 0){
        a--;+
        PORTB = a;
    }
}
/*
 * Interrupción
 */
void __interrupt () isr (void){
    if(INTCONbits.RBIF == 1){
        if (PORTBbits.RB7 == 1){
            b=0;    
            INTCONbits.RBIF == 0;
        }else if (PORTBbits.RB1 == 1){
            c = 0;
            INTCONbits.RBIF == 0;
        }
    }
    if (INTCONbits.T0IF == 1) {
        if (PORTDbits.RD0 == 1){
            PORTDbits.RD0 = 0;
            PORTDbits.RD3 = 1;
        }else if (PORTDbits.RD3 == 1){
            PORTDbits.RD0 = 1;
            PORTDbits.RD3 = 0;
        }
    }
    
    
}
/*
 *Delay codigo de ejemplo en clase
 */
void delay_ms(unsigned int dms){
    for(int i = 0; i<dms; i++){// ciclo para el aumento en miisegundos.
        for(int j = 0; j<255; j++);
    }
}

/*
 *Conversion del ADC
 */

void valorsevenseg (void){
    valor1 = conversion && 0b00001111;
    valor = valor1;
    sevenseg(valor);
}
void valorsevenseg2 (void){
    valor2 = conversion && 0b11110000;
    valor2 = valor2>>4;
    valor = valor2;
    sevenseg(valor);
}

/*
 *
 */