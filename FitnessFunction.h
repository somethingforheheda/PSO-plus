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
        //���������Ҫ���ж���εĲ����Ƿ�����ǰ�Ĳ���һ�������һ����ֱ��ȡ��ǰ�Ĳ����Ľ����Ϊ��εĽ�����Ͳ���Ҫ�ٴμ���
        //��FitnessFunction����ʱ��ϳ�ʱʹ�ã����Դ����ʡʱ��
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
    if (res ==0)//������µĲ��� ����Ҫ���¼���
    {
        //Sleep(100);
        double x = particle.position_[0];
        double y = particle.position_[1];
        double temp = sqrt(x * x + y * y);
        double fitness = sin(temp) / temp + exp(0.5 * cos(2 * PI * x) + 0.5 * cos(2 * PI * y)) - 2.71289;
        //���²�������
        lastData.my_map[thisPar] = fitness;
        count++;
        return fitness;
    }
    else//��������еĲ��� ֱ�ӷ��ض�Ӧ��ֵ
    {
        std::cout << "ʹ�������е�ֵ" << std::endl;
        return res;
    }

    

    
}

#endif //ALGORITHM_FITNESSFUNCTION_H
