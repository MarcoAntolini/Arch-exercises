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

#define MAX_LEN 100

void main()
{
	// Input
	unsigned char vet[] = {0xAA, 0xFC, 0x09};		 // Array di BYTE
	unsigned int len = sizeof(vet) / sizeof(vet[0]); // numero di byte in vet
	// Output
	unsigned char res[MAX_LEN]; // Array di BYTE contenente il risultato

	// Blocco assembler
	__asm
		{
			mov esi, 0 // inizializza l'indice di vet[] a 0
			mov edi, len // inizializza l'indice di res[] a len (sarà decrementato)
			mov ecx, len // inizializza il contatore a len (numero di byte)

		main_loop:
			mov al, vet[esi] // carica il byte da vet[esi] nel registro al
			xor dl, dl // azzera il registro dl (sarà usato per costruire il risultato)
			xor ebx, ebx // azzera il registro ebx (usato come contatore per i bit)
			mov ebx, 8 // imposta ebx a 8 (numero di bit in un byte)
			
		bit_loop:
			rcr al, 1 // ruota il bit meno significativo di al nel carry
			rcl dl, 1 // ruota il carry nel bit più significativo di dl
			dec ebx // decrementa il contatore dei bit e continua il ciclo finché non è zero
			jnz bit_loop

			// decrementa l'indice di res[] e memorizza il byte invertito
			dec edi
			mov res[edi], dl
			inc esi // incrementa l'indice di vet[]
			loop main_loop // ripete il ciclo per ogni byte
		}

	// Stampa su video
	{
		unsigned int i;
		for (i = 0; i < len; i++)
			printf("res[%2d] = %10d (%08X)\n", i, res[i], res[i]);
	}
}
