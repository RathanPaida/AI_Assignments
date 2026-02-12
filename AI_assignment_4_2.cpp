#include <bits/stdc++.h>
using namespace std;

const int rows = 10;
const int cols = 20;

/* Grid definition */
vector<vector<int>> grid = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,1,0,0,1,1,1,1,0,0,1,0,0,1,0,0,0,1},
    {1,0,0,1,0,0,1,1,1,1,0,0,1,0,0,1,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {1,1,1,0,1,1,1,1,0,0,1,1,0,0,0,1,1,1,1,1},
    {1,0,0,0,0,0,0,1,0,0,1,1,0,0,0,1,0,0,0,1},
    {1,1,1,1,0,0,0,1,0,0,1,1,0,0,0,1,0,0,0,1},
    {1,0,0,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

pair<int,int> START = {8,4};
pair<int,int> GOAL  = {4,18};

struct Node {
    pair<int,int> state;
    Node* parent;
    string action;
    int path_cost;

    Node(pair<int,int> s, Node* p=nullptr, string a="", int c=0)
        : state(s), parent(p), action(a), path_cost(c) {}
};

/* Manhattan heuristic */
int heuristic(Node* node) {
    return abs(node->state.first - GOAL.first) +
           abs(node->state.second - GOAL.second);
}

/* Comparator for Greedy Best First Search */
struct Compare {
    bool operator()(Node* a, Node* b) {
        return heuristic(a) > heuristic(b);
    }
};

vector<string> ACTIONS(pair<int,int> s) {
    vector<string> actions;
    int r = s.first, c = s.second;

    vector<pair<string,pair<int,int>>> moves = {
        {"Down",{1,0}}, {"Up",{-1,0}}, {"Right",{0,1}}, {"Left",{0,-1}}
    };

    for (auto &m : moves) {
        int nr = r + m.second.first;
        int nc = c + m.second.second;
        if (nr>=0 && nr<rows && nc>=0 && nc<cols && grid[nr][nc]==0)
            actions.push_back(m.first);
    }
    return actions;
}

pair<int,int> RESULT(pair<int,int> s, string action) {
    if (action=="Down")  return {s.first+1, s.second};
    if (action=="Up")    return {s.first-1, s.second};
    if (action=="Right") return {s.first, s.second+1};
    if (action=="Left")  return {s.first, s.second-1};
    return s;
}

Node* BEST_FIRST_SEARCH(int &explored) {
    priority_queue<Node*, vector<Node*>, Compare> frontier;
    Node* start = new Node(START);
    frontier.push(start);

    vector<vector<Node*>> reached(rows, vector<Node*>(cols,nullptr));
    reached[START.first][START.second] = start;

    explored = 0;

    while (!frontier.empty()) {
        Node* node = frontier.top();
        frontier.pop();
        explored++;

        if (node->state == GOAL)
            return node;

        for (string action : ACTIONS(node->state)) {
            pair<int,int> s2 = RESULT(node->state, action);
            int r = s2.first, c = s2.second;

            Node* child = new Node(s2, node, action, node->path_cost+1);

            if (reached[r][c]==nullptr ||
                child->path_cost < reached[r][c]->path_cost) {
                reached[r][c] = child;
                frontier.push(child);
            }
        }
    }
    return nullptr;
}

vector<pair<int,int>> get_path(Node* node) {
    vector<pair<int,int>> path;
    while (node) {
        path.push_back(node->state);
        node = node->parent;
    }
    reverse(path.begin(), path.end());
    return path;
}

void print_grid_with_path(vector<pair<int,int>> &path) {
    set<pair<int,int>> path_set(path.begin(), path.end());

    cout << "\nEvaluated Path on Grid:\n   ";
    for (int c=0;c<cols;c++) cout << c%10 << " ";
    cout << "\n";

    for (int r=0;r<rows;r++) {
        cout << r << "  ";
        for (int c=0;c<cols;c++) {
            if (make_pair(r,c)==START) cout << "S ";
            else if (make_pair(r,c)==GOAL) cout << "E ";
            else if (path_set.count({r,c})) cout << ". ";
            else if (grid[r][c]==1) cout << "# ";
            else cout << "  ";
        }
        cout << "\n";
    }
}

int main() {
    int explored;
    cout << "Starting Greedy Best First Search\n";
    cout << "Start: (" << START.first << "," << START.second << ")\n";
    cout << "Goal : (" << GOAL.first  << "," << GOAL.second  << ")\n";

    Node* solution = BEST_FIRST_SEARCH(explored);

    if (solution) {
        auto path = get_path(solution);
        cout << "\nGoal Found!\n";
        cout << "Path Length: " << path.size() << "\n";
        cout << "Total Cost : " << solution->path_cost << "\n";
        cout << "Nodes Explored: " << explored << "\n";

        print_grid_with_path(path);

        cout << "\nPath Steps:\n";
        Node* cur = solution;
        vector<string> steps;
        while (cur->parent) {
            steps.push_back(cur->action);
            cur = cur->parent;
        }
        reverse(steps.begin(), steps.end());
        for (auto &s: steps) cout << s << "\n";

        cout << "\nHeuristic Justification:\n";
        cout << "Greedy Best First Search uses f(n)=h(n)\n";
        cout << "Manhattan distance guides the robot toward the exit\n";
        cout << "without guaranteeing optimality.\n";
    }
    else {
        cout << "No path found\n";
    }
    return 0;
}
