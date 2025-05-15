
#include <iostream>
using namespace std;

struct LinkedListNode{
	int data;
	LinkedListNode * next;
};

int main(){
    // initialize head
    LinkedListNode *head = new LinkedListNode();
	
    // define head
	head->data=10;
	head->next = new LinkedListNode();
	
    // initialize second node
	head->next->data = 3;

    // third node
    head->next->next = new LinkedListNode{6, NULL};

    printf("%d %d %d", head->data, head->next->data, head->next->next->data);
	
	return 0;
}
