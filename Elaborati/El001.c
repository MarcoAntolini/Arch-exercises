/*********************************************************************************
 *                                                                               *
 *                   Architetture dei sistemi di Elaborazione                    *
 *                                                                               *
 *********************************************************************************

 Elaborato 1
 Descrizione:	Data una stringa C (terminata dal carattere nullo), contenente una
			frase (ossia parole separate da spazi e/o segni di punteggiatura), 
			trovare la parola pi� lunga e la parola pi� corta. In caso di parole
			di uguale lunghezza, considerare la prima da sinistra.
			Le due parole vanno copiate in due array di caratteri come stringhe
			C (terminate dal carattere nullo).
			I segni di punteggiatura da considerare sono: ".,;:'?!"

 **********************************************************************************/


#include <stdio.h>


void main()
{
// Variabili
	#define MAX_LEN	100
	char frase[MAX_LEN] = "Cantami, o Diva, del Pelide Achille l'ira funesta che \
												infiniti addusse lutti agli Achei";
    char parolaMax[MAX_LEN+1];
	char parolaMin[MAX_LEN+1];

// Blocco assembler
	__asm
	{
		mov eax, 0
	}

	// Stampa su video
	printf("%s\n%s\n%s\n",frase,parolaMax,parolaMin);

}

