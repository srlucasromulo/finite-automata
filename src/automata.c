#include <ctype.h>
#include "AFD.h"

char* get_word(char, FILE*);

int main(int argv, char* argc[]){

	if(argv != 3){
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

	fscanf(file, "%s %s\n", first_name, last_name);
	fscanf(file, "%s\n\n", registration);

	AFD_t* afd;
	afd = new_automata(first_name, last_name, registration);

	char* word;
	word = (char*) malloc (50*sizeof(char));
	do{

		print_afd(afd);

		word = get_word(opt, file);

		if(word){
			printf("Next word: %s! Press ENTER to check it out!!", word);
			getc(stdin);

			printf("\n--->Lets check the word %s:\n", word);
			printf(verify_word(word, afd) ?
				"\n--->Its accepted!!\n\n" : "\n--->Its rejected!!\n\n");
		}
		else printf("\n### Thats enough for today, huh?! Good bye!!\n");

		printf("Press ENTER to continue...");
		getc(stdin);

	}while(word != NULL);

	free(afd);
	fclose(file);
	return 0;
}

char* get_word(char opt, FILE* file){

	char* word;
	word = (char*) malloc (50 * sizeof(char));

	if(opt == 'F'){

		if(!feof(file)){
			fscanf(file, "%s\n", word);
			return word;
		}
	}
	else {

		char yn = '\0';
		while(yn != 'Y' && yn != 'N'){

			printf("Test a word? (y/n) _/>");
			scanf("%c", &yn);
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
