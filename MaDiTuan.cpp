#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
#include <cmath>

#define MAX 8

using namespace std;

struct State {
    int x, y, step;
    vector<pair<int, int>> path;
    int heuristic;

    bool operator>(const State& other) const {
        return (step + heuristic) > (other.step + other.heuristic);
    }
};

int A[MAX][MAX] = {0};
int X[8] = {-2, -2, -1, -1, 1, 1, 2, 2};
int Y[8] = {-1, 1, -2, 2, -2, 2, -1, 1};
int n;
int targetX, targetY;
bool foundDFS = false; 

void xuat(const vector<vector<int>>& path) {
    cout << "Cac buoc di la: \n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << " " << path[i][j];
        }
        cout << endl;
    }
}


int heuristic(int x, int y) {
    int dx = abs(x - targetX);
    int dy = abs(y - targetY);
    return max((dx + 1) / 2, (dy + 1) / 2);
}

void DFS(int x, int y, int step, vector<vector<int>>& path) {
    path[x][y] = step;

    if (step == n * n) {
        xuat(path);
        foundDFS = true; 
        return;
    }

    for (int i = 0; i < 8; i++) {
        int u = x + X[i];
        int v = y + Y[i];

        if (u >= 0 && u < n && v >= 0 && v < n && path[u][v] == 0) {
            DFS(u, v, step + 1, path);
            if (foundDFS) return; 
        }
    }

    path[x][y] = 0; // Backtrack
}

void BFS(int startX, int startY) {
    struct Node {
        int x, y, step;
        int path[MAX][MAX] = {0};
    };

    queue<Node> q;

    Node start = {startX, startY, 1};
    memset(start.path, 0, sizeof(start.path));
    start.path[startX][startY] = 1;

    q.push(start);

    while (!q.empty()) {
        Node current = q.front();
        q.pop();

        if (current.step == n * n) {
            vector<vector<int>> path(n, vector<int>(n, 0));
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    path[i][j] = current.path[i][j];
                }
            }
            xuat(path);
            exit(0);
        }

        for (int i = 0; i < 8; i++) {
            int u = current.x + X[i];
            int v = current.y + Y[i];
            if (u >= 0 && u < n && v >= 0 && v < n && current.path[u][v] == 0) {
                Node next = current;
                next.x = u;
                next.y = v;
                next.step = current.step + 1;
                next.path[u][v] = next.step;
                q.push(next);
            }
        }
    }

    cout << "Khong tim thay duong di (BFS)." << endl;
}

void AStar(int startX, int startY) {
    priority_queue<State, vector<State>, greater<State>> pq;
    pq.push({startX, startY, 1, {{startX, startY}}, heuristic(startX, startY)});
    A[startX][startY] = 1;

    while (!pq.empty()) {
        State current = pq.top();
        pq.pop();

        if (current.step == n * n) {
            vector<vector<int>> path(n, vector<int>(n, 0));
            for (const auto& p : current.path) {
                path[p.first][p.second] = current.step;
            }
            xuat(path);
            exit(0);
        }

        for (int i = 0; i < 8; i++) {
            int u = current.x + X[i];
            int v = current.y + Y[i];

            if (u >= 0 && u < n && v >= 0 && v < n && A[u][v] == 0) {
                A[u][v] = current.step + 1;
                vector<pair<int, int>> newPath = current.path;
                newPath.push_back({u, v});
                pq.push({u, v, current.step + 1, newPath, heuristic(u, v)});
            }
        }

        A[current.x][current.y] = 0;
    }

    cout << "Khong tim thay duong di." << endl;
}

int main() {
    cout << "Nhap kich thuoc ban co: ";
    cin >> n;
    int a, b;
    cout << "Nhap vi tri ban dau (x y): \n";
    cout << "x: ";
    cin >> a;
    cout << "y: ";
    cin >> b;

    if (a < 0 || a >= n || b < 0 || b >= n) {
        cout << "Vi tri ban dau khong hop le." << endl;
        return 0;
    }
    targetX = 0;
    targetY = 0;

    cout << "Chon phuong phap (1: DFS, 2: BFS, 3: A*): ";
    int choice;
    cin >> choice;

    vector<vector<int>> path(n, vector<int>(n, 0));
    if (choice == 1) {
        DFS(a, b, 1, path);
        if (!foundDFS) {
            cout << "Khong tim thay duong di (DFS)." << endl;
        }
    } else if (choice == 2) {
        BFS(a, b);
    } else if (choice == 3) {
        AStar(a, b);
    }

    return 0;
}
