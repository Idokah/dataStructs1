#include <iostream>
#include "Item.h"
#include "Stack.h"

using namespace std;

Node::Node(Item item, Node* next)
{
	this->item = item;
	this->next = next;
}

Stack::Stack()
{
	this->top = nullptr;
}

void Stack::push(Item item)
{
	this->top = new Node(item, this->top);
}


bool Stack::isEmpty()
{
	return this->top == nullptr;
}


Item Stack::pop()
{
	Node* temp;

	if (this->top == nullptr)
	{
		cout << "\nStack Underflow" << endl;
		exit(1);
	}
	else
	{
		temp = this->top;
		this->top = this->top->next;
		temp->next = nullptr;
		return temp->item;
	}
}

void Stack::makeEmpty()
{
	while (this->top != nullptr) {
		pop();
	}
}