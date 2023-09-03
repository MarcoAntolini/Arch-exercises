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

#define MAX_LEN 100

void main()
{
	// Variables
	char frase[MAX_LEN] = "Cantami, o Diva, del Pelide Achille l'ira funesta che \
											infiniti addusse lutti agli Achei";
	char parolaMax[MAX_LEN + 1];
	char parolaMin[MAX_LEN + 1];

	// Inline assembly block
	__asm
		{
			xor al, al // azzera il registro al, che conterrà il carattere corrente
			xor edi, edi // azzera il registro edi, che conterrà l'indice della frase
			xor ecx, ecx // azzera il registro ecx, che conterrà la lunghezza della parola più lunga (e in situazioni temporanee anche l'indice della parola)
			mov ebx, MAX_LEN // imposto il registro ebx a MAX_LEN, che conterrà la lunghezza della parola più corta
			xor edx, edx // azzera il registro edx, che conterrà la lunghezza della parola corrente
			xor esi, esi // azzera il registro esi, che conterrà un booleano che indica se ci si trova all'interno di una parola

		loop_start:
			mov al, byte ptr[frase + edi] // carica il carattere corrente

			// se il carattere corrente è 0, allora la frase è finita
			cmp al, 0
			je end_of_phrase

			// se il carattere corrente è uno dei seguenti segni di punteggiatura, allora siamo alla fine di una parola
			cmp al, ' '
			je end_of_word
			cmp al, ','
			je end_of_word
			cmp al, '.'
			je end_of_word
			cmp al, ';'
			je end_of_word
			cmp al, ':'
			je end_of_word
			cmp al, '\''
			je end_of_word
			cmp al, '?'
			je end_of_word
			cmp al, '!'
			je end_of_word
			cmp al, 9
			je end_of_word

			inc edx // incrementa la lunghezza della parola corrente
			test esi, esi // se siamo all'interno di una parola, allora salta a increment, altrimenti salta a change_boolean_word
			jnz increment
			jmp change_boolean_word

		end_of_word:
			test esi, esi // se non siamo all'interno di una parola, allora salta a increment, altrimenti continua
			jz increment

		last_word:
			cmp edx, ecx // se la lunghezza della parola corrente è minore o uguale della lunghezza della parola più lunga, allora salta a continue_checks 
			jle continue_checks

			push edx // sposta sullo stack la lunghezza della parola corrente, per poi ripristinarla
			mov ecx, 0 // azzera l'indice della parola corrente
			
		copy_word_max: // copia la parola corrente in parolaMax
			push edi // sposta sullo stack l'indice della frase, per poi ripristinarlo
			// calcola l'indice della parola corrente e carica il carattere corrente
			sub edi, edx
			add edi, ecx
			mov al, byte ptr[frase + edi]
			pop edi // ripristina l'indice della frase
			mov byte ptr[parolaMax + ecx], al // copia il carattere corrente in parolaMax
			inc ecx // incrementa l'indice della parola corrente
			cmp ecx, edx // se l'indice della parola corrente è minore della lunghezza della parola corrente, allora continua a copiare
			jl copy_word_max
			mov byte ptr[parolaMax + ecx], 0 // aggiunge il carattere nullo alla fine della parola corrente
			pop ecx // ripristina l'indice della parola corrente

		continue_checks:
			cmp edx, ebx // se la lunghezza della parola corrente è maggiore o uguale della lunghezza della parola più corta, allora salta a reset
			jge reset

			push ecx // sposta sullo stack l'indice della parola corrente, per poi ripristinarlo
			mov ecx, 0 // azzera l'indice della parola corrente
			mov ebx, edx // copia la lunghezza della parola corrente in ebx

		copy_word_min: // copia la parola corrente in parolaMin
			push edi // sposta sullo stack l'indice della frase, per poi ripristinarlo
			// calcola l'indice della parola corrente e carica il carattere corrente
			sub edi, edx
			add edi, ecx
			mov al, byte ptr[frase + edi]
			pop edi // ripristina l'indice della frase
			mov byte ptr[parolaMin + ecx], al // copia il carattere corrente in parolaMin
			inc ecx // incrementa l'indice della parola corrente
			cmp ecx, edx // se l'indice della parola corrente è minore della lunghezza della parola corrente, allora continua a copiare
			jl copy_word_min
			mov byte ptr[parolaMin + ecx], 0 // aggiunge il carattere nullo alla fine della parola corrente
			pop ecx // ripristina l'indice della parola corrente

		reset: // resetta le variabili per la prossima parola e salta a increment
			mov esi, 0
			mov edx, 0
			jmp increment

		change_boolean_word: // cambia a true il valore del booleano che indica se ci si trova all'interno di una parola
			mov esi, 1

		increment: // incrementa l'indice della frase e salta a loop_start
			inc edi
			jmp loop_start

		end_of_phrase: // la frase è finita
			test esi, esi // ma se siamo ancora all'interno di una parola, allora salta a last_word
			jnz last_word
		}

	// Print the results
	printf("%s\n%s\n%s\n", frase, parolaMax, parolaMin);
}
