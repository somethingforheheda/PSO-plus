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

// ��Ӧ����Խ��Խ�û���ԽСԽ��
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
    int dim_;							// ����ά�ȣ�position��velocity��ά�ȣ�
    int particle_num_;					// ���Ӹ���
    int max_iter_num_;					// ����������

    double* dt_ = nullptr;							// ʱ�䲽��
    double* wstart_ = nullptr;						// ��ʼȨ��
    double* wend_ = nullptr;						// ��ֹȨ��
    double* C1_ = nullptr;							// ���ٶ�����
    double* C2_ = nullptr;							// ���ٶ�����

    double* upper_bound_ = nullptr;					// position������Χ����
    double* lower_bound_ = nullptr;					// position������Χ����
    double* range_interval_ = nullptr;				// position�������䳤��

    int results_dim_ = 0;								// results��ά��

    int* isInt_ = nullptr;                          //ÿ��ά���Ƿ������� ������Ϊ1������Ϊ0 

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

    // �����������ͷŶ��ڴ�
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
    int dim_;							// ����ά�ȣ�position��velocity��ά�ȣ�
    double fitness_;
    double* position_ = nullptr;
    double* velocity_ = nullptr;

    double* best_position_ = nullptr;
    double best_fitness_;
    double* results_ = nullptr;			// һЩ��Ҫ������Ľ��
    int results_dim_ = 0;				// results_��ά��

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
    int particle_num_;					// ���Ӹ���
    int max_iter_num_;					// ����������
    int curr_iter_;						// ��ǰ��������

    int dim_;							// ����ά�ȣ�position��velocity��ά�ȣ�

    Particle* particles_ = nullptr;		// ��������

    double* upper_bound_ = nullptr;					// position������Χ����
    double* lower_bound_ = nullptr;					// position������Χ����
    double* range_interval_ = nullptr;				// position�������䳤��

    double* dt_ = nullptr;							// ʱ�䲽��
    double* wstart_ = nullptr;						// ��ʼȨ��
    double* wend_ = nullptr;						// ��ֹȨ��
    double* w_ = nullptr;							// ��ǰ����Ȩ��
    double* C1_ = nullptr;							// ���ٶ�����
    double* C2_ = nullptr;							// ���ٶ�����

    double all_best_fitness_;						// ȫ���������ӵ���Ӧ��ֵ
    double* all_best_position_ = nullptr;			// ȫ���������ӵ�poistion
    double* results_ = nullptr;						// һЩ��Ҫ������Ľ��
    int results_dim_ = 0;							// results��ά��

    ComputeFitness fitness_fun_ = nullptr;			// ��Ӧ�Ⱥ���

    int* isInt_ = nullptr;

public:
    // Ĭ�Ϲ��캯��
    PSOOptimizer() {}

    // ���캯��
    PSOOptimizer(PSOPara* pso_para, ComputeFitness fitness_fun);

    // ��������
    ~PSOOptimizer();

    // ��ʼ���������Ӳ���
    void InitialAllParticles();

    // ��ʼ����i�����Ӳ���
    void InitialParticle(int i);

    // ��ȡ˫�����������Ĭ�Ͼ���Ϊ0.0001��
    double GetDoubleRand(int N = 9999);

    // ��������ӵ���Ӧ��ֵ
    double GetFitness(Particle& particle, lastParAndRes& lastData);

    // �����������Ӳ���
    void UpdateAllParticles(lastParAndRes& lastData);

    // ���µ�i������
    void UpdateParticle(int i, lastParAndRes& lastData);

    // ��ȡ��ǰ������Ȩ��
    void GetInertialWeight();
};


#endif //ALGORITHM_PSO_H
