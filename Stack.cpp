#include <iostream>
#include "Item.h"
#include "Stack.h"

using namespace std;

Node::Node(Item item, Node* next)
{
	this->item = item;
	next->next = next;
}

void Stack::push(Item item)
{
	this->top = new Node(item, this->top);
}


bool Stack::isEmpty()
{
	return top == NULL;
}


Item Stack::pop()
{
	Node* temp;

	if (top == NULL)
	{
		cout << "\nStack Underflow" << endl;
		exit(1);
	}
	else
	{
		temp = top;
		top = top->next;
		temp->next = NULL;
		return temp->item;
	}
}