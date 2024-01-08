#include <iostream>
#include <string>
using namespace std;

struct ocupantes {
    int prioridade, numRegistro;
    string nome;
};

struct assentos {
    int value;
    ocupantes** heap;
};

struct fila {
    int value;
    assentos** table;
};

ocupantes* criar(string nome; int prioridade; int numRegistro) {
    ocupantes* newNode = new ocupantes;
    newNode->nome = nome;
    newNode->prioridade = prioridade;
    newNode->numRegistro = numRegistro;
    return newNode;
}

int hashFunction(fila* hashtable, int numFileira, int numAssentos) {
    for(int i=0;i<numFileira;i++) {
        for(int j=0;j<numAssentos;j++) {
            if(hashtable->table[i]->heap[j] == nullptr) {
                return i;
            }
        }
    }
    
    return -1;
}

void maxheapify(ocupantes* arr[], int n, int i) {
    int largest = i;
    int l = 2*i + 1;
    int r = 2*i + 2;
    
    if(r < n && arr[r]->prioridade > arr[largest]->prioridade) {
        largest = r;
    }
 
    if(l < n && arr[l]->prioridade > arr[largest]->prioridade) {
        largest = l;
    }

    if(largest != i) {
        swap(arr[i], arr[largest]);
        maxheapify(arr, n, largest);
    }
}

void insertmaxheap(assentos* assento, ocupantes* ocupante) {
    assento->heap[assento->value] = ocupante;
    ++assento->value;
    buildmaxheap(assento->heap, assento->value);
}

void buildmaxheap(ocupantes* arr[], int n) {
    if(n>=2) {
        for(int i=(n/2) - 1; i>=0;i--) {
            maxheapify(arr, n, i);
        }
    }
}

// não mudar ate aqui
// mudar antes daqui ta tudo certo

void cadastrar(fileiras* head1, assentos* head2, string name, int priority, int numCadastro) {
    if (head2 == nullptr && head1 == nullptr) {
        head2->value = name;
        head2->priority = priority;
        head2->fil = i;
        head2->sentada = true;
        head1->cadeirasOcupadas+=1;
    }
    else {
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
                    alocada = true;
                    break;
                }
            }
            if(alocada) {
                break;
            }
            else {
                i++;
            }
        }
    }
    if(alocada) {
        cout << name << " (" << numCadastro << ") " << "foi alocado(a) na fileira " << head2->fil << "\n";
    }
    else {
        cout << name << " (" << numCadastro << ") " << "nao foi alocado(a) em nenhuma fileira" << "\n";
    }
}

void ver(fileiras* head1, assentos* head2, string name) {
    bool achou = false;
    while(head1 != nullptr) {
        while(head2 != nullptr) {
            if(head2->value == name) {
                cout << "Sentado(a) na fileira " << head2->fil << "\n";
                achou = true;
                break;
            }
            else {
                head2 = head2->next;
            }
        }
        if(achou) {
            break;
        }
    }
    if(!achou) {
        cout << "Inexistente" << "\n";
    }
}

void remover(fileiras* head1, assentos* head2, string name) {
    bool removeu = false;
    while(head1 != nullptr) {
        while(head2 != nullptr) {
            if(head2->value == name) {
                cout << "Removido(a)" << "\n";
                removeu = true;
                head2->value = "";
                head2->sentada = false;
                head2->priority = 0;
                break;
            }
            else {
                head2 = head2->next;
            }
        }
        if(removeu) {
            break;
        }
    }
    if(!removeu) {
        cout << "Inexistente" << "\n";
    }
}

int main() {
    int numFileiras, numAssentos, n, p, numCadastro = 1;
    string command, name;
    cin >> numFileiras >> numAssentos >> n;
    
    fileiras* head1 = nullptr;
    assentos* head2 = nullptr;
    
    fileiras* totalFileiras = criarFileiras(numFileiras);
    assentos* totalAssentos = criarAssentos(numAssentos);
    
    for(int i=0;i<n;i++) {
        cin >> command >> name >> p;
        if(command == "CAD") {
            cadastrar(head1, head2, name, p, numCadastro);
            numCadastro+=1;
        }
        else if (command == "VER") {
            ver(head1, head2, name);
        }
        else if (command == "REM") {
            remover(head1, head2, name);
        }
    }
    
    
    return 0;
}
