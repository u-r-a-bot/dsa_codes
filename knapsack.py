

def knapsack(weights , profits , capacity ):
    n = len(weights)
    dp = [[0 for x in range(capacity+1)] for x in range(n+1)]

    for i in range(1 , n+1):
        for j in range(1 , capacity+1):
                if weights[i-1] <= j:
                    dp[i][j] = max(dp[i-1][j] , dp[i-1][j-weights[i-1]] + profits[i-1])
                else:
                    dp[i][j] = dp[i-1][j]
    return dp


profits = [10,20,30]
weights = [6,2,1]
capacity = 4
print(knapsack(weights , profits, capacity))