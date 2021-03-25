#include <ctype.h>
#include "AFN.h"

char* get_word(char, FILE*);

int main(int argv, char* argc[]){

	if(argv != 2){
			printf("Wrong number of arguments.\n");
		return 1;
	}

	char opt = toupper(argc[1][0]);
	if(opt != 'F' && opt != 'L'){
		printf("Wrong input option. (f/l)\n");
		return 1;
	}

	FILE* file = fopen("init.txt", "r");
	if(!file){
		printf("Couldnt open the file!\n");
		return 1;
	}

	char first_name[25], last_name[25];
	char registration[10];

	// extracts name and registration from file
	fscanf(file, "%s %s\n", first_name, last_name);
	fscanf(file, "%s\n\n", registration);

	// creates a AFN using extracted name and registration
	AFN_t* afn;
	afn = new_automata(first_name, last_name, registration);

	// gets and verifies the words
	char* word;
	word = (char*) malloc (50*sizeof(char));
	do{

		print_afn(afn);

		word = get_word(opt, file);

		if(word){
			printf("Next word: %s! Press ENTER to check it out!!", word);
			getc(stdin);

			printf("\n--->Lets check the word %s:\n\n", word);
			printf(verify_word(word, afn) ?
				"\n--->Its accepted!!\n\n" : "\n--->Its rejected!!\n\n");
		}
		else printf("\n### Thats enough for today, huh?! Good bye!!\n");

		printf("Press ENTER to continue...");
		getc(stdin);

	}while(word != NULL);

	free(afn);
	fclose(file);
	return 0;
}

char* get_word(char opt, FILE* file){

	char* word;
	word = (char*) malloc (50 * sizeof(char));

	// read next word from file
	if(opt == 'F'){

		if(!feof(file)){
			fscanf(file, "%s\n", word);
			return word;
		}
	}
	// reads next word from input
	else {

		char yn = '\0';
		while(yn != 'Y' && yn != 'N'){

			printf("Test a word? (y/n) _/>");
			yn = getc(stdin);
			yn = toupper(yn);

			if(yn != 'Y' && yn != 'N') printf("Wrong input!\n");
		}

		if(yn == 'Y'){
			printf("Type the word.\n_/> ");
			scanf("%s", word);
			return word;
		}
	}

	return NULL;
}
