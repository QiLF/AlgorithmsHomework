//
// Created by lf on 2019/5/13.
//
#include <vector>
#include <map>
#include <tuple>

using namespace std;

#ifndef KNAPSACKPROBLEM_TOPDOWN_H
#define KNAPSACKPROBLEM_TOPDOWN_H

/////* @brief 由已经求解的子问题map得到最佳方案
//// * @param knapsack_size 背包容量
//// * @param weights 物品重量
//// * @param map<tuple<int, double>, tuple<bool, double>> &subproblems 备忘录
//// * @param vector<bool> &pick
//// */
//void Plan(double knapsack_size,
//              vector<double> weights,
//              map<tuple<int, double>, tuple<bool, double>> &subproblems,
//              vector<bool> &pick) {
//    int num_items = weights.size();
//    pick.clear();
//    for (int i = 0; i < num_items; i++) { // 布尔变量指示是否选取
//        pick.push_back(false);
//    }
//    tuple<int, double> key = make_tuple(num_items, knapsack_size); // 问题的索引
//    map<tuple<int, double>, tuple<bool, double>>::iterator iter; // 从(k,knapsack_size)到(pick,value)的索引
//    for (int k = num_items; k > 0; k--) {
//        iter = subproblems.find(key);
//        bool k_pick =  get<0>(iter->second);//是否选取
//        knapsack_size -= weights[k-1] * k_pick;
//        pick[k-1]=k_pick;
//        key = make_tuple(k - 1, knapsack_size);
//    }
//}


///* @brief 自顶向下的备忘录法
// * @param knapsack_size 背包容量
// * @param weights 物品重量
// * @param values 物品价值
// * @subproblems 备忘录
// * @k 当前决定是否选取的物品序号
// * @retval 价值
// */
double memorizedTopDown(double knapsack_size,
                        vector<double> weights,
                        vector<double> values,
                        map<tuple<int, double>, tuple<bool, double>> &subproblems,
                        int k) {
    if (k < 1) { // 递归结束条件
        return 0;
    }
    double total_value = 0; // 物品总价值
    bool k_pick; // 是否选取第k个物品
    tuple<int, double> key = make_tuple(k, knapsack_size); // 问题的索引
    map<tuple<int, double>, tuple<bool, double>>::iterator iter; // 从(k,knapsack_size)到(pick,value)的索引
    iter = subproblems.find(key);
    if (iter == subproblems.end()) { // 问题未求解过
        // 求解问题
        if (knapsack_size >= weights[k - 1]) { // 若剩余背包容量足以容纳第k个物品
            double ifpick =
                    memorizedTopDown(knapsack_size - weights[k - 1], weights, values, subproblems, k - 1) +
                    values[k - 1]; // 选取第k件物品
            double ifnotpick = memorizedTopDown(knapsack_size, weights, values, subproblems, k - 1); // 不选第k件物品
            if (ifpick > ifnotpick) { // 选取第k个物品收益大
                total_value = ifpick;
                k_pick = true;
            } else { // 不选取第k个物品收益大
                total_value = ifnotpick;
                k_pick = false;
            }
        } else { // 若剩余背包容量不足够容纳第k个物品
            total_value = memorizedTopDown(knapsack_size, weights, values, subproblems, k - 1);
            k_pick = false;
        }
        // 记录子问题做出的选择及价值
        subproblems.insert(pair<tuple<int, double>, tuple<bool, double>>(key, make_tuple(k_pick, total_value)));
    } else { // 备忘录中已经求解过此问题
        total_value = get<1>(iter->second);
    }
    return total_value;
}

#endif //KNAPSACKPROBLEM_TOPDOWN_H
