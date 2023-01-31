
#include <iostream>

#include "PSO.h"
#include "FitnessFunction.h"

#include <time.h>				// time()
#include <windows.h>



int main()
{
    // 粒子群优化器参数：2为变量维度，true表示有搜索上下限
    PSOPara psopara(DIM, true);
    psopara.particle_num_ = 20;		// 粒子个数
    psopara.max_iter_num_ = 300;	// 最大迭代次数
    psopara.dt_[0] = 1.0;			// 第一维度上的时间步长
    psopara.dt_[1] = 1.0;			// 第二维度上的时间步长
    psopara.wstart_[0] = 0.9;		// 第一维度上的起始权重系数
    psopara.wstart_[1] = 0.9;		// 第二维度上的起始权重系数
    psopara.wend_[0] = 0.4;			// 第一维度上的终止权重系数
    psopara.wend_[1] = 0.4;			// 第二维度上的终止权重系数
    //psopara.C1_[0] = 1.49445;		// 第一维度上的加速度因子
    //psopara.C1_[1] = 1.49445;
    //psopara.C2_[0] = 1.49445;		// 第二维度上的加速度因子
    //psopara.C2_[1] = 1.49445;
    psopara.C1_[0] = 2;		// 第一维度上的加速度因子
    psopara.C1_[1] = 2;
    psopara.C2_[0] = 2;		// 第二维度上的加速度因子
    psopara.C2_[1] = 2;

    // 如果有搜索上下限，则设置上下限
    psopara.lower_bound_[0] = -10.0;	// 第一维度搜索下限
    psopara.lower_bound_[1] = -10.0;	// 第二维度搜索下限
    psopara.upper_bound_[0] = 10.0;	// 第一维度搜索上限
    psopara.upper_bound_[1] = 10.0;	// 第二维度搜索上限

    psopara.isInt_[0] = 0; // 设置第一个参数为连续值 0为连续
    psopara.isInt_[1] = 1; // 设置第二个参数为离散值 1为离散


    lastParAndRes lastData;


    PSOOptimizer psooptimizer(&psopara, FitnessFunction);

    std::srand((unsigned int)time(0));
    psooptimizer.InitialAllParticles();
    double fitness = psooptimizer.all_best_fitness_;
    double* result = new double[psooptimizer.max_iter_num_];
    std::cout.setf(std::ios_base::fixed, std::ios_base::floatfield);
    for (int i = 0; i < psooptimizer.max_iter_num_; i++)
    {
       

        psooptimizer.UpdateAllParticles(lastData);
        result[i] = psooptimizer.all_best_fitness_;

        /*par lastPar;
        lastPar.par1 = psooptimizer.all_best_position_[0];
        lastPar.par2 = psooptimizer.all_best_position_[1];
        lastData.my_map[lastPar] = result[i];*/

        std::cout << "第" << i << "次迭代结果：";

        //SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
        std::cout << "x = " << psooptimizer.all_best_position_[0] << ", " << "y = " << psooptimizer.all_best_position_[1];
        //SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

        std::cout << ", fitness = " << result[i] << std::endl;
        
    }
    std::cout << "一共调用"<<count;
    system("pause");
}