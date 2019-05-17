cmake_minimum_required(VERSION 3.14)
project(Knapsackproblem)

set(CMAKE_CXX_STANDARD 11)

add_executable(Knapsackproblem main.cpp solver.h bruteForce.h topDown.h backTracking.h backTracking.h dynamicProgramming.h branchAndBound.h monteCarlo.h bin2plan.h)