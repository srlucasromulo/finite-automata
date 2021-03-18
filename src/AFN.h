#ifndef __AFN__
#define __AFN__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct q_t{
	bool final;
} q_t;

typedef struct sigma_t{
	char* label;
	char value;
} sigma_t;

typedef struct delta_t{
	int** table;
} delta_t;

typedef struct AFN_t{
	q_t** q;
	sigma_t** sigma;
	delta_t* delta;
	int q_size, sigma_size;
	//q0 = q[0]
	//qf = any q with the final flag
} AFN_t;


AFN_t* new_automata(char*, char*, char*);
void print_afn(AFN_t*);
bool verify_word(char*, AFN_t*);


#endif
