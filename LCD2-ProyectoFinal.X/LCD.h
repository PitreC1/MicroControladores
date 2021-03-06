#ifndef LCD_H
#define	LCD_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h> // include processor files - each processor file is guarded.  

#include <pic16f887.h>
    


#define EN PORTDbits.RD1                    /*PIN 0 of PORTB is assigned for register select Pin of LCD*/
#define RS PORTDbits.RD3                    /*PIN 1 of PORTB is assigned for enable Pin of LCD */
//#define RW RB3
#define ldata PORTD                 /*PORTB(PB4-PB7) is assigned for LCD Data Output*/ 
#define LCD_Port TRISD
   
#define CMD_CLEAR_LCD 0x01
    
void LCD_Init();                    /*Initialize LCD*/
void LCD_Command(unsigned char );   /*Send command to LCD*/
void LCD_Char(unsigned char x);     /*Send data to LCD*/
void LCD_String(const char *);      /*Display data string on LCD*/
void LCD_String_xy(char, char , const char *);
void LCD_Clear();                   /*Clear LCD Screen*/


#ifdef	__cplusplus
}
#endif

#endif	/* LCD_H */

