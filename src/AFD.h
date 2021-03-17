#ifndef __AFD__
#define __AFD__

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

typedef struct AFD_t{
	q_t** q;
	sigma_t** sigma;
	delta_t* delta;
	int q_size, sigma_size;
	//q0 = q[0]
	//qf = any q with the final flag
} AFD_t;

AFD_t* new_automata(char*, char*, char*);

#endif
