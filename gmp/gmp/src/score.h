
#ifndef __SCORES__H__
#define __SCORES__H__

#include<stdio.h>
#include<memory.h>

typedef struct _Score {
	char name[50];
	int score;
	int clr;
} hscore;


static hscore scores[10];

extern void save_scores();

void init_scores() {

	FILE *fptr;
	unsigned int i;
	memset(&scores, 0, sizeof(scores));
	fptr = fopen("scores.dat", "rb");
	if(!fptr) save_scores();
	fread((char*)&scores, sizeof(scores), 1, fptr);
	fclose(fptr);
}

void save_scores() {

	FILE *fptr;
	unsigned int i;
	fptr = fopen("scores.dat", "wb");
	if(!fptr) return;
	for(i = 0; i < 10; i++) {
	
		fwrite((char*)&scores, sizeof(scores), 1, fptr);
	}
	fclose(fptr);
}

void swap_scores(hscore *h1, hscore *h2) {

	hscore t;
	t = *h2;
	*h2 = *h1;
	*h1 = t;
}

void sort_scores() {

	unsigned int i,z;
	for(i = 0; i <  9; i++) {
		for(z = 0; z < 9; z++) {
			if(scores[z].score < scores[z+1].score) {
				// swap
				swap_scores(&scores[z], &scores[z+1]);
			}
		}
	}

}

void add_new_score(const char *uname, int score, int clr) {

	if(scores[9].score < score) {
		scores[9].score = score;
		scores[9].clr = clr;
		strcpy(scores[9].name, uname);
		// sort
		sort_scores();
	}
}

void print_scores() {
	unsigned int i;
	for(i = 0; i < 10; i++)
		printf("%s: %d, %d\n", scores[i].name, scores[i].score, scores[i].clr);
}
#endif

