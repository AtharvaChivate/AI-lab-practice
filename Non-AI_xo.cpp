// 59267
#include <iostream>
#include <vector>

using namespace std;

enum Player
{
    EMPTY = 2,
    X,
    O
};

vector<Player> board(10, EMPTY); // Board positions 1-9

void printBoard()
{
    cout << "Current Board:" << endl;
    for (int i = 1; i <= 9; i++)
    {
        if (board[i] == EMPTY)
            cout << "-";
        else if (board[i] == X)
            cout << "X";
        else
            cout << "O";

        if (i % 3 == 0)
            cout << endl;
        else
            cout << " | ";
    }
}

bool checkWin(Player player)
{
    for (int i = 1; i <= 7; i += 3)
    {
        if (board[i] == player && board[i + 1] == player && board[i + 2] == player)
            return true;
    }
    for (int i = 1; i <= 3; i++)
    {
        if (board[i] == player && board[i + 3] == player && board[i + 6] == player)
            return true;
    }
    if ((board[1] == player && board[5] == player && board[9] == player) ||
        (board[3] == player && board[5] == player && board[7] == player))
        return true;
    return false;
}

bool isDraw()
{
    for (int i = 1; i <= 9; i++)
    {
        if (board[i] == EMPTY)
            return false;
    }
    return true;
}

int possWin(Player player)
{
    for (int i = 1; i <= 9; i++)
    {
        if (board[i] == EMPTY)
        {
            board[i] = player;
            if (checkWin(player))
            {
                board[i] = EMPTY;
                return i;
            }
            board[i] = EMPTY;
        }
    }
    return 0;
}

void go(int move, Player player)
{
    board[move] = player;
}

int make2()
{
    if (board[1] == EMPTY)
        return 1;
    if (board[3] == EMPTY)
        return 3;
    if (board[7] == EMPTY)
        return 7;
    if (board[9] == EMPTY)
        return 9;
    return 0;
}

void computerMove(int turn)
{
    int move = 0;
    switch (turn)
    {
    case 2:
        if (board[5] == EMPTY)
            move = 5;
        else
            move = 1;
        break;
    case 4:
        move = possWin(O);
        if (move == 0)
            move = make2();
        break;
    case 6:
        move = possWin(O);
        if (move == 0)
            move = possWin(X);
        if (move == 0)
            move = make2();
        break;
    case 8:
        move = possWin(O);
        if (move == 0)
            move = possWin(X);
        if (move == 0)
        {
            for (int i = 1; i <= 9; i++)
            {
                if (board[i] == EMPTY)
                {
                    move = i;
                    break;
                }
            }
        }
        break;
    }

    if (move != 0)
        go(move, O);
}

int main()
{
    int move;
    for (int turn = 1; turn <= 9; turn++)
    {
        printBoard();
        if (turn % 2 != 0)
        {
            cout << "X's turn. Enter your move (1-9): ";
            cin >> move;
            while (board[move] != EMPTY || move < 1 || move > 9)
            {
                cout << "Invalid move! Try again: ";
                cin >> move;
            }
            go(move, X);
        }
        else
        {
            computerMove(turn);
        }

        if (checkWin(X))
        {
            printBoard();
            cout << "X wins!" << endl;
            break;
        }
        if (checkWin(O))
        {
            printBoard();
            cout << "O wins!" << endl;
            break;
        }
        if (isDraw())
        {
            printBoard();
            cout << "It's a draw!" << endl;
            break;
        }
    }
    return 0;
}
