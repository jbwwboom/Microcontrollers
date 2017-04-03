;
; Track6.asm
;
; Created: 16-3-2017 15:45:07
; Author : justi
;


; Replace with your application code
start:
    ; demoprogramma 6_b: 16 bits optelling met opslag in data memory
;
.INCLUDE "m128def.inc"
;
.CSEG
.ORG $0000
rjmp main
;
.CSEG
.ORG $0200
;
main:
; initialisatie data geheugen
;
LDI YH, $04 ; Y <- $0400 adres in data memory 1 byte
LDI YL, $00 ; +1 = 2 byte
; LDI YH, HIGH(a) ;
; LDI YL, LOW(a) ;
LDD R8, Y+0 ; Haal waarden op uit data memory +1 = 3 byte
LDD R9, Y+1 ; +1 = 4 byte
LDD R6, Y+2 ; +1 = 5 byte
LDD R7, Y+3 ; +1 = 6 byte
; 16 bits optelling: R5/R4 = R9/R8 + R7/R6 (23 ab + 44 98 = 68 43)
; Stap 1: tel de LSB’s op: R4 = R6+R8
MOV R4, R8 ; R4 <- R8 +4 = 10 bytes
ADD R4, R6 ; R4 <- R4+R6 misschien Carry gezet +2 = 12 bytes
; Stap 2: tel de MSB’s op met
; de (eventuele) carry uit LSB’s:
; R3 = R5+R6+C
MOV R5, R9 ; R5 <- R9 +4 = 16 bytes
ADC R5, R7 ; R5 <- R5+R7+C +3 = 19 bytes
;
; Opslag resultaat
;
STD Y+4,R4 ; Sla resultaat op in data memory +2 = 21 bytes
STD Y+5,R5 ; +2 23 bytes
no_end: ; unlimited loop, when done TOTAAL 23 BYTES
rjmp no_end
.DSEG
.ORG $0400
a: .BYTE 2
b: .BYTE 2
c: .BYTE 2
