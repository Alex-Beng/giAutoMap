#include "GenshinImpact_AutoMap.h"

GenshinImpact_AutoMap::GenshinImpact_AutoMap(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	ui.UIObjFlagButton->setVisible(false);
	ui.UIObjList0Button->setVisible(false);
	ui.UIObjList1Button->setVisible(false);
	ui.UIObjList2Button->setVisible(false);
	ui.UIObjList999Button->setVisible(false);
	connect(ui.UIObjFlagButton, SIGNAL(clicked()), this, SLOT(setUIObjListToMapData()));
	connect(ui.UIObjList0Button, SIGNAL(clicked()), this, SLOT(setUIObjListToMapData()));
	connect(ui.UIObjList1Button, SIGNAL(clicked()), this, SLOT(setUIObjListToMapData()));
	connect(ui.UIObjList2Button, SIGNAL(clicked()), this, SLOT(setUIObjListToMapData()));
	connect(ui.UIObjList999Button, SIGNAL(clicked()), this, SLOT(setUIObjListToMapData()));
	


	//����ˢ�¶�ʱ��
	mapMessageLoopTimer = new QTimer(this);
	mapMessageLoopTimer->start(Fps);//1000/30=33.3,1000/24=42
	//mapMessageLoopTimer->setSingleShot(true);
	connect(mapMessageLoopTimer, SIGNAL(timeout()), this, SLOT(runMap()));
	//����UIObjList���ʱ��
	uiObjListSleepTimer = new QTimer(this);
	//uiObjListSleepTimer->stop();
	uiObjListSleepTimer->setSingleShot(true);
	connect(uiObjListSleepTimer, SIGNAL(timeout()), this, SLOT(setUIObjListHide()));

	//���ȫ�ֿ�ݼ�
	hotKeyAutoMode = new QtClassMyHotKeyObject("Alt+T", this);
	connect(hotKeyAutoMode, SIGNAL(Activated()), this, SLOT(setAutoMode()));
	hotKeyAddFlag = new QtClassMyHotKeyObject("Alt+F", this);
	connect(hotKeyAddFlag, SIGNAL(Activated()), this, SLOT(setAddFlag()));
	hotKeyActivationKongYingJiuGuan = new QtClassMyHotKeyObject("Alt+M", this);
	connect(hotKeyActivationKongYingJiuGuan, SIGNAL(Activated()), this, SLOT(setActivationKongYingJiuGuan()));


	connect(ui.UIButton, SIGNAL(clicked()), this, SLOT(setUIObjListShow()));
	connect(ui.ExitButton, SIGNAL(mouseDoubleClickExitExe()), this, SLOT(close()));
	connect(this, &GenshinImpact_AutoMap::mapUpdataFrontEnd, this, &GenshinImpact_AutoMap::updataFrontEnd);
	connect(this, &GenshinImpact_AutoMap::mapUpdataBackEnd, this, &GenshinImpact_AutoMap::updataBackEnd);

	//�������ָ��
	myCursor = new QCursor(QPixmap(":/CurMain/resource/GenshinImpactCur.cur"), 2, 2);
	this->setCursor(*myCursor);

	//���ð�͸���ޱ߿򴰿�
	//setWindowFlags(Qt::CustomizeWindowHint);
	//this->setWindowOpacity(0.9);
	this->setWindowFlags(Qt::FramelessWindowHint);
	this->setAttribute(Qt::WA_TranslucentBackground, true);
	ui.MainView->setAttribute(Qt::WA_TranslucentBackground);

	mapInit();
}

GenshinImpact_AutoMap::~GenshinImpact_AutoMap()
{
}

void GenshinImpact_AutoMap::mapInit()
{
	map.Init((HWND)this->winId());
}

void GenshinImpact_AutoMap::mouseMoveEvent(QMouseEvent * event)
{
	if (map.MET.bLCD)
	{
		//qDebug() << "mouse move " << event->x() << "," << event->y();
		map.setMoveMapMovePos(event->x(), event->y());
		update();
	}
	if (map.MET.bMCD)
	{
		qDebug() << "mouse move " << event->globalX() << "," << event->globalY();
		map.setOffsetMovePos(event->globalX(), event->globalY());
		map.setWindowsPos();
	}
	//if(map.MET)
}

void GenshinImpact_AutoMap::mousePressEvent(QMouseEvent * event)
{
	if (event->button() == Qt::LeftButton /*&& (event->buttons() & Qt::LeftButton)*/)
	{
		// �������
		map.MET.bLCD = true;
		map.setMoveMapDownPos(event->x(), event->y());
		//qDebug() << "mouse move setMouseLeftDownPos" << event->x() << "," << event->y();
	}
	if (event->button() == Qt::MidButton)
	{
		qDebug() << "MidButton" << event->globalPos().x() << "," << event->globalX();
		map.MET.bMCD = true;
		map.setOffsetDownPos(event->globalPos().x(), event->globalPos().y());
		map.CustomProcess(0);
	}
}

void GenshinImpact_AutoMap::mouseReleaseEvent(QMouseEvent * event)
{
	if (event->button() == Qt::LeftButton /*&& (event->buttons() & Qt::LeftButton)*/)
	{
		// �������
		map.MET.bLCD = false;
		//map.setMouseLeftUpPos(event->x(), event->y());
		//qDebug() << "mouse move res" << event->x() << "," << event->y();
	}
	if (event->button() == Qt::MidButton)
	{
		//qDebug() << "MidButton" << event->x() << "," << event->y();
		map.MET.bMCD = false;
		//map.setOffsetUpPos(event->globalX(), event->globalY());

	}
}

void GenshinImpact_AutoMap::mouseDoubleClickEvent(QMouseEvent * event)
{
	//static int i = 0;
	if (event->button() == Qt::LeftButton)
	{
		emit this->setAutoMode();

		qDebug() << "mouse move double" << event->x() << "," << event->y();
		//map.CustomProcess(0);
		//i++;
	}
}

void GenshinImpact_AutoMap::wheelEvent(QWheelEvent * event)
{
	//map.setScaleMapDelta(event->x(), event->y(), event->delta());
	if (event->delta() > 0)
	{
		if (map.MET.scale > 0.5)
		{
			map.MET.scale /= 1.2;
			//MET.zerosMinMap.x += dx * 0.2;//1.2-1
			//MET.zerosMinMap.y += dy * 0.2;//1.2-1
		}
	}
	else
	{
		if (map.MET.scale < 6)
		{
			map.MET.scale *= 1.2;
			//MET.zerosMinMap.x += dx * 0.2;//1.2-1
			//MET.zerosMinMap.y += dy * 0.2;//1.2-1
		}
	}
	update();
}

void GenshinImpact_AutoMap::paintEvent(QPaintEvent * event)
{
	//���û���Ϊ��ͼ
	QPainter painter(this);
	painter.drawImage(0, 0, map.MainImg);
}

void GenshinImpact_AutoMap::runMap()
{
	static bool isUpdataEnd = true;
	//�����Ƿ��ѽ���
	if (isUpdataEnd)
	{
		isUpdataEnd = false;
		emit this->mapUpdataFrontEnd();
		emit this->mapUpdataBackEnd();
		isUpdataEnd = true;
		//������һ֡
		mapMessageLoopTimer->start(Fps);
	}
	else
	{
		//������һ֡
		mapMessageLoopTimer->start(Fps);
	}


}

void GenshinImpact_AutoMap::updataFrontEnd()
{
	//static int count = 0;
	//qDebug() << "Updata Front-End " << count++ << " ";
	
	//���»���ͼ��
	map.FrontEndUpdata();
	//���Ƶ�����
	update();
}

void GenshinImpact_AutoMap::updataBackEnd()
{
	//static int count = 0;
	//qDebug() << "Updata Back-End " << count++ << " ";
	map.BackEndUpdata();
}

void GenshinImpact_AutoMap::setAutoMode()
{
	map.setAutoMode();
	if (map.isAutoMode)
	{
		ui.UIButton->setIcon(QIcon(":/IconUI/resource/UI0.ico"));
		//ui.UIButton->
	}
	else
	{
		ui.UIButton->setIcon(QIcon(":/IconUI/resource/UI.ico"));
	}
}

void GenshinImpact_AutoMap::setAddFlag()
{
	//map.zerosMinMap;
	map.setAddFlagOnPos();
}

void GenshinImpact_AutoMap::setActivationKongYingJiuGuan()
{
	map.setKongYingJiuGuanState();
}

void GenshinImpact_AutoMap::setUIObjListShow()
{
	qDebug() << "setUIObjListShow";
	ui.UIButton->setIcon(QIcon(":/IconUI/resource/UI1.ico"));

	ui.UIObjFlagButton->setVisible(true);
	ui.UIObjList0Button->setVisible(true);
	ui.UIObjList1Button->setVisible(true);
	ui.UIObjList2Button->setVisible(true);
	ui.UIObjList999Button->setVisible(true);

	uiObjListSleepTimer->start(2000);


}

void GenshinImpact_AutoMap::setUIObjListHide()
{
	qDebug() << "setUIObjListHide";
	ui.UIObjFlagButton->setVisible(false);
	ui.UIObjList0Button->setVisible(false);
	ui.UIObjList1Button->setVisible(false);
	ui.UIObjList2Button->setVisible(false);
	ui.UIObjList999Button->setVisible(false);


	if (map.isAutoMode)
	{
		ui.UIButton->setIcon(QIcon(":/IconUI/resource/UI0.ico"));
	}
	else
	{
		ui.UIButton->setIcon(QIcon(":/IconUI/resource/UI.ico"));
	}
}

void GenshinImpact_AutoMap::setUIObjListToMapData()
{
	QPushButton *btn = qobject_cast<QPushButton*>(sender());
	if (btn == ui.UIObjFlagButton) {
		qDebug() << "setUIObjListToMapData data 0 FST";
		map.setObjFlagIsShow();
	}
	if (btn == ui.UIObjList0Button) {
		qDebug() << "setUIObjListToMapData data 0 FST";
		map.setObjIsShow(0);
	}
	if (btn == ui.UIObjList1Button) {
		qDebug() << "setUIObjListToMapData data 1 YST";
		map.setObjIsShow(1);
	}
	if (btn == ui.UIObjList2Button) {
		qDebug() << "setUIObjListToMapData data 2 FHYS";
		map.setObjIsShow(2);
	}
	if (btn == ui.UIObjList999Button) {
		qDebug() << "setUIObjListToMapData data 999 LLD";
		map.setObjIsShow(3);
	}
}


