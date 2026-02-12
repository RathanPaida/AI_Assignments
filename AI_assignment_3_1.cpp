#include <bits/stdc++.h>
using namespace std;

int main() {
    // Environment state
    map<string, string> room = {
        {"A", "Dirty"},
        {"B", "Dirty"},
        {"C", "Dirty"}
    };

    // Rule table: (Location, Status) -> Action
    map<pair<string, string>, string> ruleTable = {
        {{"A", "Dirty"}, "Suck"},
        {{"A", "Clean"}, "MoveRight"},
        {{"B", "Dirty"}, "Suck"},
        {{"B", "Clean"}, "MoveRight"},
        {{"C", "Dirty"}, "Suck"},
        {{"C", "Clean"}, "MoveLeft"}
    };

    string location = "A";
    int cost = 0;

    cout << "=== Simple Reflex Vacuum Cleaner ===\n";

    for (int step = 1; step <= 7; step++) {
        string status = room[location];
        string action = ruleTable[{location, status}];

        cout << "Step " << step
             << " | Location: " << location
             << " | Percept: (" << location << ", " << status << ")"
             << " | Action: " << action << endl;

        // Execute action
        if (action == "Suck") {
            room[location] = "Clean";
            cost += 1;
        } 
        else if (action == "MoveRight") {
            if (location == "A") location = "B";
            else if (location == "B") location = "C";
            cost += 1;
        } 
        else if (action == "MoveLeft") {
            if (location == "C") location = "B";
            cost += 1;
        }
    }

    cout << "\nFinal State: A=" << room["A"]
         << ", B=" << room["B"]
         << ", C=" << room["C"] << endl;

    cout << "Total Performance Cost = " << cost << endl;

    return 0;
}
