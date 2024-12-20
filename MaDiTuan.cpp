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

void xuat(const vector<pair<int, int>>& path) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << " " << A[i][j];
        }
        cout << endl;
    }
    cout << "\nCac buoc di la:\n";
    for (const auto& p : path) {
        cout << "(" << p.first << ", " << p.second << ") -> ";
    }
    cout << "End" << endl;
}

int heuristic(int x, int y) {
    int dx = abs(x - targetX);
    int dy = abs(y - targetY);
    return max((dx + 1) / 2, (dy + 1) / 2);
}

void DFS(int x, int y, int step, vector<pair<int, int>>& path) {
    A[x][y] = step;
    path.push_back({x, y});

    if (step == n * n) {
        xuat(path);
        exit(0); 
    }

    for (int i = 0; i < 8; i++) {
        int u = x + X[i];
        int v = y + Y[i];

        if (u >= 0 && u < n && v >= 0 && v < n && A[u][v] == 0) {
            DFS(u, v, step + 1, path);
        }
    }

    A[x][y] = 0; // Backtrack
    path.pop_back();
}

void BFS(int startX, int startY) {
    queue<State> q;
    q.push({startX, startY, 1, {{startX, startY}}, 0}); 
    A[startX][startY] = 1;

    while (!q.empty()) {
        State current = q.front();
        q.pop();

        if (current.step == n * n) {
            xuat(current.path);
            exit(0);
        }

        for (int i = 0; i < 8; i++) {
            int u = current.x + X[i];
            int v = current.y + Y[i];

            if (u >= 0 && u < n && v >= 0 && v < n && A[u][v] == 0) {
                A[u][v] = current.step + 1;
                vector<pair<int, int>> newPath = current.path;
                newPath.push_back({u, v});
                q.push({u, v, current.step + 1, newPath, 0}); 
            }
        }
        A[current.x][current.y] = 0;
    }

    cout << "Khong tim thay duong di." << endl;
}


void AStar(int startX, int startY) {
    priority_queue<State, vector<State>, greater<State>> pq;
    pq.push({startX, startY, 1, {{startX, startY}}, heuristic(startX, startY)});
    A[startX][startY] = 1;

    while (!pq.empty()) {
        State current = pq.top();
        pq.pop();

        if (current.step == n * n) {
            xuat(current.path);
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
    cout << "Nhap n: ";
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

    if (choice == 1) {
        vector<pair<int, int>> path;
        DFS(a, b, 1, path);
    } else if (choice == 2) {
        BFS(a, b);
    } else if (choice == 3) {
        AStar(a, b);
    }

    return 0;
}