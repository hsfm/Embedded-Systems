;Versuch 4
;Sende Prompt - empfange Zeichen - ergänze mit Carriage Return und Linefeed - sende zurück
;81h = Schnittstelle/Baustein
;80h = HyperTerminal
;Schnittstelle initialisieren
INIT: PUSH PSW		;ProgramStatusWord (AF-Register) sichern
MVI A,CFh			;Modewort entspricht 1100,1111b
OUT 81h				;Schreibe an Schnittstelle
MVI A,37h			;Commandwort (0011,0111b) alternativ 3Bh
OUT 81h			
POP PSW				;AF-Register wiederherstellen
RET

;Prüfen ob geschrieben werden kann
CHECK: PUSH PSW
NFR: IN 81h			;Schnittstelle lesen (wird in A gespeichert), Wenn zum schreiben freigegeben dann weiter (NichtFrei)
ANI 01h				;AND-Vergleich mit Bitmaske überprüft ob Bit gesetzt (Maske: 0000,0001b)
JZ NFR				;Falls Zeroflag gesetzt springe zurück zu NFR
POP PSW
RET

;prompt senden (=>:)
PRMPT: PUSH PSW		;PROMPT
CALL CHECK
MVI A,3Dh			;schreibe '=' in A
OUT 80h
CALL CHECK
MVI A,3Eh			;schreibe '>' in A
OUT 80h
CALL CHECK
MVI A,3Ah			;schreibe ':' in A
OUT 80h
POP PSW
RET

;Empfangen/lesen
ECHO: PUSH PSW
IN 80h				;von HyperTerminal lesen (wird in A gespeichert)
CALL CHECK
OUT 80h				;Zeichen zurücksenden
CALL CHECK
MVI A,0Dh			;schreibe carriage return
OUT 80h
CALL CHECK
MVI A,0Ah			;schreibe line feed
OUT 80h

;Hauptprogramm
MAIN: LXI SP, 1BF0h	;Stackpointer init
CALL INIT			;INIT aufrufen
RPT: CALL PRMPT
CALL ECHO
JMP RPT
HLT