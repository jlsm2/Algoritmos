#include <iostream>
using namespace std;

struct PilhaAdj {
    int elementos[100];
    int topo;

    PilhaAdj() {
        topo = -1;
    }

    bool isempty() {
        if (topo == -1) {
            return true;
        }
        return false;
    }

    void push(int valor) {
        topo++;
        elementos[topo] = valor;
    }

    int pop() {
        if (!isempty()) {
            int valor = elementos[topo];
            topo--;
            return valor;
        }
    }
};

struct Grafo {
    int vertices, arestas, matrizAdj[100][100]; 
    PilhaAdj pilhas[100];

    Grafo(int v) {
        vertices = v;
        arestas = 0;
        for (int i = 0; i < vertices; ++i) {
            for (int j = 0; j < vertices; ++j) {
                matrizAdj[i][j] = 0;
            }
        }
    }

    void CriarAresta(int v1, int v2) {
        matrizAdj[v1][v2] = 1;
        matrizAdj[v2][v1] = 1;
        pilhas[v1].push(v2);
        pilhas[v2].push(v1);
        arestas++;
    }
    
    void PrintarListaAdj() {
        for (int i = 0; i < vertices; ++i) {
            cout << i << ": ";
            if(pilhas[i].isempty()) {
                cout << "Lista Vazia";
            }
            else {
                while (!pilhas[i].isempty()) {
                    cout << pilhas[i].pop() << " ";
                }
            }
            cout << endl;
        }
    }
    
    void ApagarArestas(int v) {
        for (int i = 0; i < vertices; ++i) {
            for (int j = 0; j < vertices; ++j) {
                if (j == v) {
                    matrizAdj[i][j] = 0;
                }
            }
        }
    }
    
    void DFS(int v) {
        for (int i = vertices - 1; i >= 0; --i) {
            if(matrizAdj[v][i] == 1) {
                cout << i << " ";
                matrizAdj[v][i] = 0;
                ApagarArestas(i);
                DFS(i);
            }
        }
    }
};

int main() {
    int v, v1, v2, continuar;
    cin >> v;
    Grafo grafo(v);
    
    while(cin >> v1 >> v2 >> continuar) {
        grafo.CriarAresta(v1,v2);
        if(continuar == 0) {
            grafo.PrintarListaAdj();
            cout << endl;
            grafo.ApagarArestas(0);
            cout << 0 << " ";
            grafo.DFS(0);
        }
    }

    return 0;
}
