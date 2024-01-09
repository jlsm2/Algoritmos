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

ocupantes* criar(string nome, int prioridade, int numRegistro) {
    ocupantes* newNode = new ocupantes;
    newNode->nome = nome;
    newNode->prioridade = prioridade;
    newNode->numRegistro = numRegistro;
    return newNode;
}

int hashFunction(fila* fila, int numFileira, int numAssentos) {
    for(int i=0;i<numFileira;i++) {
        for(int j=0;j<numAssentos;j++) {
            if(fila->table[i]->heap[j] == nullptr) {
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

void minheapify(ocupantes* arr[], int n, int i) {
    int smallest = i;
    int l = 2*i + 1;
    int r = 2*i + 2;
    
    if(r < n && arr[r]->prioridade < arr[smallest]->prioridade) {
        smallest = r;
    }
 
    if(l < n && arr[l]->prioridade < arr[smallest]->prioridade) {
        smallest = l;
    }

    if(smallest != i) {
        swap(arr[i], arr[smallest]);
        maxheapify(arr, n, smallest);
    }
}

void buildmaxheap(ocupantes* arr[], int n) {
    if(n>=2) {
        for(int i=(n/2) - 1;i>=0;i--) {
            maxheapify(arr, n, i);
        }
    }
}

void buildminheap(ocupantes* arr[], int n) {
    if(n>=2) {
        for(int i=(n/2) - 1;i>=0;i--) {
            minheapify(arr, n, i);
        }
    }
}

void insertmaxheap(assentos* assento, ocupantes* ocupante) {
    assento->heap[assento->value] = ocupante;
    ++assento->value;
    buildmaxheap(assento->heap, assento->value);
}

void insertminheap(assentos* assento, ocupantes* ocupante) {
    if(assento->heap[assento->value-1] == nullptr) {
        assento->heap[assento->value-1] = ocupante;
    }
    else {
        assento->heap[assento->value] = ocupante;
        ++assento->value;
    }
    buildminheap(assento->heap, assento->value);
}

ocupantes* removemaxheap(assentos* assento) {
    if(assento->value == 1) {
        assento->value--;
        return assento->heap[0];
    }

    ocupantes* root = assento->heap[0];
    assento->heap[0] = assento->heap[assento->value-1];
    assento->value--;

    maxheapify(assento->heap, assento->value, 0);

    return root;
}

ocupantes* removeminheap(assentos* assento) {
    if(assento->value == 1) {
        assento->value--;
        return assento->heap[0];
    }

    ocupantes* root = assento->heap[0];
    assento->heap[0] = assento->heap[assento->value-1];
    assento->value--;

    minheapify(assento->heap, assento->value, 0);

    return root;
}


// não mudar ate aqui
// mudar antes daqui ta tudo certo

void cadastrar(int numFileiras, int numAssentos, ocupantes* ocupante, fila* fila, assentos* espera) {
    int numFileira = hashFunction(fila, numFileiras, numAssentos);

    if(numFileira == -1) {
        int fileiraMenor = -1;
        ocupantes* ocupanteMenor = nullptr;

        for(int i = 0; i < numFileiras; i++) {
            ocupantes* atual = fila->table[i]->heap[0];
            if(ocupanteMenor == nullptr || atual->prioridade < ocupanteMenor->prioridade) {
                ocupanteMenor = atual;
                fileiraMenor = i;
            }
        }
        ocupantes* atual = removeminheap(fila->table[fileiraMenor]);

        if(atual->prioridade > ocupante->prioridade) {
            insertmaxheap(espera, ocupante); 
            insertminheap(fila->table[fileiraMenor], atual); 
            cout << ocupante->nome << " (" << ocupante->numRegistro << ") nao foi alocado(a) em nenhuma fileira" << "\n";
            
        }
        else if(atual->prioridade < ocupante->prioridade) {
            insertmaxheap(espera, atual);
            insertminheap(fila->table[fileiraMenor], ocupante);

            cout << ocupante->nome << " (" << ocupante->numRegistro << ") foi alocado(a) na fileira " << fileiraMenor + 1 << "\n";

        }
        else {
            if(atual->numRegistro < ocupante->numRegistro) {
                insertmaxheap(espera, ocupante);
                insertminheap(fila->table[fileiraMenor], atual); 

                cout << ocupante->nome << " (" << ocupante->numRegistro << ") nao foi alocado(a) em nenhuma fileira" << "\n";

            }
            else {
                insertmaxheap(espera, atual);
                insertminheap(fila->table[fileiraMenor], ocupante);

                cout << ocupante->nome << " (" << ocupante->numRegistro << ") foi alocado(a) na fileira " << fileiraMenor + 1 << "\n";

            }
        }
    }
    else {
        cout << ocupante->nome << " (" << ocupante->numRegistro << ") foi alocado(a) na fileira " << numFileira + 1 << "\n";
        insertminheap(fila->table[numFileira], ocupante);
    }
}

void ver(int numFileiras, int numAssentos, int registro, string nome, fila* fila, assentos* espera) {
    bool inexistente = true;
    bool semAssento = false;
    for(int i = 0; i < numFileiras; i++) {
        for(int j = 0; j < numAssentos; j++) {
            if(fila->table[i]->heap[j] != nullptr) {
                if(fila->table[i]->heap[j]->numRegistro == registro && fila->table[i]->heap[j]->nome == nome) {
                    cout << "Sentado(a) na fileira " << i + 1 << "\n";
                    inexistente = false;
                    semAssento = true;
                    break;
                }
            }
        }
    }

    if(!semAssento) {
        for(int i = 0; i < espera->value; i++) {
            if(espera->heap[i]->numRegistro == registro && espera->heap[i]->nome == nome) {
                cout << "Sem assento" << "\n";
                inexistente = false;
                break;
            }
        }
    }
    
    if(inexistente) {
        cout << "Inexistente" << "\n";
    }
}

void remover(int numFileiras, int numAssentos, int registro, string nome, fila* fila, assentos* espera) {
    ocupantes* procurando = nullptr;
    int numFileira = -1;
    for(int i = 0; i < numFileiras; i++) {
        for(int j = 0; j < numAssentos; j++) {
            if(fila->table[i]->heap[j] != nullptr) {
                if(fila->table[i]->heap[j]->numRegistro == registro && fila->table[i]->heap[j]->nome == nome) {
                    procurando = fila->table[i]->heap[j];
                    fila->table[i]->heap[j] = fila->table[i]->heap[fila->table[i]->value-1];
                    fila->table[i]->heap[fila->table[i]->value-1] = procurando;
                    fila->table[i]->heap[fila->table[i]->value-1] = nullptr;
                    numFileira = i;
                    fila->table[i]->value--;
                }
            }
        }
    }

    if(procurando == nullptr) {
        if(procurando == nullptr) {
            for(int i = 0; i < espera->value; i++) {
                if(espera->heap[i]->numRegistro == registro && espera->heap[i]->nome == nome) {
                    procurando = espera->heap[i];
                    numFileira = i;
                }
            }
        }
        else {
            if(espera->value != 0) {
                ocupantes* removido = removemaxheap(espera);
            }
        }
    }
    else {
        if(espera->value != 0) {
            ocupantes* naFila = removemaxheap(espera);
            insertminheap(fila->table[numFileira], naFila);
        }
    }

    if(procurando == nullptr) {
        cout << "Inexistente" << "\n";
    }
    else {
        cout << "Removido(a)" << "\n";
    }
}

int main() {
    int numFileiras, numAssentos, n, prioridade, numCadastro = 1;
    string command, name;
    cin >> numFileiras >> numAssentos >> n;
    
    fila* filas = new fila;
    filas->value = numFileiras;
    filas->table = new assentos*[numFileiras-1];

    for(int i = 0; i < numFileiras; i++) {
        filas->table[i] = new assentos;
        filas->table[i]->value = 0;
        filas->table[i]->heap = new ocupantes*[numAssentos];
        for (int j = 0; j < numAssentos; j++) {
            filas->table[i]->heap[j] = nullptr;
        }
    }
    assentos* espera = new assentos;
    espera->value = 0;
    espera->heap = new ocupantes*[2*(numAssentos*numFileiras)];
    
    for(int i=0;i<n;i++) {
        cin >> command >> name >> prioridade;
        if(command == "CAD") {
            ocupantes* ocupante = criar(name, numCadastro, prioridade);
            cadastrar(numFileiras, numAssentos, ocupante, filas, espera);
            numCadastro++;
        }
        else if (command == "VER") {
            ver(numFileiras, numAssentos, numCadastro, name, filas, espera);
        }
        else if (command == "REM") {
            remover(numFileiras, numAssentos, numCadastro, name, filas, espera);
        }
    }
    
    
    return 0;
}
