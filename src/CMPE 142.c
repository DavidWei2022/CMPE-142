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
int counter;

void* multiThreads(void *arg)
{
    unsigned long i = 0;
    counter += 1;
    printf("\n Job %d started\n", counter);

    for(i=0; i<(0xFFFFFFFF);i++);
    printf("\n Job %d finished\n", counter);

    return NULL;
}

int main() {
//	printf("hi");
	struct linked_list *head = ll_create();
	struct linked_list *head2= pthread_create(head,NULL,&multiThreads,NULL);
	printf("length is %d\n", ll_length(head));
	ll_add(head, 1);
	printf("length is %d\n", ll_length(head));
	ll_add(head, 2);
	ll_add(head, 3);
	ll_add(head, 5);
	ll_remove_first(head);
	ll_remove_first(head);
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

