#include<iostream>
using namespace std;

struct Adj {
    int data;
    Adj* next;
};

struct grafo {
    int data;
    bool visitado;
    grafo* next;
    Adj* lista;
};

struct listaGrafo {
    int data;
    listaGrafo* next;
};

grafo* head = nullptr;
listaGrafo* head1 = nullptr;

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

    if (temp->lista == nullptr) {
        temp->lista = newAdj;
        return;
    }

    Adj* cur = temp->lista;
    while (cur->next != nullptr) {
        cur = cur->next;
    }

    cur->next = newAdj;
}

void PrintarListaAdj(Adj* cur) {
    if (cur == nullptr) {
        return;
    }
    PrintarListaReverse(cur->next);
    cout << cur->data << " ";
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
            PrintarListaAdj(cur);
        }
        cout << endl;
        temp = temp->next;
    }
}

void AddListaGrafo(listaGrafo*& head1, int n) {
    listaGrafo* newNode = new listaGrafo;
    newNode->data = n;
    newNode->next = nullptr;

    if (head1 == nullptr) {
        head1 = newNode;
        return;
    }

    listaGrafo* temp = head1;
    while (temp->next != nullptr) {
        temp = temp->next;
    }

    temp->next = newNode;
}

void PrintarListaGrafo(grafo* head, listaGrafo* head1) {
    if(head1 == nullptr) {
        AddListaGrafo(head1, 0);
    }
    
    while(head1 != nullptr) {
        
    }
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
            cout << endl << endl;
            
            break;
        }
    }
    
    return 0;
}
