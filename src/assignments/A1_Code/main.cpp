#include "linked_list.cpp"
#include <iostream>
using namespace std;

void printList( const vector<int> &list )
{
    for( int val : list )
    {
        cout << val << " ";
    }
    cout << endl;
}

int main()
{
    cout << unitbuf;

    LinkedList ll;
    for( int i = 1; i <= 5; ++i )
        ll.insert( i );

    cout << "Original: ";
    printList( ll.display() );

    ll.reverseKGroup( 2 );
    cout << "After reverseKGroup(2): ";
    printList( ll.display() );

    LinkedList ll2;
    for( int i = 1; i <= 5; ++i )
        ll2.insert( i );
    ll2.reorderOddEven();
    cout << "After reorderOddEven: ";
    printList( ll2.display() );

    LinkedList ll3;
    for( int i = 1; i <= 5; ++i )
        ll3.insert( i );
    Node *temp = ll3.head;
    while( temp->next )
        temp = temp->next;
    temp->next = ll3.head->next->next;    // loop from last to 3rd node
    cout << "Loop detected: " << ( ll3.detectLoop() ? "Yes" : "No" ) << endl;

    return 0;
}
