#pragma once
#include <QtWidgets/QMainWindow>
#include <opencv2/opencv.hpp>
#include <Windows.h>
#include <vector>
#include "ATM_Resource.h"
#include "ATM_MouseEvent.h"
#include "ATM_GiState.h"
#include "ATM_ThreadMatch.h"
#include "ATM_ObjectLists.h"
#include "ATM_SendSocket.h"
#include "ATM_ActivationKYJG.h"

enum ThisWinState
{
	Normal,
	Minimize,
	NoTop,
	Top,
	TopShow,
	Wait,
};

class AutomaticTrackingMap
{
	//������Դ
	ATM_Resource RES;
	//ԭ�񴰿���Ϣ
	ATM_GiState GIS;
	//���߳�ƥ��
	ATM_ThreadMatch TMS;
	//������Ʒ���
	ATM_ObjectLists OLS;
	//Socketͨ��
	ATM_SendSocket SST;
	//��ӫ�ƹݼ���
	ATM_ActivationKYJG AKY;

	cv::Mat MainMat;
	cv::Mat MainMatTmp;

	int thisStateMode = 0;
	int thisStateModeNext = 0;
	bool isFristChangeThisState = true;

public:
	AutomaticTrackingMap();
	~AutomaticTrackingMap();
public:

	//���λ��
	ATM_MouseEvent MET;

	//�Զ����������
	HWND thisHandle;
	//�Ƿ������Զ�׷��
	bool isAutoMode = false;

	//��������С
	Size autoMapSize = Size(250, 200);
	//������ͼ��С
	Size mapSize = Size(RES.GIMAP.cols, RES.GIMAP.rows);
	//������ͼ�������ģ����ԭ��
	Point mapWorldCenter = Point(1416, 3306);

	//�������������Դ��ͼλ��
	Point zerosMinMap = Point(1466, 3272);
	//���������ԭ�񴰿�λ��
	Point offGiMinMap = Point(250, 100);
	//
	Rect minMapRect;

	//ԭ���Ƿ��������б�־

	string SystemUserName;
	string SystemUserLocalLow;

	//Qt
	QImage MainImg;

	void Init(HWND mapWindowsHandle);
	void Exit();

	void FrontEndUpdata();
	void BackEndUpdata();

	void Mat2QImage();

	void CustomProcess(int i);

public:
	Mat getViewMap();

	void getGiState();
	void setThisState_Normal();
	void setThisState_Minimize();
	void setThisState_Top();
	void setThisState_TopShow();

	void getThisOffset();

	void getGiHandle();
	void getThisHandle();
	void getThisHandle(HWND _thisHandle);

	void setWindowsPos();
	void setWindowsPos(HWND _thisHandle);

	void setMoveMapDownPos(int x,int y);
	void setMoveMapUpPos(int x, int y);
	void setMoveMapMovePos(int x, int y);

	void setOffsetDownPos(int x, int y);
	void setOffsetUpPos(int x, int y);
	void setOffsetMovePos(int x, int y);

	void setAutoMode();
	bool getAutoMode();

	void setObjIsShow(int klass);
	void setObjFlagIsShow();
	void setAddFlagOnPos();
	void setKongYingJiuGuanState();
private:
	int getThisState();
	void getKYJGState();
	void setThisState();
	void setThreadMatchMat();

	void drawObjectLists();

private:
	bool isContains(Rect &r, Point &p);
	void addWeightedAlpha(Mat &backgroundImage, Mat& Image,Mat &maskImage);
};

typedef AutomaticTrackingMap ATmap;

