#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>    
#include <iomanip>  
using namespace std;

class LinkedList {
    struct node {
        string data;
        node* pre;
        node* next;
    };

public:
    node* head;

    LinkedList() {
        head = nullptr;
    }

    void push(string value) {
        node* newNode = new node;
        newNode->data = value;
        if (head == nullptr) {
            newNode->next = newNode;
            newNode->pre = newNode;
            head = newNode;
        } else {
            newNode->next = head;
            newNode->pre = head->pre;
            head->pre->next = newNode;
            head->pre = newNode; 
            head = newNode;
        }
    }

    string pop() {
        if (head == nullptr) {
            cout << "Error: pop() called on empty list." << endl;
            return "";
        }
        string value = head->data;
        node* poppedNode = head;
        if (head->next == head) {
            head = nullptr;
        } else {
            head->pre->next = head->next;
            head->next->pre = head->pre;
            head = head->next;
        }
        delete poppedNode;
        return value;
    }

    LinkedList read_Infix(string Equation) {
        LinkedList list;
        string temp;
        int i = 0;
        while (i < Equation.length()) {
            temp.clear();
            if (Equation[i] == '+' || Equation[i] == '-' || Equation[i] == '*' ||
                Equation[i] == '/' || Equation[i] == '(' || Equation[i] == ')' || Equation[i] == '^') {
                temp += Equation[i];
                i++; 
            } else {
                while (i < Equation.size() && Equation[i] != '+' && Equation[i] != '-' &&
                       Equation[i] != '*' && Equation[i] != '/' &&
                       Equation[i] != '(' && Equation[i] != ')' && Equation[i] != '^') {
                    temp += Equation[i];
                    i++;
                }
            }
            if (!temp.empty()) {
                list.push(temp);
            }
        }
        list.push(")");  
        list.reverse();
        return list;
    }

    LinkedList infixToPostfix(LinkedList list) {
        LinkedList stack1;  
        LinkedList stack2;  
        stack2.push("(");
        string data;
        int prec = 0;
        while (!list.isEmpty()) {
            data = list.pop();
            if (data != "+" && data != "-" && data != "*" && data != "/" &&
                data != "(" && data != ")" && data != "^") {
                stack1.push(data);
            } else if (data == "(") {
                stack2.push(data);
            } else if (data == "+" || data == "-" || data == "*" ||
                       data == "/" || data == "^") {
                prec = getPrecedence(data);
                while (!stack2.isEmpty() && prec <= getPrecedence(stack2.head->data)) {
                    stack1.push(stack2.pop());
                }
                stack2.push(data);
            } else if (data == ")") {
                while (!stack2.isEmpty() && stack2.head->data != "(") {
                    stack1.push(stack2.pop());
                }
                stack2.pop(); 
            }
        }
        while (!stack2.isEmpty()) {
            stack1.push(stack2.pop());
        }
        cout << "Postfix Expression: ";
        stack1.reverse();
        return stack1;
    }

    double converter(string val) {
        return stod(val);
    }

    string Addition(LinkedList &stack) {
        string a = stack.pop();
        string b = stack.pop();
        double num1 = converter(a);
        double num2 = converter(b);
        double result = num2 + num1;
        return to_string(result);
    }

    string subtraction(LinkedList &stack) {
        string a = stack.pop();
        string b = stack.pop();
        double num1 = converter(a);
        double num2 = converter(b);
        double result = num2 - num1;
        return to_string(result);
    }

    string Multiplication(LinkedList &stack) {
        string a = stack.pop();
        string b = stack.pop();
        double num1 = converter(a);
        double num2 = converter(b);
        double result = num2 * num1;
        return to_string(result);
    }

    string Division(LinkedList &stack) {
        string a = stack.pop();
        string b = stack.pop();
        double num1 = converter(a); 
        double num2 = converter(b); 
        if (num1 == 0.0) {
            return "Error";
        }
        double result = num2 / num1;
        return to_string(result);
    }

    string Power(LinkedList &stack) {
        string a = stack.pop();
        string b = stack.pop();
        double exponent = converter(a);
        double base = converter(b);
        double result = pow(base, exponent);
        return to_string(result);
    }

    void solver(LinkedList list) {
        LinkedList stack;
        string data;
        while (!list.isEmpty()) {
            data = list.pop();
            if (data != "+" && data != "-" && data != "*" &&
                data != "/" && data != "^") {
                stack.push(data);
            } else {
                if (data == "+") {
                    data = Addition(stack);
                    stack.push(data);
                } else if (data == "-") {
                    data = subtraction(stack);
                    stack.push(data);
                } else if (data == "*") {
                    data = Multiplication(stack);
                    stack.push(data);
                } else if (data == "/") {
                    data = Division(stack);
                    if (data == "Error") {
                        cout << endl << "ERROR: Indeterminate" << endl;
                        cout << "Division by zero is not allowed.";
                        return;
                    }
                    stack.push(data);
                } else if (data == "^") {
                    data = Power(stack);
                    stack.push(data);
                }
            }
        }
        if (data == "Error") {
            cout << endl << "Result: Undefined (No Result)";
            return;
        }
        cout << endl << "Result: ";
        stack.display();
    }

    bool checkoperaters(LinkedList list) {
        string temp = list.pop();
        while (!list.isEmpty()) {
            if (temp == "+" || temp == "-" || temp == "*" ||
                temp == "/" || temp == "^") {
                return true;
            }
            temp = list.pop();
        }
        return false;
    }

    void reverse() {
        if (head == nullptr || head->next == head)
            return;
        node* current = head;
        node* prev = current->pre;
        node* next = nullptr;
        do {
            next = current->next;
            current->next = prev;
            current->pre = next;
            prev = current;
            current = next;
        } while (current != head);
        head = prev; 
    }

    bool isEmpty() {
        return head == nullptr;
    }

    void display() {
        if (head == nullptr) {
            cout << "List is empty.";
            return;
        }
        node* temp = head;
        do {
            cout << temp->data << " ";
            temp = temp->next;
        } while (temp != head);
        cout << endl;
    }

    int getPrecedence(string op) {
        if (op == "+" || op == "-") {
            return 1;
        } else if (op == "*" || op == "/") {
            return 2;
        } else if (op == "^") {
            return 3;
        }
        return 0;
    }
};

int main() {
    system("cls");
    LinkedList list, list2, list3;
    string expression;
    cout << "Enter your expression: ";
    cin >> expression;
    cout << "*************Results*************" << endl;
    cout << "Your Expression: " << expression << endl;

    list2 = list.read_Infix(expression);
    list3 = list.infixToPostfix(list2);
    list3.display();

    list.solver(list3);

    return 0;
}