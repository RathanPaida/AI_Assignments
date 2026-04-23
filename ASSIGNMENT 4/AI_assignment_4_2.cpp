#include<bits/stdc++.h>
using namespace std;

struct node{
    int x,y;
    int g;
    vector<pair<int,int>> path;
};

class priorityqueue{
    public:
    vector<node> pq;
        void push(node n){
            pq.push_back(n);
        }
        node pop(){
            int minindex=0;
            for(int i=1;i<pq.size();i++){
                if(pq[i].g<pq[minindex].g){
                    minindex=i;
                }
            }
            node best=pq[minindex];
            pq.erase(pq.begin()+minindex);
            return best;
        }
        bool empty(){
            return pq.empty();
        }
};

int main(){
    vector<vector<int>> floor = {
      // 0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, // 0: Top Wall
        {1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1}, // 1: "Room" (Left), Offices (Right)
        {1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1}, // 2: "Room" interior
        {1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1}, // 3: "Room" interior
        {1, 1, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1}, // 4: Wall separating rooms from hallway
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, // 5: MAIN HALLWAY (Left to Right)
        {1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1}, // 6: Junction to Entry (Left), Exit Area (Right)
        {1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1}, // 7: Vertical path to Entry
        {1, 1, 1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1}, // 8: Entry Area / Exit Stairs
        {1, 1, 1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1}, // 9: Entry Stairs
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}  // 10: Bottom Wall
    };
    vector<vector<char>> sol = {
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', ' ', ' ', ' ', ' ', '#', '#', ' ', ' ', '#', '#', ' ', ' ', '#', '#', ' ', ' ', '#', '#', '#', '#', '#', '#', '#'},
        {'#', ' ', ' ', ' ', ' ', '#', '#', ' ', ' ', '#', '#', ' ', ' ', '#', '#', ' ', ' ', '#', '#', '#', '#', '#', '#', '#'},
        {'#', ' ', ' ', ' ', ' ', '#', '#', ' ', ' ', '#', '#', ' ', ' ', '#', '#', ' ', ' ', '#', '#', '#', '#', '#', '#', '#'},
        {'#', '#', ' ', ' ', '#', '#', '#', '#', ' ', '#', '#', '#', ' ', '#', '#', '#', ' ', '#', '#', '#', '#', '#', '#', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', '#', '#', ' ', ' ', '#', '#', '#', '#', ' ', '#', '#', ' ', ' ', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', '#', '#', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#', '#', ' ', ' ', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', '#', '#', ' ', ' ', '#', ' ', '#', ' ', ' ', '#', '#', ' ', ' ', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', '#', '#', ' ', ' ', '#', ' ', '#', ' ', ' ', '#', '#', ' ', ' ', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}
    };
    int rows=floor.size();
    int cols=floor[0].size();
    int sx=9,sy=3;
    int gx=5,gy=21;

    vector<vector<bool>> vis(rows,vector<bool>(cols,false));
    priorityqueue pq;

    node start;
    start.x=sx;
    start.y=sy;
    start.g = 0;
    start.path.push_back({sx,sy});
    pq.push(start);
    int exp=0;
    int dx[4]={-1,1,0,0};
    int dy[4]={0,0,-1,1};
    cout<<"\n best_first_search evacuation"<<endl;
    while(!pq.empty()){
        node curr=pq.pop();
        exp++;
        int x=curr.x;
        int y=curr.y;
        if(vis[x][y]){
            continue;
        }
        sol[x][y] = '.';
        vis[x][y]=true;
        if(x==gx && y==gy){
            cout<<"evacuation_path"<<endl;
            for(auto p : curr.path){
                cout<<"("<<p.first<<","<<p.second<<")";
                sol[p.first][p.second] = '^';
            }
            cout << "\n";
            for (int i = 0; i < 11; i++) {
                for (int j = 0; j < 24; j++) {
                    cout << sol[i][j];
                }
                cout << "\n";
            }
            cout<<"\ncells explored:"<<exp<<endl;
            return 0;
        }
        for(int i=0;i<4;i++){
            int nx=x+dx[i];
            int ny=y+dy[i];
            if(nx>=0 && nx<rows && ny>=0 && ny<cols){
                if(!vis[nx][ny] && floor[nx][ny]==0){
                    node next;
                    next.x=nx;
                    next.y=ny;
                    next.g = curr.g + 1;
                    next.path=curr.path;
                    next.path.push_back({nx,ny});
                    pq.push(next);
                }
            }
        }
    }
    return 0;
}