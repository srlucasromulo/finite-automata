#include <string.h>
#include "AFD.h"

q_t** new_q();
sigma_t** new_sigma(char*, char*, char*);
delta_t* new_delta(int, int, q_t**, sigma_t**);

AFD_t* new_automata(char* first, char* last, char* registration){

	AFD_t* afd;
	afd = (AFD_t*) malloc (sizeof(AFD_t));

	afd->q = new_q();
	afd->q_size = 7; // its fix for that sopecific automata

	afd->sigma = new_sigma(first, last, registration);
	afd->sigma_size = 6; // fix for that specific automata

	afd->delta = new_delta(afd->q_size, afd->sigma_size, afd->q, afd->sigma);

	return afd;
}

q_t** new_q(){

	q_t** q = (q_t**) malloc (7 * sizeof(q_t*));
	for(int i = 0; i < 7; i++)
		q[i] = (q_t*) malloc (sizeof(q_t));

	for(int i = 0; i < 7; i++)
		q[i]->final = false;

	q[6]->final = true;

	return q;
}


sigma_t** new_sigma(char* first, char* last, char* registration){

	int value;

	sigma_t** sigma = (sigma_t**) malloc (6 * sizeof(sigma_t*));
	for(int i = 0; i < 6; i++)
		sigma[i] = (sigma_t*) malloc (sizeof(sigma_t));

	value = strlen(first);
	sigma[0]->label = "x1";
	sigma[0]->value = value + '0';

	value = strlen(last);
	sigma[1]->label = "x2";
	sigma[1]->value = value + '0';

	sigma[2]->label = "d2";
	sigma[2]->value = registration[1];

	sigma[3]->label = "d9";
	sigma[3]->value = registration[8];

	sigma[4]->label = "l1";
	sigma[4]->value = first[0];

	sigma[5]->label = "l2";
	sigma[5]->value = first[1];

	return sigma;
}

delta_t* new_delta(int q_size, int sigma_size, q_t** q, sigma_t** sigma){

	int** matriz = (int**) malloc (q_size * sizeof(int*));
	for(int i = 0; i < q_size; i++)
		matriz[i] = (int*) malloc (sigma_size * sizeof(int));

	for(int i = 0; i < q_size; i ++)
		for(int j = 0; j < sigma_size; j++)
			matriz[i][j] = -1;

	matriz[0][0] = 1;	// q0,x1 -> q1

	matriz[1][2] = 2;	// q1,d2 -> q2
	matriz[1][3] = 3;	// q1,d9 -> q3

	matriz[2][4] = 4;	// q2,l1 -> q4

	matriz[3][5] = 5;	// q3,l2 -> q5

	for(int i = 0; i < 6; i++)
		matriz[4][i] = 1;	// q4,(E-x2) -> q1
	matriz[4][1] = 6;		// q4,x2 -> q6

	for(int i = 0; i < 6; i++)
		matriz[5][i] = 1;	// q5,(E-x2) -> q1
	matriz[5][1] = 6;		// q5,x2 -> q6

	delta_t* delta = (delta_t*) malloc (sizeof(delta_t));
	delta->table = matriz;

	return delta;
}



