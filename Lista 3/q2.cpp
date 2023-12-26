#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct fileiras {
    int cadeiraOcupadas;
    fileiras* down;
    fileiras* head1;
};

struct assentos {
    int priority, fil;
    string value;
    bool sentada;
    assentos* head2;
    assentos* next;
};

assentos* criarAssento() {
    assentos* newNode = new assentos;
    newNode->value = "";
    newNode->sentada = false;
    newNode->priority = 0;
    newNode->fil = 0;
    newNode->next = nullptr;
    return newNode;
}

fileiras* criarFileira() {
    fileiras* newNode = new fileiras;
    newNode->cadeirasOcupadas = 0;
    newNode->down = nullptr;
    return newNode;
}

fileiras* criarFileiras(int n) {
    if (n <= 0) {
        return nullptr;
    }

    fileiras* head1 = criarFileira();
    fileiras* current = head1;

    for (int i=2;i<=n;++i) {
        current->down = criarFileira();
        current = current->down;
    }
    
    return head1;
}

assentos* criarAssentos(int n) {
    if (n <= 0) {
        return nullptr;
    }

    assentos* head2 = criarAssento();
    assentos* current = head2;

    for (int i=2;i<=n;++i) {
        current->next = criarAssento();
        current = current->next;
    }
    
    return head2;
}

void cadastrar(fileiras* head1, assentos* head2, string name, int priority, int numCadastro) {
    int i = 1;
    while(head1 != nullptr) {
        while(head2 != nullptr) {
            if(head2->sentada) {
                head2 = head2->next;
            }
            else {
                head2->value = name;
                head2->priority = priority;
                head2->fil = i;
                head2->sentada = true;
                head1->cadeirasOcupadas+=1;
                break;
            }
        }
        if(head2 != nullptr) {
            break;
        }
        else {
            i++;
        }
    }
    
    if(head1 != nullptr && head2 != nullptr) {
        cout << name << " (" << numCadastro << ") " << "foi alocado(a) na fileira " << head2->fil << "\n";
    }
    else {
        cout << name << " (" << numCadastro << ") " << " nao foi alocado(a) em nenhuma fileira" << "\n";
    }
}

void ver(fileiras* head1, assentos* head2, string name) {
    int i = 1;
    bool achou = false;
    while(head1 != nullptr) {
        while(head2 != nullptr) {
            if(head2->value == name) {
                 
            }
        }
    }
}

int main() {
    int numFileiras, numAssentos, n, p, numCadastro = 1;
    string command, name;
    cin >> numFileiras >> numAssentos >> n;
    
    fileiras* totalFileiras = criarFileiras(numFileiras);
    assentos* totalAssentos = criarAssentos(numAssentos);
    
    for(int i=0;i<n;i++) {
        cin >> command >> name >> p;
        if(command == "CAD") {
            cadastrar(head1, head2, name, p, numCadastro);
            numCadastro+=1;
        }
        else if (command == "VER") {
            
        }
        else if (command == "REM") {
            
        }
    }
    
    
    return 0;
}
