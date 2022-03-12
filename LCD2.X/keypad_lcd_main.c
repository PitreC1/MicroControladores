#include <xc.h>
#include <pic16f887.h>
#include "LCD.h"
#define _XTAL_FREQ 4000000

__CONFIG(FOSC_INTRC_CLKOUT & WDTE_OFF & PWRTE_OFF & MCLRE_OFF & CP_OFF & CPD_OFF & BOREN_OFF & IESO_OFF & FCMEN_OFF & LVP_OFF);
__CONFIG(BOR4V_BOR40V & WRT_OFF);

//unsigned char Keypad_Key_Press();            /* function to find pressed key*/
unsigned char keyfind();

unsigned char password[5] ={'2','0','2','1','0'};

unsigned char pass_user[6];
unsigned char idx = 0;

char n[10]="hola\0";
char key,key2;

void main() 
{
    //OSCCON = 0b01110001;
    OSCCON = 0x61;
    
    //TRISB = 0x0f;
    ANSELH =0x00;
    ANSEL=0x00;
    
    TRISD = 0x00;
    
    OPTION_REGbits.nRBPU=0;
    
    LCD_Init();                         /* initialize LCD16x2 in 4-bit mode */
    LCD_Clear();
    LCD_String_xy(0,0,"Prueba xxxx?");
    //LCD_Command(0xC0);
    __delay_ms(1000);
    //LCD_Command(0xC0);                  
    while(1){
        LCD_Clear();
        //LCD_String_xy(1,0,n);
        /*n++;
        if (n==0x3A){
            n=0x30;
        }*/
        //key = Keypad_Key_Press();              /* find a pressed key */
        do{
            key = keyfind();              /* find a pressed key */
            LCD_Char(key);/* display pressed key on LCD16x2 */
            pass_user[idx++] = key;
        }while(idx < 5);
        pass_user[idx] = '\0';
        LCD_String_xy(1,0,pass_user);
        
        //LCD_Char('*');/* display pressed key on LCD16x2 */
        __delay_ms(1000);
    }
        
}


