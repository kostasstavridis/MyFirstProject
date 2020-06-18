#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

#define SIZE 100
typedef struct node {
	
	char *word;
	int sum_skore;
	int num_appearances 	;
	struct node *next;
	struct node *prev;
} nodeT;

typedef struct {
	
	int size;
	int num_entries;
	nodeT *table;

} hashT;

hashT metavliti_prospelasis;


void init_list (nodeT *head) {
	
	
	head -> next = NULL;
	head -> prev = NULL;
	head -> sum_skore = 0;
	head -> num_appearances = 0;
	head -> word = NULL;
	
}

nodeT *add_node (nodeT *head, int skor, char *word1, int num_appearances) {
	
	nodeT *new_node;
	new_node = (nodeT *)malloc(sizeof(nodeT));
	if (new_node == NULL) {
		
		printf("Error allocating memory for new node\n");
		return (NULL);
	}
	
	new_node -> word = (char *)malloc(sizeof(char) * (strlen(word1)+1));
	if ((new_node -> word) == NULL) {
		
		printf("Error allocating memory for new word\n");
		return (NULL);
	}
	
	strcpy(new_node -> word, word1);
	new_node -> sum_skore = skor;
	if (num_appearances == 0) {
		new_node -> num_appearances = 1;
	}
	else {
		new_node -> num_appearances = num_appearances;
	}
	new_node -> next = head -> next;
	new_node -> prev = head;
	new_node -> prev -> next = new_node;
	if ((new_node -> next) != NULL) {
		new_node -> next -> prev = new_node;
	}
	
	new_node -> prev -> num_appearances += 1;
	metavliti_prospelasis.num_entries += 1;
	
	return (head);
}

void print_list (nodeT *head) {
	
	nodeT *current;
	
	for (current = head -> next; current != NULL; current = current -> next) {
		
		if (current -> next == NULL) {
			printf("[ \"%s\" %d %d.00 ]\n", 
			   current -> word, current -> num_appearances, current -> sum_skore);
		}
		else {
			printf("[ \"%s\" %d %d.00 ], ", 
			   current -> word, current -> num_appearances, current -> sum_skore);
		}
	}
}

void add_word (nodeT *head, int skor, char *word2, int num_appearances) {
	
	nodeT *current;
	int res;
	
	for (current = head -> next; current != NULL; current = current -> next) {
		
		res = strcmp(current -> word, word2);
		if (res == 0) {
			
			current -> sum_skore += skor;
			current -> num_appearances += 1;
			break;
		}
		
	}
	
	if (current == NULL) {
		
		head = add_node(head, skor, word2, num_appearances);
	}
	
}
	
void destroy_list (nodeT *head) {
	
	nodeT *next = NULL, *current;
	
	for (current = head -> next; current != NULL; current = next) {
		
		next = current -> next;
		free (current -> word);
		free (current);
	}	
	
}

nodeT *find_node (nodeT *head, char *word) {
	
	nodeT *current;
	int res;
	nodeT *my_find_node;
	my_find_node = (nodeT *)malloc(sizeof(nodeT));


	
	
	
	for (current = head -> next; current != NULL; current = current -> next) {
		
		res = strcmp (word, current -> word);
		if (res == 0) {
			break;
		}
		
	}
	
	my_find_node = current;
	
	return(my_find_node);
}

void remove_node (nodeT *head, nodeT *node_to_remove) {
	
	nodeT *current;
	
	for (current = head -> next; current != NULL; current = current -> next) {
		
		if (current == node_to_remove) {
			
			if (current -> next != NULL) {
				current -> next -> prev = current -> prev;
			}
			current -> prev -> next = current -> next;
			
			current -> next = NULL;
			current -> prev = NULL;
			break;
		}
	}
}

/*nodeT *find_remove_return_node (nodeT *head, char *word, nodeT **find_remove_node) {
	
	
	(*find_remove_node) = find_node (head, word, &(*find_remove_node));
	if ((*find_remove_node) == NULL) {
		return (NULL);
	}
	
	
	remove_node(head, (*find_remove_node));
	
	head -> num_appearances -= 1;
	
	return ((*find_remove_node));
}*/
		
unsigned long hash (char *str) {
	
	unsigned long hash = 5381;
	int c;
	
	while ((c = *str++))
		hash = ((hash << 5) + hash) + c;
	
	return hash;
}

void insert_word_hash_table (nodeT *array, int size, char *word, int skor, int num_appearances) {
	
	int pos_array;
	nodeT *address;
	
	pos_array = ((hash (word)) % (size));
	
	address = (&(array[pos_array]));
	
	
	add_word(address, skor, word, num_appearances);
	
}

void print_hash_table () {
	
	int i;
	
	for (i = 0; i < metavliti_prospelasis.size; i++) {
		
		if ((metavliti_prospelasis.table[i].num_appearances) != 0) {
			printf("%4d: ", i);
			print_list (&(metavliti_prospelasis.table[i]));
		}
		
	}
	
}
		
		
void destroy_hash_table () {
	
	int i;
	
	for (i = 0; i < metavliti_prospelasis.size; i++) {
		
			destroy_list(&(metavliti_prospelasis.table[i]));			
		
	}
	
	free(metavliti_prospelasis.table);
	
	metavliti_prospelasis.table = NULL;
}

void init_hash_table () {
	
	int i;
	
	metavliti_prospelasis.size = 100;
	
	for (i = 0; i < metavliti_prospelasis.size; i++) {
		
		init_list (&(metavliti_prospelasis.table[i]));
	}
	
}

void rehash_hash_table () {
	
	int new_size;
	nodeT *table2;
	int i;
	nodeT *current, *dieuthunsi_sentinel;
	
	new_size = metavliti_prospelasis.size * 2;
	
	metavliti_prospelasis.num_entries = 0;
	
	table2 = (nodeT *)malloc(sizeof(nodeT) * new_size);
	
	for (i = 0; i < new_size; i++) {
		
		init_list(&(table2[i]));
	}
	
	for (i = 0; i < metavliti_prospelasis.size; i++) {
		
		dieuthunsi_sentinel = (&(metavliti_prospelasis.table[i]));
		
		if ((dieuthunsi_sentinel -> num_appearances) != 0) {
			
			for (current = dieuthunsi_sentinel -> next; current != NULL; current = current -> next) {
				
				insert_word_hash_table (table2, new_size, current -> word, current -> sum_skore, current -> num_appearances);
				
			}
		}
	}
	
	destroy_hash_table();
	metavliti_prospelasis.table = table2;
	metavliti_prospelasis.size = new_size;
}

char *read_next_line(char *filename) {
	static int firstrun = 1;
	static FILE *fp;
	if (firstrun) {
		fp = fopen(filename, "r");
		if (fp == NULL) {
			fprintf(stderr, "Error opening file \"%s\" for reading.\n", filename);
			exit(1);
		}
		firstrun = 0;
	}
	char *line = NULL;
	size_t linecap = 0;
	ssize_t linelen;
	linelen = getline(&line, &linecap, fp);	
	if (linelen == -1) {
		fclose(fp);
		firstrun = 1;
		return NULL;
	}
	char *newline = strchr(line, '\n');
	if (newline) *newline='\0';
	return line;
}

nodeT *best_score_in_list (nodeT *head, nodeT *head_next) {
	
	nodeT *max;
	double best_score1, best_score2;
	
	
	if (head == NULL) {
		return (NULL);
	}
	
	if (head_next == NULL) {
		return (head);
	}
	
	max = best_score_in_list (head -> next, head -> next -> next);
	best_score1 = ((double)(max -> sum_skore)) / ((double)(max -> num_appearances));
	best_score2 = ((double)(head -> sum_skore)) / ((double)(head -> num_appearances));
	
	if (best_score1 > best_score2) {
		return (max);
	}
	else {
		return (head);
	}
		
}
nodeT best_score_in_array (nodeT *array, int metritis) {
	
	nodeT max;
	double best_score1, best_score2;
	
	if (metritis < metavliti_prospelasis.size) {
	
		max = best_score_in_array (array, metritis + 1);
		best_score1 = ((double)(max.sum_skore)) / ((double)(max.num_appearances));
		best_score2 = ((double)(array[metritis].sum_skore)) / ((double)(array[metritis].num_appearances));
		
		if (best_score1 > best_score2) {
			return (max);
		}
		else {
			return (array[metritis]);
		}
			
	}
}
	

int main (int argc, char *argv[]) {
	
	
	char *string_grammi; /*dieuthunsi sto string ka8e grammis*/
	int skor;
	int i, j;
	int metritis = 0; /*metraei ta '/0' se ka8e seira-string*/
	int *pinakas; /* pinakas ston opoio apothikeuontai oi theseis twn '\0'*/
	int megethos_string;
	int pos;
	double load_factor = 0.0;
	nodeT *leksi_me_megalutero_skor;
	nodeT *pinakas_best_skors;
	nodeT best_word;
	char str[] = "DONE";
	const char s[2] = " ";
	char *token;
	double skor_review = 0.0;
	double metritis_leksewn = 0.0;
	double sum_skor_review = 0.0;
	nodeT *leksi_pou_anazitw;
	
	leksi_pou_anazitw = NULL;
	
	/*if ((argc != 2) && (argc !=3) ) {
		
		printf("Incorrect number of parameters\n");
		return 0;
	}*/
	
	
	
	metavliti_prospelasis.size = 100;
	metavliti_prospelasis.num_entries = 0;
	metavliti_prospelasis.table = (nodeT *)malloc(sizeof(nodeT) * (metavliti_prospelasis.size));
	
	
	
	if (metavliti_prospelasis.table == NULL) {
		
		printf("Error in allocation memory for hash table\n");
		return (1);
	}
	
	init_hash_table();
	
	
	
	string_grammi = (read_next_line(argv[1]));
	while ((string_grammi) != NULL) {
		
		skor = atoi(&(string_grammi[0]));
		megethos_string = strlen(string_grammi);
		
		for (i = 0; i < megethos_string; i++) {
			
			if (isspace(string_grammi[i])) {
				string_grammi[i] = '\0';
				metritis += 1;
			}
		}
		
		pinakas = (int *)malloc(sizeof(int) * metritis);
		for (i = 0; i < metritis; i++) {
			pinakas[i] = 0;
		}
		
		for (i = 0, j= 0; i < megethos_string; i++) {
			if (string_grammi[i] == '\0') {
				if (string_grammi[i + 1] == '\0') {
					if ((i + 1) < megethos_string) {
						continue;
					}
				}
				pinakas[j] = i;
				j++;
			}
		}
		
		for (j = 0; j < metritis; j++) {
			
			pos = pinakas[j] + 1;
			
			for (i = pos; string_grammi[i] != '\0'; i++) {
				string_grammi[i] = tolower(string_grammi[i]);
			}
			insert_word_hash_table(metavliti_prospelasis.table, metavliti_prospelasis.size, &(string_grammi[pos]), skor, 0);
			
			load_factor = ((metavliti_prospelasis.num_entries) / (metavliti_prospelasis.size));
			if (load_factor > 3.0) {
				rehash_hash_table();
			}
			
		}
		free (pinakas);
		pinakas = NULL;
		metritis = 0;
		string_grammi = (read_next_line(argv[1]));
	}
	
	
	


	
	pinakas_best_skors = (nodeT *)malloc(sizeof(nodeT) * metavliti_prospelasis.size);
	
	for (i = 0; i < metavliti_prospelasis.size; i++) {
		pinakas_best_skors[i].num_appearances = 1;
		pinakas_best_skors[i].sum_skore = 0;
	}
	
	
	for (i = 0, j = 0; i < metavliti_prospelasis.size; i++) {
		if (((&(metavliti_prospelasis.table[i])) -> num_appearances) != 0) { 
			leksi_me_megalutero_skor = best_score_in_list ((&(metavliti_prospelasis.table[i])) -> next, (&(metavliti_prospelasis.table[i])) -> next -> next);
			pinakas_best_skors[i].word = (char *)malloc(sizeof(char) * (strlen(leksi_me_megalutero_skor -> word) + 1));
			strcpy(pinakas_best_skors[i].word, leksi_me_megalutero_skor -> word);
			pinakas_best_skors[i].sum_skore = leksi_me_megalutero_skor -> sum_skore;
			pinakas_best_skors[i].num_appearances = leksi_me_megalutero_skor -> num_appearances;
			pinakas_best_skors[i].next = NULL;
			pinakas_best_skors[i].prev = NULL;
		}
	}
	
	
	best_word = best_score_in_array (pinakas_best_skors, 0);
	printf("The most positive word is \"%s\" with a score of %.3lf\n", best_word.word, ((double)(best_word.sum_skore))/((double)(best_word.num_appearances)));
	
	printf("\n");
	print_hash_table();
	printf("\n");
	
	printf("\nEnter review or DONE to finish:\n");
	
	string_grammi = (read_next_line(argv[2]));
	while ((strcmp(string_grammi, str)) != 0) {
		
		
		token = strtok(string_grammi, s);
		
		while( token != NULL ) {
			
			/*if (ispunct(token[0])) {
				token = strtok(NULL, s);
				continue;
			}*/
			
			for (i = 0; token[i] != '\0'; i++) {
				token[i] = tolower(token[i]);
			}
			
			for (i = 0; i < metavliti_prospelasis.size; i++) {
			
				leksi_pou_anazitw = find_node ((&(metavliti_prospelasis.table[i])), token);
				
				
				if (leksi_pou_anazitw != NULL) {
					break;
				}
			}
			
			if (leksi_pou_anazitw == NULL) {
				token = strtok(NULL, s);
				continue;
			}
			
			metritis_leksewn += 1.0;
			
			
			
			skor_review += (((double)(leksi_pou_anazitw -> sum_skore))/((double)(leksi_pou_anazitw -> num_appearances)));
			
			leksi_pou_anazitw = NULL;
			
			token = strtok(NULL, s);
		}
		
		if (metritis_leksewn == 0.0) {
			printf("Sorry, there is no score for this review!\n");
			printf("\nEnter review or DONE to finish:\n");
			string_grammi = (read_next_line(argv[2]));
			continue;
		}
		
		sum_skor_review = skor_review / metritis_leksewn;
		
		printf("Review score: %.4lf\n", sum_skor_review);
		printf("This review is ");
		
		if (sum_skor_review > 2.0) {
			printf("positive");
		}
		else if (sum_skor_review == 2.0) {
			printf("neutral");
		}
		else {
			printf("negative");
		}
		printf(".\n");
		
		
		sum_skor_review = 0;
		skor_review = 0;
		metritis_leksewn = 0;
		
		printf("\nEnter review or DONE to finish:\n");
		string_grammi = (read_next_line(argv[2]));
		
		
	}
	
	


	
	free(pinakas_best_skors);
	destroy_hash_table();
	
	
	return (0);
}
	
