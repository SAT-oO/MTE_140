/**
 * @remark lecture on may 8
 * @note Pointer and LinkedLists 
 */

#include <iostream>
using namespace std;

struct LinkedListNode{
	int data;
	LinkedListNode * next;
};
void delete_head(LinkedListNode *head){
    //remove first node
    LinkedListNode *temp = head;

    head = head->next; //the second node is now the head node
    delete temp;
    temp = NULL; // unnecessary line 
}

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

    delete_head(head);
	
	return 0;
}
