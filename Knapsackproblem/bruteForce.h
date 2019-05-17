//
// Created by lf on 2019/5/12.
//
#include <iostream>
#include <cmath>
#include <vector>
#include "bin2plan.h"
using namespace std;

#ifndef KNAPSACKPROBLEM_BRUTEFORCE_H
#define KNAPSACKPROBLEM_BRUTEFORCE_H



void print(vector<bool> pick) {
    cout << "optimal plan:";
    for (auto &&i : pick) {
        cout << i << " ";
    }
    cout << endl;
}

///* @brief 暴力穷举法
// * @param knapsack_size 背包容量
// * @param weights 物品重量
// * @param values 物品价值
// * @retval vector<bool> pick 布尔指示最优方案中是否选取对应位置物品
// */
double bruteForce(double knapsack_size, vector<double> weights, vector<double> values, vector<bool>&pick) {
    int num_items = weights.size(); // 物品数量
    int num_plans = pow(2, num_items); // n个物品有2^n种组合可能
    pick.clear();
    for(int i=0;i<num_items;i++){ // 布尔变量指示是否选取
        pick.push_back(false);
    }
    unsigned int optimal_binnum = 0; // 最优方案对应的二进制数
    double optimal_value = 0; // 最优方案获得的总价值
    for (int i = 0; i < num_plans; i++) {
        // 产生一个装包方案
        planByBinNum(pick, i);
        // 计算价值
        double total_value = 0;
        double total_weight = 0;
        for (int j = 0; j < num_items; j++) { // 得到方案使用的容量及方案产生的价值
            total_weight += pick[j] * weights[j];
            total_value += pick[j] * values[j];
        }
        if (total_weight > knapsack_size) {// 若方案超过背包容量，将方案价值置0
            total_value = 0;
        }
        if (optimal_value < total_value) {// 更新最优方案
            optimal_binnum = i;
            optimal_value = total_value;
        }
    }
    planByBinNum(pick, optimal_binnum);
    return optimal_value;
}

#endif //KNAPSACKPROBLEM_BRUTEFORCE_H
