#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <stdexcept>
#include <set>

using namespace std;



// �����࣬������뱣֤�Ƿǿյ��ұ����Ƿ��󣬼����Ϳ���ͬ 
class Grid {
public:
    // ���캯�� 
    Grid() : GRID_SIZE(0), BOX_SIZE(0), gridMatrix() {}

    // ���캯����ͬʱҪ��֤������ַ����ǿ����ַ������ȱ���Ϊ��ȫƽ���� 
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

    // ��ȡ�ض�row��һ�е��ַ� 
    vector<char> getRow(int row) {
        if (row < 0 || row >= GRID_SIZE) {
            throw out_of_range("Row index out of range.");
        }
        return gridMatrix[row];
    }

    // ��ȡ�ض�col��һ�е��ַ� 
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

    // ��ȡ�Ź����ڵ����� 
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


// Sudoku�࣬�̳�Grid�� 
class Sudoku : public Grid {
public:    
    // ���캯��
    Sudoku() : Grid() {}

    // ���캯�� 
    Sudoku(string grid) : Grid(grid) {
        GRID_SIZE = 9;  // �̶�Ϊ9x9
        BOX_SIZE = 3;   // ÿ��С�Ź���Ϊ3x3
    }
    
    // ��̬�࣬���ڽ���������ַ������õ�Sudokuʵ�� 
    static Sudoku parse(string grid) {
        return Sudoku(grid);
    }
    
    // �����У���ĳ�������ַ�Ϊ'0'��ʱ��ѡ����ѡ�����ַ�ƴ�ӳ�Ϊ�ַ��� 
    vector< vector<string> > getInference() {
        vector< vector<string> > candidates(GRID_SIZE, vector<string>(GRID_SIZE));
        for (int row = 0; row < GRID_SIZE; ++row) {
            for (int col = 0; col < GRID_SIZE; ++col) {
                if (gridMatrix[row][col] == '0') {
                    set<char> usedNumbers;

                    // ��ȡ�С��кͶ�Ӧ�ķ������������
                    vector<char> rowChars = getRow(row);
                    vector<char> colChars = getColumn(col);
                    vector<char> boxChars = getBox(row, col);

                    // �ռ���������
                    usedNumbers.insert(rowChars.begin(), rowChars.end());
                    usedNumbers.insert(colChars.begin(), colChars.end());
                    usedNumbers.insert(boxChars.begin(), boxChars.end());

                    // ��ȡ��ѡ����
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
    
     
    
    
    // ������һ��������������
	// ��������н�Ļ���ʹ����������İ취�����������һ���⣬����һ���ǿյ����� 
	// ���û�У��ͷ���һ�������� 
	vector< vector<char> > solveSudoku() {
    	vector< vector<char> > solution = gridMatrix;  // ���Ƶ�ǰ����
    	if (backtrack(solution)) {
        	return solution;  // ����ҵ��⣬���ؽ�
    	}
    	return vector< vector<char> >();  // ���򷵻ؿ�����
	}



	// ������������Ļ��ݷ�
	bool backtrack(vector< vector<char> >& board) {
    	for (int row = 0; row < GRID_SIZE; ++row) {
        	for (int col = 0; col < GRID_SIZE; ++col) {
            	if (board[row][col] == '0') {  // �ҵ�һ���ո�
            		// ��ʱ�������µ�״̬��ֵ�ô���һ���µĶ���
					string new_grid = "";
					for(int i = 0; i < board.size(); i++) {
						for (int j = 0; j< board[i].size(); j++) {
							new_grid += board[i][j];
						}
					} 
            		Sudoku new_sudoku = Sudoku::parse(new_grid);
            		
                	// ��ȡ��ѡ����
                	vector< vector<string> > inference = new_sudoku.getInference();
                	string candidate = inference[row][col];
                    for (int index = 0; index < candidate.length(); index++) {
                        board[row][col] = candidate[index];  // ���������ѡ����
                        if ( backtrack(board) ) {  // �ݹ�������
                            return true;  // ����ҵ��⣬����true
                        }
                        board[row][col] = '0';  // ����
                    }
                	return false;  // ���û����Ч���룬����false
            	}
        	}
    	}
    	return true;  // �ҵ���
	}
    
    
    
};






