#pragma once
#include <opencv2/opencv.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <opencv2/xfeatures2d/nonfree.hpp>
#include <opencv2/video/tracking.hpp>
using namespace cv;

// SURFƥ�� ����
class ATM_TM_Base_SurfMatch
{
	//��ͼΪƥ�����Ŀ������ͼ��
	Mat _leftMat;
	//��ͼΪ��ƥ����󣬰���Ŀ��ͼ���ͼ��
	Mat _rightMat;

public:
	//void setLeftMat(Mat leftMat);
	//void setRightMat(Mat rightMat);

	////ƥ��
	//bool Match();
};

//class ATM_TM_Base_SurfMatch2 :private ATM_TM_Base_Match<bool>
//{
//
//public:
//	void setLeftMat(Mat leftMat);
//	void setRightMat(Mat rightMat);
//
//	bool Match();
//};