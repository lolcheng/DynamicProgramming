#include <vector>
#include <math.h>
#include <stdio.h>
#include <algorithm>

// 动态规划基本思路
// 1. 确定dp数组（dp table）以及下标的含义，其值应与所需要求的目标值之间有一定关系
// 2. 确定递推公式
// 3. dp数组如何初始化
// 4. 确定遍历顺序
// 5. 举例推导dp数组
class Solution
{
public:
    // 计算斐波那契数列
    // 思路：0 1 1 2 3 5 8 13 21 34 55
    // 1. dp[i]表示第i个斐波那契数的值
    // 2. 递推公式：dp[i]=dp[i-1]+dp[i-2]
    // 3. dp数组初始化：dp[0]=0,dp[1]=1
    // 4. 确定遍历顺序：从前到后
    int Fib(int N)
    {
        if (N <= 1)
            return N;
        std::vector<int> dp(N + 1);
        dp[0] = 0;
        dp[1] = 1;
        for (int i = 2; i <= N; i++)
        {
            dp[i] = dp[i - 1] + dp[i - 2];
        }
        return dp[N];
    }

    // 爬楼梯问题：一次可以迈一阶也可以迈两阶，问爬到某阶有几种爬法
    // 思路：爬到当前台阶只可能是从上一级台阶迈一步或从上两级台阶迈两步，故爬到当前台阶的可能次数=爬到上两阶的可能次数+爬到上一阶的可能次数
    // 1. dp[i]表示到达i阶有dp[i]种方法
    // 2. 递推公式：dp[i]=dp[i-1]+dp[i-2]
    // 3. dp数组初始化：dp[0]=1,dp[1]=1
    // 4. 确定遍历顺序：从前到后
    int ClimbStairs(int n)
    {
        if (n <= 1)
            return n;
        std::vector<int> dp(n + 1);
        dp[0] = 1;
        dp[1] = 1;
        for (int i = 2; i <= n; i++)
        {
            dp[i] = dp[i - 1] + dp[i - 2];
        }
        return dp[n];
    }

    /*使用最小花费爬楼梯：数组的每个下标作为⼀个阶梯，第 i 个阶梯对应着⼀个⾮负数的体⼒花费值 cost[i]（下标从 0 开始）。
    每当你爬上⼀个阶梯你都要花费对应的体⼒值，⼀旦⽀付了相应的体⼒值，你就可以选择向上爬⼀个阶梯或者爬两个阶梯。
    请你找出达到楼层顶部的最低花费。在开始时，你可以选择从下标为 0 或 1 的元素作为初始阶梯。*/
    // 思路：和爬楼梯问题一样，爬到当前台阶的最小花费=min(爬到上两阶的最小花费+上两阶的体力花费值,爬到上一阶的最小花费+上一阶的体力花费值)
    // 1. dp[i]表示到达i阶时的最小花费
    // 2. 递推公式：dp[i]=dp[i-1]+dp[i-2]
    // 3. dp数组初始化：dp[0]=1,dp[1]=1
    // 4. 确定遍历顺序：从前到后
    int MinCostClimbingStairs(std::vector<int> &cost)
    {
        std::vector<int> dp(cost.size() + 1);
        dp[0] = 0;
        dp[1] = 0;
        for (int i = 2; i <= cost.size(); i++)
        {
            dp[i] = std::min(dp[i - 1] + cost[i - 1], dp[i - 2] + cost[i - 2]);
        }
        return dp[cost.size()];
    }

    /*不同路径：⼀个机器⼈位于mxn⽹格的左上⻆，它每次只能向下或者向右移动⼀步。
    问总共有多少条不同的路径能使机器⼈达到⽹格的右下⻆？*/
    // 思路：由于机器人每次只能向下或者向右移动⼀步，故走到(i,j)处的机器人的可能路径数就是(i-1,j)处的机器人的可能路径数与(i,j-1)的机器人的可能路径数之和
    // 1. dp[i][j]表示到达(i,j)处时机器人的可能路径数
    // 2. 递推公式：dp[i][j]=dp[i-1][j]+dp[i][j-1]
    // 3. dp数组初始化：dp[0][j]=1,dp[i][0]=1，因为机器人到达靠上或左边的格子的路径只可能有一条
    // 4. 确定遍历顺序：从前到后
    int uniquePaths(int m, int n)
    {
        // 二维向量（数组）的声明方法
        std::vector<std::vector<int>> dp(m, std::vector<int>(n, 0));
        for (int i = 0; i < m; i++)
            dp[i][0] = 1;
        for (int j = 0; j < n; j++)
            dp[0][j] = 1;
        for (int i = 1; i < m; i++)
        {
            for (int j = 1; j < n; j++)
            {
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            }
        }
        return dp[m - 1][n - 1];
    }

    /*不同路径2：此时在网格中可能会出现障碍，obstacleGrid描绘m*n的网格，值为1的表示有障碍，值为0的没有*/
    // 思路：只要知道障碍处的dp[i][j]=0就可以了，此外，如果在上/左边的网格出现障碍，则在其下/其右的网格的dp都为0
    int uniquePathsWithObstacles(std::vector<std::vector<int>> &obstacleGrid)
    {
        int m = obstacleGrid.size();
        int n = obstacleGrid[0].size();
        if (obstacleGrid[m - 1][n - 1] == 1 || obstacleGrid[0][0] == 1) // 如果在起点或终点出现了障碍，直接返回0
            return 0;
        std::vector<std::vector<int>> dp(m, std::vector<int>(n, 0));
        for (int i = 0; i < m && obstacleGrid[i][0] == 0; i++)
            dp[i][0] = 1;
        for (int j = 0; j < n && obstacleGrid[0][j] == 0; j++)
            dp[0][j] = 1;
        for (int i = 1; i < m; i++)
        {
            for (int j = 1; j < n; j++)
            {
                if (obstacleGrid[i][j] == 1)
                    continue;
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            }
        }
        return dp[m - 1][n - 1];
    }

    /*整数拆分：给定⼀个正整数，将其拆分为⾄少两个正整数的和，并使这些整数的乘积最⼤化。*/
    // 思路：
    // 1. dp[i]表示拆分i所得的最大化乘积值（至少拆成两个），故dp[0]=dp[1]=0,dp[2]=1
    // 2. 递推公式：dp[i]=max(dp[i],max((i-j)*j,dp[i-j]*j))，内层的max用于取拆成两个数(i-j)*j或更多数dp[i-j]*j的乘积最大值，外层的max用于取不同i下max((i-j)*j,dp[i-j]*j)的最大值
    // 3. dp数组初始化：dp[0][j]=1,dp[i][0]=1，因为机器人到达靠上或左边的格子的路径只可能有一条
    // 4. 确定遍历顺序：从前到后
    int integerBreak(int n)
    {
        std::vector<int> dp(n + 1);
        dp[2] = 1;
        for (int i = 3; i <= n; i++)
        {
            for (int j = 1; j <= i; j++)
            {
                dp[i] = std::max(dp[i], std::max((i - j) * j, dp[i - j] * j));
            }
        }
        return dp[n];
    }
};