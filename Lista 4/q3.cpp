#include <iostream>
using namespace std;

int **cost, *dist, q, src;
bool *visited;

void init() {
    for (int i = 0; i < q; i++) {
        dist[i] = 99999;
    }
}

void createCostMatrix(int r, int q) {
    cost = new int *[q];
    for (int i = 0; i < q; i++) {
        cost[i] = new int[q];
    }

    for (int i = 0; i < q; i++) {
        for (int j = 0; j < q; j++) {
            if (i == j) {
                cost[i][j] = 0;
            } 
            else {
                cost[i][j] = 99999;
            }
        }
    }

    int a, b, m;
    for (int i = 0; i < r; i++) {
        cin >> a >> b >> m;
        cost[a][b] = m;
    }
}

int getNearest() {
    int minValue = 99999, minNode = 0;
    for (int i = 0; i < q; i++) {
        if (!visited[i] && dist[i] < minValue) {
            minValue = dist[i];
            minNode = i;
        }
    }
    return minNode;
}

void dijkstra() {
    init();
    for (int i = 0; i < q; i++) {
        visited[i] = false;
    }
    dist[src] = 0;
    for (int i = 0; i < q; i++) {
        int nearest = getNearest();
        visited[nearest] = true;

        for (int adj = 0; adj < q; adj++) {
            if (cost[nearest][adj] != 99999 && dist[adj] > dist[nearest] + cost[nearest][adj]) {
                dist[adj] = dist[nearest] + cost[nearest][adj];
            }
        }
    }
}

int main() {
    int r, n, a, b, m, num;
    cin >> q >> r >> n;

    dist = new int[q];
    visited = new bool[q];

    createCostMatrix(r, q);

    for (int i = 0; i < n; i++) {
        cin >> num;
        if (num == 1) {
            cin >> a >> b >> m;
            cost[a][b] = m;
        } 
        else if (num == 2) {
            cin >> a >> b;
            src = a;
            dijkstra();
            if (dist[b] == 99999) {
                cout << -1 << endl;
            } 
            else {
                cout << dist[b] << endl;
            }
        }
    }

    delete[] dist, visited;
    for (int i = 0; i < q; ++i) {
        delete[] cost[i];
    }
    delete[] cost;

    return 0;
}
