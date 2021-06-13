#pragma once
#include <windows.h>
#include <vector>
#include <QDesktopServices>
#include <QTextCodec>
#include <QSystemTrayIcon>
#include <QDesktopServices>
#include <QAction>
#include <QMenu>
#include <QProcess>
#include <QMouseEvent>
#include <QtWidgets/QMainWindow>
#include "ui_GenshinImpactNaturalLaw.h"
#include "QtWidgetsSetting.h"
#include "SettingData.h"

class GenshinImpactNaturalLaw : public QMainWindow
{
    Q_OBJECT

public:
    GenshinImpactNaturalLaw(QWidget *parent = Q_NULLPTR);
	~GenshinImpactNaturalLaw();

private:
    Ui::GenshinImpactNaturalLawClass ui;

private:
	SettingData setting;

private:
	QPoint m_Press;
	QPoint m_Move;
	bool leftBtnClk = false;
	QtWidgetsSetting *WidgetsSetting = nullptr;
	QLabel *MainMaskLabel = nullptr;
	QMenu *TrayMenu;//���̲˵�
	QSystemTrayIcon *Tray;//����ͼ����ӳ�Ա
	QAction *ShowMainAction;//����ͼ���Ҽ����ʱ����ѡ��
	QAction *ExitAction;//����ͼ���Ҽ����ʱ����ѡ��
private:
	std::vector<QPushButton*> LinkeButtonList;
	std::vector<QUrl> LinkeUrlList;
private:
	void uiConnectButton();
private:
	void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
	void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
	void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

private slots:
	void NewWidgetsSetting();
	void StartGame();
	void OpenLinkeUrl();
	
	void TrayMenuClickEvent(QSystemTrayIcon::ActivationReason reason);
	// Receive Setting From WidgetsSetting
	void ReceiveSettingFromWidgetsSetting(SettingData *setting);
	void ReceiveCloseSelfSignalFromWidgetsSetting();
// signals:
};
