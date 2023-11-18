#include <iostream>
#include <string>

using namespace std;

struct NodeEsquerda  {
    int data;
    struct NodeEsquerda* next;
    struct NodeEsquerda* prev;
};

struct NodeDireita  {
    int data;
    struct NodeDireita* next;
    struct NodeDireita* prev;
};

struct NodeEsquerda* headEsquerda;
struct NodeDireita* headDireita;

struct NodeEsquerda* GetNewNodeE(int info) {
    NodeEsquerda* newNode = new NodeEsquerda;
    newNode->data = info;
    newNode->prev = nullptr;
    newNode->next = nullptr;
    return newNode;
}

struct NodeDireita* GetNewNodeD(int info) {
    NodeDireita* newNode = new NodeDireita;
    newNode->data = info;
    newNode->prev = nullptr;
    newNode->next = nullptr;
    return newNode;
}

void InsertNodeEsquerda(int info) {
    struct NodeEsquerda* newNode = GetNewNodeE(info);
    if(headEsquerda == nullptr) {
        headEsquerda = newNode;
        return;
    }
    headEsquerda->prev = newNode;
    newNode->next = headEsquerda; 
    headEsquerda = newNode;
}

void InsertNodeDireita(int info) {
    struct NodeDireita* newNode = GetNewNodeD(info);
    if(headDireita == nullptr) {
        headDireita = newNode;
        return;
    }
    headDireita->prev = newNode;
    newNode->next = headDireita; 
    headDireita = newNode;
}

void deleteEsquerda(NodeEsquerda** headEsquerda, NodeEsquerda* del)  {

    if (*headEsquerda == del)  
        *headEsquerda = del->next;  

    if (del->next != nullptr)  
        del->next->prev = del->prev;  

    if (del->prev != nullptr)  
        del->prev->next = del->next;  
  
    free(del);  
    return;  
}

void deleteDireita(NodeDireita** headDireita, NodeDireita* del)  {

    if (*headDireita == del)  
        *headDireita = del->next;  

    if (del->next != nullptr)  
        del->next->prev = del->prev;  

    if (del->prev != nullptr)  
        del->prev->next = del->next;  
  
    free(del);  
    return;  
}

int main() {

    int t;
    cin >> t;
    int caso = 1;
    
    for (int i=0;i<t;i++) {
        int C;
        int n;
        int viagens = 0;
        bool esquerda = true;
        
        cin >> C >> n;

        int compCarrosBalsa = 0;

        for (int j=0;j<n;j++) {
            int k;
            string lado;
            
            cin >> k >> lado;
            
            if (lado == "esquerdo") {
                InsertNodeEsquerda(k);
            }
            else {
                InsertNodeDireita(k);
            }
        }
        while (true) {
            if (headEsquerda == nullptr && headDireita == nullptr){
                break;
            }
            
            if (esquerda) {
                if (headEsquerda != nullptr && headEsquerda->data+compCarrosBalsa<=C*100) {
                    compCarrosBalsa+=headEsquerda->data;
                    deleteEsquerda(&headEsquerda, headEsquerda);
                    if (headEsquerda==nullptr) {
                        viagens++;
                        esquerda = false;
                        compCarrosBalsa = 0;
                    }
                }
                else {
                    esquerda = false;
                    viagens++;
                    compCarrosBalsa = 0;
                }
            }
            else {
                if (headDireita != nullptr && headDireita->data+compCarrosBalsa<=C*100) {
                    compCarrosBalsa+=headDireita->data;
                    deleteDireita(&headDireita, headDireita);
                    if (headDireita==nullptr) {
                        viagens++;
                        esquerda = true;
                        compCarrosBalsa = 0;
                    }
                }
                else {
                    esquerda = true;
                    viagens++;
                    compCarrosBalsa = 0;
                }
            }
        }
        
        cout << "Caso " << caso << ": " << viagens << "\n";
        caso++;
    }
    return 0;
}
