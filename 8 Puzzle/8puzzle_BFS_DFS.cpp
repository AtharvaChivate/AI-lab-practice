#include <iostream>
#include <bits/stdc++.h>
#include <string>
#include <sstream>

using namespace std;

#define Width 3
#define Height 3

class State
{
public:
    State();
    State(int tiles2D[Width][Height]);
    int getValue(int x, int y);
    void setValue(int x, int y, int value);
    State operator=(State);
    bool operator==(const State &) const;
    friend bool operator<(const State &a, const State &o);
    string toString() const;
    string getPath();
    int getBlankX();
    int getBlankY();
    bool moveUp(State &);
    bool moveDown(State &);
    bool moveRight(State &);
    bool moveLeft(State &);
    vector<State> expand();

private:
    int tiles2D[Width][Height];
    vector<string> path;
};

State::State() {}

State::State(int tiles2D[Width][Height])
{
    for (int i = 0; i < Width; i++)
    {
        for (int j = 0; j < Height; j++)
        {
            setValue(i, j, tiles2D[i][j]);
        }
    }
}

int State::getValue(int x, int y)
{
    return tiles2D[x][y];
}

void State::setValue(int x, int y, int value)
{
    tiles2D[x][y] = value;
}

State State::operator=(State myState)
{
    for (int i = 0; i < Width; i++)
    {
        for (int j = 0; j < Height; j++)
        {
            setValue(i, j, myState.getValue(i, j));
        }
    }
    path = myState.path;
    return *this;
}

bool State::operator==(const State &myState) const
{
    bool result = true;
    for (int i = 0; i < Width; i++)
    {
        for (int j = 0; j < Height; j++)
        {
            if (tiles2D[i][j] != myState.tiles2D[i][j])
            {
                result = false;
            }
        }
    }
    return result;
}

bool operator<(const State &a, const State &o)
{
    return (a.toString() < o.toString());
}

string State::toString() const
{
    stringstream stringToReturn;
    for (int i = 0; i < Width; i++)
    {
        for (int j = 0; j < Height; j++)
        {
            if (tiles2D[i][j] != 0)
            {
                stringToReturn << tiles2D[i][j] << " ";
            }
            else
            {
                stringToReturn << "  ";
            }
        }
        stringToReturn << endl;
    }
    return stringToReturn.str();
}

string State::getPath()
{
    unsigned i;
    string s;
    if (path.size() > 0)
    {
        for (i = 0; i < path.size() - 1; i++)
            s += path.at(i) + ", ";
        s += path.at(i) + "\n";
    }
    return s;
}

int State::getBlankX()
{
    for (int i = 0; i < Width; i++)
    {
        for (int j = 0; j < Height; j++)
        {
            if (tiles2D[i][j] == 0)
            {
                return j;
            }
        }
    }
}

int State::getBlankY()
{
    for (int i = 0; i < Width; i++)
    {
        for (int j = 0; j < Height; j++)
        {
            if (tiles2D[i][j] == 0)
            {
                return i;
            }
        }
    }
}

bool State::moveUp(State &myState)
{
    if (getBlankY() == 1 || getBlankY() == 2)
    {
        myState = *this;
        int temp = tiles2D[getBlankY() - 1][getBlankX()];
        int tempX, tempY;
        tempX = getBlankX();
        tempY = getBlankY();
        myState.tiles2D[getBlankY() - 1][getBlankX()] = 0;
        myState.tiles2D[tempY][tempX] = temp;
        myState.path.push_back("moveUp");
        return true;
    }
    return false;
}

bool State::moveDown(State &myState)
{
    if (getBlankY() == 1 || getBlankY() == 0)
    {
        myState = *this;
        int temp = tiles2D[getBlankY() + 1][getBlankX()];
        int tempX, tempY;
        tempX = getBlankX();
        tempY = getBlankY();
        myState.tiles2D[getBlankY() + 1][getBlankX()] = 0;
        myState.tiles2D[tempY][tempX] = temp;
        myState.path.push_back("moveDown");
        return true;
    }
    return false;
}

bool State::moveRight(State &myState)
{
    if (getBlankX() == 1 || getBlankX() == 0)
    {
        myState = *this;
        int temp = tiles2D[getBlankY()][getBlankX() + 1];
        int tempX, tempY;
        tempX = getBlankX();
        tempY = getBlankY();
        myState.tiles2D[getBlankY()][getBlankX() + 1] = 0;
        myState.tiles2D[tempY][tempX] = temp;
        myState.path.push_back("moveRight");
        return true;
    }
    return false;
}

bool State::moveLeft(State &myState)
{
    if (getBlankX() == 1 || getBlankX() == 2)
    {
        myState = *this;
        int temp = tiles2D[getBlankY()][getBlankX() - 1];
        int tempX, tempY;
        tempX = getBlankX();
        tempY = getBlankY();
        myState.tiles2D[getBlankY()][getBlankX() - 1] = 0;
        myState.tiles2D[tempY][tempX] = temp;
        myState.path.push_back("moveLeft");
        return true;
    }
    return false;
}

vector<State> State::expand()
{
    vector<State> children;
    State child;

    if (moveUp(child))
    {
        children.push_back(child);
    }
    if (moveDown(child))
    {
        children.push_back(child);
    }
    if (moveLeft(child))
    {
        children.push_back(child);
    }
    if (moveRight(child))
    {
        children.push_back(child);
    }
    return children;
}

bool DFS(const State &goal, stack<State> &agenda, set<State> &closed, State &solution)
{
    State s;
    if (agenda.empty())
        return false;
    s = agenda.top();
    agenda.pop();

    if (s == goal)
    {
        solution = s;
        return true;
    }
    if (closed.size() == 0 || (closed.find(s) == closed.end()))
    {
        vector<State> children;
        children = s.expand();
        closed.insert(s);
        for (int i = children.size() - 1; i >= 0; i--)
            agenda.push(children.at(i));
    }
    return DFS(goal, agenda, closed, solution);
}

bool BFS(const State &goal, queue<State> &agenda, set<State> &closed, State &solution)
{
    State s;
    if (agenda.empty())
        return false;
    s = agenda.front();
    agenda.pop();

    if (s == goal)
    {
        solution = s;
        return true;
    }
    if (closed.size() == 0 || (closed.find(s) == closed.end()))
    {
        vector<State> children;
        children = s.expand();
        closed.insert(s);
        for (int i = children.size() - 1; i >= 0; i--)
            agenda.push(children.at(i));
    }
    return BFS(goal, agenda, closed, solution);
}

int main()
{
    cout << "// 8 Puzzle Solver //" << endl
         << endl
         << endl;

    int initialTiles2D[3][3] = {
        {1, 2, 3},
        {4, 0, 6},
        {7, 5, 8}};

    int goalTiles2D[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 0}};

    State initial(initialTiles2D);
    State goal(goalTiles2D);

    cout << "Initial puzzle:" << endl;
    cout << initial.toString();
    cout << endl;

    cout << "Goal puzzle:" << endl;
    cout << goal.toString();
    ;
    cout << endl;

    stack<State> agendaDFS;
    set<State> closedDFS;
    agendaDFS.push(initial);
    State solutionDFS;
    DFS(goal, agendaDFS, closedDFS, solutionDFS);
    cout << "Solution steps(DFS): " << endl;
    cout << solutionDFS.getPath();
    cout << endl
         << endl;

    queue<State> agendaBFS;
    set<State> closedBFS;
    agendaBFS.push(initial);
    State solutionBFS;
    BFS(goal, agendaBFS, closedBFS, solutionBFS);
    cout << "Solution steps(BFS): " << endl;
    cout << solutionBFS.getPath();
    return 0;
}