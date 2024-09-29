#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <stdexcept>
#include <set>

using namespace std;



// 方格类，方格必须保证是非空的且必须是方阵，即长和宽相同 
class Grid {
public:
    // 构造函数 
    Grid() : GRID_SIZE(0), BOX_SIZE(0), gridMatrix() {}

    // 构造函数，同时要保证输入的字符串非空且字符串长度必须为完全平方数 
    Grid(string grid) {
        if (grid.empty()) {
            throw invalid_argument("Grid string cannot be empty.");
        }

        int size = grid.length();
        GRID_SIZE = static_cast<int>(sqrt(size));
        if (GRID_SIZE * GRID_SIZE != size) {
            throw invalid_argument("Grid length must be a perfect square.");
        }
        
        gridMatrix.resize(GRID_SIZE, vector<char>(GRID_SIZE));
        for (int i = 0; i < GRID_SIZE; ++i) {
            for (int j = 0; j < GRID_SIZE; ++j) {
                gridMatrix[i][j] = grid[i * GRID_SIZE + j];
            }
        }
    }

    // 获取特定row的一行的字符 
    vector<char> getRow(int row) {
        if (row < 0 || row >= GRID_SIZE) {
            throw out_of_range("Row index out of range.");
        }
        return gridMatrix[row];
    }

    // 获取特定col的一列的字符 
    vector<char> getColumn(int col) {
        if (col < 0 || col >= GRID_SIZE) {
            throw out_of_range("Column index out of range.");
        }
        vector<char> column(GRID_SIZE);
        for (int i = 0; i < GRID_SIZE; ++i) {
            column[i] = gridMatrix[i][col];
        }
        return column;
    }

    // 获取九宫格内的数字 
    vector<char> getBox(int row, int col) {
        vector<char> box;
        int boxRowStart = (row / BOX_SIZE) * BOX_SIZE;
        int boxColStart = (col / BOX_SIZE) * BOX_SIZE;

        for (int i = 0; i < BOX_SIZE; ++i) {
            for (int j = 0; j < BOX_SIZE; ++j) {
                box.push_back(gridMatrix[boxRowStart + i][boxColStart + j]);
            }
        }
        return box;
    }

protected:
    vector< vector<char> > gridMatrix; 
    int BOX_SIZE;
    int GRID_SIZE;
};


// Sudoku类，继承Grid类 
class Sudoku : public Grid {
public:    
    // 构造函数
    Sudoku() : Grid() {}

    // 构造函数 
    Sudoku(string grid) : Grid(grid) {
        GRID_SIZE = 9;  // 固定为9x9
        BOX_SIZE = 3;   // 每个小九宫格为3x3
    }
    
    // 静态类，用于解析输入的字符串，得到Sudoku实例 
    static Sudoku parse(string grid) {
        return Sudoku(grid);
    }
    
    // 数独中，当某个格子字符为'0'的时候，选出候选数字字符拼接成为字符串 
    vector< vector<string> > getInference() {
        vector< vector<string> > candidates(GRID_SIZE, vector<string>(GRID_SIZE));
        for (int row = 0; row < GRID_SIZE; ++row) {
            for (int col = 0; col < GRID_SIZE; ++col) {
                if (gridMatrix[row][col] == '0') {
                    set<char> usedNumbers;

                    // 获取行、列和对应的方框的已用数字
                    vector<char> rowChars = getRow(row);
                    vector<char> colChars = getColumn(col);
                    vector<char> boxChars = getBox(row, col);

                    // 收集已用数字
                    usedNumbers.insert(rowChars.begin(), rowChars.end());
                    usedNumbers.insert(colChars.begin(), colChars.end());
                    usedNumbers.insert(boxChars.begin(), boxChars.end());

                    // 获取候选数字
                    for (char num = '1'; num <= '9'; ++num) {
                        if (usedNumbers.find(num) == usedNumbers.end()) {
                            candidates[row][col].push_back(num);
                        }
                    }
                }
            }
        }
        return candidates;
    }
    
     
    
    
    // 复制另一个单独的数独，
	// 如果数独有解的话，使用深度搜索的办法来解出数独的一个解，返回一个非空的向量 
	// 如果没有，就返回一个空向量 
	vector< vector<char> > solveSudoku() {
    	vector< vector<char> > solution = gridMatrix;  // 复制当前数独
    	if (backtrack(solution)) {
        	return solution;  // 如果找到解，返回解
    	}
    	return vector< vector<char> >();  // 否则返回空向量
	}



	// 深度优先搜索的回溯法
	bool backtrack(vector< vector<char> >& board) {
    	for (int row = 0; row < GRID_SIZE; ++row) {
        	for (int col = 0; col < GRID_SIZE; ++col) {
            	if (board[row][col] == '0') {  // 找到一个空格
            		// 此时是数独新的状态，值得创建一个新的对象
					string new_grid = "";
					for(int i = 0; i < board.size(); i++) {
						for (int j = 0; j< board[i].size(); j++) {
							new_grid += board[i][j];
						}
					} 
            		Sudoku new_sudoku = Sudoku::parse(new_grid);
            		
                	// 获取候选数字
                	vector< vector<string> > inference = new_sudoku.getInference();
                	string candidate = inference[row][col];
                    for (int index = 0; index < candidate.length(); index++) {
                        board[row][col] = candidate[index];  // 尝试填入候选数字
                        if ( backtrack(board) ) {  // 递归继续填充
                            return true;  // 如果找到解，返回true
                        }
                        board[row][col] = '0';  // 回溯
                    }
                	return false;  // 如果没有有效填入，返回false
            	}
        	}
    	}
    	return true;  // 找到解
	}
    
    
    
};






