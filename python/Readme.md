# Sudoku Solver 项目文档

## 项目概述
该项目实现了一个数独求解器，使用面向对象的设计思想，主要包含两个类：`Grid` 和 `Sudoku`。`Grid` 类表示数独的基本结构，而 `Sudoku` 类继承自 `Grid`，实现了数独的解析和求解功能。

## 文件结构
- `sudoku_solver.py`: 包含 `Grid` 和 `Sudoku` 类的实现。
- `main.py`: 测试代码
- `README.md`: 项目文档（本文件）。

## 类描述

### Grid 类
`Grid` 类表示数独的基本结构，包含以下方法：

- **`__init__(grid=None)`**: 构造函数，初始化方格。可以通过字符串构造方格。
- **`from_string(grid)`**: 通过字符串构造方格，确保字符串非空且长度为完全平方数。
- **`getRow(row)`**: 获取特定行的字符。
- **`getColumn(col)`**: 获取特定列的字符。
- **`getBox(row, col)`**: 获取指定位置的九宫格内的数字。

### Sudoku 类
`Sudoku` 类继承自 `Grid` 类，表示数独，并实现了以下方法：

- **`__init__(grid)`**: 构造函数，通过字符串初始化数独，固定为 9x9 的数独和 3x3 的小九宫格。
- **`parse(grid)`**: 静态方法，用于解析输入字符串并返回 `Sudoku` 实例。
- **`getInference()`**: 获取数独中每个空格子的候选数字。
- **`solveSudoku()`**: 使用深度搜索的方法解决数独。
- **`backtrack(board)`**: 深度优先搜索的回溯法。

## 使用方法

1. 确保 Python 环境已安装。
2. 将代码下载并找到 `main.py`。
3. 在终端或命令行中运行 Python 脚本：
   ```bash
   python main.py
4. 输入你所要解决的sudoku，以字符串形式输入，最终可以得到每个空格子的候选数字和整个数独的其中一个解。


## 错误处理

- 对于无效的输入字符串，构造函数和方法会抛出 `IndexError` 或 `ValueError` 异常。
- 用户应在调用这些方法时处理可能的异常，以确保程序的健壮性。


## 输入形式
形如这样的字符串输入：
\
020014500041000020000308000904070003000000000200030405000105000060000150005980070
\
300000001570020004100060000040009080000304000000200070002010005000040067600000008