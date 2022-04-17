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
struct helper_struct {
	struct linked_list *Helperhead;
	int num;
};

void* add(void *arg) {
	struct helper_struct *addArg = arg;
	ll_add(addArg->Helperhead, addArg->num);
	pthread_exit(NULL);
	return NULL;
}

void* delete(void *arg) {
	struct helper_struct *deleteArg = arg;
	ll_destroy(deleteArg->Helperhead);
	pthread_exit(NULL);
	return NULL;
}
void* remove_first(void *arg) {
	struct helper_struct *removeArg = arg;
	ll_remove_first(removeArg->Helperhead);
	pthread_exit(NULL);
	return NULL;
}
int main() {
	struct linked_list *head = ll_create();
	printf("length is %d\n", ll_length(head));
	struct helper_struct *addArg;
	addArg->Helperhead = head;
	addArg->num = 1;
	pthread_create(&tid[1], NULL, &add, (void*) &addArg);
	addArg->num = 2;
	pthread_create(&tid[0], NULL, &add, (void*) &addArg);
	printf("length is %d\n", ll_length(head));
	addArg->num = 3;
	pthread_create(&tid[1], NULL, &add, (void*) &addArg);

	pthread_create(&tid[0], NULL, &remove_first, (void*) &addArg);
//
	pthread_create(&tid[1], NULL, &remove_first, (void*) &addArg);

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

