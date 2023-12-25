#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct fileira {
    string value;
    bool sentada;
    fileira* next;
    
};

struct assentos {
    fileira** cadeiras;  
};

fileira* criarAssento(assentos* assento, string name) {
    fileira* newAssento = new fileira;
    newAssento->value = name;
    newAssento->sentada = false;
    newAssento->next = nullptr;
    return newAssento;
}

void cadastrar(assentos*& assento, string name, int priority, int qtdFileiras, int qtdAssentos) {
    fileira* cadeira = criarAssento(assento, name);
    while() {
        
    }
    
}

int main() {
    int f, q, n, p;
    string command, name;
    cin >> f >> q >> n;
    for(int i=0;i<n;i++) {
        cin >> command >> name >> p;
        if(command == "CAD") {
            
        }
        else if (command == "VER") {
            
        }
        else if (command == "REM") {
            
        }
    }
    
    
    return 0;
}
