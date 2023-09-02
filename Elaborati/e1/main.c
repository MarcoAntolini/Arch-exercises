/*********************************************************************************
 *                                                                               *
 *                   Architetture dei sistemi di Elaborazione                    *
 *                                                                               *
 *********************************************************************************

 Elaborato 1
 Descrizione:	Data una stringa C (terminata dal carattere nullo), contenente una
			frase (ossia parole separate da spazi e/o segni di punteggiatura),
			trovare la parola più lunga e la parola più corta. In caso di parole
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
	char frase[MAX_LEN] = "Cantami, o Diva, del Pelide Achille l'ira funesta che infiniti addusse lutti agli Achei";
	char parolaMax[MAX_LEN + 1];
	char parolaMin[MAX_LEN + 1];

	// Inline assembly block
	__asm
	{
		xor edi, edi // edi = i
		xor ecx, ecx // ecx = j
		xor al, al // eax = max
		mov ebx, MAX_LEN // ebx = min
		xor edx, edx // edx = len
		xor esi, esi // esi = inWord (0 for false)

	loop_start:
		mov al, byte ptr[frase + edi] // Load the next character into AL

		// Check for end of string
		cmp al, 0
		je done

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

		// It's not a space or punctuation, so it's part of a word
		inc edx // Increment len
		test esi, esi // Test inWord
		jnz increment // Already in a word, continue
		jmp change_in_word // We were not in a word, so mark inWord and reset len

	end_of_word:
		// Not part of a word
		test esi, esi // Test inWord
		jz increment	// Already not in a word, continue
		// We were in a word, so process it
	albero:
		cmp edx, ecx // Compare len with max
		jle not_max	// If len is less than or equal to max, skip
		// Update max and copy the word to parolaMax
		push edx
		mov ecx, 0 // Reset j
		
	copy_word_max:
		push edi
		sub edi, edx
		add edi, ecx

		mov al, byte ptr[frase + edi]
		pop edi
		mov byte ptr[parolaMax + ecx], al
		inc ecx
		cmp ecx, edx
		jl copy_word_max
		mov byte ptr[parolaMax + ecx], 0 // Null - terminate parolaMax
		pop ecx

	not_max:
		cmp edx, ebx // Compare len with min
		jge reset // If len is greater than or equal to min, continue
		// Update min and copy the word to parolaMin
		push ecx
		mov ecx, 0 // Reset j
		mov ebx, edx // Update min with len

	copy_word_min :
		push edi
		sub edi, edx
		add edi, ecx
		mov al, byte ptr[frase + edi]
		pop edi
		mov byte ptr[parolaMin + ecx], al
		inc ecx
		cmp ecx, edx
		jl copy_word_min
		mov byte ptr[parolaMin + ecx], 0 // Null - terminate parolaMin
		pop ecx

	reset:
		mov esi, 0 // Set inWord to false
		mov edx, 0 // Reset len
		jmp increment // Continue

	change_in_word:
		mov esi, 1

	increment:
		inc edi // Increment i
		jmp loop_start // Repeat the loop

	done:
		test esi, esi // Test inWord
		jnz albero
	}

	// Print the results
	printf("%s\n%s\n%s\n", frase, parolaMax, parolaMin);
}
