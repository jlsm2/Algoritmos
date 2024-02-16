#include <iostream>
using namespace std;

struct Matrix {
    int x, y, n, xstart, ystart, xend, yend;
    int** matrix;

    Matrix(int r, int c) {
        x = r;
        y = c;
        matrix = new int*[x];
        for (int i = 0; i < x; ++i) {
            matrix[i] = new int[y];
            for (int j = 0; j < y; ++j) {
                cin >> n;
                if (n == 2) {
                    xstart = i;
                    ystart = j;
                } 
                else if (n == 3) {
                    xend = i;
                    yend = j;
                }
                matrix[i][j] = n;
            }
        }
    }

    ~Matrix() {
        for (int i = 0; i < x; ++i) {
            delete[] matrix[i];
        }
        delete[] matrix;
    }

    bool validCell(int r, int c) {
        return (r >= 0 && r < x && c >= 0 && c < y && matrix[r][c] != 1);
    }

    int bfs() {
        bool** visited = new bool*[x];
        for (int i = 0; i < x; ++i) {
            visited[i] = new bool[y]();
        }

        int** distance = new int*[x];
        for (int i = 0; i < x; ++i) {
            distance[i] = new int[y]();
        }

        int xDirection[] = {-1, 1, 0, 0}, yDirection[] = {0, 0, -1, 1};
        int** queue = new int*[x * y];
        for (int i = 0; i < x * y; ++i) {
            queue[i] = new int[2]();
        }
        int front = 0, back = 0;
        queue[back][0] = xstart;
        queue[back][1] = ystart;
        back++;

        while (front != back) {
            int r = queue[front][0], c = queue[front][1];
            front++;

            if (r == xend && c == yend) {
                int result = distance[r][c];
                for (int i = 0; i < x; ++i) {
                    delete[] visited[i], distance[i], queue[i];
                }
                delete[] visited, distance, queue;
                return result;
            }

            for (int i = 0; i < 4; ++i) {
                int currentX = r + xDirection[i], currentY = c + yDirection[i];
                if (validCell(currentX, currentY) && !visited[currentX][currentY]) {
                    queue[back][0] = currentX;
                    queue[back][1] = currentY;
                    back++;
                    visited[currentX][currentY] = true;
                    distance[currentX][currentY] = distance[r][c] + 1;
                }
            }
        }

        for (int i = 0; i < x; ++i) {
            delete[] visited[i], distance[i], queue[i];
        }
        delete[] visited, distance, queue;

        return -1;
    }
};

int main() {
    int x, y;
    cin >> x >> y;
    Matrix matrix(x, y);

    int shortestPath = matrix.bfs();
    if (shortestPath != -1) {
        cout << shortestPath << endl;
    } 
    else {
        cout << "Labirinto Impossivel" << endl;
    }

    return 0;
}
