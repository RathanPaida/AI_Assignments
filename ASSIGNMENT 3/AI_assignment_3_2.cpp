#include <bits/stdc++.h>
using namespace std;

struct Percept
{
    bool inboundTrain;
    bool outboundTrain;
    bool obstacle;
    bool manual;
};

struct Action
{
    string gate;
    string siren;
    string signal;
    string reason;
};

Action simpleReflexAgent(const Percept &p)
{
    Action a;

    // Priority 1: Manual emergency
    if (p.manual)
    {
        a = {"DOWN", "ON", "RED",
             "Manual emergency activated by station master"};
    }
    // Priority 2: Obstacle detected
    else if (p.obstacle)
    {
        a = {"DOWN", "ON", "RED",
             "Obstacle detected in yellow box; collision risk"};
    }
    // Priority 3: Any train detected
    else if (p.inboundTrain || p.outboundTrain)
    {
        a = {"DOWN", "ON", "GREEN",
             "Train detected on track; close gates for road safety"};
    }
    // Priority 4: All clear
    else
    {
        a = {"UP", "OFF", "GREEN",
             "No train, no obstacle, normal operation"};
    }

    return a;
}

int main()
{
    vector<Percept> scenarios = {
        {1, 0, 0, 0}, // Inbound train
        {0, 0, 0, 0}, // All clear
        {0, 0, 0, 1}, // Manual emergency
        {0, 0, 1, 0}, // Obstacle
        {1, 0, 1, 0}, // Train + obstacle
        {1, 1, 0, 0}  // Double-track trains
    };

    for (int i = 0; i < scenarios.size(); i++)
    {
        Action act = simpleReflexAgent(scenarios[i]);

        cout << "\nScenario " << i + 1 << endl;
        cout << "Percept:" << endl;
        cout << "  Inbound Train : " << scenarios[i].inboundTrain << endl;
        cout << "  Outbound Train: " << scenarios[i].outboundTrain << endl;
        cout << "  Obstacle      : " << scenarios[i].obstacle << endl;
        cout << "  Manual        : " << scenarios[i].manual << endl;

        cout << "Action:" << endl;
        cout << "  Gate   : " << act.gate << endl;
        cout << "  Siren  : " << act.siren << endl;
        cout << "  Signal : " << act.signal << endl;

        cout << "Reason: " << act.reason << endl;
        cout << "--------------------------------------\n";
    }

    return 0;
}
