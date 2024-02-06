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

void RemoverListasAdj(grafo* head, int n) {
    grafo* temp = head;
    while (temp != nullptr) {
        Adj* cur = temp->lista;
        Adj* prev = nullptr;
        while (cur != nullptr) {
            if (cur->data == n) {
                if (prev == nullptr) {
                    temp->lista = cur->next;
                    if (cur->next != nullptr) {
                        cur->next->prev = nullptr;
                    }
                    delete cur;
                    cur = temp->lista;
                } 
                else {
                    prev->next = cur->next;
                    if (cur->next != nullptr) {
                        cur->next->prev = prev;
                    }
                    delete cur;
                    cur = prev->next;
                }
            } 
            else {
                prev = cur;
                cur = cur->next;
            }
        }
        temp = temp->next;
    }
}


void PrintarListaGrafo(grafo* head, int vert) {
    grafo* temp = head;
    while(vert>=1) {
        if(temp->lista != nullptr) {
            Adj* tail = GetTail(temp->lista);
            cout << tail->data << " ";
            while(temp->data != tail->data) {
                if(temp == nullptr) {
                    temp = head;
                }
                temp = temp->next;
            }
            RemoverListasAdj(head, tail->data);
            vert--;
        }
        else {
            temp = head->next;
        }
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
            cout << endl;
            if(head != nullptr) {
                cout << 0 << " ";
                RemoverListasAdj(head, 0);
                PrintarListaGrafo(head, v);
            }
            break;
        }
    }
    
    return 0;
}
