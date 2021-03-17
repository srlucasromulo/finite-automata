#include "AFD.h"

q_t** new_q();
sigma_t* new_sigma(char*, char*, char*);

AFD_t* new_automata(char* first, char* last, char* registration){

	AFD_t* afd;
	afd = (AFD_t*) malloc (sizeof(AFD_t));

	afd->q = new_q();

	for(int i = 0; i < 7; i++)
		printf(afd->q[i]->final ? "true\n" : "false\n");

//	afd->sigma = new_sigma(first, last, registration);



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


sigma_t* new_sigma(char* first, char* last, char* registration){

	sigma_t* sigma;




}





