//
// Created by lf on 2019/5/13.
//
#include <vector>
#include <map>
#include <tuple>
#include <cmath>

using namespace std;

#ifndef KNAPSACKPROBLEM_DYNAMICPROGRAMMING_H
#define KNAPSACKPROBLEM_DYNAMICPROGRAMMING_H

///* @brief 由已经求解的子问题map得到最佳方案
// * @param knapsack_size 背包容量
// * @param weights 物品重量
// * @param map<tuple<int, double>, tuple<bool, double>> &subproblems 备忘录
// * @param vector<bool> &pick
// */
void bestPlan(double knapsack_size,
              vector<double> weights,
              map<tuple<int, double>, tuple<bool, double>> &subproblems,
              vector<bool> &pick) {
    int num_items = weights.size();
    pick.clear();
    for (int i = 0; i < num_items; i++) { // 布尔变量指示是否选取
        pick.push_back(false);
    }
    tuple<int, double> key = make_tuple(num_items, knapsack_size); // 问题的索引
    map<tuple<int, double>, tuple<bool, double>>::iterator iter; // 从(k,knapsack_size)到(pick,value)的索引
    for (int k = num_items; k > 0; k--) {
        iter = subproblems.find(key);
        bool k_pick =  get<0>(iter->second);//是否选取
        knapsack_size -= weights[k-1] * k_pick;
        pick[k-1]=k_pick;
        key = make_tuple(k - 1, knapsack_size);
    }
}

///* @brief 查找背包问题的子问题对应的最优值
// * @param int k 物品数量，向背包中放前k个物品
// * @param knapsack_size 背包容量
// * @parammap <tuple<int, double>, double> subproblems 子问题的map，键为<物品数量，背包容量>,值为最优价值
// * @retval double 子问题对应的最优值
// */
double find(int k,double knapsack_size,map<tuple<int, double>, tuple<bool,double>> subproblems) {
    if(k<=0||knapsack_size<=0){
        return 0;
    }
    tuple<int, double> key = make_tuple(k, knapsack_size); // 子问题的索引
    map<tuple<int, double>, tuple<bool,double>>::iterator iter;
    iter = subproblems.find(key);
    double value = get<1>(iter->second);
    return value;
}


///* @brief 动态规划算法
// * @param knapsack_size 背包容量
// * @param weights 物品重量
// * @param values 物品价值
// * @retval vector<bool> pick 布尔指示最优方案中是否选取对应位置物品
// *////* @brief 动态规划算法
// * @param knapsack_size 背包容量
// * @param weights 物品重量
// * @param values 物品价值
// * @retval vector<bool> pick 布尔指示最优方案中是否选取对应位置物品
// */
double dynamicProgramming(double knapsack_size, vector<double> weights, vector<double> values) {
    map<tuple<int, double>, tuple<bool,double>> subproblems;
    int num_items = values.size();
    for (int k = 1; k <= num_items; k++) {
        for (int current_size = 0; current_size <= knapsack_size; current_size++) {
            double ifpick = values[k-1] + find(k-1,current_size-weights[k-1],subproblems);
            double ifnotpick = find(k-1,current_size,subproblems);
            bool k_pick;
            double total_value;
            if(ifpick>ifnotpick){
                total_value = ifpick;
                k_pick = true;
            }else{
                total_value = ifnotpick;
                k_pick = false;
            }
            subproblems.insert(pair<tuple<int, double>,tuple<bool,double>>(make_tuple(k,current_size),make_tuple(k_pick,total_value)));
        }
    }
    return find(num_items,knapsack_size,subproblems);
}

#endif //KNAPSACKPROBLEM_DYNAMICPROGRAMMING_H
