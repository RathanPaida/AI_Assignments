#include <bits/stdc++.h>
using namespace std;

const int N = 8;

struct Result 
{
    int initial_h;
    int final_h;
    int steps;
    bool solved;
    vector<int> final_board;
};

int heuristic(vector<int> &board) 
{
    int h = 0;

    for(int i = 0; i < N; i++) 
    {
        for(int j = i + 1; j < N; j++) 
        {

            if(board[i] == board[j])
                h++;

            if(abs(board[i] - board[j]) == abs(i - j))
                h++;
        }
    }
    return h;
}

vector<int> randomBoard() 
{
    vector<int> board(N);
    for(int i = 0; i < N; i++)
        board[i] = rand() % N;
    return board;
}

void printBoard(const vector<int> &board) 
{
    for(int i = 0; i < N; i++)
        cout << board[i] << " ";
}

Result hillClimb(vector<int> board) 
{

    Result res;
    res.initial_h = heuristic(board);
    res.steps = 0;

    while(true) 
    {
        int current_h = heuristic(board);
        int best_h = current_h;
        vector<int> best_board = board;

        for(int col = 0; col < N; col++) 
        {

            int original_row = board[col];

            for(int row = 0; row < N; row++)
            {

                if(row == original_row) continue;
                board[col] = row;
                int h = heuristic(board);

                if(h < best_h) {
                    best_h = h;
                    best_board = board;
                }
            }

            board[col] = original_row;
        }

        if(best_h >= current_h) {
            res.final_h = current_h;
            res.solved = (current_h == 0);
            res.final_board = board;
            return res;
        }
        board = best_board;
        res.steps++;
    }
}

int main() 
{

    srand(time(0));

    int solvedCount = 0;
    int localMinima = 0;

    cout << "Initial Board\t\t\tFinal Board\t\tInitialH\tFinalH\tSteps\t   Status\n";

    for(int i = 1; i <= 50; i++) 
    {
        vector<int> board = randomBoard();

        printBoard(board);
        cout << "\t\t";

        Result r = hillClimb(board);

        printBoard(r.final_board);
        cout << "\t";

        if(r.solved) solvedCount++;
        else localMinima++;

        cout << r.initial_h << "\t\t  "<< r.final_h << "\t\t "<< r.steps << "\t\t"<< (r.solved ? "Solved" : "Local Minima") << endl;
    }
    cout << "\nSolved: " << solvedCount << endl;
    cout << "Local Minima (Failed): " << localMinima << endl;

    return 0;
}