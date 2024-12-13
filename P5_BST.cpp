#include <iostream>
#include <queue>
#include <stack>
#include <vector>
using namespace std;

// Node structure for the binary search tree
struct Node
{
    int data;
    Node *left;
    Node *right;

    Node(int value) : data(value), left(nullptr), right(nullptr) {}
};

class BinarySearchTree
{
private:
    Node *root;

    Node *insert(Node *node, int value)
    {
        if (node == nullptr)
            return new Node(value);

        if (value < node->data)
            node->left = insert(node->left, value);
        else if (value > node->data)
            node->right = insert(node->right, value);
        else
            cout << "Duplicate value " << value << " not inserted." << endl;

        return node;
    }

    Node *deleteNode(Node *node, int value)
    {
        if (node == nullptr)
            return node;

        if (value < node->data)
            node->left = deleteNode(node->left, value);
        else if (value > node->data)
            node->right = deleteNode(node->right, value);
        else
        {
            // Node with only one child or no child
            if (node->left == nullptr)
            {
                Node *temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr)
            {
                Node *temp = node->left;
                delete node;
                return temp;
            }

            // Node with two children: Get the inorder successor
            Node *temp = minValueNode(node->right);
            node->data = temp->data;
            node->right = deleteNode(node->right, temp->data);
        }

        return node;
    }

    Node *minValueNode(Node *node)
    {
        Node *current = node;
        while (current && current->left != nullptr)
            current = current->left;
        return current;
    }

    void inOrder(Node *node)
    {
        if (node == nullptr)
            return;
        inOrder(node->left);
        cout << node->data << " ";
        inOrder(node->right);
    }

    void preOrder(Node *node)
    {
        if (node == nullptr)
            return;
        cout << node->data << " ";
        preOrder(node->left);
        preOrder(node->right);
    }

    void postOrder(Node *node)
    {
        if (node == nullptr)
            return;
        postOrder(node->left);
        postOrder(node->right);
        cout << node->data << " ";
    }

    int calculateDepth(Node *node)
    {
        if (node == nullptr)
            return 0;
        return 1 + max(calculateDepth(node->left), calculateDepth(node->right));
    }

    Node *mirror(Node *node)
    {
        if (node == nullptr)
            return nullptr;
        Node *mirrored = new Node(node->data);
        mirrored->left = mirror(node->right);
        mirrored->right = mirror(node->left);
        return mirrored;
    }

    Node *copyTree(Node *node)
    {
        if (node == nullptr)
            return nullptr;
        Node *newNode = new Node(node->data);
        newNode->left = copyTree(node->left);
        newNode->right = copyTree(node->right);
        return newNode;
    }

    void displayParentChild(Node *node)
    {
        if (node == nullptr)
            return;
        if (node->left)
            cout << node->data << " -> " << node->left->data << endl;
        if (node->right)
            cout << node->data << " -> " << node->right->data << endl;
        displayParentChild(node->left);
        displayParentChild(node->right);
    }

    void displayLeafNodes(Node *node)
    {
        if (node == nullptr)
            return;
        if (node->left == nullptr && node->right == nullptr)
        {
            cout << node->data << " ";
            return;
        }
        displayLeafNodes(node->left);
        displayLeafNodes(node->right);
    }

    void levelOrderTraversal(Node *node)
    {
        if (node == nullptr)
            return;
        queue<Node *> q;
        q.push(node);

        while (!q.empty())
        {
            Node *current = q.front();
            q.pop();
            cout << current->data << " ";

            if (current->left)
                q.push(current->left);
            if (current->right)
                q.push(current->right);
        }
    }

public:
    BinarySearchTree() : root(nullptr) {}

    void insert(int value)
    {
        root = insert(root, value);
    }

    void deleteValue(int value)
    {
        root = deleteNode(root, value);
    }

    void search(int value)
    {
        Node *current = root;
        while (current != nullptr)
        {
            if (current->data == value)
            {
                cout << "Value " << value << " found in the tree." << endl;
                return;
            }
            else if (value < current->data)
            {
                current = current->left;
            }
            else
            {
                current = current->right;
            }
        }
        cout << "Value " << value << " not found in the tree." << endl;
    }

    void displayInOrder()
    {
        cout << "In-order Traversal: ";
        inOrder(root);
        cout << endl;
    }

    void displayPreOrder()
    {
        cout << "Pre-order Traversal: ";
        preOrder(root);
        cout << endl;
    }

    void displayPostOrder()
    {
        cout << "Post-order Traversal: ";
        postOrder(root);
        cout << endl;
    }

    void displayDepth()
    {
        cout << "Depth of the tree: " << calculateDepth(root) << endl;
    }

    void displayMirrorImage()
    {
        Node *mirroredRoot = mirror(root);
        cout << "Mirror Image (In-order): ";
        inOrder(mirroredRoot);
        cout << endl;
    }

    void createCopy()
    {
        Node *copiedRoot = copyTree(root);
        cout << "Copy of the tree (In-order): ";
        inOrder(copiedRoot);
        cout << endl;
    }

    void displayParentChildNodes()
    {
        cout << "Parent -> Child Nodes: " << endl;
        displayParentChild(root);
    }

    void displayLeafNodes()
    {
        cout << "Leaf Nodes: ";
        displayLeafNodes(root);
        cout << endl;
    }

    void displayLevelWise()
    {
        cout << "Level-wise Traversal: ";
        levelOrderTraversal(root);
        cout << endl;
    }
};

int main()
{
    BinarySearchTree bst;
    int choice, value;

    do
    {
        cout << "\nMenu:\n1. Insert\n2. Delete\n3. Search\n4. In-order Traversal\n5. Pre-order Traversal\n6. Post-order Traversal\n7. Display Depth\n8. Display Mirror Image\n9. Create Copy\n10. Display Parent-Child Nodes\n11. Display Leaf Nodes\n12. Level-wise Traversal\n13. Exit\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter value to insert: ";
            cin >> value;
            bst.insert(value);
            break;
        case 2:
            cout << "Enter value to delete: ";
            cin >> value;
            bst.deleteValue(value);
            break;
        case 3:
            cout << "Enter value to search: ";
            cin >> value;
            bst.search(value);
            break;
        case 4:
            bst.displayInOrder();
            break;
        case 5:
            bst.displayPreOrder();
            break;
        case 6:
            bst.displayPostOrder();
            break;
        case 7:
            bst.displayDepth();
            break;
        case 8:
            bst.displayMirrorImage();
            break;
        case 9:
            bst.createCopy();
            break;
        case 10:
            bst.displayParentChildNodes();
            break;
        case 11:
            bst.displayLeafNodes();
            break;
        case 12:
            bst.displayLevelWise();
            break;
        case 13:
            cout << "Exiting program." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 13);

    return 0;
}