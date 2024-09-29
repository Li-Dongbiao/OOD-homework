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

    // ֱ��ʹ�� parse �������� Sudoku ʵ��
    Sudoku sudoku = Sudoku::parse(grid);

    // ��ȡ��ѡ����
    vector< vector<string> > inference = sudoku.getInference();

    // ��ӡ��ѡ����
    cout<<"ÿ���ո��ӵĺ�ѡ����������ʾ(������ǿո��ӣ���û�к�ѡ����)��"<<endl;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) { 
            cout << "Cell (" << i << ", " << j << "): " << inference[i][j] << endl;
        }
    }
	
	// ��ӡ�����Ľ⡣����޽���˵������ 
	vector< vector<char> > solve = sudoku.solveSudoku();
	
	if (solve.size()== 0) {
		cout<<"�������޽⣡��"<<endl;
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





//�������� 
// 020014500041000020000308000904070003000000000200030405000105000060000150005980070
// 300000001570020004100060000040009080000304000000200070002010005000040067600000008
