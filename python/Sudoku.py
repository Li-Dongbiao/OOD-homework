import math


# Grid 类，表示数独的基本结构
class Grid:
    def __init__(self, grid=None):
        # 默认构造函数，初始化方格
        self.GRID_SIZE = 0
        self.BOX_SIZE = 0
        self.grip = []
        
        if grid is not None:
            self.from_string(grid)

    # 通过字符串构造方格，确保字符串非空且长度为完全平方数
    def from_string(self, grid):
        if not grid:
            raise ValueError("Grid string cannot be empty.")  # 抛出异常

        size = len(grid)
        self.GRID_SIZE = int(math.sqrt(size))  # 计算方格大小
        if self.GRID_SIZE * self.GRID_SIZE != size:
            raise ValueError("Grid length must be a perfect square.")  # 抛出异常

        # 根据计算出的 GRID_SIZE 初始化方格矩阵
        self.grid = [[grid[i * self.GRID_SIZE + j] for j in range(self.GRID_SIZE)] for i in range(self.GRID_SIZE)]



    # 获取特定行的字符
    def getRow(self, row):
        if row < 0 or row >= self.GRID_SIZE:
            raise IndexError("Row index out of range.")  # 抛出越界异常
        return self.grid[row]  # 返回行

    # 获取特定列的字符
    def getColumn(self, col):
        if col < 0 or col >= self.GRID_SIZE:
            raise IndexError("Column index out of range.")  # 抛出越界异常
        return [self.grid[i][col] for i in range(self.GRID_SIZE)]

    # 获取九宫格内的数字
    def getBox(self, row, col):
        box = []
        box_row_start = (row // self.BOX_SIZE) * self.BOX_SIZE  # 计算小九宫格的起始行
        box_col_start = (col // self.BOX_SIZE) * self.BOX_SIZE  # 计算小九宫格的起始列

        # 填充小九宫格
        for i in range(self.BOX_SIZE):
            for j in range(self.BOX_SIZE):
                box.append(self.grid[box_row_start + i][box_col_start + j])
        return box  # 返回小九宫格的字符



# Sudoku 类，继承自 Grid 类，表示数独
class Sudoku(Grid):
    def __init__(self, grid):
        # 通过字符串初始化数独
        super().__init__(grid)
        self.GRID_SIZE = 9  # 固定为 9x9 的数独
        self.BOX_SIZE = 3   # 每个小九宫格为 3x3

    # 静态方法，用于解析输入字符串并返回 Sudoku 实例
    @staticmethod
    def parse(grid):
        return Sudoku(grid)

    # 数独中，当某个格子字符为 '0' 时，选出候选数字
    def getInference(self):
        candidates = [["" for _ in range(self.GRID_SIZE)] for _ in range(self.GRID_SIZE)]
        for row in range(self.GRID_SIZE):
            for col in range(self.GRID_SIZE):
                if self.grid[row][col] == '0':  # 检查是否为空格
                    used_numbers = set()  # 存储已用数字
                    
                    # 获取行、列和对应的方框的已用数字
                    row_chars = self.getRow(row)
                    col_chars = self.getColumn(col)
                    box_chars = self.getBox(row, col)

                    # 收集已用数字
                    used_numbers.update(row_chars)
                    used_numbers.update(col_chars)
                    used_numbers.update(box_chars)

                    # 获取候选数字
                    for num in '123456789':
                        if num not in used_numbers:  # 检查未使用的数字
                            candidates[row][col] += num  # 添加候选数字

        return candidates  # 返回候选数字


    # 使用深度搜索的方法解决数独
    def solveSudoku(self):
        solution = [row[:] for row in self.grid]  # 复制当前数独
        if self.backtrack(solution):  # 尝试解决数独
            return solution  # 如果找到解，返回解
        return []  # 否则返回空列表

    # 深度优先搜索的回溯法
    def backtrack(self, board):
        for row in range(self.GRID_SIZE):
            for col in range(self.GRID_SIZE):
                if board[row][col] == '0':  # 找到一个空格
                    # 此时是数独新的状态，值得创建一个新的对象
                    new_grid = ''.join(''.join(r) for r in board)  # 构建新的数独字符串
                    new_sudoku = Sudoku.parse(new_grid)  # 解析为新的 Sudoku 对象

                    # 获取候选数字
                    inference = new_sudoku.getInference()
                    candidates = inference[row][col]  # 获取当前空格的候选数字
                    for num in candidates:
                        board[row][col] = num  # 尝试填入候选数字
                        if self.backtrack(board):  # 递归继续填充
                            return True  # 如果找到解，返回 True
                        board[row][col] = '0'  # 回溯到之前的状态
                    return False  # 如果没有有效填入，返回 False
        return True  # 找到解
