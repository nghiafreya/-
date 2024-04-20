#include <stdio.h>
#include <stdlib.h>
#include "open_addressing.h"

DictOpenAddr *create_dict(int len){
	DictOpenAddr *new_dict = (DictOpenAddr*)malloc(sizeof(DictOpenAddr));
	new_dict -> H = (DictData*)malloc(sizeof(DictData)*len);	
	new_dict -> B = len; 
	//initial value = EMPTY 
	int pos = 0;
	while (pos < len){
		new_dict -> H[pos].state = EMPTY;
		pos ++;
	}
	printf("%s\n", "Dictionary created!");
	return new_dict;
}

int h(DictOpenAddr *dict, int d, int count){	
	int hash = (d % (dict -> B) + count*(7 - d % 7)) % (dict -> B); 
	return hash;
}

int search_hash(DictOpenAddr *dict, int d){ // search if d has alreadly been in the hash table, as well as fint the position of d
	int count = 0;
	int b = h(dict, d, count);
	int initial_b = b;
	
	do{	
		if (dict -> H[b].state == OCCUPIED){
			if (dict -> H[b].name == d){
				return b; // return the positiion of d
			}
		}
		else if (dict -> H[b].state == EMPTY){
			return -1;
		}
		count += 1;
		b = h(dict, d, count);		
	} while (b != initial_b);
	return -1; // when state == DELETED
}


void insert_hash(DictOpenAddr *dict, int d){
	if (search_hash(dict, d) != -1) { //d has already been in the hash table
		return; //do nothing	
	}
	
	int count = 0;
	int b = h(dict, d, count);
	int initial_b = b;
	
	
	do{
		if (dict->H[b].state == EMPTY || dict->H[b].state == DELETED){
			dict->H[b].name = d;
			dict->H[b].state = OCCUPIED;
			printf("%d ", dict->H[b].name);
			if (dict->H[b].state == OCCUPIED){
			}
			return; 
		}
		count += 1;	
		if (count >= dict -> B){
			printf("Dictionary is full, cannot insert! Already inserted %d numbers! \n", count);
			exit(EXIT_FAILURE); //when dictionary is full
		}
		b = h(dict, d, count);
	} while (b != initial_b);
	return;
}

void delete_hash(DictOpenAddr *dict, int d){
	int b = search_hash(dict, d);
	if (b != -1) { //d is in the hash table
		dict -> H[b].state = DELETED;

	return;
	}
	else { //d is not in the hash table
		return;
	}		
}

void display(DictOpenAddr *dict){
	int pos = 0;
	
	while (pos < dict -> B){
		State s = dict -> H[pos].state;
		if (dict -> H[pos].state == OCCUPIED){
			printf ("%d ", dict -> H[pos].name);		
		}
		
		else if (dict -> H[pos].state == EMPTY){
			printf ("%s ", "e");
		}
		
		else { //DELETED
			printf ("%s ", "d");
		}
		
		pos ++;
	}
	printf ("\n");
}	

void delete_dict(DictOpenAddr *dict){
	free (dict -> H);
	free (dict);
	printf("%s\n", "Dictionary deleted!");
}
	
