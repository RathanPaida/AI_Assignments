#include<bits/stdc++.h>
using namespace std;


vector<vector<pair<int,int>>> graph(14);
string city[14] = {
    "Chicago","Indianapolis","Columbus","Cleveland","Detroit",
    "Buffalo","Pittsburgh","Syracuse","Baltimore","Philadelphia",
    "New York","Providence","Boston","Portland"
};

void add_edge(int u, int v, int w){
    graph[u].push_back({v,w});
    graph[v].push_back({u,w});
}

void make_graph() {
    add_edge(0,4,283); add_edge(0,3,345); add_edge(0,1,182);
    add_edge(1,2,176);
    add_edge(2,3,144); add_edge(2,6,185);
    add_edge(3,4,169); add_edge(3,5,189); add_edge(3,6,134);
    add_edge(4,5,256);
    add_edge(5,6,215); add_edge(5,7,150);
    add_edge(6,8,247); add_edge(6,9,305);
    add_edge(7,10,254); add_edge(7,12,312); add_edge(7,9,253);
    add_edge(8,9,101);
    add_edge(9,10,97);
    add_edge(10,11,181); add_edge(10,12,215);
    add_edge(11,12,50);
    add_edge(12,13,107);
}

int city_to_index(string name){
    for(int i=0;i<14;i++){
        if(city[i] == name)
            return i;
    }
    return -1;
}


void dfs(int u,int d,
         vector<vector<pair<int,int>>>& g,
         vector<int>& vis,
         vector<int>& path,
         int cost)
{
    vis[u]=1;
    path.push_back(u);

    if(u==d){
        for(int x:path) cout<<city[x]<<" -> ";
        cout<<"Cost = "<<cost<<"\n";
    } else {
        for(auto e:g[u]){
            if(!vis[e.first])
                dfs(e.first,d,g,vis,path,cost+e.second);
        }
    }

    path.pop_back();
    vis[u]=0;
}


void bfs(int s,int d,vector<vector<pair<int,int>>>& g)
{
    vector<vector<int>> qpath;
    vector<int> qnode, qcost;

    qpath.push_back({s});
    qnode.push_back(s);
    qcost.push_back(0);

    int idx=0;
    while(idx<qnode.size()){
        int u=qnode[idx];
        int cost=qcost[idx];
        vector<int> path=qpath[idx];
        idx++;

        if(u==d){
            for(int x:path) cout<<city[x]<<" -> ";
            cout<<"Cost = "<<cost<<"\n";
            continue;
        }

        for(auto e:g[u]){
            bool used=false;
            for(int x:path) if(x==e.first) used=true;
            if(!used){
                vector<int> np=path;
                np.push_back(e.first);
                qpath.push_back(np);
                qnode.push_back(e.first);
                qcost.push_back(cost+e.second);
            }
        }
    }
}


int bfs_exploration_cost(int s,int d,
                         vector<vector<pair<int,int>>>& g)
{
    vector<vector<int>> qpath;
    vector<int> qnode, qcost;

    qpath.push_back({s});
    qnode.push_back(s);
    qcost.push_back(0);

    int idx=0, total=0;

    while(idx<qnode.size()){
        int u=qnode[idx];
        int cost=qcost[idx];
        vector<int> path=qpath[idx];
        idx++;

        total += cost;

        if(u==d) break;

        for(auto e:g[u]){
            bool used=false;
            for(int x:path) if(x==e.first) used=true;
            if(!used){
                vector<int> np=path;
                np.push_back(e.first);
                qpath.push_back(np);
                qnode.push_back(e.first);
                qcost.push_back(
                    e.second);
            }
        }
    }
    return total;
}

int main(){
    make_graph();

    string startCity, endCity;
    cin >> startCity >> endCity;

    int s = city_to_index(startCity);
    int d = city_to_index(endCity);

    if(s == -1 || d == -1){
        cout << "Invalid city name\n";
        return 0;
    }

    vector<int> visited(14,0), path;

    cout << "DFS paths:\n";
    dfs(s, d, graph, visited, path, 0);

    cout << "\nBFS paths:\n";
    bfs(s, d, graph);

    int exp_cost = bfs_exploration_cost(s, d, graph);
    cout << "\nBFS Exploration Cost = " << exp_cost << "\n";

    return 0;
}