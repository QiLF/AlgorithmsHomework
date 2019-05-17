//
// Created by lf on 2019/5/13.
//
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

#ifndef KNAPSACKPROBLEM_BRANCHANDBOUND_H
#define KNAPSACKPROBLEM_BRANCHANDBOUND_H

typedef struct Node {
    int k = 0;  // 待考虑物品序号
    double leftSize = 0;    // 背包剩余空间
    double currentValue = 0;    // 当前背包内物品价值
    double maxBound = 0;    // 背包价值上界
    int plan = 0;   // 装包方案，二进制数表示
    friend bool operator<(const Node &a, const Node &b) {//按maxBound从大到小排序
        return a.maxBound < b.maxBound;
    }
} Node;

///* @brief 将物品按照单位体积价值从大到小排序
// * @param vector<double> weights 物品重量
// * @param vector<double> values 物品价值
// * @param vector<double> &sorted_weights 单位体积价值从大到小排序后的物品重量
// * @param vector<double> &sorted_values 单位体积价值从大到小排序后的物品价值
// */
void sortByValuePerWeight(vector<double> weights,
                          vector<double> values,
                          vector<double> &sortedWeights,
                          vector<double> &sortedValues,
                          vector<int> &indices) {
    sortedValues.clear();
    sortedWeights.clear();
    indices.clear();

    int num_items = weights.size();
    vector<bool> sorted(num_items); // 布尔数组，指示物品是否已经被排序
    for (int i = 0; i < num_items; i++) {
        sorted[i] = false;
        indices.push_back(0);
    }
    for (int i = 0; i < num_items; i++) {
        int k = 0;
        double maxValuePerWeight = 0;
        for (int j = 0; j < num_items; j++) {
            if (sorted[j]) {
                continue;
            }
            double valuePerWeight = values[j] / weights[j];
            if (valuePerWeight > maxValuePerWeight) {
                k = j;
                maxValuePerWeight = valuePerWeight;
            }
        }
        {   // 得到剩余物品中单位价值最大的
            sorted[k] = true;
            sortedValues.push_back(values[k]);
            sortedWeights.push_back(weights[k]);
            indices[i] = k;
        }
    }
}


///* @brief 最大上界函数
// * @param int k 当前方案考虑物品种类
// * @param double left_size 剩余容量
// * @param double current_value 当前方案价值
// * @param vector<double> weights 物品重量
// * @param vector<double> values 物品价值
// * @retval double
// */
double maxBound(int k, double leftSize, double currentValue, vector<double> weights, vector<double> values) {
    int num_items = weights.size(); // 物品总数
    double maxBound = currentValue;
    while (k <= num_items && leftSize >= weights[k - 1]) {
        leftSize -= weights[k - 1];
        maxBound += values[k - 1];
        k++;
    }
    if (k <= num_items) {
        maxBound += values[k - 1] / weights[k - 1] * leftSize; // 装填剩余容量，这里实际上是用松弛问题: 分数背包 来求上界
    }
}


///* @brief 分支定界法
// * @param knapsack_size 背包容量
// * @param weights 物品重量
// * @param values 物品价值
// * @retval vector<bool> pick 布尔指示最优方案中是否选取对应位置物品
// */
double branchAndBound(double knapsack_size, vector<double> weights, vector<double> values, vector<bool> &pick,
                      vector<int>&indices) {
    vector<double> sortedWeights; //单位体积价值从大到小排序后的物品重量
    vector<double> sortedValues; //单位体积价值从大到小排序后的物品价值
    sortByValuePerWeight(weights, values, sortedWeights, sortedValues,indices);
    int num_items = weights.size();
    priority_queue<Node> nodes; // 关于问题结点的优先队列
    pick.clear();
    for (int i = 0; i < num_items; i++) { // 布尔变量指示是否选取
        pick.push_back(false);
    }
    int bestBinNum = 0;
    Node root;
    {// 根节点赋值
        root.k = 1;
        root.leftSize = knapsack_size;
        root.currentValue = 0;
        root.plan = 0;
        root.maxBound = maxBound(root.k, root.leftSize, root.currentValue, sortedWeights, sortedValues);
    }
    double lowerBound = 0; // 分支定界，对于最大界小于最优值下界的结点，不予扩展
    nodes.push(root);
    while (!nodes.empty()) {// 队列非空
        Node subProblem = nodes.top();
        nodes.pop();
        if (lowerBound <= subProblem.currentValue) { //更新最优值下界
            lowerBound = subProblem.currentValue;
            bestBinNum = subProblem.plan;
        }
        if (subProblem.maxBound < lowerBound || subProblem.k > num_items) { // 只扩展可能找到最优值的非叶节点
            continue;
        }
        Node ifnotpick;
        {//若不选第k种
            ifnotpick.plan = subProblem.plan;
            ifnotpick.k = subProblem.k + 1;
            ifnotpick.leftSize = subProblem.leftSize;
            ifnotpick.currentValue = subProblem.currentValue;
            ifnotpick.maxBound = maxBound(ifnotpick.k, ifnotpick.leftSize, ifnotpick.currentValue, sortedWeights,
                                          sortedValues);
        }
        nodes.push(ifnotpick);
        if (subProblem.leftSize >= sortedWeights[subProblem.k - 1]) {// 判断是否可行解
            Node ifpick;
            {//若选取第k种
                ifpick.plan = subProblem.plan + (1 << (subProblem.k - 1));
                ifpick.k = subProblem.k + 1;
                ifpick.leftSize = subProblem.leftSize - sortedWeights[subProblem.k - 1];
                ifpick.currentValue = subProblem.currentValue + sortedValues[subProblem.k - 1];
                ifpick.maxBound = maxBound(ifpick.k, ifpick.leftSize, ifpick.currentValue, sortedWeights, sortedValues);
            }
            nodes.push(ifpick);
        }
    }
    planByBinNum(pick, bestBinNum);
    return lowerBound;
}

#endif //KNAPSACKPROBLEM_BRANCHANDBOUND_H
