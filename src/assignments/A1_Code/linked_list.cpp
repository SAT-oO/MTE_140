#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

class Node {
public:
    int data;
    Node* next;

    Node(int val) {
        data = val;
        next = nullptr;
    }
};

class LinkedList {
public:
    Node* head;

    LinkedList() {
        head = nullptr;
    }

    void insert(int val);

    vector<int> display();

    void reverseKGroup(int k);

    bool detectLoop();

    void reorderOddEven();
};

vector<int> LinkedList :: display() {
    // Return the elements of the linked list as a vector
    if(head == nullptr){
        return {};
    }

    Node *curr = head;
    vector<int> vec;
    while(curr != nullptr){
        vec.push_back(curr->data);
        curr = curr->next;
    }
    return vec;
    
}
void LinkedList::insert(int val) {

    // Insert a new node with the given value at the end of the list
    Node *new_node = new Node(val);
    // if head is null
    if(head == nullptr){
        head = new_node;
        return;
    }
    // if list isnt null
    Node *curr = head;
    while(curr -> next != nullptr){
        curr = curr -> next;
    } // on the last one

    curr ->next = new_node;

    
}

/**
 * @brief Reverse nodes in groups of size k
 * @remark swapping idea: take out node and insert, iterate
 */
void LinkedList::reverseKGroup(int k) {
    // check availability of next group
    Node *curr = head;
    int count = k;
    while(curr != nullptr && count > 0){
        curr = curr->next;
        count--;
    } 
    if(count > 0) return; // if exited while loop due to nullptr 

    head = curr; // update list (iterated once)


    // (per group) start reversal in the group, curr is the last of current group [curr_start ...... curr][next_start ......]
    Node *curr_start = head;
    Node *next_start = curr -> next;

    for(int i = 1; i < k; i++){
        // (k-1 times)
        // take out start node and insert between curr and curr -> next, k times
        Node *temp = curr_start;

        // insert 
        curr -> next = temp;
        temp->next = next_start;
        // [curr_start ... curr temp][next_start ...]

        
        // update variables
        curr = temp;
        temp = temp ->next;
    }
    
    
    



}

bool LinkedList::detectLoop() {
    // Return true if a cycle is found in the list
    
    if(head == nullptr){
        return false;
    }
    
    
    if(head->next == head){
        return true;
    }

    Node *slow = head;
    Node *fast = head;

    // will be stuck in here is cycle
    while((slow -> next != nullptr) && (fast -> next -> next != nullptr)){
        
        slow = slow->next;
        fast = fast -> next-> next;

        if(slow-> data == fast -> data){
            return true;
        }

    }

    return false;
}

void LinkedList::reorderOddEven() {
    // Reorder the list with odd-positioned nodes before even-positioned ones

}

