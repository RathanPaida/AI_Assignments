#include <bits/stdc++.h>
using namespace std;


const int INF = 1e9;
struct node {
    vector<int> path;
    int cost;
};
class priorityQueue {
    vector<node> data;
    int frontIndex = 0;
public:
    void push(node x) {
        if (data.empty()) {
            data.push_back(x);
            return;
        }
        int i = data.size() - 1;
        data.push_back(x);
        while (i >= frontIndex && data[i].cost > x.cost) {
            data[i + 1] = data[i];
            i--;
        }
        data[i + 1] = x;
    }
    void pop() {
        frontIndex++;
    }
    node front() {
        return data[frontIndex];
    }


    bool empty() {
        return frontIndex >= data.size();
    }
};
void bfs(vector<vector<int>> &adjMatrix,vector<string> &cities,int start, int goal) {
    priorityQueue pq;
    node startNode;
    startNode.path = {start};
    startNode.cost = 0;
    pq.push(startNode);
    while (!pq.empty()) {
        node curr = pq.front();
        pq.pop();
        cout << "Path: ";
        for (int i = 0; i < curr.path.size(); i++) {
            cout << cities[curr.path[i]];
            if (i != curr.path.size() - 1)
                cout << " -> ";
        }
        cout << " | Cost = " << curr.cost << endl;
        int lastCity = curr.path.back();
        if (lastCity == goal) {
            cout << "\n Destination reached! \n";
            return;
        }
        for (int i = 0; i < adjMatrix.size(); i++) {
            if (adjMatrix[lastCity][i] != INF &&
                find(curr.path.begin(), curr.path.end(), i) == curr.path.end()) {
                node next;
                next.path = curr.path;
                next.path.push_back(i);
                next.cost = curr.cost + adjMatrix[lastCity][i];
                pq.push(next);
            }
        }
    }
}


int main() {
    vector<string> cities = {
        "Chicago","Indianapolis","Cleveland","Detroit","Columbus","Pittsburgh","Baltimore","Philadelphia","Buffalo","New york","Providence","Boston","Portland","Syracuse"
    };
    vector<vector<int>> adjMatrix = {
        {0,182,345,283,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF},
        {182,0,INF,INF,176,INF,INF,INF,INF,INF,INF,INF,INF,INF},
        {345,INF,0,169,144,134,INF,INF,189,INF,INF,INF,INF,INF},
        {283,INF,169,0,INF,INF,INF,INF,256,INF,INF,INF,INF,INF},
        {INF,176,144,INF,0,185,INF,INF,INF,INF,INF,INF,INF,INF},
        {INF,INF,134,INF,185,0,247,305,215,INF,INF,INF,INF,INF},
        {INF,INF,INF,INF,INF,247,0,101,INF,INF,INF,INF,INF,INF},
        {INF,INF,INF,INF,INF,305,101,0,INF,97,INF,INF,INF,253},
        {INF,INF,189,256,INF,215,INF,INF,0,INF,INF,INF,INF,150},
        {INF,INF,INF,INF,INF,INF,INF,97,INF,0,181,215,INF,254},
        {INF,INF,INF,INF,INF,INF,INF,INF,INF,181,0,50,INF,INF},
        {INF,INF,INF,INF,INF,INF,INF,INF,INF,215,50,0,107,312},
        {INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,107,0,INF},
        {INF,INF,INF,INF,INF,INF,INF,253,150,254,INF,312,INF,0}
    };
    int start = 13;
    int goal  = 0;
    bfs(adjMatrix, cities, start, goal);
    return 0;
}
