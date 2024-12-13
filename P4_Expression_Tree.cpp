#include <iostream>
#include <stack>
#include <string>
using namespace std;

// Node structure for the expression tree
struct Node {
    char data;
    Node* left;
    Node* right;

    Node(char value) : data(value), left(nullptr), right(nullptr) {}
};

class ExpressionTree {
public:
    Node* constructFromPostfix(const string& postfix) {
        stack<Node*> st;

        for (char c : postfix) {
            if (isalnum(c)) {
                st.push(new Node(c));
            } else {
                Node* node = new Node(c);
                node->right = st.top(); st.pop();
                node->left = st.top(); st.pop();
                st.push(node);
            }
        }

        return st.top();
    }

    Node* constructFromPrefix(const string& prefix) {
        stack<Node*> st;

        for (int i = prefix.length() - 1; i >= 0; --i) {
            if (isalnum(prefix[i])) {
                st.push(new Node(prefix[i]));
            } else {
                Node* node = new Node(prefix[i]);
                node->left = st.top(); st.pop();
                node->right = st.top(); st.pop();
                st.push(node);
            }
        }

        return st.top();
    }

    void recursiveInOrder(Node* root) {
        if (root == nullptr) return;
        recursiveInOrder(root->left);
        cout << root->data << " ";
        recursiveInOrder(root->right);
    }

    void recursivePreOrder(Node* root) {
        if (root == nullptr) return;
        cout << root->data << " ";
        recursivePreOrder(root->left);
        recursivePreOrder(root->right);
    }

    void recursivePostOrder(Node* root) {
        if (root == nullptr) return;
        recursivePostOrder(root->left);
        recursivePostOrder(root->right);
        cout << root->data << " ";
    }

    void nonRecursiveInOrder(Node* root) {
        stack<Node*> st;
        Node* current = root;

        while (current != nullptr || !st.empty()) {
            while (current != nullptr) {
                st.push(current);
                current = current->left;
            }
            current = st.top(); st.pop();
            cout << current->data << " ";
            current = current->right;
        }
    }

    void nonRecursivePreOrder(Node* root) {
        if (root == nullptr) return;

        stack<Node*> st;
        st.push(root);

        while (!st.empty()) {
            Node* node = st.top(); st.pop();
            cout << node->data << " ";

            if (node->right) st.push(node->right);
            if (node->left) st.push(node->left);
        }
    }

    void nonRecursivePostOrder(Node* root) {
        if (root == nullptr) return;

        stack<Node*> st1, st2;
        st1.push(root);

        while (!st1.empty()) {
            Node* node = st1.top(); st1.pop();
            st2.push(node);

            if (node->left) st1.push(node->left);
            if (node->right) st1.push(node->right);
        }

        while (!st2.empty()) {
            cout << st2.top()->data << " ";
            st2.pop();
        }
    }
};

int main() {
    ExpressionTree et;
    string postfix, prefix;

    cout << "Enter postfix expression: ";
    cin >> postfix;
    Node* postfixRoot = et.constructFromPostfix(postfix);

    cout << "Recursive In-order Traversal of Postfix Tree: ";
    et.recursiveInOrder(postfixRoot);
    cout << endl;

    cout << "Non-Recursive In-order Traversal of Postfix Tree: ";
    et.nonRecursiveInOrder(postfixRoot);
    cout << endl;

    cout << "Recursive Pre-order Traversal of Postfix Tree: ";
    et.recursivePreOrder(postfixRoot);
    cout << endl;

    cout << "Non-Recursive Pre-order Traversal of Postfix Tree: ";
    et.nonRecursivePreOrder(postfixRoot);
    cout << endl;

    cout << "Recursive Post-order Traversal of Postfix Tree: ";
    et.recursivePostOrder(postfixRoot);
    cout << endl;

    cout << "Non-Recursive Post-order Traversal of Postfix Tree: ";
    et.nonRecursivePostOrder(postfixRoot);
    cout << endl;

    cout << "Enter prefix expression: ";
    cin >> prefix;
    Node* prefixRoot = et.constructFromPrefix(prefix);

    cout << "Recursive In-order Traversal of Prefix Tree: ";
    et.recursiveInOrder(prefixRoot);
    cout << endl;

    cout << "Non-Recursive In-order Traversal of Prefix Tree: ";
    et.nonRecursiveInOrder(prefixRoot);
    cout << endl;

    cout << "Recursive Pre-order Traversal of Prefix Tree: ";
    et.recursivePreOrder(prefixRoot);
    cout << endl;

    cout << "Non-Recursive Pre-order Traversal of Prefix Tree: ";
    et.nonRecursivePreOrder(prefixRoot);
    cout << endl;

    cout << "Recursive Post-order Traversal of Prefix Tree: ";
    et.recursivePostOrder(prefixRoot);
    cout << endl;

    cout << "Non-Recursive Post-order Traversal of Prefix Tree: ";
    et.nonRecursivePostOrder(prefixRoot);
    cout << endl;

    return 0;
}