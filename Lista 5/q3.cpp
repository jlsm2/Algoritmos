#include <iostream>

using namespace std;

class UnionFind {
private:
    int *parent;
    int *rank;
    int size;

public:
    UnionFind(int n) : size(n) {
        parent = new int[size];
        rank = new int[size];
        for (int i = 0; i < size; ++i) {
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

    void removeWall(int wallIndex, int n) {
        int xWall = wallIndex / (n + (n - 1));
        int yWall = wallIndex % (n + (n - 1));
        int cell1, cell2;

        if (yWall < n - 1) {
            cell1 = n * xWall + yWall;
            cell2 = cell1 + 1;
        } else {
            cell1 = n * xWall + (yWall - (n - 1));
            cell2 = cell1 + n;
        }
        merge(cell1, cell2);
    }

    ~UnionFind() {
        delete[] parent;
        delete[] rank;
    }
};

bool isConnected(UnionFind &uf, int cell1, int cell2) {
    return uf.findParent(cell1) == uf.findParent(cell2);
}

int main() {
    int k, n, m, q, wall, cell1, cell2;
    cin >> k;

    for (int i = 0; i < k; i++) {
        cin >> n >> m >> q;

        UnionFind maze(2 * (n * n) - n);

        for (int j = 0; j < m; j++) {
            cin >> wall;
            maze.removeWall(wall, n);
        }

        for (int p = 0; p < q; p++) {
            cin >> cell1 >> cell2;
            cout << i << "." << p << " " << isConnected(maze, cell1, cell2) << endl;
            if (p == q - 1) {
                cout << endl;
            }
        }
    }

    return 0;
}
