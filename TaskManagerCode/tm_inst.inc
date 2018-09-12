; *****************************************************************;
; ;
; A Simple Task Manager v1.00 by Ross Fosler ;
; *****************************************************************;
; *******************************************************************
	#include <define.inc>
	#include PROC_INCLUDE ; Processor include file
	#include <macroins.inc>
; *******************************************************************
; *******************************************************************
_TM_SCRATCH UDATA
TEMP res 1
; *******************************************************************
; *******************************************************************
 IFDEF INT_HAND_NAME
	EXTERN INT_HAND_NAME
 ENDIF
 IFDEF SAVE_BSR
	EXTERN BACKUP_BSR
 ENDIF
 IFDEF SAVE_FSR0L
	EXTERN BACKUP_FSR0L
 ENDIF
 IFDEF SAVE_FSR0H
	EXTERN BACKUP_FSR0H
 ENDIF
 IFDEF SAVE_FSR1L
	EXTERN BACKUP_FSR1L
 ENDIF
 IFDEF SAVE_FSR1H
	EXTERN BACKUP_FSR1H
 ENDIF
 IFDEF SAVE_PRODH
	EXTERN BACKUP_PRODH
 ENDIF
 IFDEF SAVE_PRODL
	EXTERN BACKUP_PRODL
 ENDIF
 IFDEF SAVE_FSR2L
	EXTERN BACKUP_FSR2L
	EXTERN ALT_FSR2L
 ENDIF
 IFDEF SAVE_FSR2H
	EXTERN BACKUP_FSR2H
	EXTERN ALT_FSR2H
 ENDIF
 IFDEF SAVE_TBLPTRU
	EXTERN BACKUP_TBLPTRU
 ENDIF
 IFDEF SAVE_TBLPTRH
	EXTERN BACKUP_TBLPTRH
 ENDIF
 IFDEF SAVE_TBLPTRL
	EXTERN BACKUP_TBLPTRL
 ENDIF
 IFDEF SAVE_TABLAT
	EXTERN BACKUP_TABLAT
 ENDIF
	EXTERN TASK_TABLE, TASK_INFO_TABLE
	EXTERN BACKUP_WREG, BACKUP_STATUS
	EXTERN TASK_POINTER, TABLE_POINTER, TASK_COUNTER
	EXTERN TASK_COMMAND, TASK_BUFFER
	EXTERN TASK_COMMAND, TASK_BUFFER, ALT_W0
	EXTERN ALT_STATUS
; *******************************************************************

; *******************************************************************
 IFDEF LFSR_BUG ; Macro to work around lfsr bug
ldfsr2 macro JUNK, MYLIT
	movff WREG, TEMP
	movlw high MYLIT
	movwf FSR2H
	movlw low MYLIT
	movwf FSR2L
	movff TEMP, WREG
	endm
 ELSE
	ldfsr2 macro _FSR, _REG
	lfsr _FSR, _REG
	endm
 ENDIF
; *******************************************************************

; *******************************************************************
TM CODE
; *******************************************************************
TaskManager
	GLOBAL TaskManager
; *** Stop the Timer **************************************
	bcf T0CON, TMR0ON, A ; Stop the timer
; *********************************************************

; *** Save Important Data *********************************
	movwf ALT_W0, A ; Copy WREG
	movff STATUS, ALT_STATUS ; Copy STATUS

; *** Test the Interrupt Source ***
 IFDEF INT_HAND_NAME
	btfss INTCON, TMR0IF, A
	goto NT_HAND_NAME ; Check other interrupt sources
 ENDIF
; *********************************
	movf TABLE_POINTER, W, A

 IFDEF SAVE_FSR2L
	movff FSR2L, ALT_FSR2L
 ENDIF

 IFDEF SAVE_FSR2H
	movff FSR2H, ALT_FSR2H
 ENDIF
	ldfsr2 2, TASK_TABLE ; Save pointer to TOS
	movff STKPTR, PLUSW2
	ldfsr2 2, BACKUP_WREG ; Save WREG
	movff ALT_W0, PLUSW2
	ldfsr2 2, BACKUP_STATUS ; Save STATUS
	movff ALT_STATUS, PLUSW2

 IFDEF SAVE_BSR
	ldfsr2 2, BACKUP_BSR ; Save BSR
	movff BSR, PLUSW2
 ENDIF

 IFDEF SAVE_FSR0H
	ldfsr2 2, BACKUP_FSR0H ; Save FSR0H
	movff FSR0H, PLUSW2
 ENDIF

 IFDEF SAVE_FSR0L
	ldfsr2 2, BACKUP_FSR0L ; Save FSR0L
	movff FSR0L, PLUSW2
 ENDIF

 IFDEF SAVE_FSR1H
	ldfsr2 2, BACKUP_FSR1H ; Save FSR1H
	movff FSR1H, PLUSW2
 ENDIF

 IFDEF SAVE_FSR1L
	ldfsr2 2, BACKUP_FSR1L ; Save FSR1L
	movff FSR1L, PLUSW2
 ENDIF

 IFDEF SAVE_FSR2H
	ldfsr2 2, BACKUP_FSR2H ; Save FSR2H
	movff ALT_FSR2H, PLUSW2
 ENDIF

 IFDEF SAVE_FSR2L
	ldfsr2 2, BACKUP_FSR2L ; Save FSR2L
	movff ALT_FSR2L, PLUSW2
 ENDIF

 IFDEF SAVE_PRODH
	ldfsr2 2, BACKUP_PRODH ; Save PRODH
	movff PRODH, PLUSW2
 ENDIF

 IFDEF SAVE_PRODL
	ldfsr2 2, BACKUP_PRODL ; Save PRODL
	movff PRODL, PLUSW2
 ENDIF

 IFDEF SAVE_TBLPTRU
	ldfsr2 2, BACKUP_TBLPTRU ; Save TBLPTRU
	movff TBLPTRU, PLUSW2
 ENDIF

 IFDEF SAVE_TBLPTRH
	ldfsr2 2, BACKUP_TBLPTRH ; Save TBLPTRH
	movff TBLPTRH, PLUSW2
 ENDIF

 IFDEF SAVE_TBLPTRL
	ldfsr2 2, BACKUP_TBLPTRL ; Save TBLPTRL
	movff TBLPTRL, PLUSW2
 ENDIF

 IFDEF SAVE_TABLAT
	ldfsr2 2, BACKUP_TABLAT ; Save TABLAT
	movff TABLAT, PLUSW2
 ENDIF

; *********************************************************

; *** Increment the Task Pointer **************************
IncrementTaskPointer
	incf TASK_POINTER, F, A ; Increment the task pointer
; *********************************************************
; *** Reset Interrupt Flag ********************************
	bcf INTCON, TMR0IF, A ; Clear interrupt
; *********************************************************
; *** Test the Task Pointer *******************************
	movf TASK_COUNTER, W, A
	cpfslt TASK_POINTER, A ; Is the pointer lt the counter?
	clrf TASK_POINTER, A ; No, reset the pointer
; *********************************************************
; *** Find the task ***************************************
	clrf WREG2, A
	ldfsr2 2, TASK_INFO_TABLE; Set up pointer to priority table
TstTsk movlw 0x03
	andwf POSTINC2, W, A ; Mask off upper 6 bits, get task no#
	cpfseq TASK_POINTER, A ; Does the task numbers match?
	bra NxtTsk ; No

	movff WREG2, TABLE_POINTER ; Yes, store pointer

NxtTsk incf WREG2, F, A ; Check the next task
	movlw 0x04
	cpfseq WREG2, A ; Is the last possible task checked?
	bra TstTsk

	movf TABLE_POINTER, W, A
; *********************************************************

; *** Set the Priority ************************************
SetPriorityTimer
	ldfsr2 2, TASK_INFO_TABLE ; Set up pointer to priority table
	movf PLUSW2, W, A
	andlw 0xFC ; Pull out priority bits
	bz IncrimentTaskPointer ; Goto next task if no priority
	comf WREG, W, A ; Invert and set TMR0
	bcf WREG, 0, A
	bcf WREG, 1, A
	movwf TMR0L, A
; *********************************************************

; *** Restore the Saved data ******************************
RecallSavedData
	GLOBAL RecallSavedData
	movf TABLE_POINTER, W, A
	ldfsr2 2, TASK_TABLE ; Restore pointer to TOS
	movff PLUSW2, STKPTR
	ldfsr2 2, BACKUP_WREG ; Restore WREG
	movff PLUSW2, ALT_W0
	ldfsr2 2, BACKUP_STATUS ; Restore STATUS
	movff PLUSW2, STATUS

 IFDEF SAVE_BSR
	ldfsr2 2, BACKUP_BSR ; Restore BSR
	movff PLUSW2, BSR
 ENDIF

 IFDEF SAVE_FSR0H
	ldfsr2 2, BACKUP_FSR0H ; Restore FSR0H
	movff PLUSW2, FSR0H
 ENDIF

 IFDEF SAVE_FSR0L
	ldfsr2 2, BACKUP_FSR0L ; Restore FSR0L
	movff PLUSW2, FSR0L
 ENDIF

 IFDEF SAVE_FSR1H
	ldfsr2 2, BACKUP_FSR1H ; Restore FSR1H
	movff PLUSW2, FSR1H
 ENDIF

 IFDEF SAVE_FSR1L
	ldfsr2 2, BACKUP_FSR1L ; Restore FSR1L
	movff PLUSW2, FSR1L
 ENDIF

 IFDEF SAVE_FSR2H
	ldfsr2 2, BACKUP_FSR2H ; Restore FSR2H
	movff PLUSW2, ALT_FSR2H
 ENDIF

 IFDEF SAVE_FSR2L
	ldfsr2 2, BACKUP_FSR2L ; Restore FSR2L
	movff PLUSW2, ALT_FSR2L
 ENDIF

 IFDEF SAVE_PRODH
	ldfsr2 2, BACKUP_PRODH ; Restore PRODH
	movff PLUSW2, PRODH
 ENDIF

 IFDEF SAVE_PRODL
	ldfsr2 2, BACKUP_PRODL ; Restore PRODL
	movff PLUSW2, PRODL
 ENDIF

 IFDEF SAVE_TBLPTRU
	ldfsr2 2, BACKUP_TBLPTRU ; Restore TBLPTRU
	movff PLUSW2, TBLPTRU
 ENDIF

 IFDEF SAVE_TBLPTRH
	ldfsr2 2, BACKUP_TBLPTRH ; Restore TBLPTRH
	movff PLUSW2, TBLPTRH
 ENDIF

 IFDEF SAVE_TBLPTRL
	ldfsr2 2, BACKUP_TBLPTRL ; Restore TBLPTRL
	movff PLUSW2, TBLPTRL
 ENDIF

 IFDEF SAVE_TABLAT
	ldfsr2 2, BACKUP_TABLAT ; Restore TABLAT
	movff PLUSW2, TABLAT
 ENDIF

 IFDEF SAVE_FSR2H
	movff ALT_FSR2H, FSR2H
 ENDIF

 IFDEF SAVE_FSR2L
	movff ALT_FSR2L, FSR2L
 ENDIF
	movff ALT_W0, WREG
; *********************************************************

; *** Start the Timer *************************************
	bsf T0CON, TMR0ON, A ; Start the timer
; *********************************************************
	retfie 0
; *******************************************************************
	END