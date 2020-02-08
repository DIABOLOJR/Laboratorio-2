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
#define _XTAL_FREQ 4000000  
#include "7Segmentos.h"

/*
 *Variables y asignaciones previas
 */

int press1 = 0;
int press2 = 0;
uint8_t eADC = 0;
uint8_t eTMR0 = 0;
int valor;
int turnon;

int conversion = 0;
int valor1 = 0;
int valor2 = 0;
float d = 0;
int multi = 0;
int calculado;
/*
 * Interrupción
 */
void __interrupt () isr (void){
    /******** interrupicion por iocb*/
    if(INTCONbits.RBIF == 1){ /*Se enciende la bandera*/
        if (PORTBbits.RB7 == 0){
            press1 = 1;}
        if (PORTBbits.RB1 == 0){
            press2 = 1;}
        INTCONbits.RBIF = 0;
        }
   /*------------------------------------*/
   /*********** INTERRUPCION DEL ADC ***********/
    if (ADCON0bits.GO_DONE == 0){
       eADC = 1;
       PIR1bits.ADIF =0;
    }
    /*-------------------------*/
     if (INTCONbits.T0IF == 1) {
        eTMR0 = 1;        
        INTCONbits.T0IF = 0;
        TMR0 = 125;}}


/*
 *Delay codigo de ejemplo en clase
 */
void delay_ms(unsigned int dms){
    for(int i = 0; i<dms; i++){// ciclo para el aumento en miisegundos.
        for(int j = 0; j<255; j++);
    }
}



void valorsevenseg (void){//funcion del valor de 7 segmento enseñadop en calse
    PORTC= 0b00000000;/*setei dek oyeti eb 0*/
    valor1 = conversion & 0b00001111; // valor de converción añadido a valor
    sevenseg(valor1);// llamado de funcion 
    PORTDbits.RD0 = 0;/*enceder y apagar los transistores*/
    PORTDbits.RD1 = 1;
    
    
    
}
void valorsevenseg2 (void){
    PORTC = 0b00000000;
    valor2 = conversion & 0b11110000;
    valor2 = valor2>>4;//corrimiento de 4 bits para el 7 segentos 2
    sevenseg(valor2);
    PORTDbits.RD0 = 1;
    PORTDbits.RD1 = 0;
}


/*configuracion del pic16f887*/
void sett(void){
    TRISBbits.TRISB7=1;
    TRISBbits.TRISB1=1;
    ANSEL = 0;
    TRISA = 0;
    TRISC = 0;
    TRISD = 0;
    TRISE = 0b0001;
    PORTA = 0;
    PORTC = 0;
    PORTD = 0;
    // configuracion del Timer0
    OPTION_REGbits.T0CS =0;
    OPTION_REGbits.PSA =0;
    OPTION_REGbits.PS0 =0;
    OPTION_REGbits.PS1 =1;
    OPTION_REGbits.PS2 =0;
    TMR0 = 125;
    INTCONbits.T0IE = 1;
    INTCONbits.T0IF = 0;
    //configuracion del adcon (EL ADC)
    PIE1bits.ADIE = 1; 
    PIR1bits.ADIF = 0; 
    ADCON0 = 0b01010101;
    ADCON1 = 0;        
    ADCON0bits.GO_DONE=1;
 
    
}

/*MAIN PRINCIPAL-----------------------------------------------------------*/
void main(void) {
    while (1){
        sett();//Funcion de seteos
        if (press1 == 1 && PORTBbits.RB7 == 1){
            PORTA++;}//Funcion de incremento de puetro b despues delos botonasos
        if (press2 == 1 && PORTBbits.RB0 == 1){
            PORTA--;}//funcion de decremetno
        if (eADC == 1){
            eADC =0;//enable del ADC
            conversion = ADRESH;
            ADCON0bits.GO_DONE = 1;}//seteo de inciio del ADC
        if (eTMR0 == 1){
            if (multi == 0){valorsevenseg();}//valor del 7 segmentos desde la funcion
            else {valorsevenseg2();}
            multi++;//variable a icrementar para yamar por el puerto
            if (multi>1){multi = 0;}
            eTMR0 = 0;}
    }
    return;
}