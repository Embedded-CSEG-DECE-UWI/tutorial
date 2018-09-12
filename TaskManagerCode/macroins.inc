; *****************************************************************************
; Some common macros for PIC18 by Ross Fosler
; v1.00 01/05/01
;
; brset MYFILE, MYBIT, MYBANK, WHERE; Bit tests
; brclr MYFILE, MYBIT, MYBANK, WHERE
;
; cffblt MYFILE1, MYFILE2, MYBANK, WHERE; Compare file w/ file
; cffbgt MYFILE1, MYFILE2, MYBANK, WHERE
; cffbeq MYFILE1, MYFILE2, MYBANK, WHERE
; cffbne MYFILE1, MYFILE2, MYBANK, WHERE
;
; cflblt MYFILE1, MYLIT1, MYBANK, WHERE; Compare file w/ literal
; cflbgt MYFILE1, MYLIT1, MYBANK, WHERE
; cflbeq MYFILE1, MYLIT1, MYBANK, WHERE
; cflbne MYFILE1, MYLIT1, MYBANK, WHERE
;
; movlf MYLIT, MYFILE, MYBANK ; Move literal to file
; addff MYFILE1, MYFILE2, MYDIRECTION, MYBANK ; Add file to file
; addfl MYFILE1, MYLIT1, MYDIRECTION, MYBANK ; Add file to literal
; andff MYFILE1, MYFILE2, MYDIRECTION, MYBANK ; And file to file
; andfl MYFILE1, MYLIT1, MYDIRECTION, MYBANK ; And file to literal
; iorff MYFILE1, MYFILE2, MYDIRECTION, MYBANK ; Ior file to file
; iorfl MYFILE1, MYLIT1, MYDIRECTION, MYBANK ; Ior file to literal
; xorff MYFILE1, MYFILE2, MYDIRECTION, MYBANK ; Xor file to file
; xorfl MYFILE1, MYLIT1, MYDIRECTION, MYBANK ; Xor file to literal
;
; *****************************************************************************
; *****************************************************************************
W equ 0 ; To WREG
F equ 1 ; To FILE
A equ 0 ; Use Access Bank
B equ 1 ; Use BSR
WREG2 equ PRODH
WREG3 equ PRODL
; *****************************************************************************
; *** Common Branch Instructions **********************************************
; Notes:W is destroyed except for brset and brclr.
; All branching is limited to 7 bits in either direction of the
; PC, thus these branch instructions cannot reach all memory.
; *****************************************************************
; *** BRanch if bit is SET
brset macro MYFILE, MYBIT, MYBANK, WHERE
btfsc MYFILE, MYBIT, MYBANK
bra WHERE
endm
; *** BRanch if bit is CLeaR
brclr macro MYFILE, MYBIT, MYBANK, WHERE
btfss MYFILE, MYBIT, MYBANK
bra WHERE
endm
; *****************************************************************
; *****************************************************************
; *** Compare File with File and Branch if Less Than
; *** IF F1 < F2 THEN branch 
cffblt macro MYFILE1, MYFILE2, MYBANK, WHERE
movf MYFILE2, W, MYBANK
subwf MYFILE1, W, MYBANK
bn WHERE
endm
; *** Compare File with File and Branch if Greater Than
; *** IF F1 > F2 THEN branch
cffbgt macro MYFILE1, MYFILE2, MYBANK, WHERE
movf MYFILE1, W, MYBANK
subwf MYFILE2, W, MYBANK
bn WHERE
endm
; *** Compare File with File and Branch if EQual
; *** IF F1 = F2 THEN branch
cffbeq macro MYFILE1, MYFILE2, MYBANK, WHERE
movf MYFILE1, W, MYBANK
subwf MYFILE2, W, MYBANK
bz WHERE
endm
; *** Compare File with File and Branch if Not Equal
; *** IF F1 <> F2 THEN branch
cffbne macro MYFILE1, MYFILE2, MYBANK, WHERE
movf MYFILE1, W, MYBANK
subwf MYFILE2, W, MYBANK
bnz WHERE
endm
; *****************************************************************
; *****************************************************************
; *** Compare File with Literal and Branch if Less Than
; *** IF F1 < L1 THEN branch
cflblt macro MYFILE1, MYLIT1, MYBANK, WHERE
movlw MYLIT1
subwf MYFILE1, W, MYBANK
bn WHERE
endm
; *** Compare File with Literal and Branch if Greater Than
; *** IF F1 > L1 THEN branch
cflbgt macro MYFILE1, MYLIT1, MYBANK, WHERE
movf MYFILE1, W, MYBANK
sublw MYLIT1
bn WHERE
endm
; *** Compare File with Literal and Branch if EQual
; *** IF F1 = L1 THEN branch
cflbeq macro MYFILE1, MYLIT1, MYBANK, WHERE
movf MYFILE1, W, MYBANK
sublw MYLIT1
bz WHERE
endm
; *** Compare File with Literal and Branch if Not Equal
; *** IF F1 <> L1 THEN branch
cflbne macro MYFILE1, MYLIT1, MYBANK, WHERE
movf MYFILE1, W, MYBANK
sublw MYLIT1
bnz WHERE
endm
; *****************************************************************
; *****************************************************************************
; *** Other Instructions ******************************************************
; *** MOVe Literal to File ****************************************
; Notes:W is destroyed in this macro.
movlf macro MYLIT, MYFILE, MYBANK
movlw MYLIT
movwf MYFILE, MYBANK
endm
; *****************************************************************
; *** ADD File to File ********************************************
; Notes:Direction selects either the WREG or FILE1.
; W is destroyed in this macro.
addff macro MYFILE1, MYFILE2, MYDIRECTION, MYBANK
movf MYFILE2, W, MYBANK
addwf MYFILE1, MYDIRECTION, MYBANK
endm
; *****************************************************************
; *** ADD File to Literal *****************************************
; Notes:Direction selects either the WREG or FILE1.
; W is destroyed in this macro.
addfl macro MYFILE1, MYLIT1, MYDIRECTION, MYBANK
movlw MYLIT1
addwf MYFILE1, MYDIRECTION, MYBANK
endm
; *****************************************************************
; *** AND File to File ********************************************
; Notes:Direction selects either the WREG or FILE1.
; W is destroyed in this macro.
andff macro MYFILE1, MYFILE2, MYDIRECTION, MYBANK
movf MYFILE2, W, MYBANK
andwf MYFILE1, MYDIRECTION, MYBANK
endm
; *****************************************************************
; *** AND File to Literal *****************************************
; Notes:Direction selects either the WREG or FILE1.
; W is destroyed in this macro.
andfl macro MYFILE1, MYLIT1, MYDIRECTION, MYBANK
movlw MYLIT1
andwf MYFILE1, MYDIRECTION, MYBANK
endm
; *****************************************************************
; *** Inclusive OR File to File ***********************************
; Notes:Direction selects either the WREG or FILE1.
; W is destroyed in this macro.
iorff macro MYFILE1, MYFILE2, MYDIRECTION, MYBANK
movf MYFILE2, W, MYBANK
iorwf MYFILE1, MYDIRECTION, MYBANK
endm
; *****************************************************************
; *** Inclusive OR File to Literal ********************************
; Notes:Direction selects either the WREG or FILE1.
; W is destroyed in this macro.
iorfl macro MYFILE1, MYLIT1, MYDIRECTION, MYBANK
movlw MYLIT1
iorwf MYFILE1, MYDIRECTION, MYBANK
endm
; *****************************************************************
; *** XOR File to File ********************************************
; Notes:Direction selects either the WREG or FILE1.
; W is destroyed in this macro.
xorff macro MYFILE1, MYFILE2, MYDIRECTION, MYBANK
movf MYFILE2, W, MYBANK
xorwf MYFILE1, MYDIRECTION, MYBANK
endm
; *****************************************************************
; *** XOR File to Literal *****************************************
; Notes:Direction selects either the WREG or FILE1.
; W is destroyed in this macro.
xorfl macro MYFILE1, MYLIT1, MYDIRECTION, MYBANK
movlw MYLIT1
xorwf MYFILE1, MYDIRECTION, MYBANK
endm
; *****************************************************************
; *****************************************************************************