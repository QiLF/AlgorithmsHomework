//
// Created by lf on 2019/5/14.
//
#include <vector>
using namespace std;

#ifndef KNAPSACKPROBLEM_BIN2PLAN_H
#define KNAPSACKPROBLEM_BIN2PLAN_H

///* @brief 通过二进制数得到背包装配方案
// * @param vector<bool> pick 布尔指示对应位置物品是否选取
// * @param unsigned int binnum 二进制数从低到高，位为1指示选取对应物品，0指示不选取
// */
void planByBinNum(vector<bool> &pick, int binnum) {
    int num_items = pick.size();
    unsigned int tmp = 1;
    for (int j = 0; j < num_items; j++) {
        if (tmp & binnum) {
            pick[j] = true;
        } else {
            pick[j] = false;
        }
        tmp = tmp << 1;
    }
}

///* @brief 通过二进制数得到背包装配方案
// * @param vector<bool> pick 布尔指示对应位置物品是否选取
// * @param unsigned int binnum 二进制数从低到高，位为1指示选取对应物品，0指示不选取
// */
int BinNumByPlan(vector<bool> pick) {
    int num_items = pick.size();
    int tmp = 1;
    int binNum = 0;
    for (int j = 0; j < num_items; j++) {
        binNum+=(tmp<<j)*pick[j];
    }
    return binNum;
}


///* @brief 通过二进制数得到背包装配方案
// * @param vector<bool> pick 布尔指示对应位置物品是否选取
// * @param vector<int>indices 新的物品顺序映射到原物品顺序的索引
// */
void recoverPlanOrder(vector<bool> &pick,vector<int>indices) {
    int num_items = pick.size();
    vector<bool> tmp;
    tmp.assign(pick.begin(),pick.end()); // copy to local memory
    for (int j = 0; j < num_items; j++) {
        pick[indices[j]]=tmp[j];
    }
}
#endif //KNAPSACKPROBLEM_BIN2PLAN_H
