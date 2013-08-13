#include <iostream>

struct Node
{
	Node* next;
	int val;
};

void reverse(Node* prev, Node* node)
{
	if(node == NULL)
		return;
	prev->next = NULL;
	reverse(node,node->next);
	node->next = prev;
}

void print(Node* head)
{
	if(head == NULL)
	{
		std::cout << std::endl;
		return;	
	}
	std::cout << head->val << "  ";
	print(head->next);
}

int main(void)
{
	Node* n1 = new Node();
	Node* n2 = new Node();
	Node* n3 = new Node();
	Node* n4 = new Node();
	Node* n5 = new Node();
	n1->next = n2;
	n2->next = n3;
	n3->next = n4;
	n4->next = n5;
	n5->next = NULL;
	n1->val = 1;
	n2->val = 2;
	n3->val = 3;
	n4->val = 4;
	n5->val = 5;
	print(n1);
	reverse(n1,n1->next);
	print(n5);
}

