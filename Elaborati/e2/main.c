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
	int successione[50]; // Vettore in cui mettere i primi n termini della successione di Fibonacci

	// Blocco Assembler
	__asm
		{
			mov ecx, n // carica il valore di n nel registro ecx (contatore)
			inc ecx // incrementa ecx di 1 per gestire n termini
			xor eax, eax // azzera il registro eax (contiene il termine attuale)
			mov ebx, 1 // carica 1 nel registro ebx (contiene il termine precedente)
			xor edx, edx // azzera il registro edx (usato per lo scambio temporaneo)
			xor esi, esi // azzera il registro esi (usato come indice nel vettore successione)

		loop_start:
			mov successione[esi], eax // memorizza il valore corrente di eax nel vettore successione
			add esi, 4 // incrementa l'indice esi di 4 (4 byte per int)
			mov edx, eax // copia il valore di eax in edx (temporaneo)
			add eax, ebx // aggiunge il valore di ebx a eax (genera il nuovo termine)
			mov ebx, edx // copia il valore originale di eax (precedente) in ebx
			loop loop_start // ripeti il ciclo n volte
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
