#include <iostream>
#include <unordered_set>
#include <vector>
using namespace std;

class Node {
public:
  int data;
  Node *next;

  Node(int val) {
    data = val;
    next = nullptr;
  }
};

class LinkedList {
public:
  Node *head;

  LinkedList() { head = nullptr; }

  void insert(int val);

  vector<int> display();

  void reverseKGroup(int k);

  bool detectLoop();

  void reorderOddEven();
};

vector<int> LinkedList ::display() {
  // Return the elements of the linked list as a vector
  if (head == nullptr) {
    return {};
  }

  Node *curr = head;
  vector<int> vec;
  while (curr != nullptr) {
    vec.push_back(curr->data);
    curr = curr->next;
  }
  return vec;
}
void LinkedList::insert(int val) {

  // Insert a new node with the given value at the end of the list
  Node *new_node = new Node(val);
  // if head is null
  if (head == nullptr) {
    head = new_node;
    return;
  }
  // if list isnt null
  Node *curr = head;
  while (curr->next != nullptr) {
    curr = curr->next;
  } // on the last one

  curr->next = new_node;
}

// insert node between curr and curr->next
void insert(Node *insert, Node *curr) {
  insert->next = curr->next;
  curr->next = insert;
}

/**
 * @brief Reverse nodes in groups of size k
 * @remark swapping idea: take out node and insert, iterate
 *
 * @var curr_start, curr_end (curr), prev_start
 *
 * 1. check group availability
 * 2. need var.:
 *  temp(current node to insert), prev_end (to bridge)
 *  temp_next (to anchor back to),curr_end (insert after)
 * 3. iterate k-1 times
 */
void LinkedList::reverseKGroup(int k) {

  Node *prev_end = head;
  Node *temp_next = head;
  Node *curr_end = head;
  Node *temp = head;

  while (true) {

    // 1. check group availability
    int count = k - 1;

    while (curr_end != nullptr && count > 0) {
      curr_end = curr_end->next;
      count--;
    }
    if (curr_end == nullptr) 
      return; // exited while done
              // [curr_start ... curr_end]

    // 2. iterate k-1 times to insert, update head for once
    if (prev_end == head) {
      head = curr_end; // update list (iterated once)
    }else{
        prev_end->next = curr_end;
        prev_end = temp_next;
    }

    while (temp_next != curr_end) {
      // move on for temp
      temp = temp_next;
      temp_next = temp->next;

      // insert temp after curr_end
      temp->next = curr_end->next;
      curr_end->next = temp;
    }

    // end of cycle for this group, maintain variables

    count = k - 1;
    temp = prev_end->next;
    temp_next = prev_end->next;
    curr_end = prev_end->next;
    
  }
  // update variables
}

bool LinkedList::detectLoop() {
  // Return true if a cycle is found in the list

  if (head == nullptr) {
    return false;
  }

  if (head->next == head) {
    return true;
  }

  Node *slow = head;
  Node *fast = head;

  // will be stuck in here is cycle
  while ((slow->next != nullptr) && (fast->next->next != nullptr)) {

    slow = slow->next;
    fast = fast->next->next;

    if (slow->data == fast->data) {
      return true;
    }
  }

  return false;
}

void LinkedList::reorderOddEven() {
  // Reorder the list with odd-positioned nodes before even-positioned ones
}
