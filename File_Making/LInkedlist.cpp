#include <iostream>
using namespace std;

class Node{
	public :
		char id;
		Node *next;
		Node(){
			next = NULL;
		}
};

class LinkedList{
	public :
		Node *head;
		Node *tail;
		LinkedList(){
			head = tail = NULL;
		}
	
	//Menambahkan data di awal	
	void insertToHead(char data){
		Node *node = new Node();
		node->id = data;
	
		//Jika Linkedlist Kosong
		if (head == NULL){
			head = tail = NULL;
		}else {
			Node *tmp = head;
			head = node;
			head->next = tmp;
		}
	}
	
	//Menambahkan data di akhir
	void insertToTail(char data){
		Node *node = new Node();
		node -> id = data;
		
		//Jika Linkedlist Kosong
		if (head == NULL){
			head = tail = NULL;
		}else {
			tail->next = node;
			tail = node;
		}
	}
	
	//Menyisipkan data di tengah
	void insertNodeAfter(char data, char after){
		
		//Jika Linkedlist Kosong
		if (head == NULL){
			cout << "Error : Data Kosong, tidak bisa memasukan data di tengah" << endl;
		}else if (tail -> id == data){
			insertToTail(data); 
		}else {
			Node *node = new Node();
			node -> id = data;
		
			Node *tmp = head;
			while (tmp != NULL && tmp->id != after){
				tmp = tmp -> next;
			}
			if (tmp == NULL){
				cout << "Error : Data Tidak ditemukan!" << endl;
			} else{
			
				node -> next = tmp -> next;
				tmp -> next = node;
			}
		}
	}
	
	//Menampilkan Data Linkedlist
	void printALL(){
		if (head != NULL){
			Node *tmp = head;
			do {
				cout << tmp->id << "->";
				tmp = tmp->next;
			}while (tmp != NULL);
		}
	}
	
	//Menghapus Data di Head
	void removeHead(){
		if (head == tail){
			delete tail;
			head = tail = NULL;	
		}else if (head != NULL){
			Node *hapus = head;
			head = head->next;
			delete hapus;
		}else{
			cout << "Error : Linkedlist Kosong.";
		}	
	}
	
	//Menghapus Data di Tail
	void removeTail(){	
		if (head != NULL){
			if (head == tail){
				delete tail;
				head = tail = NULL;	
			}else{
				Node *tmp = head;
				while (tmp->next != tail){
				tmp = tmp->next;
				}
				delete tail;
				tail = tmp;
				tail->next = NULL;
			}
		} else{
			cout << "Error : Linkedlist Kosong.";
		}
	}
	
	//Menghapus Data di Tengah
	void removeNodeAfter(char data, char after){
		if (head != NULL){
			Node *tmp = head;
			while (tmp != NULL && tmp->id != after){
				tmp = tmp->next;
			}
			if (tmp == NULL || tmp->next ==NULL){
				cout << "Error : Data Tidak Ditemukan.";
			} else{
				Node *hapus = tmp->next;
				tmp->next = tmp->next->next;
				delete hapus;
			}
		} else{
			cout << "Error : Linkedlist Kosong.";
		}
	}
};

int main (int argc, char** argv ){
	//Buat link untuk memanggil data
	LinkedList *link1 = new LinkedList();
	
	//buat Node awal
	Node *node1 = new Node();
	node1->id = 'A';
	Node *node2 = new Node();
	node2->id = 'B';
	node1->next = node2;
	Node *node3 = new Node();
	node3->id = 'C';
	node2->next = node3;
	Node *node4 = new Node();
	node4->id = 'D';
	node3->next = node4;
	
	link1->head = node1;
	link1->tail = node4;
	
	//Tampilkan data awal
	cout << "Tampilan Data Awal : " << endl;
	link1->printALL();
	cout << "\n";
	link1->insertToHead('X');
	link1->insertToTail('Z');
	link1->insertNodeAfter('Y', 'B');
	
	//Tampilkan data Setelah di Insert
	cout << "Tampilan Data Insert : " << endl;
	link1->printALL();
	cout << "\n";
	
	//Menghapus Head
	cout << "Tampilan Data Delete Head : " << endl;
	link1->removeHead();
	link1->printALL();
	cout << "\n";
	
	//Menghapus Tail
	cout << "Tampilan Data Delete Tail : " << endl;
	link1->removeTail();
	link1->printALL();
	cout << "\n";
	
	//Menghapus Middle
	cout << "Tampilan Data Delete Middle : " << endl;
	link1->removeNodeAfter('Y', 'B');
	link1->printALL();
	cout << "\n";
	
	return 0;
}
