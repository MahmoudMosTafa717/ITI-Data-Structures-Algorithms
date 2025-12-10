#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
using namespace std;

// =========================== EMPLOYEE CLASS ===========================

class Employee
{
    int id;
    string name;

public:
    Employee(int id, string name)
        : id(id), name(name) {}

    int getId() const { return id; }
    string getName() const { return name; }

    void setId(int id) { this->id = id; }
    void setName(string name) { this->name = name; }
};

// ============================== NODE CLASS ============================

class Node
{
public:
    Employee data;
    Node *left;
    Node *right;

    Node(Employee emp) : data(emp), left(nullptr), right(nullptr) {}
};

// =============================== BST CLASS ============================

class BST
{
    Node *root;

    // ========== Insert Helper ==========
    // Handle recursive logic of inserting a node into the tree.
    Node *insertNode(Node *node, const Employee &emp)
    {
        if (node == nullptr)
            return new Node(emp);

        if (emp.getId() < node->data.getId())
            node->left = insertNode(node->left, emp);

        else if (emp.getId() > node->data.getId())
            node->right = insertNode(node->right, emp);

        return node;
    }

    // ========== Search Helper ==========
    Node *findNode(Node *node, int id)
    {
        if (!node)
            return nullptr;

        if (id == node->data.getId())
            return node;

        if (id < node->data.getId())
            return findNode(node->left, id);

        return findNode(node->right, id);
    }

    // ========== Find Max Helper (used in delete) ==========
    Node *findMax(Node *node)
    {
        while (node->right)
            node = node->right;
        return node;
    }

    // ========== Height Helper ==========
    int height(Node *node)
    {
        if (!node)
            return 0;
        return max(height(node->left), height(node->right)) + 1;
    }

    // ========== Check if Tree Balanced ==========
    bool checkBalance(Node *node)
    {
        if (!node)
            return true;

        int lh = height(node->left);
        int rh = height(node->right);

        if (abs(lh - rh) > 1)
            return false;

        return checkBalance(node->left) && checkBalance(node->right);
    }

    // ========== Store Nodes Inorder ==========
    void storeInOrder(Node *node, vector<Employee> &arr)
    {
        if (!node)
            return;

        storeInOrder(node->left, arr);
        arr.push_back(node->data);
        storeInOrder(node->right, arr);
    }

    // ========== Build Balanced Tree ==========
    Node *buildBalancedTree(vector<Employee> &arr, int left, int right)
    {
        if (left > right)
            return nullptr;

        int mid = (left + right) / 2;
        Node *node = new Node(arr[mid]);

        node->left = buildBalancedTree(arr, left, mid - 1);
        node->right = buildBalancedTree(arr, mid + 1, right);

        return node;
    }

    // ========== Balance the whole tree ==========
    void balanceTree()
    {
        if (checkBalance(root))
            return;

        vector<Employee> arr;
        storeInOrder(root, arr);

        root = buildBalancedTree(arr, 0, arr.size() - 1);
    }

    // ========== Delete Helper ==========
    Node *deleteNode(Node *node, int id)
    {
        if (!node)
            return nullptr;

        if (id < node->data.getId())
            node->left = deleteNode(node->left, id);

        else if (id > node->data.getId())
            node->right = deleteNode(node->right, id);

        else
        {
            if (!node->left)
            {
                Node *temp = node->right;
                delete node;
                return temp;
            }
            if (!node->right)
            {
                Node *temp = node->left;
                delete node;
                return temp;
            }

            Node *temp = findMax(node->left);
            node->data = temp->data;
            node->left = deleteNode(node->left, temp->data.getId());
        }

        return node;
    }

    // ========== Inorder Print ==========
    void inorderTraversal(Node *node)
    {
        if (!node)
            return;

        inorderTraversal(node->left);
        cout << "ID: " << node->data.getId()
             << ", Name: " << node->data.getName() << endl;
        inorderTraversal(node->right);
    }

public:
    BST() : root(nullptr) {}

    // ================== Public Insert ==================
    void insert(const Employee &emp)
    {
        // Check duplication
        if (findNode(root, emp.getId()))
            cout << "Employee already exists!" <<endl;

        root = insertNode(root, emp);
        balanceTree();
    }

    // ================== Public Search ==================
    Employee search(int id)
    {
        Node *node = findNode(root, id);
        if (!node)
            throw runtime_error("Employee not found!");
        return node->data;
    }

    // ================== Public Delete ==================
    void deleteNode(int id)
    {
        if (!findNode(root, id))
            throw runtime_error("Employee not found!");

        root = deleteNode(root, id);
        balanceTree();
    }

    // ================== Print Tree ==================
    void printTree()
    {
        inorderTraversal(root);
    }

    // ================== Count Nodes ==================
    int countNodes(Node *node)
    {
        if (!node)
            return 0;
        return 1 + countNodes(node->left) + countNodes(node->right);
    }

    int countNodes() { return countNodes(root); }

    // ================== Count Levels ==================
    int countLevels() { return height(root); }
};

// ============================= MAIN FUNCTION =============================

int main()
{
    BST tree;

    tree.insert(Employee(10, "Ahmed"));
    tree.insert(Employee(5, "Omar"));
    tree.insert(Employee(20, "Youssef"));
    tree.insert(Employee(3, "Mona"));
    tree.insert(Employee(7, "Sara"));
    tree.insert(Employee(15, "Ali"));
    tree.insert(Employee(30, "Laila"));

    tree.printTree();

    cout << "\nFound: " << tree.search(7).getName() << endl;

    cout << "\nDeleting ID 5...\n";
    tree.deleteNode(5);

    tree.printTree();

    cout << "\nTotal nodes: " << tree.countNodes() << endl;
    cout << "Levels: " << tree.countLevels() << endl;

    return 0;
}
