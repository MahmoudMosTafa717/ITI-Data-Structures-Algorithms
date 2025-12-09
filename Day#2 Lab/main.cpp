#include <iostream>
using namespace std;

// ======================= Employee Struct ============================
struct Employee {
    int ID;
    string Name;

    Employee(int id = 0, string name = "") : ID(id), Name(name) {}
};

// ============================ Node =================================
class Node {
public:
    Employee Data;
    Node* pNext;
    Node* pPrev;

    Node(Employee emp = Employee())
        : Data(emp), pNext(NULL), pPrev(NULL) {}
};

// ============================ DLL ==================================
class DLL {
protected:
    Node* pStart; // Head
    Node* pLast; // Tail

public:
    DLL() : pStart(NULL), pLast(NULL) {}

    // --------------------- Copy Constructor -------------------------
    DLL(const DLL& other) {
        pStart = pLast = NULL;

        Node* curr = other.pStart;

        while (curr != NULL) {
            AddNode(new Node(curr->Data));
            curr = curr->pNext;
        }
    }

    // ---------------------- Operator = ------------------------------
    DLL& operator=(const DLL& other) {
        if (this == &other) return *this; // prevent self-assignment

        // delete old data
        Node* temp = pStart;
        while (temp != NULL) {
            Node* del = temp;
            temp = temp->pNext;
            delete del;
        }
        pStart = pLast = NULL;

        // copy new
        Node* curr = other.pStart;
        while (curr != NULL) {
            AddNode(new Node(curr->Data));
            curr = curr->pNext;
        }
        return *this;
    }

    // ------------------------ Destructor ----------------------------
    virtual ~DLL() {
        Node* curr = pStart;
        while (curr != NULL) {
            Node* del = curr;
            curr = curr->pNext;
            delete del;
        }
    }

    // -------------------------- AddNode -----------------------------
    void AddNode(Node* pNew) {
        // empty
        if (pStart == NULL) {
            pStart = pLast = pNew;
        // add to end
        } else {
            pLast->pNext = pNew;
            pNew->pPrev = pLast;
            pLast = pNew;
        }
    }

    // ------------------------ SearchList ----------------------------
    Node* SearchList(int ID) {
        Node* curr = pStart;
        while (curr != NULL) {
            if (curr->Data.ID == ID) return curr;
            curr = curr->pNext;
        }
        return NULL;
    }

    // ------------------------ DeleteNode ----------------------------
    bool DeleteNode(int ID) {
        Node* target = SearchList(ID); // call searchList() , then make a pointer -> address
        if (!target) return false;

        if (target == pStart) {
            pStart = target->pNext; // make head pointer -> pNext addresss

            if (pStart) pStart->pPrev = NULL;

            else pLast = NULL;
        }
        else if (target == pLast) {
            pLast = target->pPrev; // make Last pointer -> the previous one
            pLast->pNext = NULL;
        }
        else {

            target->pPrev->pNext = target->pNext;

            target->pNext->pPrev = target->pPrev;

//           Node* NextNodePtr = target->pNext;
//           Node* PrevNodePtr = target -> pPrev;
//
//           PrevNodePtr-> pNext = NextNodePtr;
//           NextNodePtr-> pPrev = PrevNodePtr;
        }

        delete target;
        return true;
    }

    // ------------------------ DisplayNode ---------------------------
    bool DisplayNode(int ID) {
        Node* temp = SearchList(ID);
        if (!temp) return false;

        cout << "ID: " << temp->Data.ID
             << ", Name: " << temp->Data.Name << endl;
        return true;
    }

    // ------------------------ DisplayALL ----------------------------
    void DisplayALL() {
        Node* curr = pStart;
        if (!curr) { cout << "[List is Empty]\n"; return; }

        while (curr != NULL) {
            cout << curr->Data.ID << " - " << curr->Data.Name << endl;
            curr = curr->pNext;
        }
    }

    // ------------------------ NodeNumber ----------------------------
    int NodeNumber() {
        int count = 0;
        Node* curr = pStart;
        while (curr != NULL) {
            count++;
            curr = curr->pNext;
        }
        return count;
    }

    // ------------------------ operator[] ----------------------------
    Node* operator[](int index) {
        int i = 0;
        Node* curr = pStart;        // temp iterator pointer
        while (curr != NULL) {
            if (i == index) return curr;
            curr = curr->pNext;
            i++;
        }
        return NULL;
    }
};

// ======================== SortedDLL ================================
class SortedDLL : public DLL {
public:
    void InsertNode(Node* pNew) {

        // empty list
        if (pStart == NULL) {
            pStart = pLast = pNew;
            return;
        }

        Node* curr = pStart;

        // insert at front
        if (pNew->Data.ID < curr->Data.ID) {
            pNew->pNext = pStart;
            pStart->pPrev = pNew;
            pStart = pNew;
            return;
        }

 // move to position until (break the loop when) NULL or ID of new (want to add) is less < than current
        while (curr != NULL && pNew->Data.ID > curr->Data.ID)
            curr = curr->pNext;

        // insert at end
        if (curr == NULL) {
            pLast->pNext = pNew;
            pNew->pPrev = pLast;
            pLast = pNew;
        }

        // insert before current (4 ptrs want to change)
        else {
            pNew->pNext = curr;
            pNew->pPrev = curr->pPrev;

            curr->pPrev->pNext = pNew; // Node before curr

            curr->pPrev = pNew; // curr Node prevPtr
        }
    }
};

// ============================ StackDLL =============================
class StackDLL : public DLL {
public:
    void Push(Node* pNew) {
        if (pStart == NULL) {
            pStart = pLast = pNew;
            return;
        }
        pNew->pNext = pStart;
        pStart->pPrev = pNew;
        pStart = pNew;
    }

    Node* Pop() {
        if (pStart == NULL) return NULL;

        Node* temp = pStart;

        if (pStart == pLast) {
            pStart = pLast = NULL;
        } else {
            pStart = pStart->pNext;
            pStart->pPrev = NULL;
        }

        temp->pNext = temp->pPrev = NULL;
        return temp;
    }

    Node* Peek() {
        return pStart;
    }
};

// ============================== Queue ===============================
class Queue : public DLL {
public:
    void EnQ(Node* pNew) {
        AddNode(pNew);
    }

    Node* DeQ() {
        if (pStart == NULL) return NULL;

        Node* temp = pStart;

        if (pStart == pLast) {
            pStart = pLast = NULL;

        } else {
            pStart = pStart->pNext;
            pStart->pPrev = NULL;
        }

        temp->pNext = temp->pPrev = NULL;
        return temp;
    }

    Node* Peek() {
        return pStart;
    }
};

// ============================== MAIN ===============================
int main() {

    cout << "======== TEST SortedDLL (sorted insert) ========\n";
    SortedDLL s;

    s.InsertNode(new Node(Employee(10,"Omar")));
    s.InsertNode(new Node(Employee(30,"Ali")));
    s.InsertNode(new Node(Employee(20,"Mahmoud")));
    s.InsertNode(new Node(Employee(25,"MosTafa")));

    s.DisplayALL();


    cout << "\n======== TEST StackDLL (LIFO) ========\n";
    StackDLL st;

    st.Push(new Node(Employee(1,"A")));
    st.Push(new Node(Employee(2,"B")));
    st.Push(new Node(Employee(3,"C")));

    st.DisplayALL();

    cout << "\n" << "Pop => " << st.Pop()->Data.Name << "\n" << endl;
    st.DisplayALL();

    Node* top = st.Peek();

    if (top == NULL) {
        cout << "Stack is EMPTY\n";
    }
    else {
        cout << "\n" << "Peek => " << top->Data.ID << " - " << top->Data.Name << endl;
    }

    cout << "\n======== TEST Queue (FIFO) ========\n";
    Queue q;

    q.EnQ(new Node(Employee(11,"A")));
    q.EnQ(new Node(Employee(22,"B")));
    q.EnQ(new Node(Employee(33,"C")));

    q.DisplayALL();

    cout << "\n" << "DeQ => " << q.DeQ()->Data.Name << "\n" << endl;
    q.DisplayALL();

    Node* front = q.Peek();
    if (front == NULL) {
        cout << "Queue is EMPTY\n";
    }
    else {
        cout << "\n" << "Peek => " << front->Data.ID << " - " << front->Data.Name << endl;
    }

    return 0;
}
