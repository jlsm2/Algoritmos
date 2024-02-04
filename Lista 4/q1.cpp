#include <bits/stdc++.h>
using namespace std;

struct Adj {
    int data;
    Adj* next
    Adj* prev;
};

Adj* head = nullptr;

Adj* CriarNode(int data) {
    Adj* newNode = new Adj;
    newNode->data = data;
    newNode->next = nullptr;
    newNode->prev = nullptr;
}

void CriarArestas(int v1, int v2) {
    
}

int main() {
    int vertices, v1, v2, continuar;
    cin >> vertices;
    
    for (int i=0;i<vertices;i++) {
        CriarNode(i);
    }
    
    while (cin >> v1 >> v2 >> continuar) {
        
    }
    
    return 0;
}
