//
// Created by lf on 2019/5/13.
//
#include <vector>
#include <cmath>
#include <stack>
#include <tuple>
#include "bin2plan.h"

using namespace std;

#ifndef KNAPSACKPROBLEM_BACKTRACKING_H
#define KNAPSACKPROBLEM_BACKTRACKING_H


///* @brief 回溯算法
// * @param knapsack_size 背包容量
// * @param weights 物品重量
// * @param values 物品价值
// * @retval vector<bool> pick 布尔指示最优方案中是否选取对应位置物品
// */
double back_tracking(double knapsack_size, vector<double> weights, vector<double> values, vector<bool> &pick) {

    stack<tuple<int, int, double, double >> s; // 深度优先搜索的栈 <物品序号，方案所对应二进制数，背包剩余容量>
    int num_items = weights.size();
    double optimal_value = 0;
    int k = 0;
    int bestBinNum = 0;
    int binNum = 0;
    tuple<int, int, double, double> root = make_tuple(1, 0, knapsack_size, 0);
    s.push(root);
    while (!s.empty()) {
        double current_value = 0;
        tie(k, binNum, knapsack_size, current_value) = s.top();
        s.pop();
        if(current_value>optimal_value){// 记录最优解
            optimal_value = current_value;
            bestBinNum = binNum;
        }
        if (k <= num_items) {
            if (knapsack_size >= weights[k - 1]) {
                s.push(make_tuple(k + 1, binNum + (1 << (k - 1)), knapsack_size - weights[k - 1],
                                  current_value + values[k - 1])); // 选取第k种物品
            }
            s.push(make_tuple(k + 1, binNum, knapsack_size,current_value)); // 不选第k种物品
        }
    }
    pick.clear();
    for(int i=0;i<num_items;i++){ // 布尔变量指示是否选取
        pick.push_back(false);
    }
    planByBinNum(pick,bestBinNum);
    return optimal_value;
}

#endif //KNAPSACKPROBLEM_BACKTRACKING_H

