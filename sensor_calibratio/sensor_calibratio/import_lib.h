#pragma once
#include <stdio.h>
#include <string>
#include <iostream>
#define USE_OPENCV 1
#define USE_QT 0
using namespace std;
#if USE_OPENCV 
#include <opencv2/opencv.hpp>
using namespace cv;

//#pragma comment(lib,"image_feature_extractor.lib")
//#pragma comment(lib,"ceres.lib")

#ifdef _DEBUG
#pragma comment(lib,"opencv_calib3d2413d.lib")
#pragma comment(lib,"opencv_contrib2413d.lib")
#pragma comment(lib,"opencv_core2413d.lib")
#pragma comment(lib,"opencv_features2d2413d.lib")
#pragma comment(lib,"opencv_flann2413d.lib")
#pragma comment(lib,"opencv_highgui2413d.lib")
#pragma comment(lib,"opencv_imgproc2413d.lib")
#pragma comment(lib,"opencv_legacy2413d.lib")
#pragma comment(lib,"opencv_ml2413d.lib")
#pragma comment(lib,"opencv_objdetect2413d.lib")
#pragma comment(lib,"opencv_ts2413d.lib")
#pragma comment(lib,"opencv_video2413d.lib")
#pragma comment(lib,"opencv_nonfree2413d.lib")
//#pragma comment(lib,"opencv_viz2413d.lib")
#else 
#pragma comment(lib,"opencv_calib3d2413.lib")
//#pragma comment(lib,"opencv_contrib2413.lib")
#pragma comment(lib,"opencv_core2413.lib")
#pragma comment(lib,"opencv_features2d2413.lib")
#pragma comment(lib,"opencv_flann2413.lib")
#pragma comment(lib,"opencv_gpu2413.lib")
#pragma comment(lib,"opencv_highgui2413.lib")
#pragma comment(lib,"opencv_imgproc2413.lib")
#pragma comment(lib,"opencv_legacy2413.lib")
#pragma comment(lib,"opencv_ml2413.lib")
#pragma comment(lib,"opencv_objdetect2413.lib")
#pragma comment(lib,"opencv_ts2413.lib")
#pragma comment(lib,"opencv_video2413.lib")
#pragma comment(lib,"opencv_nonfree2413.lib")
//#pragma comment(lib,"opencv_viz2413.lib")
#endif

#if USE_QT 
#ifdef _DEBUG
#pragma comment(lib,"qtmaind.lib")
#pragma comment(lib,"Qt5Cored.lib")
#pragma comment(lib,"Qt5Guid.lib")
#pragma comment(lib,"Qt5PrintSupportd.lib")
#pragma comment(lib,"Qt5Widgetsd.lib")
#pragma comment(lib,"Qt5SerialPortd.lib")
#pragma comment(lib,"Qt5Networkd.lib")
#else
#pragma comment(lib,"qtmain.lib")
#pragma comment(lib,"Qt5Core.lib")
#pragma comment(lib,"Qt5Gui.lib")
#pragma comment(lib,"Qt5PrintSupport.lib")
#pragma comment(lib,"Qt5Widgets.lib")
#pragma comment(lib,"Qt5SerialPort.lib")
#pragma comment(lib,"Qt5Network.lib")
#endif
#endif

#endif