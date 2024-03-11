
def matchainmul(arr):
    n  =len(arr)-1
    table = [[None for  x in range(n)] for x in range(n)] #Initializing The table
    s = [[None for  x in range(n)] for x in range(n)]  # Initializing the k value table
    for i in range(n):
        table[i][i] , s[i][i] = 0 ,0
    for subchain in range(2 , n+1): # Starting to select a subchain of length 2
        for i in range(0 ,n-subchain+1 ): #Starting value of i from zero
            j = i+subchain -1       # initializing i value
            table[i][j] = float('inf') #Storing a max value
            for k in range(i , j): #  initializing value of k between i and j
                val = table[i][k] + table[k+1][j] + arr[i]* arr[k+1] * arr[j+1] # Calculating Value
                if val < table[i][j]:
                    table[i][j] = val # Storing the value if small
                    s[i][j] = k # Storing the k value in s
    return table , s


def print_paranthesis(s , i , j):
    if i==j:
        print(f"A{i}" , end="") # if i = j print Matrix Number
    else:
        print("(", end = "") # print openning bracket
        print_paranthesis(s , i , s[i][j]) # Recursive Calling for the first s[i][j] th value
        print_paranthesis(s , s[i][j]+1 ,j) # Recursive Calling for the last s[i][j]th value
        print(")" , end = "")# print Closing bracket


lis = [30 , 20, 40 , 90, 100 , 12, 36]
table , s = matchainmul(lis)
print("Values in table is ")

for i in table:
    print(i)
print("Values of k used")
for i in s:
    print(i)

print(f"Min number of Multiplications required Will be:- {table[0][len(lis) -2 ]}")
print("Parenthesis Are:- ")
print_paranthesis(s , 0 , len(lis) - 2)


