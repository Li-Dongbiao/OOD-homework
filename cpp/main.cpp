#include"Sudoku.cpp"
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <stdexcept>
#include <set>

using namespace std;






int main() {
    string grid;
    cin >> grid;

    // 直接使用 parse 方法创建 Sudoku 实例
    Sudoku sudoku = Sudoku::parse(grid);

    // 获取候选数字
    vector< vector<string> > inference = sudoku.getInference();

    // 打印候选数字
    cout<<"每个空格子的候选数字如下所示(如果不是空格子，则没有候选数字)："<<endl;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) { 
            cout << "Cell (" << i << ", " << j << "): " << inference[i][j] << endl;
        }
    }
	
	// 打印数独的解。如果无解则说明出来 
	vector< vector<char> > solve = sudoku.solveSudoku();
	
	if (solve.size()== 0) {
		cout<<"该数独无解！！"<<endl;
	}
	
	else {
		
		for (int i = 0; i < 9; i++) {
        	for (int j = 0; j < 9; j++) {
            	cout << solve[i][j]<<" ";
        	}
        	cout<<endl;
    	}
	}
	
    return 0;
}





//测试样例 
// 020014500041000020000308000904070003000000000200030405000105000060000150005980070
// 300000001570020004100060000040009080000304000000200070002010005000040067600000008
