# ----------------------------------------------------
# This file is generated by the Qt Visual Studio Tools.
# ------------------------------------------------------
QT += widgets network
TEMPLATE = app
TARGET = TianLi_Map
DESTDIR = ../x64/Release
CONFIG += release
INCLUDEPATH += C:/projects/opencv/include/ \
	-C:/projects/opencv/include/opencv2/ \
LIBS += -L"." \
	-"C:/projects/opencv/x64/vc15/staticlib/*.lib" \
	-L"C:/projects/opencv/x64/vc15/staticlib/*.lib" \
	-l"C:/projects/opencv/x64/vc15/staticlib/*.lib" \
    -lopencv_world450 \
    -lade \
    -lIlmImf \
    -lippicvmt \
    -lippiw \
    -littnotify \
    -llibjpeg-turbo \
    -llibopenjp2 \
    -llibpng \
    -llibprotobuf \
    -llibtiff \
    -llibwebp \
    -lopencv_img_hash450 \
    -lquirc \
    -lzlib \
    -l$(Qt_LIBS_) \
	-lkernel32.lib \
	-luser32.lib \
	-lgdi32.lib \
	-lwinspool.lib \
	-lcomdlg32.lib \
	-ladvapi32.lib \
	-lshell32.lib \
	-lole32.lib \
	-loleaut32.lib \
	-luuid.lib \
	-lodbc32.lib \
	-lodbccp32.lib \
DEPENDPATH += .
MOC_DIR += ./release/moc
OBJECTS_DIR += ./release/obj
UI_DIR += ./release/ui
RCC_DIR += ./release/rcc
win32:RC_FILE = GenshinImpact_AutoMap.rc
HEADERS += ./ATM_ActivationKYJG.h \
    ./ATM_GiState.h \
    ./ATM_GI_ScreenResolution.h \
    ./ATM_Matrix.h \
    ./ATM_Modules.h \
    ./ATM_MouseEvent.h \
    ./ATM_ObjectLists.h \
    ./ATM_Resource.h \
    ./ATM_SaveLoadFile.h \
    ./ATM_SendSocket.h \
    ./ATM_ThreadMatch.h \
    ./AutomaticTrackingMap.h \
    ./QtClassMyHotKayNativeEventFilter.h \
    ./resource.h \
    ./GenshinImpact_AutoMap.h \
    ./QtClassMyExitButton.h \
    ./QtClassMyHotKeyObject.h \
    ./QtWidgetsClassMySelectGenshinImpactHandle.h
SOURCES += ./ATM_ActivationKYJG.cpp \
    ./ATM_GI_ScreenResolution.cpp \
    ./ATM_Matrix.cpp \
    ./ATM_Modules.cpp \
    ./ATM_ObjectLists.cpp \
    ./ATM_SaveLoadFile.cpp \
    ./ATM_SendSocket.cpp \
    ./ATM_ThreadMatch.cpp \
    ./QtClassMyExitButton.cpp \
    ./QtClassMyHotKayNativeEventFilter.cpp \
    ./QtClassMyHotKeyObject.cpp \
    ./QtWidgetsClassMySelectGenshinImpactHandle.cpp \
    ./ATM_GiState.cpp \
    ./ATM_MouseEvent.cpp \
    ./ATM_Resource.cpp \
    ./AutomaticTrackingMap.cpp \
    ./GenshinImpact_AutoMap.cpp \
    ./main.cpp
FORMS += ./GenshinImpact_AutoMap.ui \
    ./QtWidgetsClassMySelectGenshinImpactHandle.ui
RESOURCES += GenshinImpact_AutoMap_Icon.qrc \
    GenshinImpact_AutoMap_Items.qrc \
    GenshinImpact_AutoMap_UI.qrc \
    GenshinImpact_AutoMap.qrc
