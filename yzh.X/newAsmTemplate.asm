#include "p16F1786.inc"

; CONFIG1
; __config 0xFFE7
 __CONFIG _CONFIG1, _FOSC_ECH & _WDTE_OFF & _PWRTE_ON & _MCLRE_ON & _CP_OFF & _CPD_OFF & _BOREN_ON & _CLKOUTEN_OFF & _IESO_ON & _FCMEN_ON
; CONFIG2
; __config 0xFFFF
 __CONFIG _CONFIG2, _WRT_OFF & _VCAPEN_OFF & _PLLEN_ON & _STVREN_ON & _BORV_LO & _LPBOR_OFF & _LVP_ON

  
 
CODE 0x0
CALL MAIN
MOVLW 00H ;??????06H??W
MOVWF 20H ;?????????
 
MOVLW 00H ;??????06H??W
MOVWF 21H ;??4?

MOVLW 00H ;??????06H??W
MOVWF 22H ;??9?
 
LOOP
banksel PORTA; movlw offset ;load offset in w reg
CLRW
ADDWF 21H,0
ADDWF 22H,0
CALL TABLE
MOVWF PORTA
 
CLRW
ADDWF 21H,0
ADDLW 1
MOVWF 21H 
 
BTFSC 21H,2
CLRF 21H
 
BANKSEL INTCON
BCF INTCON,0		;BCF:????f ???b ???
MOVLW B'00001100'
MOVWF TMR0
 
 
CLRW
ADDWF 20H,0
CALL STABLE
MOVWF PORTC
 
CLRW
ADDWF 20H,0
ADDLW 1
MOVWF 20H
 
BTFSC 20H,3
CLRF 20H
 
 
GOTO LOOP
	
;ISR CODE 0X04
;CLRW
;ADDWF 22H,0
;ADDLW 1
;MOVWF 22H 
;
;ANDLW B'00001001'
;CLRF 22H
;RETFIE
 
CHANGE
    BANKSEL INTCON
    BTFSS INTCON,2
;    CALL CHANGE
    GOTO CHANGE
RETURN
 
MAIN
	BANKSEL PORTA	;??????BANKSEL???????BANK?
			    ;??????????????STATUS??PR1?PR0???
	CLRF PORTA		;?PORTA??
    ;    MOVLW B'11111111'	;?????
    ;    MOVWF PORTA

	BANKSEL LATA	;Data Latch
	CLRF LATA


	BANKSEL ANSELA
	CLRF ANSELA		;digital I/O

	BANKSEL TRISA
	MOVLW B'00000000'	;????
	MOVWF TRISA	    	;??00000000????TRISA

	BANKSEL PORTC	;??????BANKSEL???????BANK?
			    ;??????????????STATUS??PR1?PR0???
	CLRF PORTC	;?PORTC??
    ;    BANKSEL ANSELA
    ;    CLRF ANSELA		;digital I/O
	MOVLW B'00000000'	;?????
	MOVWF PORTC


	BANKSEL TRISC
	MOVLW B'00000000'	;?????
	MOVWF TRISC	    	;??00000000????TRISA

	BANKSEL OPTION_REG
	CLRF OPTION_REG
	MOVLW B'00000111'   ;?????1?256
	MOVWF OPTION_REG	;bit 3 PSA????????   0 = ???????Timer0 ??

	BANKSEL TMR0
	CLRF TMR0
	MOVLW B'00001100' 
	MOVWF TMR0		;??TMR0?12 ?256??

	BANKSEL OSCCON	;?????
	MOVLW B'00110011'	;3-6??0110 = 250 kHz MF
	MOVWF OSCCON	;SCS<1:0>????????  1x = ???????

	BANKSEL INTCON	;INTCON????????
	CLRF INTCON		;bit 2 TMR0IF?Timer0 ???????
			    ;1 = TMR0 ??????	

    RETURN
   
    
    TABLE:
    addwf PCL,F		;?W ??????????f ????????d ?0?????W ??????d ?1????????f?
    ;retlw - ?????????W
    retlw  B'00111111' ;??0
    retlw  B'00000110'	;??1
    retlw  B'01011011'	;??2
    retlw  B'01000111' ;??3
    retlw  B'01100110' ;??4
    retlw  B'01101101' ;??5
    retlw  B'01111101' ;??6
    retlw  B'00000111' ;??7
    retlw  B'01111111' ;??8
    retlw  B'01100111' ;??9
    retlw  B'10000000' ;??
    
    
STABLE:
MOVWF PCL;???????,??PORTC??
RETLW B'11111110';1
RETLW B'11111101';2
RETLW B'11111011';3
RETLW B'11110111';4
end