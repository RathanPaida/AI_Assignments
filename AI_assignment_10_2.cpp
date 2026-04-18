#include<bits/stdc++.h>
using namespace std;

enum Location{A,B};
enum Dirt{CLEAN=0,DIRTY=1};

struct State{
    Location loc;
    Dirt dirtA,dirtB;

    bool operator<(const State&other)const{
        if(loc!=other.loc)return loc<other.loc;
        if(dirtA!=other.dirtA)return dirtA<other.dirtA;
        return dirtB<other.dirtB;
    }
};

enum Action{MOVE_LEFT,MOVE_RIGHT,SUCK};

void printState(const State&s){
    cout<<(s.loc==A?"A":"B")<<":("<<(s.dirtA?"1":"0")<<","<<(s.dirtB?"1":"0")<<")";
}

string actionToString(Action a){
    if(a==MOVE_LEFT)return "MoveLeft";
    if(a==MOVE_RIGHT)return "MoveRight";
    return "Suck";
}

vector<State>getSuckOutcomes(const State&s){
    vector<State>outcomes;

    if(s.loc==A){
        if(s.dirtA==DIRTY){
            outcomes.push_back({A,CLEAN,s.dirtB});
            outcomes.push_back({A,CLEAN,CLEAN});
        }else{
            outcomes.push_back(s);
            outcomes.push_back({A,DIRTY,s.dirtB});
        }
    }else{
        if(s.dirtB==DIRTY){
            outcomes.push_back({B,s.dirtA,CLEAN});
            outcomes.push_back({B,CLEAN,CLEAN});
        }else{
            outcomes.push_back(s);
            outcomes.push_back({B,s.dirtA,DIRTY});
        }
    }
    return outcomes;
}

State moveLeft(const State&s){
    if(s.loc==B)return{A,s.dirtA,s.dirtB};
    return s;
}

State moveRight(const State&s){
    if(s.loc==A)return{B,s.dirtA,s.dirtB};
    return s;
}

vector<State>getOutcomes(const State&s,Action act){
    if(act==MOVE_LEFT)return{moveLeft(s)};
    if(act==MOVE_RIGHT)return{moveRight(s)};
    return getSuckOutcomes(s);
}

bool isGoal(const State&s){
    return s.dirtA==CLEAN&&s.dirtB==CLEAN;
}

map<State,Action>andOrGraphSearch(){
    vector<State>allStates;

    for(Location loc:{A,B})
        for(Dirt da:{CLEAN,DIRTY})
            for(Dirt db:{CLEAN,DIRTY})
                allStates.push_back({loc,da,db});

    set<State>solved;
    map<State,Action>policy;

    for(auto&s:allStates)
        if(isGoal(s))solved.insert(s);

    bool changed;

    do{
        changed=false;
        for(auto&s:allStates){
            if(solved.count(s))continue;

            for(Action act:{MOVE_LEFT,MOVE_RIGHT,SUCK}){
                auto outcomes=getOutcomes(s,act);
                bool ok=true;

                for(auto&nxt:outcomes){
                    if(!solved.count(nxt)){ok=false;break;}
                }

                if(ok&&!outcomes.empty()){
                    solved.insert(s);
                    policy[s]=act;
                    changed=true;
                    break;
                }
            }
        }
    }while(changed);

    cout<<"Solved states:\n";
    for(auto&s:allStates){
        printState(s);
        cout<<" -> ";
        if(isGoal(s))cout<<"Goal\n";
        else cout<<actionToString(policy[s])<<"\n";
    }
    return policy;
}

void simulate(State current,const map<State,Action>&policy){
    srand(time(0));

    cout<<"\nSimulation start: ";
    printState(current);
    cout<<"\n";

    int step=0;

    while(!isGoal(current)){
        Action act=policy.at(current);

        cout<<"Step "<<step<<": ";
        printState(current);
        cout<<" -> "<<actionToString(act);

        if(act==SUCK){
            auto outcomes=getSuckOutcomes(current);
            current=outcomes[rand()%outcomes.size()];
        }else if(act==MOVE_LEFT){
            current=moveLeft(current);
        }else{
            current=moveRight(current);
        }

        cout<<" -> ";
        printState(current);
        cout<<"\n";

        if(++step>20)break;
    }
    cout<<"Goal reached!\n";
}

int main(){
    auto policy=andOrGraphSearch();

    simulate({A,DIRTY,DIRTY},policy);
    simulate({B,CLEAN,DIRTY},policy);
    simulate({A,CLEAN,DIRTY},policy);

    return 0;
}