#include <bits/stdc++.h>
using namespace std;
const int N = 8;
vector<vector<int>> dist = {
    {0,10,15,20,25,30,35,40},
    {12,0,35,15,20,25,30,45},
    {25,30,0,10,40,20,15,35},
    {18,25,12,0,15,30,20,10},
    {22,18,28,20,0,15,25,30},
    {35,22,18,28,12,0,40,20},
    {30,35,22,18,28,32,0,15},
    {40,28,35,22,18,25,12,0}
};
vector<char> city = {'A','B','C','D','E','F','G','H'};
int POP_SIZE = 20;
int GENERATIONS = 200;
double MUT_RATE = 0.2;
int cost(vector<int> &p) {
    int c = 0;
    for (int i = 0; i < N-1; i++)
        c += dist[p[i]][p[i+1]];
    c += dist[p[N-1]][p[0]];
    return c;
}
vector<int> randomPath() {
    vector<int> p;
    for (int i = 1; i < N; i++) p.push_back(i);
    random_shuffle(p.begin(), p.end());
    p.insert(p.begin(), 0);
    return p;
}
vector<int> select(vector<vector<int>> &pop) {
    int i = rand()%POP_SIZE;
    int j = rand()%POP_SIZE;
    return (cost(pop[i]) < cost(pop[j])) ? pop[i] : pop[j];
}
void repair(vector<int> &c) {
    vector<bool> used(N,false);
    used[0]=true;
    for(int i=1;i<N;i++){
        if(!used[c[i]]) used[c[i]]=true;
        else{
            for(int j=1;j<N;j++){
                if(!used[j]){
                    c[i]=j;
                    used[j]=true;
                    break;
                }
            }
        }
    }
}
vector<int> onePoint(vector<int> p1, vector<int> p2) {
    int cut = rand()%(N-1)+1;
    vector<int> child = p1;
    for(int i=cut;i<N;i++) child[i]=p2[i];
    repair(child);
    return child;
}
vector<int> twoPoint(vector<int> p1, vector<int> p2){
    int a = rand()%(N-1)+1;
    int b = rand()%(N-1)+1;
    if(a>b) swap(a,b);
    vector<int> child = p1;
    for(int i=a;i<=b;i++) child[i]=p2[i];
    repair(child);
    return child;
}
void mutate(vector<int> &p){
    if((double)rand()/RAND_MAX < MUT_RATE){
        int i = rand()%(N-1)+1;
        int j = rand()%(N-1)+1;
        swap(p[i],p[j]);
    }
}
pair<int,int> runGA(bool useTwoPoint){
    vector<vector<int>> pop;
    for(int i=0;i<POP_SIZE;i++)
        pop.push_back(randomPath());
    int bestCost = INT_MAX;
    int bestGen = 0;
    for(int gen=0; gen<GENERATIONS; gen++){
        vector<vector<int>> newPop;
        for(int i=0;i<POP_SIZE;i++){
            vector<int> p1 = select(pop);
            vector<int> p2 = select(pop);
            vector<int> child;
            if(useTwoPoint)
                child = twoPoint(p1,p2);
            else
                child = onePoint(p1,p2);
            mutate(child);
            newPop.push_back(child);
            int c = cost(child);
            if(c < bestCost){
                bestCost = c;
                bestGen = gen;
            }
        }
        pop = newPop;
    }
    return {bestCost, bestGen};
}
int main() {
    srand(time(0));
    auto one = runGA(false);
    auto two = runGA(true);
    cout << "One-Point Crossover:\n";
    cout << "Best Cost = " << one.first << endl;
    cout << "\nTwo-Point Crossover:\n";
    cout << "Best Cost = " << two.first << endl;
    return 0;
}