/*
 * Algorithm homework3: Knapsack Problem
 * Dynamic Programming
 * Author: qlf
 * Date: 2019-5-9
 */
#include <iostream>
#include <vector>
#include <fstream>
#include <cassert>
#include "solver.h"

using namespace std;

///* @brief 背包问题的初始化
// * @param knapsack_size 背包容量
// * @param weights 物品重量
// * @param values 物品价值
// */
void problem_initialize_keyboard(double &knapsack_size, vector<double> weights, vector<double> values) {
    cin >> knapsack_size;
    double weight;
    while (cin >> weight) {
        weights.push_back(weight);
    }
    double value;
    while (cin >> value) {
        values.push_back(value);
    }
}

///* @brief 背包问题的初始化
// * @param knapsack_size 背包容量
// * @param weights 物品重量
// * @param values 物品价值
// */
void problem_initialize_fin(double &knapsack_size, vector<double> &weights, vector<double> &values) {
    ifstream fin("D:/clionProjects/Knapsackproblem/data2");   //将文件流对象与文件连接起来
    assert(fin.is_open());  //若失败,则输出错误消息,并终止程序运行
    fin >> knapsack_size;
    cout<<"knapsack_size="<<knapsack_size<<endl;
    double weight;
    cout<<"Weights:";
    while (fin >> weight) {
        cout<<weight<<" ";
        weights.push_back(weight);
        if( fin.get()=='\n'){
            break;
        }
    }
    cout<<endl;
    double value;
    cout<<"Values:";
    while (fin >> value) {
        cout<<value<<" ";
        values.push_back(value);
        if( fin.get()=='\n'){
            break;
        }
    }
    cout<<endl;
    fin.close(); //关闭文件输入流
}

int main() {
    double knapsack_size;
    vector<double> weights;
    vector<double> values;
    vector<bool> pick;
   // problem_initialize_keyboard(knapsack_size, weights, values); // 从键盘输入
    problem_initialize_fin(knapsack_size, weights, values); // 从文件读取
    int num_items = weights.size();
    cout<<"----------------------------  Brute-Force  ----------------------------"<<endl;
    cout<<"optimal total-value:"<<bruteForce(knapsack_size, weights, values,pick)<<endl;
    print(pick);
    cout<<"---------------------------- Memorized-Top-Down-Approach ----------------------------"<<endl;
    map<tuple<int,double>,tuple<bool,double>> subproblems;
    cout<<"optimal total-value:"<<memorizedTopDown(knapsack_size,weights,values,subproblems,num_items)<<endl;
    bestPlan(knapsack_size, weights, subproblems, pick);
    print(pick);
    cout<<"---------------------------- Dynamic-Programming ----------------------------"<<endl;
    cout<<"optimal total-value:"<<dynamicProgramming(knapsack_size,weights,values)<<endl;
    bestPlan(knapsack_size, weights, subproblems, pick);
    print(pick);
    cout<<"---------------------------- Back-Tracking ----------------------------"<<endl;
    cout<<"optimal total-value:"<<back_tracking(knapsack_size,weights,values,pick)<<endl;
    print(pick);
    cout<<"---------------------------- Branch-And-Bound ----------------------------"<<endl;
    vector<int>indices;
    cout<<"optimal total-value:"<<branchAndBound(knapsack_size,weights,values,pick,indices)<<endl;
    recoverPlanOrder(pick,indices);
    print(pick);
    cout<<"---------------------------- Monte-Carlo ----------------------------"<<endl;
    cout<<"optimal total-value:"<<solveByMonteCarlo(knapsack_size,weights,values,1000,pick)<<endl;
    print(pick);
    return 0;
}