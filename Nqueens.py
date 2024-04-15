N = int(input("Input size of the board "))
board = [[False for i in range(N)] for i in range(N)]

def isSafe(row , col):
    for i in range(col):
        if board[row][i]:
            return False
    i , j = row , col
    while i>= 0 and j>= 0:
        if board[i][j]:
            return False
        i-=1
        j-=1
    i , j = row , col
    while i<N and j>0 :
        if board[i][j]:
            return False
        i+=1
        j-=1

    return True
def PlaceQueen(col):
    if col == N:
        return True
    for i in range(N):
        if isSafe(i , col):
            board[i][col] = True
            if PlaceQueen(col+1):
                return True
            board[i][col] = False
    return False
def Board_printer(board):
    for i in board:
        for j in i:
            if j:
                print(" Q " , end = " ")
            else:
                print(" . " , end = " ")
        print("" , end="\n")
def Solve():
    if PlaceQueen(0) == False:
        return False
    Board_printer(board)
    return True

Solve()
