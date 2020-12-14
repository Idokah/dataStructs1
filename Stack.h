#pragma once
#include "Item.h"

struct Node {
	Item item;
	struct Node* next;
	Node(Item item, Node* next);
};


class Stack {
	public:
		bool isEmpty();
		void makeEmpty();
		void push(Item item);
		Item pop(void);
	private:
		Node* top;
};