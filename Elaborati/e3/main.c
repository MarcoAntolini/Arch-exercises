/********************************************************************************
 *                                                                              *
 *                   Architetture dei sistemi di Elaborazione                   *
 *                                                                              *
 ********************************************************************************

 Elaborato 3
 Descrizione: Dato un array di BYTE, invertire l'ordine dei bit all'interno
			  dell'array.

 ********************************************************************************/


#include <stdio.h>

#define MAX_LEN	100

void main()
{
	// Input
	unsigned char vet[] = { 0xAA, 0xFC, 0x09 };			//Array di BYTE
	unsigned int len = sizeof(vet) / sizeof(vet[0]);	// numero di byte in vet	
	// Output
	unsigned char res[MAX_LEN];						//Array di BYTE contenente il risultato 

	// Blocco assembler
	__asm
	{
		mov esi, 0
		mov edi, len
		mov ecx, len
		
	loop_start:
		mov al, vet[esi]
		xor dl, dl
		xor ebx, ebx
		mov ebx, 8
	bit_loop_start:
		rcr al, 1
		rcl dl, 1
		dec ebx
		jnz bit_loop_start

		dec edi
		mov res[edi], dl
		inc esi
		loop loop_start
	}

	// Stampa su video
	{
		unsigned int i;
		for (i = 0; i < len; i++)
			printf("res[%2d] = %10d (%08X)\n", i, res[i], res[i]);
	}
}

