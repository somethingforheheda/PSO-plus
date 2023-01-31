#pragma once
//
// Created by qijixing on 2022/11/17.
//

#ifndef ALGORITHM_PSO_H
#define ALGORITHM_PSO_H


#pragma once
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <map>
#include <iomanip>
#include <iosfwd>

#include <sstream>
#define DIM 2

// 适应度是越大越好还是越小越好
//#define MINIMIZE_FITNESS
#define MAXIMIZE_FITNESS

struct par {
    double par1;
    double par2;
    bool operator<(const par& a) const {
        /*if (par1 != a.par1) {
            return this->par1 > a.par1;
        }
        else if (par1 == a.par1) {
            return this->par2 > a.par2;
        }*/
        return std::tie(this->par1, this->par2) < std::tie(a.par1, a.par2);
        

    }
   
};

struct lastParAndRes {
    std::map<par, double> my_map;
};

struct PSOPara
{
    int dim_;							// 参数维度（position和velocity的维度）
    int particle_num_;					// 粒子个数
    int max_iter_num_;					// 最大迭代次数

    double* dt_ = nullptr;							// 时间步长
    double* wstart_ = nullptr;						// 初始权重
    double* wend_ = nullptr;						// 终止权重
    double* C1_ = nullptr;							// 加速度因子
    double* C2_ = nullptr;							// 加速度因子

    double* upper_bound_ = nullptr;					// position搜索范围上限
    double* lower_bound_ = nullptr;					// position搜索范围下限
    double* range_interval_ = nullptr;				// position搜索区间长度

    int results_dim_ = 0;								// results的维度

    int* isInt_ = nullptr;                          //每个维度是否是整数 是则设为1否则设为0 

    PSOPara() {}

    PSOPara(int dim, bool hasBound = false)
    {
        dim_ = dim;

        dt_ = new double[dim_];
        wstart_ = new double[dim_];
        wend_ = new double[dim_];
        C1_ = new double[dim_];
        C2_ = new double[dim_];
        if (hasBound)
        {
            upper_bound_ = new double[dim_];
            lower_bound_ = new double[dim_];
            range_interval_ = new double[dim_];
        }
        isInt_= new int[dim_];
    }

    // 析构函数：释放堆内存
    ~PSOPara()
    {
        if (upper_bound_) { delete[]upper_bound_; }
        if (lower_bound_) { delete[]lower_bound_; }
        if (range_interval_) { delete[]range_interval_; }
        if (dt_) { delete[]dt_; }
        if (wstart_) { delete[]wstart_; }
        if (wend_) { delete[]wend_; }
        if (C1_) { delete[]C1_; }
        if (C2_) { delete[]C2_; }
        if (isInt_) { delete[]isInt_; }
    }
};

struct Particle
{
    int dim_;							// 参数维度（position和velocity的维度）
    double fitness_;
    double* position_ = nullptr;
    double* velocity_ = nullptr;

    double* best_position_ = nullptr;
    double best_fitness_;
    double* results_ = nullptr;			// 一些需要保存出的结果
    int results_dim_ = 0;				// results_的维度

    Particle() {}

    ~Particle()
    {
        if (position_) { delete[]position_; }
        if (velocity_) { delete[]velocity_; }
        if (best_position_) { delete[]best_position_; }
        if (results_) { delete[]results_; }
    }

    Particle(int dim, double* position, double* velocity, double* best_position, double best_fitness);
};

typedef double(*ComputeFitness)(Particle& particle, lastParAndRes& lastData);

class PSOOptimizer
{
public:
    int particle_num_;					// 粒子个数
    int max_iter_num_;					// 最大迭代次数
    int curr_iter_;						// 当前迭代次数

    int dim_;							// 参数维度（position和velocity的维度）

    Particle* particles_ = nullptr;		// 所有粒子

    double* upper_bound_ = nullptr;					// position搜索范围上限
    double* lower_bound_ = nullptr;					// position搜索范围下限
    double* range_interval_ = nullptr;				// position搜索区间长度

    double* dt_ = nullptr;							// 时间步长
    double* wstart_ = nullptr;						// 初始权重
    double* wend_ = nullptr;						// 终止权重
    double* w_ = nullptr;							// 当前迭代权重
    double* C1_ = nullptr;							// 加速度因子
    double* C2_ = nullptr;							// 加速度因子

    double all_best_fitness_;						// 全局最优粒子的适应度值
    double* all_best_position_ = nullptr;			// 全局最优粒子的poistion
    double* results_ = nullptr;						// 一些需要保存出的结果
    int results_dim_ = 0;							// results的维度

    ComputeFitness fitness_fun_ = nullptr;			// 适应度函数

    int* isInt_ = nullptr;

public:
    // 默认构造函数
    PSOOptimizer() {}

    // 构造函数
    PSOOptimizer(PSOPara* pso_para, ComputeFitness fitness_fun);

    // 析构函数
    ~PSOOptimizer();

    // 初始化所有粒子参数
    void InitialAllParticles();

    // 初始化第i个粒子参数
    void InitialParticle(int i);

    // 获取双精度随机数（默认精度为0.0001）
    double GetDoubleRand(int N = 9999);

    // 计算该粒子的适应度值
    double GetFitness(Particle& particle, lastParAndRes& lastData);

    // 更新所有粒子参数
    void UpdateAllParticles(lastParAndRes& lastData);

    // 更新第i个粒子
    void UpdateParticle(int i, lastParAndRes& lastData);

    // 获取当前迭代的权重
    void GetInertialWeight();
};


#endif //ALGORITHM_PSO_H
