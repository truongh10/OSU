;***********************************************************
;*
;*	Hao_Truong_Lab6_sourcecode.asm
;*
;*	Enternal Interrupt
;*
;*	This is the skeleton file for Lab 6 of ECE 375
;*
;***********************************************************
;*
;*	 Author: Hao Truong
;*	   Date: 11/12/2021
;*
;***********************************************************

.include "m128def.inc"			; Include definition file

;***********************************************************
;*	Internal Register Definitions and Constants
;***********************************************************
.def	mpr = r16				; Multipurpose register 
.def	waitcnt = r23			; wait loop counter
.def	ilcnt = r24				; Inner Loop Counter
.def	olcnt = r25				; Outer Loop Counter

.def	rightcnt = r3
.def	leftcnt = r4


.equ	WTime = 100				; Time to wait in wait loop


.equ	WskrR = 0				; Right Whisker Input Bit
.equ	WskrL = 1				; Left Whisker Input Bit

;***********************************************************
;*	Start of Code Segment
;***********************************************************
.cseg							; Beginning of code segment

;***********************************************************
;*	Interrupt Vectors
;***********************************************************
.org	$0000					; Beginning of IVs
		rjmp 	INIT			; Reset interrupt

		; Set up interrupt vectors for any interrupts being used
; enternal interrupt request 0 (INT0) is located at Program address $0002
.org	$0002
		rcall	HitRight
		reti

; enternal interrupt request 1 (INT1) is located at Program address $0004
.org	$0004
		rcall	HitLeft
		reti

; enternal interrupt request 2 (INT2) is located at Program address $0006
.org	$0006
		rcall ClearRightCounter
		reti

; enternal interrupt request 3 (INT3) is located at Program address $0008
.org	$0008
		rcall ClearLeftCounter
		reti

		; This is just an example:
;.org	$002E					; Analog Comparator IV
;		rcall	HandleAC		; Call function to handle interrupt
;		reti					; Return from interrupt

.org	$0046					; End of Interrupt Vectors

;***********************************************************
;*	Program Initialization
;***********************************************************
INIT:							; The initialization routine
		; Initialize Stack Pointer
		ldi				mpr, low(RAMEND)
		out				SPL, mpr			; load SPL with low byte of RAM
		ldi				mpr, high(RAMEND)
		out				SPH, mpr			; load SPH with high byte of RAM
		
		; Initialize Port B for output
		ldi				mpr, $FF			; set Port B Data Direction Register
		out				DDRB, mpr			; for output
		ldi				mpr, $00			; initialize Port B Data Register
		out				PORTB, mpr			; so all port B data outputs are low
		
		; Initialize Port D for input
		ldi			mpr, $00			; set Port D Data Direction Register
		out			DDRD, mpr			; for input
		ldi			mpr, $FF			; initialize Port D Data Direction Register
		out			PORTD, mpr			; so all Port D inputs are Tri-State

		; Initialize LCD Display
		RCALL		LCDInit



		; Display left counter and right counter on LCD (both counters are initially 0)
		; initialize right counter
		ldi		mpr, 0			; load 0 to rightcnt
		ldi		XL, $00				; Y <- data memory address of line 1
		ldi		XH, $01
;		st		X, mpr
		; call Bin2ASCII function
		rcall   Bin2ASCII       ; convert value in ASCII

		; initialize left counter
;		ldi		mpr, 0b00000000			; load 0 to leftcnt
		ldi		XL, $10				; Y <- data memory address of line 2
		ldi		XH, $01
;		st		X, mpr
		; call Bin2ASCII function
		rcall   Bin2ASCII       ; convert value in ASCII
		rcall	LCDWrite

		; initialize left and right counters
		clr		leftcnt
		clr		rightcnt




		; Initialize external interrupts
		; Set the Interrupt Sense Control to falling edge 
		ldi			mpr, 0b10101010		; ISCn1 is set to 1, ISCn0 is cleared -> falling edge
		sts			EICRA, mpr

		; Configure the External Interrupt Mask
		ldi			mpr, 0b00001111
		out			EIMSK, mpr			; enable interrupts 0, 1, 2, and 3

		; Turn on interrupts
		sei								; set interrupts
			; NOTE: This must be the last thing to do in the INIT function

;***********************************************************
;*	Main Program
;***********************************************************
MAIN:							; The Main program

		; TODO: ???



		; The BumpBot initially moves forwards
		ldi		mpr, 0b01100000
		out		PORTB, mpr

		rjmp	MAIN			; Create an infinite while loop to signify the 
								; end of the program.

;***********************************************************
;*	Functions and Subroutines
;***********************************************************

;-----------------------------------------------------------
;	You will probably want several functions, one to handle the 
;	left whisker interrupt, one to handle the right whisker 
;	interrupt, and maybe a wait function
;------------------------------------------------------------

;----------------------------------------------------------------
; Sub:	HitRight
; Desc:	Handles functionality of the TekBot when the right whisker
;		is triggered and displays number of right whikser hit on LCD.
;----------------------------------------------------------------
HitRight:
		push	mpr					; Save mpr register
		push	waitcnt				; Save wait register
		in		mpr, SREG			; Save program state
		push	mpr					;
		push	XL					; save YL
		push	XH					; save YH
		push	ZL
		push	ZH


					
		ldi		mpr, 0
		inc		mpr
		add		rightcnt, mpr
		mov		mpr, rightcnt

		ldi		XL, $00				; X <- data memory address of line 1
		ldi		XH, $01

		; call Bin2ASCII function
		rcall   Bin2ASCII       ; convert value in ASCII
		
		rcall	LCDWrLn1		; write both lines onto LCD
		



		; Move Backwards for a second
		ldi		mpr, 0b00000000		; Load Move Backward command
		out		PORTB, mpr			; Send command to port
		ldi		waitcnt, WTime		; Wait for 1 second
		rcall	Wait1				; Call wait function

		; Turn left for a second
		ldi		mpr, 0b00100000		; Load Turn Left Command
		out		PORTB, mpr			; Send command to port
		ldi		waitcnt, WTime		; Wait for 1 second
		rcall	Wait1				; Call wait function

		; Move Forward again	
		ldi		mpr, 0b01100000		; Load Move Forward command
		out		PORTB, mpr			; Send command to port

		; Avoid queued interrupts by writing 1 to EIFR
		ldi		mpr, 0b00001111
		out		EIFR, mpr


		pop		ZH
		pop		ZL
		pop		XH
		pop		XL
		pop		mpr					; Restore program state
		out		SREG, mpr			;
		pop		waitcnt				; Restore wait register
		pop		mpr					; Restore mpr
		ret							; Return from subroutine

;----------------------------------------------------------------
; Sub:	HitLeft
; Desc:	Handles functionality of the TekBot when the left whisker
;		is triggered and displays number of left whisker hit on LCD.
;----------------------------------------------------------------
HitLeft:
		push	mpr					; Save mpr register
		push	waitcnt				; Save wait register
		in		mpr, SREG			; Save program state
		push	mpr					;
		push	XL					; save YL
		push	XH					; save YH


		ldi		mpr, 0
		inc		mpr
		add		leftcnt, mpr
		mov		mpr, leftcnt

\

		ldi		XL, $10				; X <- data memory address of line 2
		ldi		XH, $01

		; call Bin2ASCII function
		rcall   Bin2ASCII       ; convert value in ASCII
		
		rcall	LCDWrLn2		; write both lines onto LCD
		mov		leftcnt, mpr

		; Move Backwards for a second
		ldi		mpr, 0b00000000		; Load Move Backward command
		out		PORTB, mpr			; Send command to port
		ldi		waitcnt, WTime		; Wait for 1 second
		rcall	Wait1				; Call wait function

		; Turn right for a second
		ldi		mpr, 0b01000000		; Load Turn Left Command
		out		PORTB, mpr			; Send command to port
		ldi		waitcnt, WTime		; Wait for 1 second
		rcall	Wait1				; Call wait function

		; Move Forward again	
		ldi		mpr, 0b00000000		; Load Move Forward command
		out		PORTB, mpr			; Send command to port

		; Avoid queued interrupts by writing 1 to EIFR
		ldi		mpr, 0b00001111
		out		EIFR, mpr


		pop		XH
		pop		XL
		pop		mpr					; Restore program state
		out		SREG, mpr			;
		pop		waitcnt				; Restore wait register
		pop		mpr					; Restore mpr
		ret							; Return from subroutine


;--------------------------------------------------------------
; Sub: ClearRightCounter
; Desc: Clear right whisker counter and display 0 to line 1 of LCD
;--------------------------------------------------------------
ClearRightCounter:
		push	mpr
		push	XL
		push	XH



		clr		rightcnt
		mov		mpr, rightcnt

		ldi		XL, $00				; X <- data memory address of line 1
		ldi		xH, $01

		; call Bin2ASCII function
		rcall   Bin2ASCII       ; convert value in ASCII
		
		rcall	LCDWrLn1		; write both lines onto LCD

		; Avoid queued interrupts by writing 1 to EIFR
		ldi		mpr, 0b00001111
		out		EIFR, mpr


		pop		XH
		pop		XL
		pop		mpr


;--------------------------------------------------------------
; Sub: ClearRightCounter
; Desc: Clear left whisker counter and display 0 to line 2 of LCD
;--------------------------------------------------------------
ClearLeftCounter:
		push	mpr
		push	XL
		push	XH


		clr		leftcnt			; clear rightcnt
		mov		mpr, leftcnt


		ldi		XL, $10				; X <- data memory address of line 1
		ldi		XH, $01

		; call Bin2ASCII function
		rcall   Bin2ASCII       ; convert value in ASCII
		
		rcall	LCDWrLn2		; write both lines onto LCD

		; Avoid queued interrupts by writing 1 to EIFR
		ldi		mpr, 0b00001111
		out		EIFR, mpr


		pop		XH
		pop		XL
		pop		mpr

;----------------------------------------------------------------
; Sub:	Wait
; Desc:	A wait loop that is 16 + 159975*waitcnt cycles or roughly 
;		waitcnt*10ms.  Just initialize wait for the specific amount 
;		of time in 10ms intervals. Here is the general eqaution
;		for the number of clock cycles in the wait loop:
;			((3 * ilcnt + 3) * olcnt + 3) * waitcnt + 13 + call
;----------------------------------------------------------------
Wait1:
		push	waitcnt			; Save wait register
		push	ilcnt			; Save ilcnt register
		push	olcnt			; Save olcnt register

Loop:	ldi		olcnt, 224		; load olcnt register
OLoop:	ldi		ilcnt, 237		; load ilcnt register
ILoop:	dec		ilcnt			; decrement ilcnt
		brne	ILoop			; Continue Inner Loop
		dec		olcnt		; decrement olcnt
		brne	OLoop			; Continue Outer Loop
		dec		waitcnt		; Decrement wait 
		brne	Loop			; Continue Wait loop	

		pop		olcnt		; Restore olcnt register
		pop		ilcnt		; Restore ilcnt register
		pop		waitcnt		; Restore wait register
		ret				; Return from subroutine

;-----------------------------------------------------------
; Func: Template function header
; Desc: Cut and paste this and fill in the info at the 
;		beginning of your functions
;-----------------------------------------------------------
FUNC:							; Begin a function with a label

		; Save variable by pushing them to the stack

		; Execute the function here
		
		; Restore variable by popping them from the stack in reverse order

		ret						; End a function with RET

;***********************************************************
;*	Stored Program Data
;***********************************************************

; Enter any stored data you might need here

;***********************************************************
;*	Data memory allocation
;***********************************************************


;***********************************************************
;*	Additional Program Includes
;***********************************************************
.include "LCDDriver.asm"		; Include the LCD Driver
