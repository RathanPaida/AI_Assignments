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
            return (board[i][0]=='X')?10:-10;

        if(board[0][i]==board[1][i] &&
           board[1][i]==board[2][i] &&
           board[0][i]!=' ')
            return (board[0][i]=='X')?10:-10;
    }

    // diagonals
    if(board[0][0]==board[1][1] &&
       board[1][1]==board[2][2] &&
       board[0][0]!=' ')
        return (board[0][0]=='X')?10:-10;

    if(board[0][2]==board[1][1] &&
       board[1][1]==board[2][0] &&
       board[0][2]!=' ')
        return (board[0][2]=='X')?10:-10;

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



int minimax(bool isMax)
{
    nodesExplored++;

    int score = evaluate();

    if(score==10 || score==-10)
        return score;

    if(!movesLeft())
        return 0;

    if(isMax)
    {
        int best = -1000;

        for(int i=0;i<3;i++){
        for(int j=0;j<3;j++)
        {
            if(board[i][j]==' ')
            {
                board[i][j]='X';
                best = max(best, minimax(false));
                board[i][j]=' ';
            }
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
                best = min(best, minimax(true));
                board[i][j]=' ';
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

    for(int i=0;i<3;i++){
    for(int j=0;j<3;j++)
    {
        if(board[i][j]==' ')
        {
            board[i][j]='O';        

            int moveVal = minimax(true);

            board[i][j]=' ';
            if(moveVal < bestVal)
            {
                bestVal = moveVal;
                move = {i,j};
            }
        }
    }
    }

    cout << "AI analyzed " << nodesExplored
         << " possibilities.\n";

    return move;
}


int main()
{
    cout<<"Tic Tac Toe (You = X, AI = O)\n";

    while(true)
    {
        printBoard();

        int r,c;
        cout<<"Enter row and column (0-2): ";
        cin>>r>>c;

        if(board[r][c]!=' ')
            continue;

        board[r][c]='X';

        if(evaluate()==10 || !movesLeft())
            break;

        cout<<"AI thinking...\n";

        auto ai = bestMove();
        board[ai.first][ai.second]='O';

        printBoard();

        if(evaluate()==-10 || !movesLeft())
            break;
    }

    int result=evaluate();

    if(result==10) cout<<"You Win\n";
    else if(result==-10) cout<<"AI Wins\n";
    else cout<<"Draw\n";
}