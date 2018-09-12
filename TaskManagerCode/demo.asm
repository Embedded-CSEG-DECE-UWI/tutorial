; *******************************************************************
; A Simple Task Manager v1.00 by Ross Fosler
; This is a small demonstration of the task manager.
; *******************************************************************
; *******************************************************************
	#include <define.inc>; Definitions
	#include PROC_INCLUDE; Processor include file
	#include macroins.inc; Complex p18 instructions
	#include tm_inst.inc; Task Manager instructions
; *******************************************************************
; *******************************************************************
	EXTERN ALT_STATUS, ALT_W0; Must be included
; *******************************************************************
; *******************************************************************
VAR1 UDATA_ACS
; *******************************************************************
; *******************************************************************
; *******************************************************************
INT1 CODE
; *******************************************************************
; This is the interrupt handler for all interrupts other than TIMER0.
; TIMER0 is dedicated to the task manager. Interrupt latency in the
; TM is 8 instruction cycles. The STATUS and WREG is already saved.
InterruptHandler
	; btfsc INTCON, INT0IF, A ; Check INT0
	; goto HandleINT0
	; btfsc INTCON, RBIF, A ; Check interrupt on change
	; goto HandleRBChange
	retfint ; Macro to return from interrupt
	
	GLOBAL InterruptHandler ; This line must be included
; *******************************************************************
; *******************************************************************
STP CODE
; *******************************************************************
; Use this section to include any setup code upon power-up or reset.
Setup
	clrf TRISB
	return
	GLOBAL Setup
; *******************************************************************
; *******************************************************************
TSK1 CODE
; *******************************************************************
; This is a demonstration task. Each task can trigger a task swap by
; using the ’swptsk’ macro. Otherwise, the task manger will
; automatically swap at the end of its cycle.
Task1
	nop
	nop
	btg LATB,5
	nop
	swptsk ; Force the TM to swap
	btg LATB,7
	btg LATB,6
	nop
	swptsk
	bra Task1
	GLOBAL Task1 ; This line must be included
; *******************************************************************
; *******************************************************************
TSK2 CODE
; *******************************************************************
; This is a demonstration task.
Task2
	btg LATB,4
	; swptsk ; Force the TM to swap
	bra Task2
	GLOBAL Task2 ; This line must me included
; *******************************************************************
END
