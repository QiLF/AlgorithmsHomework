//
// Created by lf on 2019/5/13.
//
#include <vector>
#include <random>
#include "bin2plan.h"
using namespace std;

#ifndef KNAPSACKPROBLEM_MONTECARLO_H
#define KNAPSACKPROBLEM_MONTECARLO_H

///* @brief 方案所对应最大的二进制数
// * @param vector<bool> pick 布尔指示对应位置物品是否选取
// * @param unsigned int binnum 二进制数从低到高，位为1指示选取对应物品，0指示不选取
// */
int maxBinNum(int num_items)
{
    int upBound = 0;
    int tmp = 1;
    for(int i=0;i<num_items;i++){
        upBound+=tmp;
        tmp = tmp<<1;
    }
    return upBound;
}


///* @brief 蒙特卡罗法
// * @param knapsack_size 背包容量
// * @param weights 物品重量
// * @param values 物品价值
// * @retval double 最优方案的价值
// */
double solveByMonteCarlo(double knapsack_size, vector<double> weights, vector<double> values, int sampleTimes,vector<bool>&pick) {
    int num_items = weights.size();
    pick.clear();
    for(int i=0;i<num_items;i++){ // 布尔变量指示是否选取
        pick.push_back(false);
    }
    default_random_engine random;
    int upBound = maxBinNum(num_items);
    double optimalVal = 0;
    int bestBinNum = 0;
    for(int i=0;i<sampleTimes;i++){
        int binNum = random()%(upBound+1);  // 生成随机数代表一种背包装填方案
        planByBinNum(pick,binNum);
        double totalWeight = 0;
        double totalValue = 0;
        for(int k = 0;k<num_items;k++){
            totalWeight+=weights[k]*pick[k]; // 计算方案物品总重量
            totalValue+=values[k]*pick[k]; // 计算方案总价值
        }
        if(totalWeight>knapsack_size){
            continue;
        }else {
            if(totalValue > optimalVal) {
                optimalVal = totalValue;
                bestBinNum = binNum;
            }
        }
    }
    planByBinNum(pick,bestBinNum);
    return optimalVal;
}
#endif //KNAPSACKPROBLEM_MONTECARLO_H
