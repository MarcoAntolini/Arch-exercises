#include <stdio.h>

void main()
{

	unsigned short int Mat = 7047;
	unsigned char Vet[100];
	unsigned short Ris1, Ris2, Ris3, Ris4, Ris5;

	__asm
	{
		MOV DX, Mat
		MOV AX, DX
		OR AX, 0FFFFh
		XOR DX, AX
		NEG DX
		NOT DX
		MOV Ris1, DX
		// --------------------------------------
		MOV DX, Mat
		TEST DX, 03h; TEST si comporta come AND, ma non modifica il primo operando
		JNZ L1
		JMP L2
	L1 : NOT DX
		JMP L3
	L2 : NEG DX
	L3 : DEC DX
		XOR DX, 0FFFFh
		MOV Ris2, DX
		// --------------------------------------
		MOV AX, Mat
		MOV BYTE PTR Vet[10], AL
		MOV BYTE PTR Vet[14], 99
		MOV BYTE PTR Vet[18], AH
		MOV BYTE PTR Vet[22], 17
		LEA ESI, Vet
		ADD ESI, 9
		XOR EBX, EBX
		MOV ECX, 4
	L4: XOR BL, [ESI + 1]
		ADD ESI, 4
		LOOP L4
		MOV Ris3, BX
		// --------------------------------------
		MOV AX, Mat
		XOR AH, AH
		XOR BL, BL
		ADD BL, 3
		DIV BL; Divis.senza segno di AX per r / m8: risultato in AL, resto in AH
		MOV Ris4, AX
		// --------------------------------------
		MOV AX, Mat
		AND AL, 73h
		OR AL, 90h
		XOR BL, BL
		SUB BL, 2
		IMUL BL; Moltiplic.con segno di AL per r / m8: ris.in AX
		MOV Ris5, AX

	}

	printf("Ris1 = %X\nRis2 = %X\nRis3 = %X\nRis4 = %X\nRis5 = %X\n", Ris1, Ris2, Ris3, Ris4, Ris5);

}