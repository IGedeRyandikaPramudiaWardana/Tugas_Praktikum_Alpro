#include <iostream>
using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

class Node{
	public:
		char id;
		
		Node *next;
		
		Node()
		{
			next = NULL;
		}
		
};

class LinkedList{
	public:
		Node *head;
		Node *tail;
		
		LinkedList()
		{
			head = tail = NULL;
		}
	
};



int main(int argc, char** argv) 
{
	LinkedList *link1 = new LinkedList();
	
	Node *nodex = new Node();
	nodex->id = 'X';
	Node *node1 = new Node();
	node1->id = 'A';
	
	
	link1->head = nodex;
	link1->head->next = node1;

	
	Node *node2 = new Node();
	node2->id = 'B';
	link1->tail->next = node2;
	link1->tail = node2;
	
	cout << link1->head->id << endl;
	cout << link1->head->next->id << endl;
	cout << link1->tail->id << endl;
	
	
	return 0;
}