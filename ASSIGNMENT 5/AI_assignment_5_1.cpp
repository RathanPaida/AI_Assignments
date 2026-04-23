#include<bits/stdc++.h>
using namespace std;
struct state{
    int girlnum;
    int boynum;
    int boatpos;
    int depth;
    vector<pair<int,int>> path;
};
int explored = 0;
bool issafe(int girlleft,int boyleft,int girltotal,int boytotal){
    if(girlleft < 0 || boyleft < 0 || girlleft > girltotal || boyleft > boytotal) return false;
    int girlright = girltotal - girlleft;
    int boyright = boytotal - boyleft;
    if((girlleft > 0 && girlleft < boyleft) ||(girlright > 0 && girlright < boyright)) return false;
    return true;
}
bool depthlimitedsearch(state startstate,int girll,int boyl,int depth_limit,bool visited[4][4][2]){
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
            for(int k=0; k<2; k++) visited[i][j][k] = false;
    stack<state> s;
    s.push(startstate);
    visited[startstate.girlnum][startstate.boynum][startstate.boatpos] = true;
    while(!s.empty()){
        state current = s.top();
        s.pop();
        explored++;
        if(current.girlnum == 0 && current.boynum == 0 && current.boatpos == 1){
            cout<<"Goal reached Successfully"<<endl;
            cout<<"path (girl,boy): "<<endl;
            for(auto it : current.path){
                cout<<"( "<<it.first<<","<<it.second<<")"<<endl;
            }
            return true;
        }
        else {
            if(current.depth < depth_limit){
                for(int g=0;g<=2;g++){
                    for(int b=0;b<=2;b++){
                        if( g+b >= 1 && g+b <=2){
                            state temp = current;
                            temp.depth++;
                            if(current.boatpos == 0){
                                temp.girlnum -= g;
                                temp.boynum -= b;
                                temp.boatpos = 1;
                            }
                            else{
                                temp.girlnum += g;
                                temp.boynum += b;
                                temp.boatpos = 0;
                            }
                            if(issafe(temp.girlnum,temp.boynum,girll,boyl) && !visited[temp.girlnum][temp.boynum][temp.boatpos]){
                                temp.path.push_back({g,b});
                                s.push(temp);
                                visited[temp.girlnum][temp.boynum][temp.boatpos] = true;
                            }
                        }
                    }
                }
            }
        }
    }
    return false;
}
void iterativeDeepening(state start, int girll, int boyl,bool visited[4][4][2]) {
    int total_exp = 0;
    for (int i = 0; i <= 20; i++) {
        cout << "Searching at depth limit: " << i << endl;
        explored = 0;
        bool found = depthlimitedsearch(start,girll,boyl,i,visited);
        total_exp += explored;
        if (found) {
            cout<<"Depth : "<<i<<endl;
            cout<<"total explored : "<<total_exp<<endl;
            return;
        }
    }
    cout << "No solution found within depth 20" << endl;
}
int main(){
    int girlleft,boysleft,boatstart,limit;
    cout<<"enter number of girls : ";
    cin>>girlleft;
    cout<<"enter number of boys : ";
    cin>>boysleft;
    cout<<"enter boat state : ";
    cin>>boatstart;
    cout<<"enter depth limit : ";
    cin>>limit;
    bool visited[4][4][2];
    state start{girlleft,boysleft,boatstart,0,{}};
    cout << "\n---Depth Limited Search ---" << endl;
    explored = 0;
    if(!depthlimitedsearch(start, girlleft, boysleft, limit, visited)){
        cout << "Cannot reach goal state with depth limit " << limit << endl;
    }
    cout<<"explored in DLS: "<<explored<<endl;
    cout<<"\n";
    cout<<"---IDFS---"<<endl;
    iterativeDeepening(start, girlleft, boysleft,visited);
    return 0;
}