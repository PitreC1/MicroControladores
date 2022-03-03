#include <xc.h>
#include <pic16f887.h>
#define _XTAL_FREQ 8000000

__CONFIG(FOSC_INTRC_CLKOUT & WDTE_OFF & PWRTE_OFF & MCLRE_OFF & CP_OFF & CPD_OFF & BOREN_OFF & IESO_OFF & FCMEN_OFF & LVP_OFF);
__CONFIG(BOR4V_BOR40V & WRT_OFF);
void MSdelay (unsigned int val);

void main(void) {
    OSCCON = 0b01110001;
    
    TRISD = 0x00;
    TRISB = 0x00;
    ANSELH = 0x00;
    
    while(1){
        PORTD = 0x81;
        __delay_ms(500);//espera 500ms antes de continuar
        PORTD = ~PORTD;
        __delay_ms(500);
        for (int i=0; i<8; i++){
            PORTD = 1<<i;
            __delay_ms(500);
        }
    }
    return;
}
void MSdelay (unsigned int val){
    unsigned int i,j;
    for(i=0; i<val;i++)
    {for(j=0; j<i; j++);
    }
}
