; *****************************************************************
; A Simple Task Manager v1.00 by Ross Fosler
; Variables used for the task manager.
; *****************************************************************
; *******************************************************************
CONSTANT TABLE_DEPTH = 0x04
; *******************************************************************
; *******************************************************************
EXTERN TaskManager
 IFDEF TASK1_NAME ; Include any pre-defined tasks
EXTERN TASK1_NAME
 ENDIF
 IFDEF TASK2_NAME
EXTERN TASK2_NAME
 ENDIF
 IFDEF TASK3_NAME
EXTERN TASK3_NAME
 ENDIF
 IFDEF TASK4_NAME
EXTERN TASK4_NAME
 ENDIF
 IFDEF SETUP_NAME
EXTERN SETUP_NAME
 ENDIF
; *******************************************************************
; *******************************************************************
ACS udata_acs
; *******************************************************************
TASK_POINTER res 1 ; Pointer to running task
TABLE_POINTER res 1 ; Pointer to data tables
TASK_COUNTER res 1 ; Number of tasks
GLOBAL TASK_POINTER, TABLE_POINTER, TASK_COUNTER
ALT_W0 res 1 ; An alternate WREG
ALT_STATUS res 1 ; An alternate STATUS
 IFDEF SAVE_FSR2L ; An alternate FSR2L
ALT_FSR2L res 1
GLOBAL ALT_FSR2L
 ENDIF
 IFDEF SAVE_FSR2H ; An alternate FSR2H
ALT_FSR2H res 1
 GLOBAL ALT_FSR2H
 ENDIF
TASK_COMMAND res 1 ; Register globally available to control
; tasks
TASK_BUFFER res 1 ; Buffer to hold a new task
GLOBAL TASK_COMMAND, TASK_BUFFER, ALT_W0
GLOBAL ALT_STATUS
; *******************************************************************
; *******************************************************************
TBL udata ; Tables
; *******************************************************************
TASK_TABLE res TABLE_DEPTH ; Table for holding pointers
BACKUP_WREG res TABLE_DEPTH
BACKUP_STATUS res TABLE_DEPTH
TASK_INFO_TABLE res TABLE_DEPTH ; Task number and priority table
GLOBAL TASK_TABLE, TASK_INFO_TABLE
GLOBAL BACKUP_WREG, BACKUP_STATUS
 IFDEF SAVE_BSR
BACKUP_BSR res TABLE_DEPTH
GLOBAL BACKUP_BSR
 ENDIF
 IFDEF SAVE_FSR0L
BACKUP_FSR0L res TABLE_DEPTH
GLOBAL BACKUP_FSR0L
 ENDIF
 IFDEF SAVE_FSR0H
BACKUP_FSR0H res TABLE_DEPTH
GLOBAL BACKUP_FSR0H
 ENDIF
 IFDEF SAVE_FSR1L
BACKUP_FSR1L res TABLE_DEPTH
GLOBAL BACKUP_FSR1L
 ENDIF
 IFDEF SAVE_FSR1H
BACKUP_FSR1H res TABLE_DEPTH
GLOBAL BACKUP_FSR1H
 ENDIF
 IFDEF SAVE_PRODH
BACKUP_PRODH res TABLE_DEPTH
GLOBAL BACKUP_PRODH
 ENDIF
 IFDEF SAVE_PRODL
BACKUP_PRODL res TABLE_DEPTH
GLOBAL BACKUP_PRODL
 ENDIF
 IFDEF SAVE_TBLPTRU
BACKUP_TBLPTRU res TABLE_DEPTH
GLOBAL BACKUP_TBLPTRU
 ENDIF
 IFDEF SAVE_TBLPTRH
BACKUP_TBLPTRH res TABLE_DEPTH
GLOBAL BACKUP_TBLPTRH
 ENDIF
 IFDEF SAVE_TBLPTRL
BACKUP_TBLPTRL res TABLE_DEPTH
GLOBAL BACKUP_TBLPTRL
 ENDIF
 IFDEF SAVE_TABLAT
BACKUP_TABLAT res TABLE_DEPTH
GLOBAL BACKUP_TABLAT
 ENDIF
 IFDEF SAVE_FSR2L
BACKUP_FSR2L res TABLE_DEPTH
GLOBAL BACKUP_FSR2L
 ENDIF
 IFDEF SAVE_FSR2H
BACKUP_FSR2H res TABLE_DEPTH
 GLOBAL BACKUP_FSR2H
 ENDIF
; *******************************************************************