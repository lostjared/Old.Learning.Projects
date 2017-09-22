#include "input.h"

unsigned int dot = 0;
unsigned long size = 0;
int input_char = 0;
char source[256];
char *inputstr = 0;

char *get_input() {
	FILE *file;
	unsigned long pos = 0;
	file = fopen(source,"r");
	fseek(file,0,SEEK_END);
	size = ftell(file);
	rewind(file);

	inputstr = (char*) malloc (sizeof(char) * size+2);

	while(!feof(file)) {
		inputstr[pos++] = fgetc(file);
	}

	inputstr[pos] = 0;
	fclose(file);
	return inputstr;
}