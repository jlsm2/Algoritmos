#include<iostream>
using namespace std;

struct Adj {
    int data;
    Adj* next;
    Adj* prev;
};

struct grafo {
    int data;
    bool visitado;
    grafo* next;
    Adj* lista;
};

grafo* head = nullptr;

grafo* CriarVertices(grafo*& head, int vert) {
    grafo* newNode = new grafo;
    newNode->data = vert;
    newNode->next = nullptr;
    newNode->visitado = false;
    
    if(head == nullptr) {
        head = newNode;
    } 
    else {
        grafo* temp = head;
        while(temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void CriarAresta(grafo*& head, int v1, int v2) {
    grafo* temp = head;
    while (temp != nullptr && temp->data != v1) {
        temp = temp->next;
    }

    if (temp == nullptr) {
        return;
    }
    
    Adj* newAdj = new Adj;
    newAdj->data = v2;
    newAdj->next = nullptr;
    newAdj->prev = nullptr;

    if (temp->lista == nullptr) {
        temp->lista = newAdj;
        return;
    }

    Adj* cur = temp->lista;
    while (cur->next != nullptr) {
        cur = cur->next;
    }

    cur->next = newAdj;
    newAdj->prev = cur;
}

void Visitar(grafo* head, int n) {
    if (head == nullptr) {
        return;
    }
    if(head->data == n) {
        head->visitado = true;
        return;
    }
    Visitar(head->next, n);
}

bool ChecarStatus(grafo* head, int n) {
    if(head->data == n) {
        if(head->visitado) {
            return true;
        }
        return false;
    }
    ChecarStatus(head->next, n);
}

void PrintarListaAdj(Adj* tail) {
    while (tail != nullptr) {
        cout << tail->data << " ";
        tail = tail->prev;
    }
}

Adj* GetTail(Adj* lista) {
    if (lista == nullptr)
        return nullptr;

    while (lista->next != nullptr) {
        lista = lista->next;
    }
    return lista;
}

void PrintarTudo(grafo* head) {
    grafo* temp = head;
    while (temp != nullptr) {
        cout << temp->data << ": ";
        Adj* cur = temp->lista;
        if(cur == nullptr) {
            cout << "Lista Vazia";
        }
        else {
            Adj* tail = GetTail(cur);
            PrintarListaAdj(tail);
        }
        cout << endl;
        temp = temp->next;
    }
}

void PrintarListaGrafo(grafo* head) {
    
}

int main() {
    int v, v1, v2, continuar;
    cin >> v;
    
    for (int i=0;i<v;i++) {
        CriarVertices(head, i);
    }
    
    while(cin >> v1 >> v2 >> continuar) {
        CriarAresta(head, v1, v2);
        CriarAresta(head, v2, v1);
        if(continuar == 0) {
            PrintarTudo(head);
            cout << endl;
            if(head != nullptr) {
                cout << 0;
            }
            break;
        }
    }
    
    return 0;
}
