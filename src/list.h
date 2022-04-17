#ifndef LIST_H
#define LIST_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

struct linked_list {
	int val;
	struct linked_list *next;
	pthread_mutex_t *mutex;

};

static inline struct linked_list*
ll_create(void) {

	//consider the case when the memory is running out
	struct linked_list *node = malloc(sizeof(struct linked_list));

	if (pthread_mutex_init(node->mutex, NULL)) {
		printf("not init\n");
	} else {
		printf("successfully init\n");
	}

	if (!node) {
		return NULL;
	} else {
		node->val = NULL;
		node->next = NULL;
		return node;
	}
}

static inline int ll_length(struct linked_list *ll) {
//	pthread_mutex_lock(ll->mutex);
	if (ll->val == NULL) {
//		pthread_mutex_unlock(ll->mutex);
		return 0;
	} else {
		int len = 0;
		struct linked_list *node;
		node = ll;
		while (node->val != NULL) {
			//		printf("%d\n",node->val);
			node = node->next;
			//		ll = temp;
			len++;
		}
//		pthread_mutex_unlock(ll->mutex);
		return len;
	}
}

static inline int ll_destroy(struct linked_list *ll) {
	if (pthread_mutex_lock(ll->mutex) == 0) {
		printf("Lock successful\n");
	} else {
		printf("Lock Unsuccessful\n");
	}

	//check if the linked list is empty, if it is not, don't deallocate it
	if (ll_length(ll) != 0) {
		pthread_mutex_unlock(ll->mutex);
		return 0;
	} else {
		pthread_mutex_unlock(ll->mutex);
		free(ll);
		ll = NULL;

		//return 1 if it is destroyed, 0 if it is not destroyed
		if (ll == NULL) {
			return 1;
		} else {
			return 0;
		}
	}
	return 1;
}

static inline void ll_add(struct linked_list *ll, int value) {
	if (pthread_mutex_lock(ll->mutex) == 0) {
		printf("Lock successful\n");
	} else {
		printf("Lock Unsuccessful\n");
	}
//	struct linked_list *temp = ll->next;
	struct linked_list *new = malloc(sizeof(struct linked_list));
//make new into ll, then change the value of ll into the parameter
	new->val = ll->val;
	new->next = ll->next;
	ll->val = value;
	ll->next = new;
	if(pthread_mutex_unlock(ll->mutex)){
		printf("Unlock failed\n");
	}
	else{
		printf("Unlock successful\n");
	}
}

static inline bool ll_remove_first(struct linked_list *ll) {
	if (pthread_mutex_lock(ll->mutex) == 0) {
		printf("Lock successful\n");
	} else {
		printf("Lock Unsuccessful\n");
	}
//	printf("%d",ll->val);
//	struct linked_list* temp;
	if (ll->val == NULL) {
		//		printf("no node!\n");
		return false;
	}
//if the linked list only has one node, remove the node
	else if (ll->next == NULL) {
		//		printf("only one node!\n");
		if(pthread_mutex_unlock(ll->mutex)){
			printf("Unlock failed\n");
		}
		else{
			printf("Unlock successful\n");
		}
		ll->val = NULL;
		ll->next = NULL;
		return 1;
	} else {
		if(pthread_mutex_unlock(ll->mutex)){
			printf("Unlock failed\n");
		}
		else{
			printf("Unlock successful\n");
		}
		//		printf("so many nodes!\n");
		struct linked_list *temp = ll->next;
		//		temp->val = ll->val;
		//		new->next = ll->next;
		ll->val = ll->next->val;
		ll->next = ll->next->next;
		free(temp);

		return 1;
	}
}

static inline int ll_contains(struct linked_list *ll, int value) {
	if (pthread_mutex_lock(ll->mutex) == 0) {
		printf("Lock successful\n");
	} else {
		printf("Lock Unsuccessful\n");
	}
	if (ll == NULL) {
		return 0;
	} else {
		if(pthread_mutex_unlock(ll->mutex)){
			printf("Unlock failed\n");
		}
		else{
			printf("Unlock successful\n");
		}
		struct linked_list *temp;
		struct linked_list *head;
		int position = 1;
		while (ll->next != NULL) {
			if (value != ll->val) {
				temp = ll->next;
				ll = temp;

				position++;
			} else {
				return position;
			}
		}
	}

	return 0;
}

#endif
