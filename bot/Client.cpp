//#include <baseapi.h> // tesseract
//#include <allheaders.h> // leptonica 
//#include <opencv.hpp> // opencv 
//#include <iostream>
//#include <Windows.h>
//using namespace cv;
//using namespace std;
//using namespace tesseract;
//bool FindPage(Mat img, Mat sample,double rightVal) {
//    Mat result;
//    // ��������� ������� � ������������
//    cv::matchTemplate(img, sample, result, cv::TM_SQDIFF_NORMED);
//
//    // ���������� ���������� ����������
//    double minVal = 0;
//    cv::Point minLoc;
//    cv::minMaxLoc(result, &minVal, nullptr, &minLoc, nullptr);
//
//    // �������� ���������� ����������
//    if (minVal < rightVal) {
//        return true;
//    }
//    return false;
//}
//Rect FindObj(Mat img, Mat mask) {
//    // ����������� ����������� � ������� ������
//    Mat grayImage;
//    cvtColor(mask, grayImage, COLOR_BGR2GRAY);
//    // ���������� �����������
//    Mat binaryImage;
//    threshold(grayImage, binaryImage, 127, 255, THRESH_BINARY_INV);
//    // ������� �������
//    vector<vector<Point>> contours;
//    findContours(binaryImage, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
//    // ������� ��������������, ����������� ������
//    Rect boundingRect1 = boundingRect(contours[0]);
//    return boundingRect1;
//}
//HWND FindEmu() {
//    HWND hwnd = FindWindowA("Qt5154QWindowIcon", NULL);
//    HWND child = FindWindowExA(hwnd, NULL, NULL, "HD-Player");
//    return child;
//}