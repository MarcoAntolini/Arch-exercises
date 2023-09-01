/********************************************************************************
 *                                                                              *
 *                   Architetture dei sistemi di Elaborazione                   *
 *                                                                              *
 ********************************************************************************

 Elaborato 2
 Descrizione: Dato in input un numero naturale n, restituire i primi n termini
			  della successione di Fibonacci.

 ********************************************************************************/

#include <stdio.h>

void main()
{
	// Variabili
	int n = 12;			 // Numero di termini da restituire
	int successione[50]; // Vettore in cui mettere i primi n termini
	// della successione di Fibonacci

	// Blocco Assembler
	__asm
	{
		mov ecx, n
		inc ecx
		xor eax, eax
		mov ebx, 1
		xor edx, edx
		xor esi, esi

	loop_start:
		mov successione[esi], eax
		add esi, 4
		mov edx, eax
		add eax, ebx
		mov ebx, edx
		loop loop_start
	}

	// Stampa su video
	{
		int i;
		for (i = 0; i <= n; i++)
		{
			printf("%d\n", successione[i]);
		}
	}
}
