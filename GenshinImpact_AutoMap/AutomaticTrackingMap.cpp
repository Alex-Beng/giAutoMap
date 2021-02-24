#include "AutomaticTrackingMap.h"

AutomaticTrackingMap::AutomaticTrackingMap()
{
}

AutomaticTrackingMap::~AutomaticTrackingMap()
{
	Exit();
}

void AutomaticTrackingMap::Init(HWND mapWindowsHandle)
{
	/*
	����״̬��ʼ��
	*/
	MET.zerosMinMap = zerosMinMap;
	MET.offGiMinMap = offGiMinMap;
	SST.setPort(6666);

	getGiHandle();
	getThisHandle(mapWindowsHandle);


	/*
	������ݸ���
	*/
	BackEndUpdata();


	
	/**/
}

void AutomaticTrackingMap::Exit()
{
}

//ǰ����ʾ
void AutomaticTrackingMap::FrontEndUpdata()
{
	/*
	���ò���
	*/

	setThisState();
	setThreadMatchMat();

	/*
	��ʾ����
	*/

	//��ȡ��ʾ�����ͼ
	MainMat = getViewMap();
	//�����Ʒͼ��
	drawObjectLists();

	//��ӵ�ǰλ��ͼ��

	/*
	��ʾ�������
	*/

	//ͼƬ�����Qt��ʾ
	Mat2QImage();
}

//���״̬����
void AutomaticTrackingMap::BackEndUpdata()
{
	/*
	���ݴ�����
	*/

	if (isAutoMode)
	{
		//���̼߳�����
		TMS.CheckThread();
		TMS.GetMatchResults();
		//���̳߳�ʼ��
		TMS.cThreadSurfMapInit(RES.GIMAP);
		TMS.cThreadSurfMapMatch();
		TMS.cThreadTemplatePaimonMatch(RES.GIPAIMON[GIS.resIdPaimon]);
		TMS.cThreadOrbAvatarInit(RES.GIAVATAR);
		TMS.cThreadOrbAvatarMatch();
		TMS.cThreadTemplateUIDInit(RES.GINUMUID);
		TMS.cThreadTemplateUIDMatch();

		if (TMS.tIsEndSurfMapInit)
		{
			zerosMinMap = TMS.pos;
			MET.zerosMinMap = zerosMinMap;
			GIS.isPaimonVisible = TMS.isPaimonVisial;

			if (TMS.isPaimonVisial&&TMS.isContinuity)
			{
				SST.AutoMapUdpSocketSend(zerosMinMap.x, zerosMinMap.y, TMS.rotationAngle,TMS.uid);
				std::cout << TMS.uid << endl;;
			}
		}
	}

	/*
	��ȡ����
	*/

	//��ȡԭ�񴰿�״̬
	getGiState();

	//��ȡ�������ԭ��λ��
	getThisOffset();
	getThisState();

	/*
	״̬ת�Ʋ���
	*/


	//�жϵ�ǰ������״̬
	thisStateMode = getThisState();


}

void AutomaticTrackingMap::Mat2QImage()
{
	std::vector<Mat> mv0;
	std::vector<Mat> mv1;

	//ͨ������
	split(MainMat, mv0);
	split(RES.MAINMASK, mv1);
	mv0.push_back(mv1[0]);
	merge(mv0, MainMat);
	MainImg = QImage((uchar*)(MainMat.data), MainMat.cols, MainMat.rows, MainMat.cols*(MainMat.channels()), QImage::Format_ARGB32);
}

void AutomaticTrackingMap::CustomProcess(int i)
{
	GIS.getGiFrame();
	string name("OutputPNG_id_");
	name.append(to_string(i));
	name.append("_GiFrame.png");
	if (GIS.isRunning)
	{
		//imwrite(name, GIS.giFrame);
		//imshow("testOut",GIS.giFrameMap);
		ATM_TM_ORBAvatar orb;
		Mat tes,te2;
		int len1=300, lne2 = 96;
		cvtColor(RES.GIAVATAR, tes, CV_RGB2GRAY);
		resize(tes, tes, Size(len1, len1),0,0, INTER_CUBIC);//INTER_AREAz

		orb.setAvatarTemplate(tes);

		cvtColor(GIS.giFrameMap(Rect(82, 82, 48, 48)), te2, CV_RGB2GRAY);
		resize(te2, te2, Size(len1, len1),0,0, INTER_CUBIC);
		orb.setAvatarMat(te2);

		orb.Init();
		orb.ORBMatch();
		TMS.rotationAngle = orb.getRotationAngle();
	}
}

Mat AutomaticTrackingMap::getViewMap()
{
	static Mat minMap;

	Point minMapPoint = Point(0, 0);

	Size reMapSize = autoMapSize;
	reMapSize.width = (int)(reMapSize.width * MET.scale);
	reMapSize.height = (int)(reMapSize.height * MET.scale);

	Size R = reMapSize / 2;

	Point LT = zerosMinMap - Point(R);
	Point RB = zerosMinMap + Point(R);

	minMapPoint = LT;

	if (LT.x < 0)
	{
		minMapPoint.x = 0;
	}
	if (LT.y < 0)
	{
		minMapPoint.y = 0;
	}
	if (RB.x > mapSize.width)
	{
		minMapPoint.x = mapSize.width - reMapSize.width;
	}
	if (RB.y > mapSize.height)
	{
		minMapPoint.y = mapSize.height - reMapSize.height;
	}
	minMapRect = Rect(minMapPoint, reMapSize);

	resize(RES.GIMAP(minMapRect), minMap, autoMapSize);
	return minMap;
}

void AutomaticTrackingMap::getGiState()
{
	GIS.getGiState();
	if (GIS.giRectMode > 0)
	{
		GIS.getGiFrame();
	}
}

void AutomaticTrackingMap::setThisState_Normal()
{
	//���ô���λ��
	//setWindowsPos();
	SetWindowPos(thisHandle, HWND_TOP, GIS.giRect.left + offGiMinMap.x, GIS.giRect.top + offGiMinMap.y, 0, 0, SWP_NOSIZE);
}

void AutomaticTrackingMap::setThisState_Minimize()
{
	//��С����ʾ����
	ShowWindow(thisHandle, SW_MINIMIZE);
	//����ԭ�񴰿�Ϊǰ̨
	SetForegroundWindow(GIS.giHandle);/* ��ԭ�񴰿ڵĲ��� */

}

void AutomaticTrackingMap::setThisState_Top()
{
	//���ô���λ��
	setWindowsPos();
	//��ԭ��ʾ����
	//ShowWindow(thisHandle, SW_SHOW);
	ShowWindow(thisHandle, SW_RESTORE);
}

void AutomaticTrackingMap::setThisState_TopShow()
{
	//���ô���λ��
	setWindowsPos();
	//��ԭ��ʾ����
	//ShowWindow(thisHandle, SW_SHOW);
	ShowWindow(thisHandle, SW_RESTORE);
	//����ԭ�񴰿�Ϊǰ̨
	SetForegroundWindow(GIS.giHandle);/* ��ԭ�񴰿ڵĲ��� */
}

void AutomaticTrackingMap::getThisOffset()
{
	static Point offGiMinMapTmp;
	if (GIS.giRectMode > 0)
	{
		offGiMinMapTmp = GIS.getOffset();
		if (offGiMinMap != offGiMinMapTmp)
		{
			offGiMinMap = offGiMinMapTmp;
		}
	}
}

void AutomaticTrackingMap::getGiHandle()
{
	GIS.getHandle();
}

void AutomaticTrackingMap::getThisHandle()
{
	thisHandle = FindWindowA(NULL, "GenshinImpact_AutoMap");
}

void AutomaticTrackingMap::getThisHandle(HWND _thisHandle)
{
	thisHandle = _thisHandle;
}

void AutomaticTrackingMap::setWindowsPos()
{
	SetWindowPos(thisHandle, HWND_TOPMOST, GIS.giRect.left + offGiMinMap.x, GIS.giRect.top + offGiMinMap.y, 0, 0, SWP_NOSIZE);
}

void AutomaticTrackingMap::setWindowsPos(HWND _thisHandle)
{
	SetWindowPos(_thisHandle, HWND_TOPMOST, GIS.giRect.left + offGiMinMap.x, GIS.giRect.top + offGiMinMap.y, 0, 0, SWP_NOSIZE);
}

void AutomaticTrackingMap::setMoveMapDownPos(int x, int y)
{
	MET.setMouseLeftDownPos(x, y);
}

void AutomaticTrackingMap::setMoveMapUpPos(int x, int y)
{
	MET.setMouseLeftUpPos(x, y);
	MET.normalizationZerosMinMap(Rect(0, 0, mapSize.width, mapSize.width));
	zerosMinMap = MET.zerosMinMap;
}

void AutomaticTrackingMap::setMoveMapMovePos(int x, int y)
{
	MET.setMouseLeftMovePos(x, y);
	MET.normalizationZerosMinMap(Rect(0,0,mapSize.width,mapSize.width));
	zerosMinMap = MET.zerosMinMap;
	
}

void AutomaticTrackingMap::setOffsetDownPos(int x, int y)
{
	//MET.offGiMinMap = offGiMinMap;
	MET.setMouseMidDownPos(x, y);

}

void AutomaticTrackingMap::setOffsetUpPos(int x, int y)
{
	MET.setMouseMidUpPos(x, y);
	offGiMinMap = MET.offGiMinMap;
}

void AutomaticTrackingMap::setOffsetMovePos(int x, int y)
{
	MET.setMouseMidMovePos(x, y);
	offGiMinMap = MET.offGiMinMap;
}

void AutomaticTrackingMap::setAutoMode()
{
	isAutoMode = !isAutoMode;
}

bool AutomaticTrackingMap::getAutoMode()
{
	return isAutoMode;
}

void AutomaticTrackingMap::setObjIsShow(int klass)
{
	OLS.setShow(klass);
}

void AutomaticTrackingMap::setObjFlagIsShow()
{
	OLS.setShowFlag();
}

void AutomaticTrackingMap::setAddFlagOnPos()
{
	OLS.appendFlag(zerosMinMap.x, zerosMinMap.y);
}

int AutomaticTrackingMap::getThisState()
{
	//����״̬���Ա����Ƿ���������״̬���ã���ֹ��������ԭ�񴰿ڣ���꽹���޷�ת�ơ�
	thisStateModeNext = thisStateMode;
	//����ԭ��״̬�ж���һ֡ʱ������״̬
	if (GIS.isRunning)
	{
		if (isAutoMode)
		{
			if (TMS.tIsEndSurfMapInit == true)
			{
				if (GIS.isPaimonVisible)
				{
					thisStateModeNext = ThisWinState::TopShow;
				}
				else
				{
					thisStateModeNext = ThisWinState::Minimize;
				}
			}
			else
			{
				thisStateModeNext = ThisWinState::TopShow;
			}

		}
		else
		{
			thisStateModeNext = ThisWinState::Top;
		}
	}
	else
	{
		thisStateModeNext = ThisWinState::Normal;
	}
	//���״̬����һ֡��ͬ��������״̬����������
	if (isFristChangeThisState||thisStateModeNext != thisStateMode)
	{
		thisStateMode = thisStateModeNext;
		isFristChangeThisState = true;
	}
	else
	{
		thisStateModeNext = ThisWinState::Wait;
	}

	return thisStateMode;
}

void AutomaticTrackingMap::setThisState()
{
	//if (thisStateModeNext == ThisWinState::Wait)return;
	if (isFristChangeThisState != true)
	{
		return;
	}
	else
	{
		isFristChangeThisState = false;
	}
	switch (thisStateMode)
	{
		case ThisWinState::Normal:
		{
			setThisState_Normal();
			break;
		}
		case ThisWinState::Minimize:
		{
			setThisState_Minimize();
			break;
		}
		case ThisWinState::Top:
		{
			//���ñ����ö���ǰ����״̬
			setThisState_Top();
			break;
		}
		case ThisWinState::TopShow:
		{
			//���ñ����ö���ǰ����״̬
			setThisState_TopShow();
			break;
		}
		default:
		{
			setThisState_Normal();
			break;
		}
	}
}

void AutomaticTrackingMap::setThreadMatchMat()
{
	if (GIS.isRunning&&GIS.giRectMode > 0)
	{
		Mat matRGB2GRAY;
		cvtColor(GIS.giFrameMap, matRGB2GRAY, CV_RGB2GRAY);
		TMS.getObjMinMap(matRGB2GRAY);
		cvtColor(GIS.giFramePaimon, matRGB2GRAY, CV_RGB2GRAY);
		TMS.getObjPaimon(matRGB2GRAY);
		//cvtColor(GIS.giFrameUID, matRGB2GRAY, CV_RGB2GRAY);
		TMS.getObjUID(GIS.giFrameUID);
	}
	else
	{
		TMS.isExistObjMinMap = false;
		TMS.isExistObjPaimon = false;
		TMS.isExistObjUID = false;
	}
}

void AutomaticTrackingMap::drawObjectLists()
{
	int x = 0, y = 0;
	Point p;
	Mat ObjIconROIMat;
	const int dx = 16, dy = 16;//ͼ�궥�㵽ͼ�����ĵ�ƫ��
	for (int objKlass = 0; objKlass < OLS.objectListsNumber(); objKlass++)
	{
		if (OLS.isShow(objKlass))
		{
			for (int objOrder = 0; objOrder < OLS.objectsNumber(objKlass); objOrder++)
			{
				p= OLS.p(objKlass, objOrder);
				if (isContains(minMapRect, p))
				{
					x = (int)((p.x - minMapRect.x) / MET.scale) - dx;
					y = (int)((p.y - minMapRect.y) / MET.scale) - dy;
					//��x��y��ΧҪ���㹻�Ŀռ������ͼ��
					if (x > 0 && y > 0 && x + RES.GIOBJICON[objKlass].cols < autoMapSize.width&&y + RES.GIOBJICON[objKlass].rows < autoMapSize.height)
					{
						ObjIconROIMat = MainMat(Rect(x, y, RES.GIOBJICON[objKlass].cols, RES.GIOBJICON[objKlass].rows));
						//RES.GIOBJICON[objKlass].copyTo(ObjIconROIMat, RES.GIOBJICONMASK[objKlass]);
						addWeightedAlpha(ObjIconROIMat, RES.GIOBJICON[objKlass], RES.GIOBJICONMASK[objKlass]);
					}
				}
			}
		}
	}
	if (OLS.isShowFlag())
	{
		for (int objOrder = 0; objOrder < OLS.flagNumber(); objOrder++)
		{
			p = OLS.fp(objOrder);
			if (isContains(minMapRect, p))
			{
				x = (int)((p.x - minMapRect.x) / MET.scale) - dx;
				y = (int)((p.y - minMapRect.y) / MET.scale) - dy;
				//��x��y��ΧҪ���㹻�Ŀռ������ͼ��
				if (x > 0 && y > 0 && x + RES.GIOBJFLAGICON[0].cols < autoMapSize.width&&y + RES.GIOBJFLAGICON[0].rows < autoMapSize.height)
				{
					ObjIconROIMat = MainMat(Rect(x, y, RES.GIOBJFLAGICON[0].cols, RES.GIOBJFLAGICON[0].rows));
					//RES.GIOBJICON[objKlass].copyTo(ObjIconROIMat, RES.GIOBJICONMASK[objKlass]);
					addWeightedAlpha(ObjIconROIMat, RES.GIOBJFLAGICON[0], RES.GIOBJFLAGICONMASK[0]);
				}
			}
		}
	}

}

bool AutomaticTrackingMap::isContains(Rect & r, Point & p)
{
	if (p.x<r.x || p.x>(r.x + r.width) || p.y<r.y || p.y>(r.y + r.height))
	{
		return false;
	}
	else
	{
		return true;
	}
	return false;
}

void AutomaticTrackingMap::addWeightedAlpha(Mat & backgroundImage, Mat & Image, Mat &maskImage)
{
	std::vector<cv::Mat>scr_channels;
	std::vector<cv::Mat>dstt_channels;
	std::vector<cv::Mat>alpha_channels;
	split(Image, scr_channels);
	split(backgroundImage, dstt_channels);
	split(maskImage, alpha_channels);

	Mat Alpha = alpha_channels[0];

	for (int i = 0; i < 3; i++)
	{
		dstt_channels[i] = dstt_channels[i].mul(Alpha / 255.0);
		dstt_channels[i] += scr_channels[i].mul(1.0 - Alpha / 255.0);
	}
	merge(dstt_channels, backgroundImage);
}
