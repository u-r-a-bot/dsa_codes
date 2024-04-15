N = int(input("Input size of the board "))
board = [[False for i in range(N)] for i in range(N)]


def isSafe(row, col, board):
    for i in range(col):
        if board[row][i]:
            return False

    i, j = row, col
    while i >= 0 and j >= 0:
        if board[i][j]:
            return False
        i -= 1
        j -= 1

    i, j = row, col
    while i < len(board) and j >= 0:
        if board[i][j]:
            return False
        i += 1
        j -= 1

    return True

def PlaceQueen(col, board, solutions):
    if col == len(board):
        solutions.append([row[:] for row in board])
        return

    for i in range(len(board)):
        if isSafe(i, col, board):
            board[i][col] = True
            PlaceQueen(col + 1, board, solutions)
            board[i][col] = False

def Board_printer(board):
    for row in board:
        for cell in row:
            if cell:
                print(" Q ", end="")
            else:
                print(" . ", end="")
        print("")

def Solve():
    board = [[False] * N for _ in range(N)]
    solutions = []
    PlaceQueen(0, board, solutions)
    for i , solution in enumerate(solutions):
        print(f"{i+1}th Solution is:- ")
        Board_printer(solution)
    if len(solutions) == 0:
        print("No possible solutions")


Solve()
