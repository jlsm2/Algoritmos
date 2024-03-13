#include <iostream>
using namespace std;

#define INT_MAX 2147483647

int **cost, m, n, mstcost;

struct Aresta {
    int src, destino, custo;
};

struct Subset {
    int parent, height;
};

void calculateMinCost() {
    for (int k = 0; k < m; k++) {
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < m; j++) {
                if (cost[i][k] != INT_MAX && cost[k][j] != INT_MAX && cost[i][j] > cost[i][k] + cost[k][j]) {
                    cost[i][j] = cost[i][k] + cost[k][j];
                }
            }
        }
    }
}

int findParent(Subset subsets[], int i) {
    if (subsets[i].parent != i) {
        subsets[i].parent = findParent(subsets, subsets[i].parent);
    }
    return subsets[i].parent;
}

void unionSubsets(Subset subsets[], int x, int y) {
    int xroot = findParent(subsets, x);
    int yroot = findParent(subsets, y);

    if (subsets[xroot].height < subsets[yroot].height) {
        subsets[xroot].parent = yroot;
    } 
    else if (subsets[xroot].height > subsets[yroot].height) {
        subsets[yroot].parent = xroot;
    } 
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].height++;
    }
}

void kruskalMST(Aresta arestas[], Subset subsets[]) {
    int **MST = new int *[m];
    for (int i = 0; i < m; i++) {
        MST[i] = new int[m];
    }

    int e = 0;
    int i = 0;
    while (i < m - 1) {
        Aresta next_Aresta = arestas[e++];

        int x = findParent(subsets, next_Aresta.src);
        int y = findParent(subsets, next_Aresta.destino);

        if (x != y) {
            MST[next_Aresta.src][next_Aresta.destino] = next_Aresta.custo;
            MST[next_Aresta.destino][next_Aresta.src] = next_Aresta.custo;
            unionSubsets(subsets, x, y);
            i++;
        }
    }

    for (int i = 0; i < m; i++) {
        for (int j = i + 1; j < m; j++) {
            if (MST[i][j] != 0) {
                mstcost += MST[i][j];
            }
        }
    }

    for (int i = 0; i < m; i++) {
        delete[] MST[i];
    }
    delete[] MST;
}

void createCostMatrix(int n, int m) {
    cost = new int *[m];
    for (int i = 0; i < m; i++) {
        cost[i] = new int[m];
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            if (i == j) {
                cost[i][j] = 0;
            } 
            else {
                cost[i][j] = INT_MAX;
            }
        }
    }

    int IdA, IdB, custo;
    for (int i = 0; i < n; i++) {
        cin >> IdA >> IdB >> custo;
        cost[IdA][IdB] = cost[IdB][IdA] = custo;
    }

    calculateMinCost();
}

void freeMemory(int m) {
    for (int i = 0; i < m; i++) {
        delete[] cost[i];
    }
    delete[] cost;
}

int main() {
    cin >> m >> n;

    createCostMatrix(n, m);

    Aresta *arestas = new Aresta[m * m];
    int atual = 0;
    for (int i = 0; i < m; i++) {
        for (int j = i + 1; j < m; j++) {
            if (cost[i][j] != INT_MAX) {
                arestas[atual].src = i;
                arestas[atual].destino = j;
                arestas[atual].custo = cost[i][j];
                atual++;
            }
        }
    }

    for (int i = 0; i < atual - 1; i++) {
        for (int j = 0; j < atual - i - 1; j++) {
            if (arestas[j].custo > arestas[j+1].custo) {
                Aresta temp = arestas[j];
                arestas[j] = arestas[j+1];
                arestas[j+1] = temp;
            }
        }
    }

    Subset *subsets = new Subset[m];
    for (int i = 0; i < m; i++) {
        subsets[i].parent = i;
        subsets[i].height = 0;
    }

    kruskalMST(arestas, subsets);
    cout << mstcost << endl;

    delete[] arestas, subsets;
    freeMemory(m);

    return 0;
}
