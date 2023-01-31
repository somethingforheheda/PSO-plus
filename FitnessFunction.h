//
// Created by qijixing on 2022/11/17.
//

#ifndef ALGORITHM_FITNESSFUNCTION_H
#define ALGORITHM_FITNESSFUNCTION_H

#pragma once
#include "PSO.h"
#include <math.h>
#include <Windows.h>
#define PI 3.1415926

double FitnessFunction(Particle& particle, lastParAndRes& lastData);

static int count = 0;

double setPrecision(double src, int bits) {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(bits) << src;
    ss >> src;
    return src;
}

double isInMap(const std::map<par, double>& my_map,const par& p) {
    /*if (my_map.size()==0)
    {
        return true;
    }*/

    for (const auto& it : my_map) {
        //这个条件主要是判断这次的参数是否与以前的参数一样，如果一样，直接取以前的参数的结果作为这次的结果，就不需要再次计算
        //在FitnessFunction运算时间较长时使用，可以大幅节省时间
        //if (std::abs(it.first.par1 - p.par1)<0.01&& std::abs(it.first.par2- p.par2) < 0.01)
        if (it.first.par1== p.par1&& it.first.par2== p.par2)
        {
            return it.second;
        }
    }
    return 0;
}

double FitnessFunction(Particle& particle, lastParAndRes& lastData)
{
    par thisPar;
    thisPar.par1 = particle.position_[0];
    thisPar.par2 = particle.position_[1];

    double res = isInMap(lastData.my_map, thisPar);
    if (res ==0)//如果是新的参数 则需要重新计算
    {
        //Sleep(100);
        double x = particle.position_[0];
        double y = particle.position_[1];
        double temp = sqrt(x * x + y * y);
        double fitness = sin(temp) / temp + exp(0.5 * cos(2 * PI * x) + 0.5 * cos(2 * PI * y)) - 2.71289;
        //将新参数加入
        lastData.my_map[thisPar] = fitness;
        count++;
        return fitness;
    }
    else//如果是已有的参数 直接返回对应的值
    {
        std::cout << "使用了已有的值" << std::endl;
        return res;
    }

    

    
}

#endif //ALGORITHM_FITNESSFUNCTION_H
