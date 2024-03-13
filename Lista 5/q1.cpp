#include <iostream>
using namespace std;

struct Node {
    int vertice;
    Node* next;
    
    Node(int v) : vertice(v), next(nullptr) {}
};

struct UnionFind {
    int *parent, *rank;
    
    UnionFind(int n) {
        parent = new int[n + 1];
        rank = new int[n + 1];
        for (int i = 1; i <= n; ++i) {
            parent[i] = i;
            rank[i] = 0;
        }
    }
    
    int findParent(int u) {
        while (u != parent[u]) {
            parent[u] = parent[parent[u]]; 
            u = parent[u];
        }
        return u;
    }

    
    void merge(int u, int v) {
        int uroot = findParent(u);
        int vroot = findParent(v);
        if (uroot != vroot) {
            if (rank[uroot] < rank[vroot])
                swap(uroot, vroot);
            parent[vroot] = uroot;
            if (rank[uroot] == rank[vroot])
                rank[uroot]++;
        }
    }
    
    ~UnionFind() {
        delete[] parent;
        delete[] rank;
    }
};

struct Grafo {
    int vertices;
    Node** adjList;
    
    Grafo(int v) {
        vertices = v;
        
        adjList = new Node*[vertices + 1];
        for (int i = 1; i <= vertices; ++i) {
            adjList[i] = nullptr;
        }
    }
    
    void CriarAresta(int v1, int v2) {
        Node* newNode = new Node(v2);
        newNode->next = adjList[v1];
        adjList[v1] = newNode;
        
        newNode = new Node(v1);
        newNode->next = adjList[v2];
        adjList[v2] = newNode;
    }

    void darNoticia() {
        UnionFind uf(vertices);
        int *sizes = new int[vertices + 1]{0};
        
        for (int i = 1; i <= vertices; ++i) {
            for (Node* cur = adjList[i]; cur != nullptr; cur = cur->next) {
                int vert = cur->vertice;
                uf.merge(i, vert);
            }
        }

        for (int i = 1; i <= vertices; ++i) {
            int root = uf.findParent(i);
            sizes[root]++;
        }

        for (int i = 1; i <= vertices; ++i) {
            cout << sizes[uf.findParent(i)];
            if (i < vertices) {
                cout << " ";
            }
        }

        delete[] sizes;
    }
    
    ~Grafo() {
        for (int i = 1; i <= vertices; ++i) {
            Node* cur = adjList[i];
            while (cur) {
                Node* temp = cur;
                cur = cur->next;
                delete temp;
            }
        }
        delete[] adjList;
    }
};

int main() {
    int n, m, v1, v2;
    cin >> n >> m;
    
    Grafo grafo(n);
    
    for (int i = 1; i <= m; ++i) {
        cin >> v1 >> v2;
        grafo.CriarAresta(v1, v2);
    }
    
    grafo.darNoticia();
    cout << endl;
    
    return 0;
}
