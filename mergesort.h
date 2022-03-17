#ifndef MERGESORT_H_
#define MERGESORT_H_

#include <stdlib.h>
#include <stdio.h>


typedef struct node{
	struct node *p;
	int val;
}node;

node * node_from_val(int val)
{
	node * new = malloc(sizeof(node));
	new -> val = val;
	new -> p   = NULL;
	return new;
}

void attach_at_tail(node *newnode, node *head)
{
	node *tmp = head;
	while(tmp->p != NULL)
	{
		tmp = tmp->p;
	}
	tmp->p = newnode;
}

node * makelist(FILE*stream)
{
	node *head = new_node(stream);
	node *tmp;
	while((tmp = new_node(stream))->val != EOF)
	{
		attach_at_tail(tmp, head);
	}
	return head;
}

node * divide(node *head)
{
	node * tmp = head;
	int len = 1;
	while(1)
	{
		tmp = (tmp)->p;
		if(tmp == NULL) break;
		len++;
	}
	tmp = head;
	if(len ==  1) return head;
	for(int i = 0; i<(len/2)-1; i++)
	{
		tmp = tmp -> p;
	}
	node * head2 = tmp->p;
	tmp->p = NULL;
	return head2;
}

void pop_head(node **head)
{
	*head = (*head)->p;
}

node * merge(node *head1, node *head2)
{
	node *head3 = node_from_val(0);
	while(head1 != NULL && head2 != NULL)
	{
		if(head1->val < head2->val)
		{
			attach_at_tail(node_from_val(head1->val), head3);
			pop_head(&head1);
		}
		else
		{
			attach_at_tail(node_from_val(head2->val), head3);
			pop_head(&head2);

		}
	}
	if(head2 != NULL) attach_at_tail(head2, head3);
	if(head1 != NULL) attach_at_tail(head1, head3);
	return head3->p;
}

node * divide_and_merge(node * head)
{
	node * tmp = head;
	int len = 1;
	while(1)
	{
		tmp = tmp->p;
		if(tmp == NULL) break;
		len++;
	}

	if(len>1)
	{
		node * splitted = divide(head);
		return merge(divide_and_merge(splitted), divide_and_merge(head));
	}
	else return head;
}
#endif
