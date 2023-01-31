
#include <iostream>

#include "PSO.h"
#include "FitnessFunction.h"

#include <time.h>				// time()
#include <windows.h>



int main()
{
    // ����Ⱥ�Ż���������2Ϊ����ά�ȣ�true��ʾ������������
    PSOPara psopara(DIM, true);
    psopara.particle_num_ = 20;		// ���Ӹ���
    psopara.max_iter_num_ = 300;	// ����������
    psopara.dt_[0] = 1.0;			// ��һά���ϵ�ʱ�䲽��
    psopara.dt_[1] = 1.0;			// �ڶ�ά���ϵ�ʱ�䲽��
    psopara.wstart_[0] = 0.9;		// ��һά���ϵ���ʼȨ��ϵ��
    psopara.wstart_[1] = 0.9;		// �ڶ�ά���ϵ���ʼȨ��ϵ��
    psopara.wend_[0] = 0.4;			// ��һά���ϵ���ֹȨ��ϵ��
    psopara.wend_[1] = 0.4;			// �ڶ�ά���ϵ���ֹȨ��ϵ��
    //psopara.C1_[0] = 1.49445;		// ��һά���ϵļ��ٶ�����
    //psopara.C1_[1] = 1.49445;
    //psopara.C2_[0] = 1.49445;		// �ڶ�ά���ϵļ��ٶ�����
    //psopara.C2_[1] = 1.49445;
    psopara.C1_[0] = 2;		// ��һά���ϵļ��ٶ�����
    psopara.C1_[1] = 2;
    psopara.C2_[0] = 2;		// �ڶ�ά���ϵļ��ٶ�����
    psopara.C2_[1] = 2;

    // ��������������ޣ�������������
    psopara.lower_bound_[0] = -10.0;	// ��һά����������
    psopara.lower_bound_[1] = -10.0;	// �ڶ�ά����������
    psopara.upper_bound_[0] = 10.0;	// ��һά����������
    psopara.upper_bound_[1] = 10.0;	// �ڶ�ά����������

    psopara.isInt_[0] = 0; // ���õ�һ������Ϊ����ֵ 0Ϊ����
    psopara.isInt_[1] = 1; // ���õڶ�������Ϊ��ɢֵ 1Ϊ��ɢ


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

        std::cout << "��" << i << "�ε��������";

        //SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
        std::cout << "x = " << psooptimizer.all_best_position_[0] << ", " << "y = " << psooptimizer.all_best_position_[1];
        //SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

        std::cout << ", fitness = " << result[i] << std::endl;
        
    }
    std::cout << "һ������"<<count;
    system("pause");
}