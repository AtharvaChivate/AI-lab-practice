//45618

#include <stdio.h>
#include <iostream>
using namespace std;

class TTT
{
	int grid[3][3], winningPositions[8][3] = {
						{0, 1, 2},
						{3, 4, 5},
						{6, 7, 8},
						{0, 3, 6},
						{1, 4, 7},
						{2, 5, 8},
						{0, 4, 8},
						{2, 4, 6}};

public:
	TTT()
	{
		// Initializes the game board.
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				this->grid[i][j] = 0;
			}
		}
	}

	bool checkHasWon(char player)
	{
		int targetPlayerNumber = (player == 'X') ? 1 : 2;

		for (int i = 0; i < 8; i++)
		{
			int matchCount = 0;
			for (int j = 0; j < 3; j++)
			{
				int x = this->winningPositions[i][j] / 3;
				int y = this->winningPositions[i][j] % 3;

				if (this->grid[x][y] == targetPlayerNumber)
				{
					++matchCount;
				}
			}
			if (matchCount == 3)
				return true;
		}
		return false;
	}

	// Make a move on the board.
	bool makeMove(char player, int x, int y)
	{
		if (isPositionTaken(x, y))
			return false;
		this->grid[x][y] = (player == 'X') ? 1 : 2;
		return true;
	}

	bool isPositionTaken(int x, int y)
	{
		if ((x < 3) && (y < 3) && (this->grid[x][y] == 0))
			return false;
		return true;
	}

	int miniMax(int newGrid[3][3], bool isMaximizing)
	{
		bool winX = false;
		bool winO = false;

		int targetPlayerNumber = 1;
		for (int i = 0; i < 8; i++)
		{
			int matchCount = 0;
			for (int j = 0; j < 3; j++)
			{
				int x = this->winningPositions[i][j] / 3;
				int y = this->winningPositions[i][j] % 3;

				if (newGrid[x][y] == targetPlayerNumber)
				{
					++matchCount;
				}
			}
			if (matchCount == 3)
			{
				winX = true;
				break;
			}
			else
				winX = false;
		}

		targetPlayerNumber = 2;
		for (int i = 0; i < 8; i++)
		{
			int matchCount = 0;
			for (int j = 0; j < 3; j++)
			{
				int x = this->winningPositions[i][j] / 3;
				int y = this->winningPositions[i][j] % 3;

				if (newGrid[x][y] == targetPlayerNumber)
				{
					++matchCount;
				}
			}
			if (matchCount == 3)
			{
				winO = true;
				break;
			}
			else
				winO = false;
		}

		bool isTie = true;
		for (int i = 0; i < 9; i++)
		{
			int x = i / 3;
			int y = i % 3;
			if ((newGrid[x][y] == 0))
			{
				isTie = false;
			}
		}

		if (winX)
		{
			return 1;
		}
		else if (winO)
		{
			return -1;
		}
		else if (isTie)
		{
			return 0;
		}

		if (isMaximizing)
		{
			int maxScore = -100;
			for (int i = 0; i < 9; i++)
			{
				int x = i / 3;
				int y = i % 3;

				if (newGrid[x][y] == 0)
				{
					newGrid[x][y] = 1;
					int score = miniMax(newGrid, false);
					if (score > maxScore)
					{
						maxScore = score;
					}
					newGrid[x][y] = 0;
				}
			}
			return maxScore;
		}
		else
		{
			int minScore = 100;
			for (int i = 0; i < 9; i++)
			{
				int x = i / 3;
				int y = i % 3;

				if (newGrid[x][y] == 0)
				{
					newGrid[x][y] = 2;
					int score = miniMax(newGrid, true);
					if (score < minScore)
					{
						minScore = score;
					}
					newGrid[x][y] = 0;
				}
			}
			return minScore;
		}
	}

	// AI makes a move using the minimax algorithm.
	void AI()
	{
		int choice = -1;
		int bestMove = -1000;
		int localGrid[3][3];

		for (int i = 0; i <= 8; i++)
		{
			int x = i / 3;
			int y = i % 3;
			localGrid[x][y] = this->grid[x][y];
		}

		for (int i = 0; i <= 8; i++)
		{
			int x = i / 3;
			int y = i % 3;

			if (localGrid[x][y] == 0)
			{
				localGrid[x][y] = 1;

				int move = miniMax(localGrid, false);
				if (bestMove < move)
				{
					bestMove = move;
					choice = i;
				}
				localGrid[x][y] = 0;
			}
		}
		this->makeMove('X', choice / 3, choice % 3);
	}

	// Print the current state of the game board.
	void printBoard()
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				int x = this->grid[i][j];

				cout << " ";
				if (x == 0)
				{
					cout << " ";
				}
				else if (x == 1)
				{
					cout << "X";
				}
				else
				{
					cout << "O";
				}
				cout << " ";
				if (j < 2)
					cout << "|";
			}

			cout << "\n";
			if (i != 2)
			{
				cout << "-----------" << endl;
			}
		}
		cout << "\n";
	}

	// Print the available positions on the board.
	void printBoardStatus()
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				int x = (i * 3) + j;

				cout << " ";
				if (this->isPositionTaken(i, j))
				{
					cout << x;
				}
				else
				{
					cout << x;
				}
				cout << " ";

				if (j < 2)
					cout << "|";
			}
			cout << "\n";
			if (i < 2)
				cout << "-----------\n";
		}
		cout << "\n";
	}
};

int main()
{

	TTT game;
	int turn = 0;
	bool checkWinO = game.checkHasWon('O');
	bool checkWinX = game.checkHasWon('X');

	while (!checkWinO && !checkWinX)
	{
		char currentPlayer;
		cout << "AVAILABLE INPUTS - " << endl;
		game.printBoardStatus();
		game.printBoard();

		if ((turn % 2) == 0)
		{
			currentPlayer = 'O';
		}
		else
		{
			currentPlayer = 'X';
		}

		int position;
		bool validPosition = true;

		if (currentPlayer == 'O')
		{
			do
			{
				cout << "Chance of " << currentPlayer << ": ";
				scanf("%d", &position);
				int x = position / 3;
				int y = position % 3;

				validPosition = game.makeMove(currentPlayer, x, y);
				if (!validPosition)
				{
					cout << "INVALID POSITION" << endl;
				}
			} while (!validPosition);
		}
		else
		{
			cout << "CALLING AI" << endl;
			game.AI();
		}

		++turn;
		checkWinO = game.checkHasWon('O');
		checkWinX = game.checkHasWon('X');

		if (turn == 9 && !checkWinO && !checkWinX)
		{
			break;
		}
	}

	game.printBoard();
	if (checkWinO)
		cout << "O WON!!!!" << endl;
	else if (checkWinX)
		cout << "X WON!!!!" << endl;
	else
		cout << "TIE..." << endl;

	return 0;
};