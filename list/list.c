#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

typedef struct list
{
	int data;


	struct list *next;
}list_t;


int add_list_node(list_t *head, list_t *node)
{
	if(head == NULL || node == NULL)
		return -1;

	node->next = head->next;
	head->next = node;

	return 0;
}


int del_list_node(list_t *head, int data)
{
	if(head == NULL)
		return -1;

	list_t *p = head->next;
	list_t *step = head;

	while(p)
	{
		if(p->data == data)
		{
			step->next = p->next;
			free(p);
			p = NULL;
			return 0;
		}
		else
		{
			step = p;
			p = p->next;
		}

	}

	return -1;
}


int main()
{
	list_t head = {0, NULL};
	list_t *p = NULL;
	int i;

	for(i = 0; i < 10; i++)
	{
		p = (list_t*)malloc(sizeof(list_t));

		p->data = i;
		p->next = NULL;

		add_list_node(&head, p);
	}

	p = head.next;
	while(p)
	{
		printf("Q_Q :[%d]\n", p->data);
		p = p->next;
	}

	printf("--------------------------------------\n\n");

	del_list_node(&head, 0);

	p = head.next;
	while(p)
	{
		printf("Q_Q :[%d]\n", p->data);
		p = p->next;
	}


	printf("--------------------------------------\n\n");  

	del_list_node(&head, 6);

	p = head.next;
	while(p)
	{
		printf("Q_Q :[%d]\n", p->data);
		p = p->next;
	}

	return 0;

}







