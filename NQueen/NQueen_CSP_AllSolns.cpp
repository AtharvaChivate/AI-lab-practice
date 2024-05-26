#include<iostream>
#include<vector>
using namespace std;

class CSP
{
    int boardSize;
    vector<int> currentSolution;
    vector<vector<int>> allSolutions;

public:
    CSP(int boardSize) : boardSize(boardSize) {}

    void solve(){
        backtrack(0);
    }

    void printAllSolutions(){
        if(allSolutions.empty()){
            cout << "No Solutions Found" << endl;
        }
        else{
            for(auto solution : allSolutions){
                for(int row = 0; row<boardSize; row++){
                    for(int column = 0; column < boardSize; column++){
                        if(column == solution[row]){
                            cout << "Q ";
                        }
                        else{
                            cout << ". ";
                        }
                    }
                    cout << endl;
                }
                cout << endl;
            }
        }
    }

private:
    void backtrack(int row){
        if(row == boardSize){
            allSolutions.push_back(currentSolution);
            return;
        }else{
            for(int col = 0; col < boardSize; col++){
                if(isSafe(row,col)){
                    currentSolution.push_back(col);
                    backtrack(row+1);
                    currentSolution.pop_back();
                }
            }
        }
    }

    bool isSafe(int row, int col){
        for(int i = 0; i< row; i++){
            int prevCol = currentSolution[i];
            if(prevCol == col || abs(prevCol - col) == abs(i - row)){
                return false;
            }
        }
        return true;
    }
};

int main(){
    int n;
    cout << "Enter the number of queens (n) n should be greater than 3: ";
    cin >> n;

    CSP csp(n);
    csp.solve(); // Attempt to solve the N-Queens problem

    cout << "Solutions found:" << endl;
    csp.printAllSolutions();

    return 0;
}