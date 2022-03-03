#include    <xc.h>
#include    <pic16f887.h> //Header file PIC16f887 definitions

__CONFIG(FOSC_INTRC_CLKOUT & WDTE_OFF & PWRTE_OFF & MCLRE_OFF & CP_OFF & CPD_OFF & BOREN_OFF & IESO_OFF & FCMEN_OFF & LVP_OFF);
__CONFIG(BOR4V_BOR40V & WRT_OFF);

#define _XTAL_FREQ 8000000

unsigned char count = 0;
unsigned char count_ms = 0;
char display [10]={0x3F,0x06,0x5B,0xF4,0x66,0x6D,0x7D,0x07,0x7F,0x6F};

int main(void) {
    
    TRISB0 = 0;  		//pinRB0 como salida digital, se colocará el led
    PORTB = 0;  		//El led se inicia apagado y parpadea cada 500ms
    ANSELH = 0x00;
    
    INTCONbits.GIE = 0;
    OPTION_REGbits.T0CS = 0;//mode temporizador
    OPTION_REGbits.PSA = 0; // prescaler enable
    OPTION_REGbits.PS = 0b111; // prescaler 256
    TMR0 = 60;
    
    TRISD = 0x00;
    PORTD = 0x00;
    
    TRISA4 = 1;//reset del contador
    ANSEL = 0x00;//digital
    
    INTCONbits.T0IF = 0;
    INTCONbits.T0IE = 1;
    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;
    
    while (1) {
        //LATD = ((count / 10) << 4) + (count % 10);
        PORTD = display[count % 10];
        __delay_ms(20);
        //PORTD = (1 << 4) + (count / 10);
        //__delay_ms(20);
        
        
        if (!PORTAbits.RA4) {
            __delay_ms(50);
            count = 0;
            TMR0 = 60;
            INTCONbits.T0IF = 0;
        }
    }
    //return 1;
}

void interrupt ISR_TIMER_0(void) {
    if (INTCONbits.T0IE && INTCONbits.T0IF) {
        PORTB = ~PORTB;
        count_ms++;
        if(count_ms == 20){
            if (++count == 100) {
                count = 0;
            }
            count_ms = 0;
        }
        TMR0 = 60;
        INTCONbits.T0IF = 0;
    }
}
