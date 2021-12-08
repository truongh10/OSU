;***********************************************************
;*
;*	Hao_Truong_Lab4_sourcecode
;*
;*	Data Manipulation
;*
;*	This is the skeleton file for Lab 4 of ECE 375
;*
;***********************************************************
;*
;*	 Author: Hao Truong
;*	   Date: 10/29/2021
;*
;***********************************************************

.include "m128def.inc"			; Include definition file

;***********************************************************
;*	Internal Register Definitions and Constants
;***********************************************************
.def	mpr = r16				; Multipurpose register is
								; required for LCD Driver
.def	count1 = r23


.equ	Button0 = 0
.equ	Button1 = 1
.equ	Button7 = 7


;***********************************************************
;*	Start of Code Segment
;***********************************************************
.cseg							; Beginning of code segment

;***********************************************************
;*	Interrupt Vectors
;***********************************************************
.org	$0000					; Beginning of IVs
		rjmp INIT				; Reset interrupt

.org	$0046					; End of Interrupt Vectors

;***********************************************************
;*	Program Initialization
;***********************************************************
INIT:							; The initialization routine
		; Initialize Stack Pointer
		ldi			mpr, low(RAMEND)	; Load the low byte of ram's end addrress\
		out			SPL, mpr			; Set the SP low register
		ldi			mpr, high(RAMEND)	; Load the high byte of ram's end address
		out			SPH, mpr			; set the SP high register

		; Initialize LCD Display
		RCALL		LCDInit

		; Initialize Port D for input
		ldi			mpr, $00			; set Port D Data Direction Register
		out			DDRD, mpr			; for input
		ldi			mpr, $FF			; initialize Port D Data Direction Register
		out			PORTD, mpr			; so all Port D inputs are Tri-State




		; NOTE that there is no RET or RJMP from INIT, this
		; is because the next instruction executed is the
		; first instruction of the main program

;***********************************************************
;*	Main Program
;***********************************************************
MAIN:							; The Main program
		; Main function design is up to you. Below is an example to brainstorm.
	
		
		; Display the strings on the LCD Display
		in			mpr, PIND			; get input from Port D
;		andi		mpr, (1<<Button0 | 1<<Button1 | 1<<Button7)
		cpi			mpr, (0b11111110)	; check for input Button0
		brne		Next				; continue with next check if not equal
		rcall		ButtonPD0			; call subroutine ButtonDP0
		rjmp		MAIN
Next:
		cpi			mpr, (0b11111101)	; check for Button1
		brne		Next1				; continue with next check if not equal
		rcall		LCDClr				; clear both lines of LCD
		rcall		ButtonPD1			; call subroutine ButtonDP1
		rjmp		MAIN
Next1:
		cpi			mpr, (0b01111111)	; check for Button7
		brne		MAIN
		rcall		LCDClr				; clear both lines of LCD

		rjmp	MAIN			; jump back to main and create an infinite
								; while loop.  Generally, every main program is an
								; infinite while loop, never let the main program
								; just run off

;***********************************************************
;*	Functions and Subroutines
;***********************************************************

;-----------------------------------------------------------
; sub: ButtonPD0
; Desc: When you press PD0: Displays your name (Hao Truong) on the first line of the LCD, 
;		and a phrase like ”Hello World!” on the second line of the screen.
;-----------------------------------------------------------
ButtonPD0:							; Begin a function with a label
		; Save variables by pushing them to the stack
		push	mpr				; save mpr register
		push	count1			; save count1
		push	ZL				; save ZL
		push	ZH				; save ZH
		push	YL				; save YL
		push	YH				; save YH

		; Execute the function here
		; Move strings from Program Memory to Data Memory
		; move first string from Program Memory to Data Memory
		ldi		ZL, low(STRING_BEG << 1)		; extract low byte of STRING_BEG
		ldi		ZH, high(STRING_BEG << 1)		; extract high byte of STRING_BEG
												; Z now points to first char (H)				
		ldi		YL, $00							; Y <- data memory address of character destination (line 1)
		ldi		YH, $01
		ldi		count1, 10						; used to count down chars, first line contains 10 letters
Line1:
		lpm		mpr, Z+					; load Z to mpr
		st		Y+, mpr					; load mpr to Y
		dec		count1					; count down # of words to add
		BRNE	Line1					; if not done loop

		; Move second string from Program Memory to Data Memory
		ldi		ZL, low(STRING_END << 1)		; extract low byte of STRING_BEG
		ldi		ZH, high(STRING_END << 1)		; extract high byte of STRING_BEG
												; Z now points to first char (H)				
		ldi		YL, $10							; Y <- data memory address of character destination (line 2)
		ldi		YH, $01
		clr		count1
		ldi		count1, 12						; used to count down chars, first line contains 12 letters
Line2:
		lpm		mpr, Z+					; load Z to mpr
		st		Y+, mpr					; load mpr to Y
		dec		count1					; count down # of words to add
		BRNE	Line2					; if not done loop

		rcall		LCDWrite			; write both lines of the LCD


		; Restore variables by popping them from the stack,
		; in reverse order
		pop		YH
		pop		YL
		pop		ZH
		pop		ZL
		pop		count
		pop		mpr

		ret						; End a function with RET


;-----------------------------------------------------------
; sub: ButtonPD0
; Desc: When you press PD0: Displays (Hello, World) on the first line of the LCD, 
;		and my name ”Hao Truong” on the second line of the screen.
;-----------------------------------------------------------
ButtonPD1:							; Begin a function with a label
		; Save variables by pushing them to the stack
		push	mpr				; save mpr register
		push	count1			; save count1
		push	ZL				; save ZL
		push	ZH				; save ZH
		push	YL				; save YL
		push	YH				; save YH

		; Execute the function here
		; Move strings from Program Memory to Data Memory
		; move first string from Program Memory to Data Memory
		ldi		ZL, low(STRING_END << 1)		; extract low byte of STRING_BEG
		ldi		ZH, high(STRING_END << 1)		; extract high byte of STRING_BEG
												; Z now points to first char (H)				
		ldi		YL, $00							; Y <- data memory address of character destination (line 1)
		ldi		YH, $01
		clr		count1
		ldi		count1, 12						; used to count down chars, first line contains 10 letters
Loop:
		lpm		mpr, Z+					; load Z to mpr
		st		Y+, mpr					; load mpr to Y
		dec		count1					; count down # of words to add
		BRNE	Loop					; if not done loop

		; Move second string from Program Memory to Data Memory
		ldi		ZL, low(STRING_BEG << 1)		; extract low byte of STRING_BEG
		ldi		ZH, high(STRING_BEG << 1)		; extract high byte of STRING_BEG
												; Z now points to first char (H)				
		ldi		YL, $10							; Y <- data memory address of character destination (line 2)
		ldi		YH, $01
		clr		count1
		ldi		count1, 10						; used to count down chars, first line contains 12 letters
Loop1:
		lpm		mpr, Z+					; load Z to mpr
		st		Y+, mpr					; load mpr to Y
		dec		count1					; count down # of words to add
		BRNE	Loop1					; if not done loop

		rcall		LCDWrite			; write both lines of the LCD


		; Restore variables by popping them from the stack,
		; in reverse order
		pop		YH
		pop		YL
		pop		ZH
		pop		ZL
		pop		count
		pop		mpr

		ret						; End a function with RET



;***********************************************************
;*	Stored Program Data
;***********************************************************

;-----------------------------------------------------------
; An example of storing a string. Note the labels before and
; after the .DB directive; these can help to access the data
;-----------------------------------------------------------
STRING_BEG:
.DB		"Hao Truong"		; Declaring data in ProgMem
STRING_END:
.DB		"Hello, World"

;***********************************************************
;*	Additional Program Includes
;***********************************************************
.include "LCDDriver.asm"		; Include the LCD Driver
