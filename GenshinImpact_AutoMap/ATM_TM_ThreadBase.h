#pragma once
#include <thread>
#include <Windows.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

template <class FunOut,class FunIn>
class ATM_TM_ThreadBase
{
	//ʵ���̵߳ĵ�������

	//�߳�ʵ��
	thread *tLoopWork = nullptr;

	//��������
	FunOut*(*ptr)(FunIn *funIn) = nullptr;

	//�����������
	FunOut *_funOut = nullptr;
	FunIn *_funIn = nullptr;

	//�Ƿ��˳��߳�
	bool isExitThread = false;
	//�Ƿ���ڹ�������
	bool isExistFunction = false;
	//�Ƿ����й���
	bool isRunWork = false;
	//�Ƿ��������
	bool isEndWork = false;

	//�߳�ִ��ʵ��
	void run()
	{
		//ѭ������ֱ���Ƿ��˳��߳�Ϊ�棬Ӧ��ֻ����Ҫ����ʱ�˳�
		while (isExitThread == false)
		{
			//�Ƿ����й���Ϊ�沢�ҹ���������Ϊ��
			if (isRunWork && (*ptr) != nullptr)
			{
				//�Ƿ��������Ϊ�٣�������������
				isEndWork = false;

				//Ӧ���ȼ���

				//ִ�к���
				_funOut = ptr(_funIn);

				//Ӧ���ͷ���

				//�Ƿ����й���Ϊ�٣�ÿ������ֻ����һ��ѭ��
				isRunWork = false;
				//�Ƿ��������Ϊ�棬�����ѽ���
				isEndWork = true;
			}
			else
			{
				//����1ms
				std::this_thread::sleep_for(std::chrono::milliseconds(1));
			}
		}
	};

public:
	//bool isInit = false;
	ATM_TM_ThreadBase()
	{
		//�����߳�ʵ�壬���������߳�ִ��ʵ��
		tLoopWork = new thread(&ATM_TM_ThreadBase::run, this);
	};
	~ATM_TM_ThreadBase()
	{
		//����߳�ʵ�岻Ϊ��
		if (tLoopWork != nullptr)
		{
			//Ӧ����ȡ��
			//�����Ƿ��˳��߳�Ϊ��
			isExitThread = true;

			//�����߳�ʵ��
			tLoopWork->join();
			//�����߳�ʵ��
			delete tLoopWork;
		}
	}

	ATM_TM_ThreadBase(FunOut(*funPtr)(FunIn &funIn))
	{
		//ֱ�����ù�������
		fptr = funPtr;
		//�����߳�ʵ�壬���������߳�ִ��ʵ��
		tLoopWork = new thread(&ATM_TM_ThreadBase::run, this);
	}

	//void setFunction(FunOut(*funPtr)(FunIn &funIn))
	//{
	//	//���ù�������
	//	if (isRunWork && (*ptr) != nullptr)
	//	{

	//	}
	//	fptr = funPtr;
	//}

	//virtual void workfun() {}
	void start()
	{
		isRunWork = true;
		isEndWork = false;
	}

	void start(FunIn & funIn)
	{
		//if (isExistFunction == false)
		//{
		//	throw"Not Found Work Function";
		//}
		////workInput = funIn;
		isRunWork = true;
		isEndWork = false;
	}

	void setFunIn(FunIn funIn)
	{
		_funIn = funIn;
	}

	FunOut getFunOut()
	{
		return _funOut;
	}

	bool isEnd()
	{
		return isEndWork;
	}
};
typedef ATM_TM_ThreadBase<bool, Mat> ATM_TM_toBool;
typedef ATM_TM_ThreadBase<int, Mat> ATM_TM_toInt;
typedef ATM_TM_ThreadBase<double, Mat> ATM_TM_toDouble;
typedef ATM_TM_ThreadBase<Point2d, Mat> ATM_TM_toPoint;
typedef ATM_TM_ThreadBase<vector<Point2d>, Mat> ATM_TM_toVecPoint;
