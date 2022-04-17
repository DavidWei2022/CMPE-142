/*
 ============================================================================
 Name        : CMPE.c
 Author      : David Wie
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include <pthread.h>

pthread_t tid[2];
//int counter;
pthread_t hi;
struct add_struct{
	struct linked_list *Addhead;
	int num;
};


void *add(void *arg){
	struct add_struct *addArg =arg;
	ll_add(addArg->Addhead,addArg->num);
}

void *delete (void *arg){
	struct add_struct *deleteArg = arg;
	ll_destory(deleteArg->Addhead);
}
void *remove_first(void *arg){
	struct add_struct *removeArg = arg;
	ll_remove_first(removeArg->Addhead);
}
int main() {

//	printf("hi");
	struct linked_list *head = ll_create();
	printf("length is %d\n", ll_length(head));
	ll_add(head, 1);

	ll_add(head, 2);
	printf("length is %d\n", ll_length(head));
	ll_add(head, 3);
	ll_add(head, 4);
	struct add_struct *addArg;
	addArg->Addhead = head;
	addArg->num = 2;
//	pthread_create(&hi, NULL, &add, (void*) &addArg);


	//	addArg->num = 2;
	//	pthread_create(&hi, NULL, &add, (void*) &addArg);
//
//
	//	addArg->num = 2;
	//	pthread_create(&hi, NULL, &add, (void*) &addArg);
//
//
	pthread_create(&tid[0], NULL, &remove_first, (void*)&addArg);
//
	pthread_create(&tid[0], NULL, &remove_first, (void*)&addArg);


	printf("length is %d\n", ll_length(head));
	int test_var = 5;
	if (ll_contains(head, test_var)) {
		printf("It contains %d\n", test_var);
	} else {
		printf("It does not contains %d\n", test_var);
	}
	test_var = 1;
	if (ll_contains(head, test_var)) {
		printf("It contains %d\n", test_var);
	} else {
		printf("It does not contains %d\n", test_var);
	}
	ll_remove_first(head);
	printf("length is %d\n", ll_length(head));
	if (ll_destroy(head) == 0) {
		printf("could not destroy the linked list!\n");
	}
	ll_remove_first(head);
	//ll_destroy should not perform its function since the linked list is not empty
	if (ll_destroy(head) == 1) {
		printf("successfuly destroy the linked list!\n");
	}

	return 0;
}

