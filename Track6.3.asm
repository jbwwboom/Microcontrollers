

.INCLUDE "m128def.inc"
;
.CSEG
.ORG 	$0000
		rjmp main
;
.CSEG
.ORG	$0200
;
main:
	mov $8b0, $660 //Dit kopieert de gehuegenwaarde van 660h naar de plaats 8b0
	mov $8b1, $661
	mov $8b2, $662
	mov $8b3, $663
	mov $8b4, $664
	mov $8b5, $665
	mov $8b6, $666
	mov $8b7, $667
	mov $8b7, $668
	mov $8b9, $669
	mov $8c0, $670


			
no_end:   					; unlimited loop, when done
		rjmp no_end			
		
.DSEG
.ORG	$0c00
		.BYTE	200	
