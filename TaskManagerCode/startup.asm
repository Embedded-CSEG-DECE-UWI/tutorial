; *****************************************************************
;;;
; A Simple Task Manager v1.00 by Ross Fosler ;
; ;
; This is the start-up routine for the task manager.;
; *****************************************************************;
; *******************************************************************
	#include <define.inc>
	#include PROC_INCLUDE ; Processor include file
	#include <var.inc>
	#include <macroins.inc>
; *******************************************************************
TEST CODE 0x00
	bra 0x200
TEST2 CODE 0x08
	bra 0x208
; *******************************************************************
STRT CODE 0x0200
	goto TMSetup
INT CODE 0x0208
	goto TaskManager
; *******************************************************************
; *******************************************************************
STP CODE
; *******************************************************************
;This routine sets up all important registers for PIC OS2 to run
;properly.
TMSetup
 IFDEF SETUP_NAME
	call SETUP_NAME ; Do some user setup
 ENDIF

	movlw TIMER_PRESCALE ; Set Prescaler
	movwf T0CON, A
	bsf T0CON, T08BIT, A ; Force 8-bit mode
	bsf T0CON, TMR0ON, A ; Turn TMR0 on

	clrf TASK_POINTER, A ; Init the important registers
	clrf TABLE_POINTER, A
	clrf TASK_COMMAND, A
	clrf TASK_BUFFER, A
	clrf TASK_COUNTER, A

	movlw TASK1 ; Prime the task table
	movff WREG, TASK_TABLE
	movlw TASK2
	movff WREG, TASK_TABLE + 1
	movlw TASK3
	movff WREG, TASK_TABLE + 2
	movlw TASK4
	movff WREG, TASK_TABLE + 3

 IFDEF TASK1_NAME ; Seed task1
	movff TASK_TABLE, STKPTR
	movlw low TASK1_NAME
	movwf TOSL, A
	movlw high TASK1_NAME
	movwf TOSH, A
	clrf TOSU, A
	incf TASK_COUNTER, F, A
 ENDIF

 IFDEF TASK2_NAME ; Seed task2
	movff TASK_TABLE+1, STKPTR
	movlw low TASK2_NAME
	movwf TOSL, A
	movlw high TASK2_NAME
	movwf TOSH, A
	clrf TOSU, A
	incf TASK_COUNTER, F, A
 ENDIF

 IFDEF TASK3_NAME ; Seed task3
	movff TASK_TABLE+2, STKPTR
	movlw low TASK3_NAME
	movwf TOSL, A
	movlwhigh TASK3_NAME
	movwf TOSH, A
	clrf TOSU, A
	incf TASK_COUNTER, F, A
 ENDIF

 IFDEF TASK4_NAME ; Seed task4
	movff TASK_TABLE+3, STKPTR
	movlw low TASK4_NAME
	movwf TOSL, A
	movlw high TASK4_NAME
	movwf TOSH, A
	clrf TOSU, A
	incf TASK_COUNTER, F, A
 ENDIF

	movlw TASK1 ; Reset the stack pointer
	movwf STKPTR, A
	
	movlw high TASK_INFO_TABLE ; Setup priority
	movwf FSR0H
	movlw low TASK_INFO_TABLE
	movwf FSR0L
	
	movlw ((TASK1_TIME * 4) + 0x00)
	movwf POSTINC0, A
	movlw ((TASK2_TIME * 4) + 0x01)
	movwf POSTINC0, A
	movlw ((TASK3_TIME * 4) + 0x02)
	movwf POSTINC0, A
	movlw ((TASK4_TIME * 4) + 0x03)
	movwf POSTINC0, A
	
	movlw TASK1_TIME ; Init the timer
	comf WREG, W, A
	bcf WREG, 0, A
	bcf WREG, 1, A
	movwf TMR0L, A
	
	bcf RCON, IPEN, A ; No priority levels
	bsf INTCON, TMR0IE, A ; Enable timer 0 interrupt
	bsf INTCON, GIE, A ; Enable global interrupts
	
	return 0
; *******************************************************************
	END