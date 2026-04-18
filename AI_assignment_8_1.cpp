#include <bits/stdc++.h>
using namespace std;
struct State{
    vector<int> path;
    vector<bool> visited;
    int cost;
    bool operator<(const State &other) const{
        return cost < other.cost;
    }
};
State tsp_beam(vector<vector<int>> &graph, int k){
    int n = graph.size();
    vector<State> beam;
    State start;
    start.path = {0};
    start.visited = vector<bool>(n, false);
    start.visited[0] = true;
    start.cost = 0;
    beam.push_back(start);
    for(int i = 1; i < n; i++){
        vector<State> cities;
        for(auto &state : beam){
            int last = state.path.back();
            for(int city = 0; city < n; city++) {
                if(!state.visited[city]) {
                    State next = state;
                    next.path.push_back(city);
                    next.visited[city] = true;
                    next.cost += graph[last][city];
                    cities.push_back(next);
                }
            }
        }
        sort(cities.begin(), cities.end());
        beam.clear();
        for(int i = 0; i < min(k, (int)cities.size()); i++) {
            beam.push_back(cities[i]);
        }
    }
    State best;
    best.cost = INT_MAX;
    for(auto &state : beam) {
        int last = state.path.back();
        int total_cost = state.cost + graph[last][0];
        if(total_cost < best.cost){
            best = state;
            best.cost = total_cost;
        }
    }
    return best;
}
int main() {
    vector<vector<int>> graph = {
        {0,10,15,20,25,30,35,40},
        {12,0,35,15,20,25,30,45},
        {25,30,0,10,40,20,15,35},
        {18,25,12,0,15,30,20,10},
        {22,18,28,20,0,15,25,30},
        {35,22,18,28,12,0,40,20},
        {30,35,22,18,28,32,0,15},
        {40,28,35,22,18,25,12,0}
    };
    vector<int> ks = {3,5,10};
    for(int k : ks){
        State res = tsp_beam(graph, k);
        cout << "k=" << k << " Cost: " << res.cost << "\nPath: ";
        for(int city : res.path){
            cout << char('A' + city) << " ";
        }
        cout << char('A' + res.path[0]) << endl;
        cout << "---------------------\n";
    }

    return 0;
}