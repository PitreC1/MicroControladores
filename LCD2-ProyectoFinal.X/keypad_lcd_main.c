#include <xc.h>
#include <pic16f887.h>
#include <stdio.h>
#include <string.h>
#include "LCD.h"
#define _XTAL_FREQ 4000000

__CONFIG(FOSC_INTRC_CLKOUT & WDTE_OFF & PWRTE_OFF & MCLRE_OFF & CP_OFF & CPD_OFF & BOREN_OFF & IESO_OFF & FCMEN_OFF & LVP_OFF);
__CONFIG(BOR4V_BOR40V & WRT_OFF);

//unsigned char Keypad_Key_Press();            /* function to find pressed key*/
unsigned char keyfind();

unsigned char password[5] ={'2','0','2','1',0};

unsigned char pass_user[5];
unsigned char key_temp[5];
unsigned char idx = 0;
unsigned char value_pass, value_passU;
unsigned int wrong_count=0;
unsigned int ok_count=0;

//char n[10]="hola\0";
char key;

void main() 
{
    //OSCCON = 0b01110001;
    OSCCON = 0x61;
    
    //TRISB = 0x0f;
    //Configuramos para tener pines digitales, etc
    ANSELH =0x00;
    ANSEL=0x00;
    
    //Configuración para tener cada puerto como corresponde
    TRISD = 0x00; 
    TRISA = 0x01;
    TRISC = 0x00;
    PORTC = 0x00;
    PORTA = 0x00;
    
    OPTION_REGbits.nRBPU=0; //activas los pull-ups del puerto B
    
    LCD_Init();                         /* initialize LCD16x2 in 4-bit mode */
    LCD_Clear();
    LCD_String_xy(0,0,"Bienvenido"); //mensaje inicial
    __delay_ms(2000);    
    LCD_Clear(); 
                   
    while(1){
        LCD_Clear();
        LCD_String_xy(0,0,"Todo en Orden"); 
        PORTCbits.RC0 = 1; //enciende led verde
         __delay_ms(2000); 
        LCD_Clear();
    
        //Si se detecta una presencia
         if(PORTAbits.RA0 == 0){
             LCD_String_xy(2,0,"Peligro"); //mensaje de alerta
             PORTCbits.RC0 = 0; //apaga led verde
             PORTCbits.RC1 = 1; //enciende led amarillo
             PORTCbits.RC2 = 1; //enciende led rojo
             __delay_ms(1000);
             LCD_Clear();
             Secuencia_Clave();
             
             //reset los leds amarillo y verde
             PORTCbits.RC1 = 0;
             PORTCbits.RC2 = 0;
             __delay_ms(1000);
             
         }
        //si hay alguna puerta o ventana abierta
        else if(PORTAbits.RA1 == 1){ 
            Logica_SensoresHall();
        }
        
        else if(PORTAbits.RA2 == 1){
            Logica_SensoresHall();
         }
        
    }
    
}

Secuencia_Clave (void){
    while(1){
        LCD_String_xy(1,0,"Ingrese Clave"); //solicitamos confirmación de
                                                    //identidad del usuario          
        for(int i=0; i<4;i++){
            key = keyfind();
            LCD_Command(0xC0); 
            LCD_Char('*');
            //LCD_Char('\0');
            pass_user[i] = key;
            //idx++;
        }
                
        //¿ingresa clave correcta?
        if(strcmp(pass_user,password)!=0){
            LCD_Clear();
            LCD_String_xy(0,0,"Clave Erronea");
            __delay_ms(2000);
            wrong_count++;
        }
        else{
            ok_count++;
        }
        if(ok_count>=1){
            //idx=0;
            ok_count=0;
            wrong_count=0;
        
            pass_user[0]=0;
            pass_user[1]=0;
            pass_user[2]=0;
            pass_user[3]=0;
            pass_user[4]=0;
            
            break;
        }
        else if(wrong_count>=3){
            while(1){
                LCD_Clear();
                LCD_String_xy(0,0,"Debe Reiniciar");
                LCD_Command(0xC0);
                LCD_String("El Sistema");
                __delay_ms(2000);
            }
        }
    }

}

Logica_SensoresHall(void){
    LCD_String_xy(0,0,"Deteccion");
    LCD_Command(0xC0);
    LCD_String("En Sensores");
    PORTCbits.RC0 = 0; //apaga led verde
    PORTCbits.RC1 = 1; //enciende led amarillo
    __delay_ms(7000);
             
    if(PORTAbits.RA1 == 1){
        PORTCbits.RC2 = 1; //enciende led rojo
        LCD_Clear();
        LCD_String_xy(0,0,"Deteccion");
        LCD_Command(0xC0);
        LCD_String("Sensor 1");
        __delay_ms(7000);
        LCD_Clear();
        Secuencia_Clave();
        PORTCbits.RC1 = 0;
        PORTCbits.RC2 = 0;
        LCD_Clear();
    }
    else if(PORTAbits.RA2 == 1){
        PORTCbits.RC2 = 1; //enciende led rojo
        LCD_String_xy(0,0,"Deteccion");
        LCD_Command(0xC0);
        LCD_String("Sensor 2");
        __delay_ms(7000);
        LCD_Clear();
        Secuencia_Clave();
        PORTCbits.RC1 = 0;
        PORTCbits.RC2 = 0;
        LCD_Clear();
    }
    else{
        PORTCbits.RC1 = 0;
        PORTCbits.RC2 = 0;
        LCD_Clear();
    }
}

