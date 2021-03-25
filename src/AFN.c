#include <string.h>
#include "AFN.h"

// *** new_automata functions *** //
q_t** new_q();
sigma_t** new_sigma(char*, char*, char*);
delta_t* new_delta(int, int, q_t**, sigma_t**);

// *** verify_word functions *** //
int verify_entry(char, sigma_t**, int);


// creates the automata and sets its informations
AFN_t* new_automata(char* first, char* last, char* registration){

	// creates the afn
	AFN_t* afn;
	afn = (AFN_t*) malloc (sizeof(AFN_t));

	// sets Q and q_size
	afn->q = new_q();
	afn->q_size = 7; // its fix for that sopecific automata

	// creates sigma using information in init and sets sigma_size
	afn->sigma = new_sigma(first, last, registration);
	afn->sigma_size = 6; // fix for that specific automata

	// creates a graph that represents the delta rules
	afn->delta = new_delta(afn->q_size, afn->sigma_size, afn->q, afn->sigma);

	return afn;
}

// prints the automata in "human vision"
void print_afn(AFN_t* afn){

	system("clear||cls");

	printf("###################################\n");

	printf("M = (Q, Sigma, Delta, q0, qf)\n");

	printf("->Q = { ");
	for(int i = 0; i < afn->q_size; i++)
		printf("q%d ", i);
	printf("}\n");

	printf("->Sigma = { ");
	for(int i = 0; i < afn->sigma_size; i++)
		printf("%c ", afn->sigma[i]->value);
	printf("}\n");

	printf("->Delta = { \n");
	for(int i = 0; i < afn->q_size; i++)
		for(int j = 0; j < afn->sigma_size; j++)
			if(afn->delta->table[i][j] != -1)
				printf("\t-delta(q%d, %c) -> q%d\n",
				i, afn->sigma[j]->value, afn->delta->table[i][j]);
	printf("}\n");

	printf("->q0 = q0\n");

	printf("->qf = { ");
	for(int i = 0; i < afn->q_size; i++)
		if(afn->q[i]->final)
			printf("q%d ", i);
	printf("}\n");

	printf("###################################\n");
}

// verifies and validates (or not) the entry word
bool verify_word(char* word, AFN_t* afn){

	// gets Q and sigma size, for easier reading
	int q_s = afn->q_size;
	int s_s = afn->sigma_size;

	int q[q_s];		// representation of the current Qs
	int q_aux[q_s];	// represents Qs destinations

	// gets the delta graph. Easier reading
	int** delta = afn->delta->table;

	// sets q0 as current state
	// if a state is activated, its value is > 0
	for(int i = 0; i < q_s; i++)
		q[i] = 0;
	q[0] = 1;

	char c;		// reads chars from word
	int index;	// destination state after the current transition

	// goest through the current word
	for(int i = 0; i < strlen(word); i++){

		c = word[i];
		// prints active states
		printf("\nCurrent: state(s):");
		for(int j = 0; j < q_s; j++)
			if(q[j]) printf(" q%d", j);
		printf(", entry: %c\n", c);

		// verifies if there is any active states
		int sum = 0;
		for(int j = 0; j < q_s; j++)
			sum += q[j];

		// stop if there is no active state
		if(!sum){
			printf("-ERROR: No active state!!\n");
			return false;
		}

		// verify if entry belongs to sigma or stops
		if(!verify_entry(c, afn->sigma, s_s)){
			printf("-ERROR: Entry doesnt belong to Sigma!!\n");
			return false;
		}

		// clears the destination states array
		for(int j = 0; j < q_s; j++)
			q_aux[j] = 0;

		// goes through current states
		for(int m = 0; m < q_s; m++){
			//if its active
			if(q[m]){
				//goes through signma
				for(int n = 0; n < s_s; n++){
					// if current sigma = current entry
					if(afn->sigma[n]->value == c){
						// gets the delta rule from current (state,entry)=destiny
						index = delta[m][n];
						// verifies if theres a destiny state
						if(index != -1){
							// saves destiny in the array
							q_aux[index]++;
							printf("-delta(q%d, %c) -> q%d\n", m, c, index);
						}
					}
				}
			}
		}

	// sets destinies as current states
	for(int j = 0; j < q_s; j++)
		q[j] = q_aux[j];
	}

	// checks if theres final state(s) and returns
	for(int j = 0; j < q_s; j++)
		if(q[j] && afn->q[j]->final)
			return true;

	printf("-Reached the end of the word, but state isnt final!!\n");
	return false;
}


// *** verify_word functions *** //

// entry belongs to delta? true : false
int verify_entry(char c, sigma_t** sigma, int sigma_size){

	for(int i = 0; i < sigma_size; i++)
		if(sigma[i]->value == c)
			return 1;

	return 0;
}


// *** new_automata functions *** //

// allocs Q and sets final states
q_t** new_q(){

	q_t** q = (q_t**) malloc (7 * sizeof(q_t*));
	for(int i = 0; i < 7; i++)
		q[i] = (q_t*) malloc (sizeof(q_t));

	for(int i = 0; i < 7; i++)
		q[i]->final = false;

	// in that specific machine, q6 is the only final starte
	q[6]->final = true;

	return q;
}

// allocs sigma and gets its values
sigma_t** new_sigma(char* first, char* last, char* registration){

	int value;	// used to convert int to char

	sigma_t** sigma = (sigma_t**) malloc (6 * sizeof(sigma_t*));
	for(int i = 0; i < 6; i++)
		sigma[i] = (sigma_t*) malloc (sizeof(sigma_t));

	// sigma = [x1, x2, d2, d9, l1, l2]

	value = strlen(first);	// first name size
	sigma[0]->label = "x1";
	sigma[0]->value = value + '0';	// converts int in char based on ASCII

	value = strlen(last);	// second name size
	sigma[1]->label = "x2";
	sigma[1]->value = value + '0';

	sigma[2]->label = "d2";	// 2nd letter from registration
	sigma[2]->value = registration[1];

	sigma[3]->label = "d9";	// 9th letter from registration
	sigma[3]->value = registration[8];

	sigma[4]->label = "l1";	// 1st letter from 1st name
	sigma[4]->value = first[0];

	sigma[5]->label = "l2";	// 2nd letter from 1st name
	sigma[5]->value = first[1];

	return sigma;
}

// allocs a graph that represents delta rules
delta_t* new_delta(int q_size, int sigma_size, q_t** q, sigma_t** sigma){

	int** matriz = (int**) malloc (q_size * sizeof(int*));
	for(int i = 0; i < q_size; i++)
		matriz[i] = (int*) malloc (sigma_size * sizeof(int));

	// the graph is set as if there is no rules.
	// -1 means that there are no rule from current (state,entry)
	for(int i = 0; i < q_size; i ++)
		for(int j = 0; j < sigma_size; j++)
			matriz[i][j] = -1;

	// Q = q[0, 1, 2, 3, 4, 5, 6]
	// sigma = [x1, x2, d2, d9, l1, l2]

	// matriz 1st prosition represents Q
	// 2nd position represents sigma

	matriz[0][0] = 1;	// q0,x1 -> q1

	matriz[1][2] = 2;	// q1,d2 -> q2
	matriz[1][3] = 3;	// q1,d9 -> q3

	matriz[2][4] = 4;	// q2,l1 -> q4

	matriz[3][5] = 5;	// q3,l2 -> q5

	matriz[4][1] = 6;	// q4,x2 -> q6
	matriz[4][2] = 2;	// q4,d2 -> q2
	matriz[4][3] = 3;	// q4,d9 -> q3

	matriz[5][1] = 6;	// q5,x2 -> q6
	matriz[5][3] = 3;	// q5,d9 -> q3
	matriz[5][2] = 2;	// q5,d2 -> q2

	delta_t* delta = (delta_t*) malloc (sizeof(delta_t));
	delta->table = matriz;

	return delta;
}
