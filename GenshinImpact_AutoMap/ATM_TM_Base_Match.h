#pragma once
#include <opencv2/opencv.hpp>
// ƥ�� ����
template<class FunOut>
class ATM_TM_Base_Match
{
	//��ͼΪƥ�����Ŀ������ͼ��
	cv::Mat _leftMat;
	//��ͼΪ��ƥ����󣬰���Ŀ��ͼ���ͼ��
	cv::Mat _rightMat;

public:
	void setLeftMat(cv::Mat leftMat)
	{
		_leftMat = leftMat;
	}
	void setRightMat(cv::Mat rightMat)
	{
		_rightMat = rightMat;
	}

	//ƥ��
	virtual FunOut Match()=0;
	//virtual void* Match()=0;
};
