/********************************************************************************
 *                                                                              *
 *                   Architetture dei sistemi di Elaborazione                   *
 *                                                                              *
 ********************************************************************************

 Elaborato 3
 Descrizione: Dato un array di BYTE, invertire l’ordine dei bit all’interno
			  dell’array.

 ********************************************************************************/


#include <stdio.h>

void main()
{
	#define MAX_LEN	100

// Input
	unsigned char vet[]={0xAA,0xFC,0x09};			//Array di BYTE
	unsigned int len=sizeof(vet)/sizeof(vet[0]);	// numero di byte in vet	
// Output
	unsigned char res[MAX_LEN];						//Array di BYTE contenente il risultato 

// Blocco assembler
	__asm
	{
	}

// Stampa su video
	{	
		unsigned int i;
		for (i=0;i<len;i++)
			printf("res[%2d] = %10d (%08X)\n",i,res[i],res[i]);
	}
}

