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
			mov esi, 0 // Inizializza l'indice sorgente (esi) a 0
			mov edi, len // Inizializza l'indice destinazione (edi) a len
			mov ecx, len // Inizializza il contatore (ecx) a len (numero di byte)

		loop_start:
			mov al, vet[esi] // Carica il byte da vet[esi] nel registro al
			xor dl, dl // Azzera il registro dl (sarà usato per costruire il risultato)
			xor ebx, ebx // Azzera il registro ebx (usato come contatore per i bit)
			mov ebx, 8 // Imposta ebx a 8 (numero di bit in un byte)
			
		bit_loop_start:
			rcr al, 1 // Ruota il bit meno significativo di al nel carry (rcr = rotate through carry right)
			rcl dl, 1 // Ruota il carry nel bit più significativo di dl (rcl = rotate through carry left)
			dec ebx // Decrementa il contatore dei bit
			jnz bit_loop_start // Salta a bit_loop_start se ebx non è zero (ancora bit da processare)

			dec edi // Decrementa l'indice di destinazione (edi)
			mov res[edi], dl // Memorizza il byte invertito nel vettore di risultato
			inc esi // Incrementa l'indice sorgente (esi)
			loop loop_start // Ripeti il ciclo fino a quando ecx non è zero
		}

	// Stampa su video
	{
		unsigned int i;
		for (i = 0; i < len; i++)
			printf("res[%2d] = %10d (%08X)\n", i, res[i], res[i]);
	}
}
