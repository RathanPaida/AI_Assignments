#include <iostream>
using namespace std;



string name[12] = {
    "Raj", "Priya", "Aarav",
    "Sunil", "Akash", "Neha",
    "Sneha", "Rahul", "Maya",
    "Arjun", "Pooja", "Arjun2"
};

int graph[12][20];
int edgeCount[12];

void add_edge(int u, int v){
    graph[u][edgeCount[u]++] = v;
    graph[v][edgeCount[v]++] = u;
}

void make_graph(){
    for(int i = 0; i < 12; i++){
        edgeCount[i] = 0;
    }
    
    add_edge(0,1); // Raj - Priya
    add_edge(0,3); // Raj - Sunil
    add_edge(1,2); // Priya - Aarav
    add_edge(1,5); // Priya - Neha
    add_edge(2,5); // Aarav - Neha
    add_edge(2,9); // Aarav - Arjun
    add_edge(3,4); // Sunil - Akash
    add_edge(3,6); // Sunil - Sneha
    add_edge(4,5); // Akash - Neha
    add_edge(5,7); // Neha - Rahul
    add_edge(5,9); // Neha - Arjun
    add_edge(6,7); // Sneha - Rahul
    add_edge(6,8); // Sneha - Maya
    add_edge(7,9); // Rahul - Arjun
    add_edge(7,10); // Rahul - Pooja
    add_edge(8,11); // Maya - Arjun2
    add_edge(9,10); // Arjun - Pooja
    add_edge(10,11); // Pooja - Arjun2
}

void dfs(int u, int vis[]){
    vis[u] = 1;
    cout << name[u] << " ";
    
    for(int i = 0; i < edgeCount[u]; i++){
        int v = graph[u][i];
        if(!vis[v])
            dfs(v, vis);
    }
}

void bfs(int s){
    int queue[12];
    int front = 0, rear = 0;
    int vis[12] = {0};
    
    queue[rear++] = s;
    vis[s] = 1;
    
    while(front < rear){
        int u = queue[front++];
        cout << name[u] << " ";
        
        for(int i = 0; i < edgeCount[u]; i++){
            int v = graph[u][i];
            if(!vis[v]){
                vis[v] = 1;
                queue[rear++] = v;
            }
        }
    }
}

int main(){
    make_graph();
    
    int vis[12] = {0};
    
    cout << "DFS Tree:\n";
    dfs(0, vis);//Raj
    
    cout << "\n\nBFS Tree:\n";
    bfs(0);
    
    return 0;
}
