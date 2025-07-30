#include <iostream>
#include <iomanip>
using namespace std;

class Queue {  // implemented as a circular array, but should resize dynamically
private:
    int init_capacity;      // original capacity
    int current_capacity;   // current array length
    int size;               // number of elements
    int iFront;             // index of front element
    int iRear;              // index of next insertion
    int *items;             // pointer to dynamic array

    // Reallocate the array to newCapacity
    void resizeBuffer(int newCapacity) {
        // TODO: Allocate a new array of length newCapacity.
        int *newItems = new int[newCapacity];
        // TODO: Copy existing elements (in FIFO order) into it.
        for (int i = 0; i < size; i++) {
            if (iFront + i >= current_capacity)
                iFront = -i;
            newItems[i] = items[iFront+i];
        }
        // TODO: Reset iFront and iRear accordingly.
        iFront = 0;
        iRear = size; 
        // TODO: Delete old array and update current_capacity.
        int *temp = items;
        items = newItems; 
        current_capacity = newCapacity;
        delete [] temp;
        temp = nullptr;
        newItems = nullptr;
    }

public:
    Queue(int cap);
    ~Queue();

    void enqueue(int x);
    int dequeue();
    int peek();
    void print();
    int getSize() const { return size; }    // needed for Part B
};

Queue::Queue(int cap) : init_capacity(cap), current_capacity(cap), size(0), iFront(0), iRear(0) {
    // TODO: Initialize init_capacity and current_capacity (minimum 1).
    if (cap < 0) {
        cout << "invalid capacity, setting to default size of 10." << endl;
        init_capacity = 10;
        current_capacity = 10;
    }
    // TODO: Set size, iFront, iRear to 0.
    // TODO: Allocate items to array of length current_capacity.
    items = new int[cap];
}

Queue::~Queue() {
    // TODO: Deallocate the items array.
    delete [] items;
    items = nullptr;
}

void Queue::enqueue(int x) {
    // TODO: If full, call resizeBuffer to double capacity.
    if (size == current_capacity) {
        cout << "Queue cap is reached, doubling its size." << endl;
        resizeBuffer(current_capacity*2);
    }
    // TODO: Insert x at iRear (circular) and increment size.
    items[iRear++] = x;
    if (iRear >= current_capacity) {
        iRear = 0;
    }
    size++;
}

int Queue::dequeue() {
    // TODO: If empty, print message and return a sentinel.
    if (size == 0) {
        cout << "Queue is empty, cannot dequeue." << endl;
        return -999999;
    }
    // TODO: Otherwise, remove front element, adjust iFront and size.
    int returnVal = items[iFront++];
    if (iFront >= current_capacity)
        iFront = 0;
    size--; 
    // TODO: If usage drops to ≤ 1/4 of capacity and can shrink, call resizeBuffer to halve.
    if (size <= current_capacity / 4 && current_capacity > init_capacity)
        resizeBuffer(current_capacity/2);
    return returnVal; 
}

int Queue::peek() {
    if (size == 0) {
        cout << "Queue is empty! nothing to peek." << endl;
        return -9999;
    }
    return items[iFront];
}

void Queue::print() {
    if (size == 0) {
        cout << "Queue is empty! nothing to print." << endl;
        return;
    }
    for (int k = 0; k < size; ++k) {
        int idx = (iFront + k) % current_capacity;
        cout << items[idx] << " ";
    }
    cout << endl;
}

// ---------------- Part B: Customer Service Desk ----------------

static Queue* desk = nullptr;
static int arrivalTimeMap[1001];  // arrivalTimeMap[ID] = arrivalTime

void addCustomer(int customerID, int arrivalTime) {
    // TODO: Enqueue customerID into desk and record arrivalTimeMap[customerID].
    desk->enqueue(customerID);
    arrivalTimeMap[customerID] = arrivalTime;
    // TODO: Print confirmation message.
    cout << "Customer with ID: " << customerID << " and arrival time: " << arrivalTime << " enqueued" << endl;
}

void serveNext(int currentTime) {
    // TODO: Dequeue next customer from desk (if any), compute wait = currentTime − arrivalTime, and print service message.
    int tempID = desk->dequeue();
    cout << "Customer with ID: " << tempID << " served with a wait time of: " << currentTime - arrivalTimeMap[tempID] << endl; 
}

double averageWaitTime(int currentTime) {
    // TODO: If desk is empty, return 0.0.
    if (desk->peek() == -9999)
        return 0.0;
    // TODO: Otherwise, sum (currentTime − arrivalTime) for each waiting customer and return the average.
    int sum = 0;
    for (int i = 0; i < desk->getSize(); i++) {
        int tempID = desk->dequeue(); 
        sum += currentTime-arrivalTimeMap[tempID];
        desk->enqueue(tempID);
    }
    return sum/desk->getSize(); 
}

int main() {
    Queue queue1(3);
    Queue *queue2 = new Queue(3);

    cout << "Test 1:" << endl;
    cout << "Queue 1:" << endl;
    queue1.print();
    cout << "Queue 2:" << endl;
    queue2->print();
    cout << endl;

    cout << "Test 2:" << endl;
    queue1.enqueue(99);
    queue1.enqueue(88);
    queue1.enqueue(44);
    queue1.enqueue(22);

    cout << "Queue 1:" << endl;
    queue1.print();
    cout << "Queue 2:" << endl;
    queue2->print();
    cout << endl;

    cout << "Test 3:" << endl;
    queue2->enqueue(queue1.dequeue());
    queue2->enqueue(queue1.dequeue());
    queue2->enqueue(queue1.dequeue());

    cout << "Queue 1:" << endl;
    queue1.print();
    cout << "Queue 2:" << endl;
    queue2->print();
    cout << endl;

    cout << "Test 4:" << endl;
    cout << queue1.dequeue() << endl;
    cout << queue1.dequeue() << endl;
    cout << queue1.dequeue() << endl;

    cout << "Test 5:" << endl;
    queue1.enqueue(1);
    queue1.enqueue(2);
    queue1.enqueue(3);

    cout << queue1.dequeue() << endl;
    cout << queue1.dequeue() << endl;

    queue1.enqueue(4);
    queue1.enqueue(5);
    queue1.enqueue(6);

    cout << queue1.dequeue() << endl;
    cout << queue1.dequeue() << endl;

    queue1.enqueue(7);
    queue1.enqueue(8);
    queue1.enqueue(9);

    cout << queue1.dequeue() << endl;
    cout << queue1.dequeue() << endl;

    queue1.enqueue(10);
    queue1.enqueue(11);
    queue1.enqueue(12);

    cout << "Queue 1:" << endl;
    queue1.print();
    cout << endl;

    delete queue2;

    // Part B
    desk = new Queue(4);

    addCustomer(101, 0);
    addCustomer(102, 2);
    addCustomer(103, 4);

    cout << "Average wait at t=5: " << fixed << setprecision(2)
         << averageWaitTime(5) << endl;

    serveNext(6);
    serveNext(7);

    addCustomer(200, 8);
    cout << "Average wait at t=9: " << averageWaitTime(9) << endl;

    delete desk;
    return 0;
}
