#include "p16F887.inc"

; CONFIG1
; __config 0x3FF1
 __CONFIG _CONFIG1, _FOSC_XT & _WDTE_OFF & _PWRTE_OFF & _MCLRE_ON & _CP_OFF & _CPD_OFF & _BOREN_ON & _IESO_ON & _FCMEN_ON & _LVP_ON
; CONFIG2
; __config 0x3FFF
 __CONFIG _CONFIG2, _BOR4V_BOR40V & _WRT_OFF

  LIST p=16F887
  org	0x00

;Manipulacion de Registros

BANKSEL PORTE ;
CLRF PORTE;
BANKSEL ANSEL;
CLRF ANSEL;
BCF STATUS,RP1;
BANKSEL TRISE;
MOVLW B'00001011';
MOVWF TRISE;

BANKSEL PORTE
BSF PORTE,2 ; enciende el led

LOOP:
    nop
    nop
    goto LOOP
end