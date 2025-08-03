#include <vector>
#include <iomanip> 
#include <iostream>

using namespace std;

#define Size 8

const int n = 8;
const vector<int> arrI = {-2, -2, -1, -1, 1, 1, 2, 2};
const vector<int> arrJ = {-1, 1, -2, 2, -2, 2, -1, 1};

bool isSafe(int newi,int newj,const vector<vector<int>> &board){
    return (newi >= 0 && newj >= 0 && newi < board.size() && newj < board[0].size() && board[newi][newj] == -1);
}

bool Knight_Tour(int i, int j, int stepcount,vector<vector<int>> &board)
{
    if(stepcount == n*n ) return true;

    for(int k = 0; k < Size; ++k){
        
        int newi = i + arrI[k];
        int newj = j + arrJ[k];
        
        if(isSafe(newi,newj,board)){
            board[newi][newj] = stepcount;
            
            if(Knight_Tour(newi,newj,stepcount+1,board))
                return true;
            
            board[newi][newj] = -1;
        }
    }

    return false;
}
void printBoard(const vector<vector<int>>& board) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << setw(2) << board[i][j] << " ";
        }
        cout << endl;
    }
}
int main()
{

    vector<vector<int>> board(n, vector<int>(n, -1));

    board[0][0] = 0;
    if(Knight_Tour(0, 0, 1 ,board)){
        printBoard(board);
    }else{
        cout <<"Is Not Possible"<<endl;
    }
    
    return 0;
}
