from Sudoku import Grid, Sudoku




# 主程序
if __name__ == "__main__":
    grid = input("请输入数独字符串: ")  # 接收用户输入的数独字符串

    # 直接使用 parse 方法创建 Sudoku 实例
    sudoku = Sudoku.parse(grid)

    # 获取候选数字
    inference = sudoku.getInference()

    # 打印候选数字
    print("每个空格子的候选数字如下所示(如果不是空格子，则没有候选数字)：")
    for i in range(9):
        for j in range(9):
            print(f"Cell ({i}, {j}): {inference[i][j]}")

    # 打印数独的解。如果无解则说明出来 
    solve = sudoku.solveSudoku()

    if not solve:
        print("该数独无解！！")
    else:
        for i in range(9):
            for j in range(9):
                print(solve[i][j], end=" ")
            
            print()  #换行

            

#测试样例 
# 020014500041000020000308000904070003000000000200030405000105000060000150005980070
# 300000001570020004100060000040009080000304000000200070002010005000040067600000008

