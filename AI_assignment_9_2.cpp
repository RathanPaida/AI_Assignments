#include <bits/stdc++.h>
using namespace std;

char board[3][3] = {
    {' ',' ',' '},
    {' ',' ',' '},
    {' ',' ',' '}
};

long long nodesExplored = 0;

void printBoard()
{
    cout << "\n";
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            cout << board[i][j];
            if(j<2) cout << " | ";
        }
        cout << "\n";
        if(i<2) cout << "--+---+--\n";
    }
    cout << "\n";
}

int evaluate()
{
    
    for(int i=0;i<3;i++)
    {
        if(board[i][0]==board[i][1] &&
           board[i][1]==board[i][2] &&
           board[i][0]!=' ')
            return (board[i][0]=='X') ? 10 : -10;

        if(board[0][i]==board[1][i] &&
           board[1][i]==board[2][i] &&
           board[0][i]!=' ')
            return (board[0][i]=='X') ? 10 : -10;
    }

    
    if(board[0][0]==board[1][1] &&
       board[1][1]==board[2][2] &&
       board[0][0]!=' ')
        return (board[0][0]=='X') ? 10 : -10;

    if(board[0][2]==board[1][1] &&
       board[1][1]==board[2][0] &&
       board[0][2]!=' ')
        return (board[0][2]=='X') ? 10 : -10;

    return 0;
}

bool movesLeft()
{
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            if(board[i][j]==' ')
                return true;
    return false;
}

int alphaBeta(bool isMax, int alpha, int beta)
{
    nodesExplored++;

    int score = evaluate();

    if(score == 10 || score == -10)
        return score;

    if(!movesLeft())
        return 0;

    if(isMax)
    {
        int best = -1000;

        for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
        {
            if(board[i][j]==' ')
            {
                board[i][j]='X';

                best = max(best,
                           alphaBeta(false, alpha, beta));

                board[i][j]=' ';

                alpha = max(alpha, best);

                if(beta <= alpha)
                    return best;   
            }
        }
        return best;
    }
    
    else
    {
        int best = 1000;

        for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
        {
            if(board[i][j]==' ')
            {
                board[i][j]='O';

                best = min(best,
                           alphaBeta(true, alpha, beta));

                board[i][j]=' ';

                beta = min(beta, best);

                if(beta <= alpha)
                    return best;   
            }
        }
        return best;
    }
}


pair<int,int> bestMove()
{
    int bestVal = 1000;
    pair<int,int> move = {-1,-1};

    nodesExplored = 0;

    for(int i=0;i<3;i++)
    for(int j=0;j<3;j++)
    {
        if(board[i][j]==' ')
        {
            board[i][j]='O';

            int value =
                alphaBeta(true, -1000, 1000);

            board[i][j]=' ';

            if(value < bestVal)
            {
                bestVal = value;
                move = {i,j};
            }
        }
    }

    cout << "AI explored "
         << nodesExplored
         << " nodes (Alpha-Beta)\n";

    return move;
}

int main()
{
    cout<<"Tic Tac Toe (Alpha-Beta Pruning)\n";
    cout<<"You = X | AI = O\n";

    while(true)
    {
        printBoard();

        int r,c;


        while(true)
        {
            cout<<"Enter row and column (0-2): ";
            cin>>r>>c;

            if(cin.fail())
            {
                cin.clear();
                cin.ignore(1000,'\n');
                continue;
            }

            if(r>=0 && r<3 && c>=0 && c<3 &&
               board[r][c]==' ')
                break;

            cout<<"Invalid move! Try again.\n";
        }

        board[r][c]='X';

        if(evaluate()==10 || !movesLeft())
            break;

    
        cout<<"AI thinking...\n";

        auto ai = bestMove();
        board[ai.first][ai.second]='O';

        if(evaluate()==-10 || !movesLeft())
            break;
    }

    printBoard();

    int result = evaluate();

    if(result==10) cout<<"You Win!\n";
    else if(result==-10) cout<<"AI Wins!\n";
    else cout<<"Draw!\n";

    return 0;
}