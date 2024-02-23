#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kmp.h"

#define BUFF_LEN buffer_length

void kmp_table(char *buffer, const int buffer_length, int *table) {
	int pos = 1;
	int cnd = 0;

	table[0] = -1;

	while(pos < buffer_length) {
		if(buffer[pos] == buffer[cnd])
			table[pos] = table[cnd];
		else {
			table[pos] = cnd;
			while(cnd >= 0 && buffer[pos] != buffer[cnd]) 
				cnd = table[cnd];
		}

		++pos, ++cnd;
	}

	table[pos] = cnd;
}

int *kmp_search(char *pattern, char *buffer, int const buffer_length) {
	int table[1025] = {0};
	int k=0;
	int j=0;

	int *occurences = malloc(sizeof(int) * 124);
	int i=0;

	kmp_table(buffer, buffer_length, table);

	while(j < buffer_length) {
		if(buffer[j] == pattern[k]) {
			++j, ++k;
			if(k == strlen(pattern))
				*occurences++ = j - k, i++;
		}
		else {
			k = table[k];
			if(k<0) ++j, ++k;
		}
		
	}

	return occurences - i;
}
