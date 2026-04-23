#include <bits/stdc++.h>
using namespace std;

#define N 9

// domain[i][v] = 1 means value (v+1) allowed in cell i
int domain[81][9];

// neighbors of each cell
vector<int> neighbors[81];

int removedCount = 0;

// convert (row,col) → index
int getIndex(int r, int c) {
    return r * 9 + c;
}

// count domain size
int domainSize(int i) {
    int count = 0;
    for (int v = 0; v < 9; v++)
        if (domain[i][v]) count++;
    return count;
}

// get single value (if size = 1)
int getSingleValue(int i) {
    for (int v = 0; v < 9; v++)
        if (domain[i][v]) return v;
    return -1;
}

// generate neighbors (row, col, box)
void generateNeighbors() {
    for (int r = 0; r < 9; r++) {
        for (int c = 0; c < 9; c++) {

            int idx = getIndex(r, c);
            bool used[81] = {0};

            // row
            for (int j = 0; j < 9; j++) {
                if (j != c) {
                    int ni = getIndex(r, j);
                    neighbors[idx].push_back(ni);
                    used[ni] = 1;
                }
            }

            // column
            for (int i = 0; i < 9; i++) {
                if (i != r) {
                    int ni = getIndex(i, c);
                    if (!used[ni]) {
                        neighbors[idx].push_back(ni);
                        used[ni] = 1;
                    }
                }
            }

            // box
            int sr = (r / 3) * 3;
            int sc = (c / 3) * 3;

            for (int i = sr; i < sr + 3; i++) {
                for (int j = sc; j < sc + 3; j++) {
                    if (i != r || j != c) {
                        int ni = getIndex(i, j);
                        if (!used[ni]) {
                            neighbors[idx].push_back(ni);
                            used[ni] = 1;
                        }
                    }
                }
            }
        }
    }
}

// revise function
bool removeInvalid(int Xi, int Xj) {
    bool changed = false;

    // if Xj has only one value
    if (domainSize(Xj) == 1) {
        int val = getSingleValue(Xj);

        if (domain[Xi][val]) {
            domain[Xi][val] = 0;
            removedCount++;
            changed = true;
        }
    }

    return changed;
}

// AC-3
bool applyAC3() {
    queue<pair<int,int>> q;

    // add all arcs
    for (int i = 0; i < 81; i++) {
        for (int j : neighbors[i]) {
            q.push({i, j});
        }
    }

    while (!q.empty()) {
        auto p = q.front();
        q.pop();

        int Xi = p.first;
        int Xj = p.second;

        if (removeInvalid(Xi, Xj)) {

            // failure check
            if (domainSize(Xi) == 0) return false;

            // add neighbors again
            for (int Xk : neighbors[Xi]) {
                if (Xk != Xj) {
                    q.push({Xk, Xi});
                }
            }
        }
    }

    return true;
}

// print domain sizes
void printDomainSizes() {
    cout << "\nDomain Size Grid:\n";

    for (int i = 0; i < 81; i++) {
        cout << domainSize(i) << " ";
        if ((i + 1) % 9 == 0) cout << "\n";
    }
}

int main() {

    int grid[9][9] = {
        {0,0,0,0,0,6,0,0,0},
        {0,5,9,0,0,0,0,0,8},
        {2,0,0,0,0,8,0,0,0},
        {0,4,5,0,0,0,0,0,0},
        {0,0,3,0,0,0,0,0,0},
        {0,0,6,0,0,3,0,5,0},
        {0,0,0,0,0,7,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,5,0,0,0,2}
    };

    // initialize domains
    for (int r = 0; r < 9; r++) {
        for (int c = 0; c < 9; c++) {
            int idx = getIndex(r, c);

            if (grid[r][c] != 0) {
                for (int v = 0; v < 9; v++) domain[idx][v] = 0;
                domain[idx][grid[r][c] - 1] = 1;
            } else {
                for (int v = 0; v < 9; v++) domain[idx][v] = 1;
            }
        }
    }

    generateNeighbors();

    bool result = applyAC3();

    cout << "Total values removed: " << removedCount << "\n";

    printDomainSizes();

    if (!result)
        cout << "\nFailure: Some domain became empty\n";
    else
        cout << "\nAC-3 finished (partial reduction)\n";

    return 0;
}