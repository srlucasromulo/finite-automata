#include <string.h>
#include "AFD.h"

// *** new_automata functions *** //
q_t** new_q();
sigma_t** new_sigma(char*, char*, char*);
delta_t* new_delta(int, int, q_t**, sigma_t**);

// *** verify_word functions *** //
int get_sigma_index(char, sigma_t**, int);


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

bool verify_word(char* word, AFD_t* afd){

	int q_aux, q = 0;	// next q, current q (starts in q0)
	int index;

	int** delta = afd->delta->table;

	char c;

	for(int i = 0; i < strlen(word); i++){

		c = word[i];

		printf("\nCurrent: state: q%d, entry: %c\n", q, c);

		index = get_sigma_index(c, afd->sigma, afd->sigma_size);
		if(index == -1){
			printf("-ERROR:Entry doesnt belong to Sigma!!\n");
			return false;
		}

		printf("INDEX ACHADO: %d <<<<-----\n", index);
		q_aux = delta[q][index];
		if(q_aux == -1){
			printf("-ERROR:Undefined production!!\n");
			return false;
		}

		printf("-delta(q%d, %c) -> q%d\n", q, c, q_aux);

		q = q_aux;
	}

	if(!afd->q[q]->final)
		printf("-Reached the end of the word, but state isnt final!!\n");

	return afd->q[q]->final;
}

void print_afd(AFD_t* afd){

	system("clear||cls");

	printf("###################################\n");

	printf("M = (Q, Sigma, Delta, q0, qf)\n");

	printf("->Q = { ");
	for(int i = 0; i < afd->q_size; i++)
		printf("q%d ", i);
	printf("}\n");

	printf("->Sigma = { ");
	for(int i = 0; i < afd->sigma_size; i++)
		printf("%c ", afd->sigma[i]->value);
	printf("}\n");

	printf("->Delta = { \n");
	for(int i = 0; i < afd->q_size; i++)
		for(int j = 0; j < afd->sigma_size; j++)
			if(afd->delta->table[i][j] != -1)
				printf("\t-delta(q%d, %c) -> q%d\n",
				i, afd->sigma[j]->value, afd->delta->table[i][j]);
	printf("}\n");

	printf("->q0 = q0\n");

	printf("->qf = { ");
	for(int i = 0; i < afd->q_size; i++)
		if(afd->q[i]->final)
			printf("q%d ", i);
	printf("}\n");



	printf("###################################\n");

}


// *** verify_word functions *** ///
int get_sigma_index(char c, sigma_t** sigma, int sigma_size){

	for(int i = 0; i < sigma_size; i++)
		if(sigma[i]->value == c)
			return i;

	return -1;
}


// *** new_automata functions *** //
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



