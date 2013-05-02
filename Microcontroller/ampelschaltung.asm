;Ampelsteuerung: Hauptstraße, Nebenstraße und Fußgänger
;Adresse,Hex-Darstellung des Befehls, Mnemomnic
   	 			;Startadresse
				ORG 01800h
1800 31 F0 1B	LXI SP,01BF0h		;stackpointer mit 1bf0 () laden
1803 3E 80 	 	MVI A,080h			;Einstellung des 8085 (128) ins Register A
1805 D3 83 	 	OUT 083h			;dann an adresse schreiben
   	 
				;alle ampeln auf rot schalten
1807 3E 44 	 	STRG: MVI A,044h	;bitwerte für rot (4h) HS/NS
1809 D3 81 	 	OUT 081h			;setze port b auf rot
180B D3 82 	 	OUT 082h			;setze port c auf rot
180D 3E 55 	 	MVI A,055h			;bitwert für rot (5h) fußgänger
180F D3 80 	 	OUT 080h			;setze port a auf rot
1811 01 02 00	LXI B,0002h			;anzahl durchläufe zeitschleife in registerpaar bc
1814 CD 7A 18	CALL EZEIT			;Zeitschleife aufrufen für 0,5sec
   	 
				;HS gelb/rot
1817 3E 46 	 	MVI A,046h
1819 D3 81 	 	OUT 081h
181B D3 82 	 	OUT 82h
181D 01 02 00	LXI B,0002h			
1820 CD 7A 18	CALL EZEIT			
   	 
				;HS grün
1823 3E 41 	 	MVI A,41h
1825 D3 81 	 	OUT 81h
1827 D3 82 	 	OUT 82h
1829 3E 88 	 	MVI A,088h			;bitwert für grün (8h) fußgängerNS
182B D3 80 	 	OUT 080h			;setze port a auf grün
182D 01 14  0	LXI B,0014h			
1830 CD 7A 18	CALL EZEIT			
   	 
				;HS gelb
1833 3E 42 	 	MVI A,42h
1835 D3 81 	 	OUT 81h
1837 D3 82 	 	OUT 82h
1839 01 04 00	LXI B,0004h			
183C CD 7A 18	CALL EZEIT			
   	 
	 
	 
				;alle rot
183F 3E 44 	 	MVI A,44h
1841 D3 81 	 	OUT 81h
1843 D3 82 	 	OUT 82h
1845 3E 55 	 	MVI A,055h
1847 D3 80 	 	OUT 080h
1849 01 02 00	LXI B,0002h			
184C CD 7A 18	CALL EZEIT			
   	 
				;NS gelb/rot
184F 3E 64 	 	MVI A,64h
1851 D3 81 	 	OUT 81h
1853 D3 82 	 	OUT 82h
1855 01 02 00	LXI B,0002h			
1858 CD 7A 18	CALL EZEIT			
   	 
				;NS grün
185B 3E 14 	 	MVI A,14h
185D D3 81 	 	OUT 81h
185F D3 82 	 	OUT 82h
1861 3E 22 	 	MVI A,022h			;bitwerte für grün (2h) fußgängerHS
1863 D3 80 	 	OUT 080h
1865 01 0A 00	LXI b,000Ah			
1868 CD 7A 18	CALL EZEIT			
   	 
				;NS gelb
186B 3E 24 	 	MVI A,24h
186D D3 81 	 	OUT 81h
186F D3 82 	 	OUT 82h
1871 01 04 00	LXI B,0004h			
1874 CD 7A 18	CALL EZEIT			
   	 
1877 C3 07 018	JMP STRG			;Programm läuft in endlosschleife
				;Ende - Hauptprogramm
   	 
				;Unterprogramm Anzahl Schleifendurchläufe (Registerpaar BC-Zähler)
				;Die durch UZEIT erzeugte Verzögerung wird x-mal durchlaufen
				;x*0.5sec, x ist im Register BC gespeichert
187A F5  	 	EZEIT: PUSH PSW		;Flag-Register (PSW/AF) auf Stack => Hauptprogramms sichern
187B 79  	 	ESCHL: MOV A,C		;lade akkumulator mit anzahl schleifendurchläufen
187C B0  	 	ORA B				;a || b
187D CA 8A 18	JZ EEND				;zeroflag gesetzt?
1880 0B  	 	DCX B				;dekrementiere um 1
1881 11 0B 0C1	LXI D,0C10Bh		;Registerpaar DE mit 49419dez(Anzahl Durchläufe für UZEIT) laden
1884 CD 8C 18	CALL UZEIT			;UZEIT aufrufen (verschachtelte Schleife beginnt hier)
1887 C3 7B 18	JMP ESCHL			;Nach der Rückkehr von UZEIT (Wert im Stackpointer) zum Anfang Schleife
188A F1  	 	EEND: POP PSW		;Flag-Register (PSW) vom Stack entfernen => Zustand Hauptprogramms wiederherstellen
188B C9  	 	RET					;Mit Aufruferadresse+1 im Hauptprogramm fortfahren (Wert im Stackpointer) 
  	 
				;Start - Unterprogramm zur Verzögerung um 0.5sec (Registerpaar DE-Zähler)
				;Funktioniert Analog zum Unterprogramm EZEIT. Entspricht for(i=49419;i==0;i--)
188C F5  	 	UZEIT: PUSH PSW
188D 7B  	 	ZSCHL: MOV A,E
188E B2  	 	ORA D
188F CA 96 18	JZ UPEND
1892 1B  	 	DCX D
1893 C3 8D 18	JMP ZSCHL
1896 F1  	 	UPEND: POP PSW
1897 C9  	 	RET
