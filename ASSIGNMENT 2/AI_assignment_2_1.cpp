#include<bits/stdc++.h>
using namespace std;

using vii = vector<vector<int>>;
using node = pair<vii,int>;   

class queue1 {
    vector<node> data;
    int frontIndex;
public:
    queue1() {
        frontIndex = 0;
    }
    void push(node x) {
        data.push_back(x);
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

pair<int,int> find0(vii &temp){
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(temp[i][j] == 0)
                return {i,j};
        }
    }
    return {-1,-1};
}

int main(){
    vii start = {{7,2,4},{5,0,6},{8,3,1}};
    vii goal  = {{0,1,2},{3,4,5},{6,7,8}};
    queue1 q;
    q.push({start, 0});          
    map<vii,bool> vis;
    vis[start] = true;
    int no_of_states = 0;
    while(!q.empty()){
        node cur = q.front();
        q.pop();

        vii temp = cur.first;
        int depth = cur.second;
        // cout << "[";
        // for(int i=0;i<3;i++){
        //     cout << "[";
        //     for(int j=0;j<3;j++){
        //         cout << temp[i][j] << ((j == 2)? "":" ");
        //     }
        //     cout << ((i == 2) ? "]" : "],");
        // }
        // cout << "]\n";

        no_of_states++;
        if(temp == goal){
            cout << "\nNumber of states explored = " << no_of_states << endl;
            cout << "Cost (depth) = " << depth << endl;
            break;
        }

        pair<int,int> p = find0(temp);

        int dx[] = {-1,1,0,0};
        int dy[] = {0,0,1,-1};

        for(int i=0;i<4;i++){
            int x = p.first + dx[i];
            int y = p.second + dy[i];

            if(x>=0 && x<3 && y>=0 && y<3){
                vii temp1 = temp;
                swap(temp1[p.first][p.second], temp1[x][y]);

                if(!vis[temp1]){
                    vis[temp1] = true;
                    q.push({temp1, depth + 1});  
                }
            }
        }
    }
    return 0;
}