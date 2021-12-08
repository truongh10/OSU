;***********************************************************
;*
;*	Hao_Truong_Lab7_sourcecode.asm
;*
;*	Timer/Counters
;*
;*	This is the skeleton file for Lab 7 of ECE 375
;*
;***********************************************************
;*
;*	 Author: Hao Truong
;*	   Date: 11/19/2021
;*
;***********************************************************

.include "m128def.inc"			; Include definition file

;***********************************************************
;*	Internal Register Definitions and Constants
;***********************************************************
.def	mpr = r16				; Multipurpose register
.def	speed_level = r17		; speed level
.def	tmp = r18

.equ	EngEnR = 4				; right Engine Enable Bit
.equ	EngEnL = 7				; left Engine Enable Bit
.equ	EngDirR = 5				; right Engine Direction Bit
.equ	EngDirL = 6				; left Engine Direction Bit

;***********************************************************
;*	Start of Code Segment
;***********************************************************
.cseg							; beginning of code segment

;***********************************************************
;*	Interrupt Vectors
;***********************************************************
.org	$0000
		rjmp	INIT			; reset interrupt

		; place instructions in interrupt vectors here, if needed
.org	$0002					; INT0
		rcall	SPEED_DOWN		; service INT0
		reti					; return from INT0

.org	$0004					; INT1
		rcall	SPEED_UP		; service INT1
		reti					; return from INT1

.org	$0006					; INT2
		rcall	SPEED_MIN		; service INT2
		reti					; return from INT2

.org	$0008					; INT3
		rcall	SPEED_MAX		; service INT3
		reti					; return from INT3

.org	$0046					; end of interrupt vectors

;***********************************************************
;*	Program Initialization
;***********************************************************
INIT:
		; Initialize the Stack Pointer
		ldi		mpr, low(RAMEND)
		out		SPL, mpr
		ldi		mpr, high(RAMEND)
		out		SPH, mpr

		; Configure I/O ports
		ldi		mpr, 0b11111111		; initialize Port B for output
		out		DDRB, mpr			; set Port B directional register for output

		ldi		mpr, 0b00000000		; initialize Port D for input
		out		DDRD, mpr			; set Port D directional register for input
		ldi		mpr, 0b00001111		
		out		PORTD, mpr			; activate pull-up registers

		; Configure External Interrupts, if needed
		; Set the Interrupt Sense Control to falling edge
		ldi		mpr, 0b10101010
		sts		EICRA, mpr
		; Set up the external interrupt mask
		ldi		mpr, 0b00001111
		out		EIMSK, mpr


		; Configure 8-bit Timer/Counters
		ldi		mpr, 0b01111001		; activate Fast PWM mode with toggle
		out		TCCR0, mpr			; no prescaling, inverting
		out		TCCR2, mpr			

		; Set TekBot to Move Forward (1<<EngDirR|1<<EngDirL), with max speed
		ldi		speed_level, 0b01101111
		out		PORTB, speed_level
		ldi		mpr, 255
		out		OCR0, mpr						; write speed_level to OCR0
		out		OCR2, mpr						; write speed_level to OCR2
		

		; Set initial speed, display on Port B pins 3:0
		
		; Enable global interrupts (if any are used)
		sei						; turn on interrupt

;***********************************************************
;*	Main Program
;***********************************************************
MAIN:
		; poll Port D pushbuttons (if needed)

								; if pressed, adjust speed
								; also, adjust speed indication

		rjmp	MAIN			; return to top of MAIN

;***********************************************************
;*	Functions and Subroutines
;***********************************************************

;-----------------------------------------------------------
; Sub:	SPEED_DOWN
; Desc:	decrease speed by just one level
;		
;-----------------------------------------------------------
SPEED_DOWN:
		in		mpr, OCR0			; read OCR0
		cpi		mpr, 0				; checks if speed level is 0
		breq	SKIP				; speed level is 0, skip
		subi	mpr, 17				; subtract 17 from mpr (levels are 17 apart)
		out		OCR0, mpr			; write speed level to OCR0
		out		OCR2, mpr			; write speed level to OCR2
		dec		speed_level			; decrement speed_level
		out		PORTB, speed_level	; display speed_level on PORT B

SKIP:
		; Avoid queued interrupts by writing 1 to EIFR
		ldi		mpr, 0b00001111
		out		EIFR, mpr
		ret

;-----------------------------------------------------------
; Sub:	SPEED_UP
; Desc:	increase speed by just one level
;-----------------------------------------------------------
SPEED_UP:
		in		mpr, OCR2			; read OCR2
		cpi		mpr, 255			; checks if speed level is 15 (MAX)
		breq	SKIP1				; speed level is 0, skip
		ldi		tmp, 17
		add		mpr, tmp			; subtract 17 from mpr (levels are 17 apart)
		out		OCR0, mpr			; write speed level to OCR0
		out		OCR2, mpr			; write speed level to OCR2
		inc		speed_level			; decrement speed_level
		out		PORTB, speed_level	; display speed_level on PORT B

SKIP1:
		; Avoid queued interrupts by writing 1 to EIFR
		ldi		mpr, 0b00001111
		out		EIFR, mpr
		ret

;-----------------------------------------------------------
; Sub:	SPEED_MIN
; Desc:	immediately decrease speed to lowest level (stopped)
;-----------------------------------------------------------
SPEED_MIN:
		in		mpr, OCR0			; read OCR0
		mov		tmp, mpr			; copy mpr to tmp
		sub		mpr, tmp			; subtract tmp from mpr (speed is now 0% -> speed level is 0)
		out		OCR0, mpr			; write speed level to OCR0
		out		OCR2, mpr			; write speed level to OCR2
		ldi		mpr, 0b11110000		
		out		PORTB, mpr			; Tekbot halts

		; Avoid queued interrupts by writing 1 to EIFR
		ldi		mpr, 0b00001111
		out		EIFR, mpr
		ret

;-----------------------------------------------------------
; Sub:	SPEED_MAX
; Desc:	immediately increase speed to hoghest level (max)
;-----------------------------------------------------------
SPEED_MAX:


;		ldi		tmp, 255			; load 255 to mpr	(255 is full speed)
;		sub		tmp, mpr
;		add		mpr, tmp
		ldi		mpr, 255
		out		OCR0, mpr			; write speed level to OCR0
		out		OCR2, tmp			; write speed level to OCR2
		ldi		speed_level, 0b01101111		
		out		PORTB, speed_level			; Tekbot moves forward at max speed

		; Avoid queued interrupts by writing 1 to EIFR
		ldi		mpr, 0b00001111
		out		EIFR, mpr
		ret

;-----------------------------------------------------------
; Func:	Template function header
; Desc:	Cut and paste this and fill in the info at the 
;		beginning of your functions
;-----------------------------------------------------------
FUNC:	; Begin a function with a label

		; If needed, save variables by pushing to the stack

		; Execute the function here
		
		; Restore any saved variables by popping from stack

		ret						; End a function with RET

;***********************************************************
;*	Stored Program Data
;***********************************************************
		; Enter any stored data you might need here

;***********************************************************
;*	Additional Program Includes
;***********************************************************
		; There are no additional file includes for this program