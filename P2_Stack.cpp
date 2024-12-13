#include <iostream>
#include <stack>
#include <string>
#include <cctype>
#include <cmath>
#include <algorithm>
using namespace std;

struct Node
{
    char data;
    Node *next;
};

class Stack
{
private:
    Node *top;

public:
    Stack() : top(nullptr) {}

    void push(char value)
    {
        Node *newNode = new Node;
        newNode->data = value;
        newNode->next = top;
        top = newNode;
    }

    char pop()
    {
        if (isEmpty())
        {
            throw runtime_error("Stack underflow");
        }
        Node *temp = top;
        char value = temp->data;
        top = top->next;
        delete temp;
        return value;
    }

    char peek()
    {
        if (isEmpty())
        {
            throw runtime_error("Stack is empty");
        }
        return top->data;
    }

    bool isEmpty()
    {
        return top == nullptr;
    }

    ~Stack()
    {
        while (!isEmpty())
        {
            pop();
        }
    }
};

int precedence(char op)
{
    if (op == '^')
        return 3;
    if (op == '*' || op == '/')
        return 2;
    if (op == '+' || op == '-')
        return 1;
    return 0;
}

bool isOperator(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

string infixToPostfix(const string &infix)
{
    Stack stack;
    string postfix;

    for (char c : infix)
    {
        if (isalnum(c))
        {
            postfix += c;
        }
        else if (c == '(')
        {
            stack.push(c);
        }
        else if (c == ')')
        {
            while (!stack.isEmpty() && stack.peek() != '(')
            {
                postfix += stack.pop();
            }
            stack.pop(); // Remove '('
        }
        else if (isOperator(c))
        {
            while (!stack.isEmpty() && precedence(stack.peek()) >= precedence(c))
            {
                postfix += stack.pop();
            }
            stack.push(c);
        }
    }

    while (!stack.isEmpty())
    {
        postfix += stack.pop();
    }

    return postfix;
}

string infixToPrefix(const string &infix)
{
    string reversedInfix;
    for (int i = infix.length() - 1; i >= 0; --i)
    {
        if (infix[i] == '(')
            reversedInfix += ')';
        else if (infix[i] == ')')
            reversedInfix += '(';
        else
            reversedInfix += infix[i];
    }

    string reversedPostfix = infixToPostfix(reversedInfix);
    reverse(reversedPostfix.begin(), reversedPostfix.end());

    return reversedPostfix;
}

int evaluatePostfix(const string &postfix)
{
    stack<int> evalStack;

    for (char c : postfix)
    {
        if (isdigit(c))
        {
            evalStack.push(c - '0');
        }
        else if (isOperator(c))
        {
            int b = evalStack.top();
            evalStack.pop();
            int a = evalStack.top();
            evalStack.pop();

            switch (c)
            {
            case '+':
                evalStack.push(a + b);
                break;
            case '-':
                evalStack.push(a - b);
                break;
            case '*':
                evalStack.push(a * b);
                break;
            case '/':
                evalStack.push(a / b);
                break;
            case '^':
                evalStack.push(pow(a, b));
                break;
            }
        }
    }

    return evalStack.top();
}

int evaluatePrefix(const string &prefix)
{
    stack<int> evalStack;

    for (int i = prefix.length() - 1; i >= 0; --i)
    {
        char c = prefix[i];

        if (isdigit(c))
        {
            evalStack.push(c - '0');
        }
        else if (isOperator(c))
        {
            int a = evalStack.top();
            evalStack.pop();
            int b = evalStack.top();
            evalStack.pop();

            switch (c)
            {
            case '+':
                evalStack.push(a + b);
                break;
            case '-':
                evalStack.push(a - b);
                break;
            case '*':
                evalStack.push(a * b);
                break;
            case '/':
                evalStack.push(a / b);
                break;
            case '^':
                evalStack.push(pow(a, b));
                break;
            }
        }
    }

    return evalStack.top();
}

int main()
{
    string infix;

    cout << "Enter an infix expression: ";
    cin >> infix;

    string postfix = infixToPostfix(infix);
    string prefix = infixToPrefix(infix);

    cout << "Postfix: " << postfix << endl;
    cout << "Prefix: " << prefix << endl;

    cout << "Postfix Evaluation: " << evaluatePostfix(postfix) << endl;
    cout << "Prefix Evaluation: " << evaluatePrefix(prefix) << endl;

    return 0;
}