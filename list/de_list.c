#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

typedef struct list
{
	int data;

	struct list *next;
	struct list *front;
}list_t;



int add_new_node(list_t *head, int pos, list_t *node)
{
	list_t *p = head->next;

	while(p)
	{
		if(p->data == pos)
		{
			node->next = p->next;
			p->next->front = node;
			node->front = p;
			p->next = node;
			return 0;
		}
		p = p->next;
	}

	node->next = head->next;
	head->next = node;
	node->front = head;


	return 0;
}

int del_node(list_t *head, int data)
{

	list_t *p = head->next;

	while(p)
	{
		if(p->data == data)
		{
			p->next->front = p->front;
			p->front->next = p->next;
			free(p);
			return 0;
		}
	}

	return -1;
}

int main()
{
	list_t *p;
	list_t head = {0, NULL, NULL};

	int i ;

	for(i = 0; i < 5; i++)
	{
		p = (list_t*)malloc(sizeof(list_t));

		p->data = i;
		p->next = NULL;
		p->front = NULL;

		add_new_node(&head, -1, p);
	}

	p = head.next;
	while(p)
	{
		printf("Q_Q :[%d]\n", p->data);
		p = p->next;
	}

	printf("--------------------------------------\n\n");

	p = (list_t*)malloc(sizeof(list_t));
	p->data = 6;
	p->next = NULL;
	p->front = NULL;
	add_new_node(&head, 1, p);

	p = (list_t*)malloc(sizeof(list_t));
	p->data = 7;
	p->next = NULL;
	p->front = NULL;
	add_new_node(&head, 3, p);


	p = head.next;
	while(p)
	{
		printf("Q_Q :[%d]\n", p->data);
		p = p->next;
	}



	return 0;
}











