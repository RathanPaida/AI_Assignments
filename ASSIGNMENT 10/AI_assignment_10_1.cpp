#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <limits>
#include <iomanip>

using namespace std;

struct Point {
    double x, y;
};
vector<Point> loadCSV(const string& filename) {
    vector<Point> cities;
    ifstream file(filename);
    string line;
    getline(file, line); // skip header "A,B"

    while (getline(file, line)) {
        stringstream ss(line);
        string xStr, yStr;
        getline(ss, xStr, ',');
        getline(ss, yStr, ',');
        cities.push_back({stod(xStr), stod(yStr)});
    }
    return cities;
}
double squaredDist(Point a, Point b) {
    return (a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y);
}
vector<int> assignClusters(const vector<Point>& cities, const vector<Point>& airports) {
    vector<int> labels(cities.size());
    for (int i = 0; i < cities.size(); i++) {
        double minDist = numeric_limits<double>::max();
        int best = 0;
        for (int k = 0; k < airports.size(); k++) {
            double d = squaredDist(cities[i], airports[k]);
            if (d < minDist) {
                minDist = d;
                best = k;
            }
        }
        labels[i] = best;
    }
    return labels;
}
double totalSSD(const vector<Point>& cities, const vector<Point>& airports, const vector<int>& labels) {
    double total = 0;
    for (int i = 0; i < cities.size(); i++) {
        total += squaredDist(cities[i], airports[labels[i]]);
    }
    return total;
}
vector<Point> gradientDescent(const vector<Point>& cities, vector<Point> airports,
                               double learningRate = 0.01, int maxIter = 1000) {
    int K = airports.size();

    for (int iter = 0; iter < maxIter; iter++) {
        vector<int> labels = assignClusters(cities, airports);

        vector<Point> newAirports = airports;
        bool converged = true;

        for (int k = 0; k < K; k++) {
            double sumX = 0, sumY = 0;
            int count = 0;
            for (int i = 0; i < cities.size(); i++) {
                if (labels[i] == k) {
                    sumX += cities[i].x;
                    sumY += cities[i].y;
                    count++;
                }
            }
            if (count == 0) continue;
            double gradX = 2.0 * (count * airports[k].x - sumX);
            double gradY = 2.0 * (count * airports[k].y - sumY);
            newAirports[k].x = airports[k].x - learningRate * gradX;
            newAirports[k].y = airports[k].y - learningRate * gradY;
            if (fabs(newAirports[k].x - airports[k].x) > 1e-6 ||
                fabs(newAirports[k].y - airports[k].y) > 1e-6) {
                converged = false;
            }
        }
        airports = newAirports;
        if (converged) {
            cout << "  [GD] Converged at iteration " << iter << endl;
            break;
        }
    }
    return airports;
}
vector<Point> newtonRaphson(const vector<Point>& cities, vector<Point> airports,
                             int maxIter = 1000) {
    int K = airports.size();
    for (int iter = 0; iter < maxIter; iter++) {
        vector<int> labels = assignClusters(cities, airports);
        vector<Point> newAirports = airports;
        bool converged = true;
        for (int k = 0; k < K; k++) {
            double sumX = 0, sumY = 0;
            int count = 0;
            for (int i = 0; i < cities.size(); i++) {
                if (labels[i] == k) {
                    sumX += cities[i].x;
                    sumY += cities[i].y;
                    count++;
                }
            }
            if (count == 0) continue;
            double gradX = 2.0 * (count * airports[k].x - sumX);
            double gradY = 2.0 * (count * airports[k].y - sumY);
            double hessX = 2.0 * count;
            double hessY = 2.0 * count;
            newAirports[k].x = airports[k].x - gradX / hessX;
            newAirports[k].y = airports[k].y - gradY / hessY;
            if (fabs(newAirports[k].x - airports[k].x) > 1e-6 ||
                fabs(newAirports[k].y - airports[k].y) > 1e-6) {
                converged = false;
            }
        }
        airports = newAirports;
        if (converged) {
            cout << "  [NR] Converged at iteration " << iter << endl;
            break;
        }
    }
    return airports;
}
void printResults(const string& method, const vector<Point>& airports,
                  const vector<Point>& cities) {
    vector<int> labels = assignClusters(cities, airports);
    double ssd = totalSSD(cities, airports, labels);
    cout << "\n========== " << method << " ==========\n";
    for (int k = 0; k < airports.size(); k++) {
        int count = 0;
        for (int l : labels) if (l == k) count++;
        cout << "Airport " << k+1 << ": (" 
             << fixed << setprecision(4) << airports[k].x 
             << ", " << airports[k].y << ")"
             << "  [" << count << " cities assigned]\n";
    }
    cout << "Total Sum of Squared Distances: " << fixed << setprecision(4) << ssd << "\n";
}
int main() {
    vector<Point> cities = loadCSV("cities.csv");
    cout << "Loaded " << cities.size() << " cities.\n";
    vector<Point> initAirports = {
        {0.0, 0.0},
        {0.0, 5.0},
        {5.0, 5.0}
    };
    cout << "\nRunning Gradient Descent...\n";
    vector<Point> gdAirports = gradientDescent(cities, initAirports, 0.001, 10000);
    printResults("GRADIENT DESCENT", gdAirports, cities);
    cout << "\nRunning Newton-Raphson...\n";
    vector<Point> nrAirports = newtonRaphson(cities, initAirports, 1000);
    printResults("NEWTON-RAPHSON", nrAirports, cities);
    {
        vector<int> gdLabels = assignClusters(cities, gdAirports);
        vector<int> nrLabels = assignClusters(cities, nrAirports);
        double gdSSD = totalSSD(cities, gdAirports, gdLabels);
        double nrSSD = totalSSD(cities, nrAirports, nrLabels);

        cout << "\n========== COMPARISON ==========\n";
        cout << "Gradient Descent SSD : " << fixed << setprecision(4) << gdSSD << "\n";
        cout << "Newton-Raphson SSD   : " << fixed << setprecision(4) << nrSSD << "\n";
        if (gdSSD < nrSSD)
            cout << "Winner: Gradient Descent\n";
        else if (nrSSD < gdSSD)
            cout << "Winner: Newton-Raphson\n";
        else
            cout << "Both methods give same result.\n";
    }
    return 0;
}