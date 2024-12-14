#include <iostream>
using namespace std;

// Node structure for the In-order Threaded Binary Tree
struct Node
{
    int data;
    Node *left;
    Node *right;
    bool isThreaded; // true if right points to the in-order successor

    Node(int value) : data(value), left(nullptr), right(nullptr), isThreaded(false) {}
};

class ThreadedBinaryTree
{
private:
    Node *root;

    Node *insert(Node *root, int value)
    {
        if (root == nullptr)
            return new Node(value);

        if (value < root->data)
            root->left = insert(root->left, value);
        else if (value > root->data)
        {
            if (root->isThreaded)
            {
                Node *temp = new Node(value);
                temp->right = root->right;
                temp->isThreaded = true;
                root->right = temp;
                root->isThreaded = false;
            }
            else
            {
                root->right = insert(root->right, value);
            }
        }

        return root;
    }

    Node *leftmost(Node *node)
    {
        while (node && node->left != nullptr)
            node = node->left;
        return node;
    }

public:
    ThreadedBinaryTree() : root(nullptr) {}

    void insert(int value)
    {
        root = insert(root, value);
    }

    void inOrderTraversal()
    {
        Node *current = leftmost(root);
        while (current != nullptr)
        {
            cout << current->data << " ";
            if (current->isThreaded)
                current = current->right;
            else
                current = leftmost(current->right);
        }
        cout << endl;
    }

    void preOrderTraversal()
    {
        Node *current = root;
        while (current != nullptr)
        {
            cout << current->data << " ";

            if (current->left)
                current = current->left;
            else if (!current->isThreaded)
                current = current->right;
            else
                current = nullptr;
        }
        cout << endl;
    }
};

int main()
{
    ThreadedBinaryTree tbt;
    int choice, value;

    do
    {
        cout << "\nMenu:\n1. Insert\n2. In-order Traversal\n3. Pre-order Traversal\n4. Exit\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter value to insert: ";
            cin >> value;
            tbt.insert(value);
            break;
        case 2:
            cout << "In-order Traversal: ";
            tbt.inOrderTraversal();
            break;
        case 3:
            cout << "Pre-order Traversal: ";
            tbt.preOrderTraversal();
            break;
        case 4:
            cout << "Exiting program." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 4);

    return 0;
}
