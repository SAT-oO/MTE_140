#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

struct Call {
    int id;
    int severity;
    int waitTime;
    string location;

    Call() : id(0), severity(0), waitTime(0), location("") {}
    Call(int id, int severity, int waitTime, string location)
        : id(id), severity(severity), waitTime(waitTime), location(location) {}

    int getPriority() const {
        return severity * 10 - waitTime * waitTime;
    }

    void print() const {
        cout << "Call ID: " << id
             << ", Severity: " << severity
             << ", Wait Time: " << waitTime
             << ", Location: " << location
             << ", Priority: " << getPriority()
             << endl;
    }
};

// helper function
/**
 * @brief swap leaf node with parent node
 * @param parent index of old parent node
 * @param leaf index of old leaf node
 * @param vec vector of calls
 * @param mp index to call ID
 * 
 * @note only need to swap indexes in the vector and the map
 */
void swap(int parent, int leaf, vector<Call>&vec, unordered_map<int, int>&mp){
    int parentID = vec[parent].id;
    int leafID = vec[leaf].id;

    // swap the indexes in the vector
    Call temp = vec[parent];
    vec[parent] = vec[leaf];
    vec[leaf] = temp;

    // swap the indexes in the map
    
    mp[parentID] = leaf;
    mp[leafID] = parent;
}

/**
 * @brief returns the next empty index in the vector
 * @param vec vector of calls to check
 * @return index of the next empty slot
 * 
 * @note if all full, returns vector size -1 (since 1-indexed)
 */
int nextEmpty(vector<Call>& vec){
    for(int i = 1; i <= vec.size(); i++){ // 1-indexed
        if(vec[i].id == 0) return i;
    }
    return vec.size()-1;
}

class MinHeap {
private:
    vector<Call> elements; // vector of calls in order of priority
    int size;
    unordered_map<int, int> idToIndex; // ID to index of call in vector 

public:
    MinHeap();
    bool Enqueue(Call call);
    Call Dequeue();
    void ReheapUp(int index);
    void ReheapDown(int index);
    void updateWaitTimes();
    void printAll();
    int getSize();
    bool updateCall(int callID, int newSeverity);
};

MinHeap::MinHeap() {
    elements.push_back(Call()); // dummy node at index 0
    size = 0;
}

bool MinHeap::Enqueue(Call call) { // TODO test, empty space?

    // 1. add new Call to heap
    elements.push_back(call);
    size++;

    // 2. track ID with idToIndex
    idToIndex[call.id] = size;
    
    // 3. reheap up
    ReheapUp(size);
    
    return true;
}

Call MinHeap::Dequeue() {

    // 1. remove root call
    if(size == 0){
        return Call(-999, 0, 0, "EMPTY");
    }
    Call res = elements[1]; 
    swap(1, size, elements, idToIndex); // populate root with last element
    idToIndex.erase(res.id); 
    elements.pop_back(); 
    size--;

    // 2. call reheap down
    ReheapDown(1);

    return res;
}

void MinHeap::ReheapUp(int index) {
    
    for(int i = index; i > 1; i /=2){ // traversing up the sub-tree -- i: child
        if(elements[i].getPriority() < elements[i/2].getPriority()){ 
            swap(i, i/2, elements, idToIndex);
        } 
    }
}

void MinHeap::ReheapDown(int index) {
    
    for(int i = index; i <= size/2; i++){ // traversing down the sub-tree -- i: parent
        if(elements[i].getPriority() > elements[i*2].getPriority()){
            swap(i, i*2, elements, idToIndex);
        } 
        if(((i*2+1)<= size) && (elements[i].getPriority() > elements[i*2+1].getPriority())){
            swap(i, i*2+1, elements, idToIndex);
        } 

    }
}

void MinHeap::updateWaitTimes() {
    // TODO: Increment waitTime for all calls, update priorities

    // 1. increment wait times
    for (int i = 1; i <= size; i++) {
        elements[i].waitTime++;

    }

    // 2. reheapify 
    ReheapDown(1);

}

void MinHeap::printAll() {
    if (size == 0) {
        cout << "No active calls in the queue.\n";
        return;
    }
    for (int i = 1; i <= size; i++) {
        elements[i].print();
    }
}

int MinHeap::getSize() {
    return size;
}

bool MinHeap::updateCall(int callID, int newSeverity) {
    // TODO: Update severity of a specific call and reheap

    if(idToIndex.find(callID) != idToIndex.end()) {
        // update severity
        int index = idToIndex[callID];
        elements[index].severity = newSeverity;

        // reheap 
        ReheapUp(index);
        ReheapDown(1);

        return true;
    }

    return false;
}

void test(){
    MinHeap hp;
    // Test Enqueue
    cout<< "Testing Enqueue:\n";
    hp.Enqueue(Call(1, 5, 0, "Location A"));
    hp.Enqueue(Call(2, 3, 0, "Location B"));
    hp.Enqueue(Call(3, 8, 0, "Location C"));
    hp.Enqueue(Call(4, 2, 0, "Location D"));
    hp.Enqueue(Call(5, 6, 0, "Location E"));
    hp.Enqueue(Call(6, 1, 0, "Location F"));
    hp.printAll();

    // test Update Wait Times
    cout << "\nTesting Update Wait Times:\n";
    hp.updateWaitTimes();
    hp.printAll();
    cout<<"another round\n";
    hp.updateWaitTimes();
    hp.printAll();
    cout<<"another round\n";
    hp.updateWaitTimes();
    hp.printAll();
    cout<<"another round\n";
    hp.updateWaitTimes();
    hp.printAll();
    cout<<"another round\n";
    hp.updateWaitTimes();
    hp.printAll();

    // Test Dequeue
    cout << "\nTesting Dequeue:\n";
    cout<< "Dequeued Call: ";
    Call dequeuedCall = hp.Dequeue();
    dequeuedCall.print();
    cout << "Remaining Calls:\n";
    hp.printAll();

    cout<< "Dequeued Call: ";
    dequeuedCall = hp.Dequeue();
    dequeuedCall.print();
    cout << "Remaining Calls:\n";
    hp.printAll();

    // Test Update Call
    cout << "\nTesting Update Call:\n";
    hp.updateCall(3, 1);
    hp.printAll();
    cout<<"another round\n";
    hp.updateCall(2, 10);
    hp.printAll();


}


int main() {
    MinHeap dispatch;
    int choice, callID = 1;

    while (true) {
        cout << "\n--- Emergency Dispatch System ---\n";
        cout << "1. Add Emergency Call\n";
        cout << "2. Update Wait Times + Dispatch\n";
        cout << "3. Change Severity of Call by ID\n";
        cout << "4. Print Call Queue\n";
        cout << "5. Exit\n";
        cout << "Choose: ";
        cin >> choice;

        if (choice == 1) {
            int severity;
            string location;
            cout << "Enter severity (1-10): ";
            cin >> severity;
            cin.ignore();
            cout << "Enter location: ";
            getline(cin, location);
            Call newCall(callID++, severity, 0, location);
            if (!dispatch.Enqueue(newCall))
                cout << "Heap full or enqueue failed!\n";
            else
                cout << "Call added successfully.\n";
        } else if (choice == 2) {
            dispatch.updateWaitTimes();
            if (dispatch.getSize() > 0) {
                Call next = dispatch.Dequeue();
                cout << "\n--- Dispatching Call ---\n";
                next.print();
            } else {
                cout << "No calls to dispatch.\n";
            }
        } else if (choice == 3) {
            int id, newSeverity;
            cout << "Enter Call ID to update: ";
            cin >> id;
            cout << "Enter new severity (1-10): ";
            cin >> newSeverity;
            if (!dispatch.updateCall(id, newSeverity))
                cout << "Call not found.\n";
            else
                cout << "Severity updated.\n";
        } else if (choice == 4) {
            cout << "\n--- Current Call Queue ---\n";
            dispatch.printAll();
        } else if (choice == 5) {
            cout << "Exiting...\n";
            break;
        } else {
            cout << "Invalid choice!\n";
        }
    }

    return 0;
}
