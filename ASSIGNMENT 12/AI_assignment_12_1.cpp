#include <bits/stdc++.h>
using namespace std;

int n = 6;

// domain[i][j] = 1  room j allowed for team i
int domain[6][3];

// conflict graph
vector<int> graph[6];

// Function to remove invalid values
bool removeInvalidValues(int Xi, int Xj){
    bool changed = false;
    for (int x=0;x<3;x++){
        if (domain[Xi][x] == 0) continue;
        bool valid = false;
        for (int y=0;y<3;y++){
            if (domain[Xj][y] == 1 && x != y) {
                valid = true;
                break;
            }
        }
        if (!valid){
            domain[Xi][x] = 0;
            changed = true;
        }
    }
    return changed;
}


// AC-3 main function
bool applyAC3() {
    queue<pair<int,int>> q;
    // add all arcs
    for (int i = 0;i<n;i++) {
        for (int j : graph[i]) {
            q.push({i, j});
        }
    }

    while (!q.empty()){
        auto p = q.front();
        q.pop();

        int Xi = p.first;
        int Xj = p.second;

        if(removeInvalidValues(Xi,Xj)){

            // check if domain becomes empty
            bool empty = true;
            for (int k=0;k<3;k++) {
                if (domain[Xi][k] == 1){
                    empty = false;
                    break;
                }
            }
            if(empty) return false;
            // add neighbors again
            for (int Xk : graph[Xi]){
                if (Xk != Xj) {
                    q.push({Xk, Xi});
                }
            }
        }
    }
    return true;
}

// Function to display domains
void displayDomains(){
    for (int i=0;i<n;i++) {
        cout << "P" << i+1 << " : { ";
        for (int j=0;j<3;j++){
            if (domain[i][j]){
                cout << "R" << j+1 << " ";
            }
        }
        cout << "}\n";
    }
    cout << "\n";
}


int main(){
    // initialize domains
    for (int i=0;i<6;i++){
        for (int j=0;j<3;j++){
            domain[i][j] = 1;
        }
    }
    // conflicts
    graph[0] = {1,2,5};
    graph[1] = {0,2,3};
    graph[2] = {0,1,4};
    graph[3] = {1,5};
    graph[4] = {2,5};
    graph[5] = {0,3,4};

    cout << "Initial Domains:\n";
    displayDomains();

    // run AC-3
    bool res = applyAC3();

    cout << "After AC-3:\n";
    displayDomains();

    if (res) cout << "Arc-consistent\n";
    else cout << "Failure\n";

    // assign P1 = R1
    cout << "\nAfter assigning P1 = R1:\n";

    for (int j=0;j<3;j++) domain[0][j] = 0;
    domain[0][0] = 1;

    bool res2 = applyAC3();

    displayDomains();

    if (res2) cout << "Still consistent (No failure)\n";
    else cout << "Failure detected\n";
    return 0;
}