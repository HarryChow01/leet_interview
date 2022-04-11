
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <climits>
#include <string>
#include <vector>
#include <list>
#include <stack>
#include <array>
#include <iostream>
#include <algorithm>
#include <cassert>
#include <map>

using namespace std;

#include <stdio.h>


/*
 * 动态规划：连续数组最大和，并记录最大子数组的边界
 */
int getSumOfArray() {

    vector<int> data = {1, -2, 3, 5, -1, 2}; // result = 9, left = 2, right = 5
    assert(!data.empty());

    size_t left = 0;
    size_t right = 0;
    size_t begin = 0;

    // 初始化变量，maxSum为最大和，curSum为当前和
    int maxSum = data[0];
    int curSum = data[0];
    // 遍历所有元素
    for (size_t i = 1; i < data.size(); i++) {
        //curSum = std::max(data[i], data[i] + curSum);
        // 等同于下面if else；

        // 如果当前和小于等于0，说明之前的是负数，则抛弃前面的和，重新计算
        if (curSum <= 0) { //状态转移方程：dp[j]<0,dp[k]=max(dp[k-1]+a[k],a[k])
            curSum = data[i];
            begin = i;
        } else { // 如果没有问题，直接累加
            curSum += data[i];
        }

        //maxSum = std::max(maxSum, curSum);
        //等同于下面这一句；

        // 更新最大和
        if (curSum > maxSum) {
            maxSum = curSum;
            left = begin;
            right = i;
        }

    }
    cout << "left: " << left << ", right: " << right << endl;
    cout << "maxSum: " << maxSum << endl;
    return maxSum;
}

/*
 * 动态规划：连续二维数组最大和
 * https://blog.csdn.net/linyunzju/article/details/7723730
 * https://blog.csdn.net/hxz_qlh/article/details/15339441
 */

int getSumOf2DArray() {
    const size_t kRowNum = 3;
    const size_t kColNum = 3;
    int data[kRowNum][kColNum] = {
            {-1, 3,  -1},
            {2,  -1, 3},
            {-3, 1,  2},
    };
    int PS[kRowNum + 1][kColNum + 1];
    for (size_t i = 0; i <= kRowNum; ++i) {
        PS[i][0] = 0;
    }
    for (size_t j = 0; j <= kColNum; ++j) {
        PS[0][j] = 0;
    }
    for (size_t i = 1; i <= kRowNum; ++i) {
        for (size_t j = 1; j <= kColNum; ++j) {
            PS[i][j] = data[i - 1][j - 1] + PS[i - 1][j] +
                       PS[i][j - 1] - PS[i - 1][j - 1];
        }
    }
    int64_t allSum = INT32_MIN;
    for (size_t iStart = 1; iStart <= kRowNum; ++iStart) {
        for (size_t iEnd = iStart; iEnd <= kRowNum; ++iEnd) {
            int64_t partSum = INT32_MIN;
            for (size_t j = 1; j <= kColNum; ++j) {
                int64_t curSum = PS[iEnd][j] - PS[iStart - 1][j] -
                                 PS[iEnd][j - 1] + PS[iStart - 1][j - 1];
                partSum = std::max(curSum, partSum + curSum);
                allSum = std::max(allSum, partSum);
            }
        }
    }
    cout << "allSum: " << allSum << endl;
    return (int) allSum;
}

int maxLength(const vector<int>& arr) {
    // write code here
    if (arr.empty()) return 0;
    vector<int> v(100000);
    int res=0;
    int i=0;
    int j=0;
    while (j<arr.size()) {
        if (v[arr[j]] == 0) {
            v[arr[j]] = 1;
            res = max(res,j-i+1);
            j++;
        } else {
            v[arr[i]] = 0;
            i++;
        }
    }
    return res;
}

/*
 * 动态规划：LCS最长公共子序列
 */

// 输出组成LCS的字符串，用一个二维数组记录要打印的状态
void printLCS(vector<vector<size_t>> &vec, string str, size_t i, size_t j) {
    if (i == 0 || j == 0) {
        return;
    }
    if (vec[i][j] == 0) {
        printLCS(vec, str, i - 1, j - 1);
        cout << str[i - 1];
    } else if (vec[i][j] == 1) {
        printLCS(vec, str, i - 1, j);
    } else {
        printLCS(vec, str, i, j - 1);
    }
}

// 获取LCS并输出；
size_t getLCS1() {
    std::string s1 = "ABCBDAB";
    std::string s2 = "BDCABA";
    if (s1.empty() || s2.empty()) {
        return 0;
    }
    vector<vector<size_t>> lcs(s1.size() + 1, vector<size_t>(s2.size() + 1, 0));
    vector<vector<size_t>> vec(s1.size() + 1, vector<size_t>(s2.size() + 1, 0));
    for (size_t i = 1; i <= s1.size(); i++) {
        for (size_t j = 1; j <= s2.size(); j++) {
            if (s1[i - 1] == s2[j - 1]) {
                lcs[i][j] = lcs[i - 1][j - 1] + 1;
                vec[i][j] = 0;
            } else if (lcs[i - 1][j] >= lcs[i][j - 1]) {
                lcs[i][j] = lcs[i - 1][j];
                vec[i][j] = 1;
            } else {
                lcs[i][j] = lcs[i][j - 1];
                vec[i][j] = 2;
            }
        }
    }
    cout << "LCS: " << lcs[s1.size()][s2.size()] << endl;
    printLCS(vec, s1, s1.size(), s2.size());
    return lcs[s1.size()][s2.size()];
}

// 滚动数组实现，降低了存储空间，但是没有改变时间复杂度
size_t getLCS2() {
    std::string s1 = "ABCBDAB";
    std::string s2 = "BDCABA";
    if (s1.empty() || s2.empty()) {
        return 0;
    }
    vector<vector<size_t>> lcs(2, vector<size_t>(s2.size() + 1, 0));

    for (size_t i = 1; i <= s1.size(); ++i) {
        for (size_t j = 1; j <= s2.size(); ++j) {
            if (s1[i - 1] == s2[j - 1]) {
                lcs[i % 2][j] = lcs[(i - 1) % 2][j - 1] + 1;
            } else {
                lcs[i % 2][j] = std::max(lcs[(i - 1) % 2][j], lcs[i % 2][j - 1]);
            }
        }
    }
    cout << "LCS: " << lcs[s1.size() % 2][s2.size()] << endl;
    return lcs[s1.size() % 2][s2.size()];
}


/*
 * 动态规划：编辑距离
 */
size_t editDistance() {
    // https://www.cnblogs.com/littlepanpc/p/7895810.html
    std::string s1 = "sailn";
    std::string s2 = "failing";
    size_t lenA = s1.size();
    size_t lenB = s2.size();
    vector<vector<size_t>> d(lenA + 1, vector<size_t>(lenB + 1, 0));
    for (size_t i = 0; i <= lenA; i++) {
        d[i][0] = i;
    }
    for (size_t i = 0; i <= lenB; i++) {
        d[0][i] = i;
    }
    for (size_t i = 1; i <= lenA; i++) {
        for (size_t j = 1; j <= lenB; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                d[i][j] = d[i - 1][j - 1];
            } else {
                d[i][j] = std::min(d[i - 1][j - 1], std::min(d[i][j - 1], d[i - 1][j])) + 1;
            }
        }
    }
    cout << "editDistance: " << d[lenA][lenB] << endl;  // editDistance: 3
    return d[lenA][lenB];
}

/*
 * 动态规划：硬币找零问题，二维数组保存
 */
size_t coinsChange1(size_t sum) {
    vector<size_t> coinValues = {1, 2, 5};
    size_t coinsNum = coinValues.size();
    vector<vector<size_t>> dp(coinsNum + 1, vector<size_t>(sum + 1, 0));
    for (size_t i = 1; i <= sum; ++i) {
        dp[0][i] = UINT_MAX;
    }
    for (size_t i = 0; i <= coinsNum; ++i) {
        dp[i][0] = 0;
    }

    for (size_t i = 1; i <= coinsNum; i++) {
        for (size_t j = 1; j <= sum; j++) {
            size_t minCoinsNum = UINT_MAX;
            size_t lastIdx = j - coinValues[i - 1];
            if (j >= coinValues[i - 1]) {
                minCoinsNum = dp[i][lastIdx] + 1;
            }
            dp[i][j] = std::min(dp[i - 1][j], minCoinsNum);
        }
    }

    cout << "targetValue uses coins num: " << dp[coinsNum][sum] << endl;
    cout << "coins values: ";
    for (int i = 0; i < coinsNum; ++i) {
        cout << coinValues[i] << " ";
    }
    cout << "\n\nminCoinsNum:" << endl;
    for (size_t i = 1; i <= coinsNum; ++i) {
        for (size_t j = 1; j <= sum; ++j) {
            cout << dp[i][j] << " ";
        }
        cout << endl;
    }
    return dp[coinsNum][sum];
}

/*
 * 动态规划：硬币找零问题，二维数组保存
 * total是要找零的钱数，只用两个一维数组，记录最小coins数目和所有的coins
 * https://blog.csdn.net/wdxin1322/article/details/9501163
 */
size_t coinsChange2(size_t target) {
    vector<size_t> values = {1, 2, 5}; //硬币面值
    //vector<size_t> values ={1,2,5,21,25}; //硬币面值
    vector<size_t> coinsUsedNum(target + 1, 0); //保存每个面值对应最小值，因为0号位置舍弃，故加1
    vector<size_t> coinsTrack(target + 1, 0);

    coinsUsedNum[0] = 0;
    coinsTrack[0] = 0;
    for (size_t i = 1; i <= target; ++i) {
        size_t minCoinNum = UINT64_MAX;
        size_t lastIn = 0;
        for (size_t j = 0; j < values.size(); ++j) {
            if (i >= values[j]) {
                if (coinsUsedNum[i - values[j]] + 1 < minCoinNum) {
                    minCoinNum = coinsUsedNum[i - values[j]] + 1;
                    lastIn = values[j];
                }
            }
        }
        coinsUsedNum[i] = minCoinNum;
        coinsTrack[i] = lastIn;
    }

    for (int i = 1; i < coinsUsedNum.size(); ++i) {
        cout << "changedValue: " << i << " minCoinNum: " << coinsUsedNum[i] << endl;
    }
    cout << "targetValue uses coins num: " << coinsUsedNum[target] << endl;
    size_t i = target;
    while (i > 0 && coinsTrack[i] != 0) {
        cout << coinsTrack[i] << " ";
        i -= coinsTrack[i];
    }
    return coinsUsedNum[target];
}


/* 动态规划：0-1背包问题
 * 给定n种物品和一背包。物品i的重量是wi，其价值为vi，背包的容量为c。
 * 问应如何选择装入背包的物品，使得装入背包中物品的总价值最大?
 * 同时输出最优解物品序列
 * 参考网站：https://blog.csdn.net/luoshixian099/article/details/46572285
 */
void package1() {
    const size_t kItemNum = 5;
    size_t w[kItemNum] = {3, 6, 3, 8, 6}; //商品重量
    size_t v[kItemNum] = {4, 6, 6, 12, 10}; //商品价值
    size_t C = 10; //背包容量
    //c[i][j]表示在商品1到i中，背包容量为j时，最大价值
    vector<vector<size_t>> c(kItemNum + 1, vector<size_t>(C + 1, 0));

    for (size_t i = 1; i <= kItemNum; ++i) {
        for (size_t j = 1; j <= C; ++j) {
            if (j < w[i - 1]) {
                //背包容量小于商品i的重量，商品i一定不选
                c[i][j] = c[i - 1][j];
            } else {
                //比较选与不选商品i的背包总价值大小
                c[i][j] = std::max(c[i - 1][j], v[i - 1] + c[i - 1][j - w[i - 1]]);
            }
        }
    }

    for (size_t i = 0; i <= kItemNum; ++i) {
        for (size_t j = 0; j <= C; ++j) {
            cout << c[i][j] << " ";
        }
        cout << endl;
    }
    size_t i = kItemNum;
    size_t j = C;
    cout << "max value: " << c[i][j] << endl;
    while (i != 0) {
        if (c[i][j] == c[i - 1][j]) {
            cout << "item" << i << " 0" << endl;
        } else {
            cout << "item" << i << " 1" << endl;
            j = j - w[i - 1];
        }
        i--;
    }
}

/*
 * 动态规划：求两个顶点之间的最短路径（维特比[Viterbi]算法）
 * 同时构建最短路径序列
 * https://www.jianshu.com/p/218c1e4f0891
 */
void shortestPath1() {
    const size_t kNodeNum = 10;
    const size_t kMax = INT_MAX;
    vector<size_t> dist(kNodeNum, 0); //记录最短路径为多少
    vector<size_t> path(kNodeNum, 0); //记录最短路径
    size_t array[kNodeNum][kNodeNum] = {
            {kMax, 4,    2,    3,    kMax, kMax, kMax, kMax, kMax, kMax},
            {kMax, kMax, kMax, kMax, 10,   9,    kMax, kMax, kMax, kMax},
            {kMax, kMax, kMax, kMax, 6,    7,    10,   kMax, kMax, kMax},
            {kMax, kMax, kMax, kMax, kMax, 3,    8,    kMax, kMax, kMax},
            {kMax, kMax, kMax, kMax, kMax, kMax, kMax, 4,    8,    kMax},
            {kMax, kMax, kMax, kMax, kMax, kMax, kMax, 9,    6,    kMax},
            {kMax, kMax, kMax, kMax, kMax, kMax, kMax, 5,    4,    kMax},
            {kMax, kMax, kMax, kMax, kMax, kMax, kMax, kMax, kMax, 8},
            {kMax, kMax, kMax, kMax, kMax, kMax, kMax, kMax, kMax, 4},
            {kMax, kMax, kMax, kMax, kMax, kMax, kMax, kMax, kMax, kMax}
    };

    cout << "dist: \n";
    for (size_t col = 1; col < kNodeNum; ++col) {
        size_t minDist = kMax;
        for (size_t row = 0; row < col; ++row) {
            if ((array[row][col] != kMax) && (dist[row] + array[row][col]) < minDist)
                minDist = dist[row] + array[row][col];
        }
        dist[col] = minDist;
        cout << dist[col] << " " << endl;
    }
    cout << "\nshortest path value: " << dist[kNodeNum - 1] << endl;

    size_t col = kNodeNum - 1;
    int idx = 0;
    path[idx++] = col + 1;
    while (col > 0) {
        for (size_t row = col - 1; row >= 0; --row) {
            if ((array[row][col] != kMax) && (dist[row] == (dist[col] - array[row][col]))) {
                col = row;
                path[idx++] = col + 1;
                break;
            }
        }
    }
    while (idx > 0)
        cout << "shortest path: " << path[--idx] << endl;
}


/* 回溯法：0-1背包问题
 * 给定n种物品和一背包。物品i的重量是wi，其价值为pi，背包的容量为C。
 * 问应如何选择装入背包的物品，使得装入背包中物品的总价值最大?
 */

const size_t kItemSize = 3;         //物品的数量
const size_t kCapacity = 16;        //背包的容量
int curWeight = 0;  //当前放入背包的物品总重量
int curValue = 0;   //当前放入背包的物品总价值
int maxValue = 0;  //最优值；当前的最大价值，初始化为0

size_t weight[kItemSize] = {10, 8, 5};  //每个物品的重量
size_t value[kItemSize] = {5, 4, 1};   //每个物品的价值
size_t curItems[kItemSize] = {0, 0, 0};   //curItems[i]=1代表物品i放入背包，0代表不放入

size_t maxValueItems[kItemSize];       //最优解；maxValueItems[i] = 1代表物品i放入背包，0代表不放入


//t = 0 to kItemSize - 1
void packBackTrace(int itemIndex) {

    if (itemIndex >= kItemSize) { //叶子节点，输出结果
        if (curValue > maxValue) { //如果找到了一个更优的解, 保存更优的值和解
            maxValue = curValue;
            for (size_t i = 0; i < kItemSize; ++i)
                maxValueItems[i] = curItems[i];
        }
    } else {
        //遍历当前节点的子节点：0 不放入背包，1放入背包
        for (size_t i = 0; i <= 1; ++i) {
            // i取0和1
            curItems[itemIndex] = i;

            if (i == 0) {  //不放入背包
                packBackTrace(itemIndex + 1);
            } else { //放入背包
                //约束条件：放的下
                if ((curWeight + weight[itemIndex]) <= kCapacity) {
                    curWeight += weight[itemIndex];
                    curValue += value[itemIndex];
                    packBackTrace(itemIndex + 1);
                    curWeight -= weight[itemIndex];
                    curValue -= value[itemIndex];
                }
            }
        }
    }
}

void testPack() {
    packBackTrace(0);
    printf("maxValue：%d\n", maxValue);
    cout << "maxValue items: ";
    for (size_t i = 0; i < kItemSize; ++i) {
        cout << maxValueItems[i] << " ";
    }
    cout << "\ncurWeight: " << curWeight << endl;
    cout << "curValue: " << curValue << endl;
}


int main() {

    //getSumOfArray();
    getSumOf2DArray();
    //getLCS1();
    //editDistance();
    //testPack();
    //coinsChange1(29);
    //package1();
    //shortestPath1();

    return 0;
}










