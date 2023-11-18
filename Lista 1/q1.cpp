#include <iostream>
using namespace std;

struct Node {
    int data;
    Node *next;
};

Node *top = NULL;

void push(int number) {
    Node *ptr = new Node();
    ptr->data = number;
    ptr->next = top;
    top = ptr;
}
 
void clearStack(Node** top) {
    Node* current = *top;
    Node* next = NULL;
    
    while (current!=NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    *top = NULL;
}
 
void stackSize() {
    int size = 0;
    Node *current = top;
    while(current!=NULL) {
        size++;
        current = current->next;
      }
    cout << size;
 }
 
void pop() {
    Node *ptr = top;
    top = top -> next;
    delete(ptr);
}

int main() {
    int t;
    int n = 1;
    cin >> t;
    
    for (int i=0;i<t;i++) {
        int numero;
        bool first = false;
        while (true) {
            cin >> numero;
            if (not first) {
                push(numero);
                first = true;
            }
            else {
                if (numero!=0) {
                    if ((numero%2==0 and top->data%2==0) or (numero%2!=0 and top->data%2!=0)) {
                        if (numero - top->data >= 0) {
                            numero = numero - top->data;
                            pop();
                            push(numero);
                        }
                        else {
                            numero = -(numero - top->data);
                            pop();
                            push(numero);
                        }
                    }
                    else {
                        push(numero);
                    }
                }
                else {
                    cout << "Pilha " << n << ": ";
                    stackSize();
                    cout << " " << top->data << "\n";
                    n++;
                    clearStack(&top);
                    break;
                }
            }
        }
    }

return 0;
}
