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
//    // Сравнение шаблона с изображением
//    cv::matchTemplate(img, sample, result, cv::TM_SQDIFF_NORMED);
//
//    // Нахождение наилучшего совпадения
//    double minVal = 0;
//    cv::Point minLoc;
//    cv::minMaxLoc(result, &minVal, nullptr, &minLoc, nullptr);
//
//    // Проверка наилучшего совпадения
//    if (minVal < rightVal) {
//        return true;
//    }
//    return false;
//}
//Rect FindObj(Mat img, Mat mask) {
//    // Преобразуем изображение в оттенки серого
//    Mat grayImage;
//    cvtColor(mask, grayImage, COLOR_BGR2GRAY);
//    // Бинаризуем изображение
//    Mat binaryImage;
//    threshold(grayImage, binaryImage, 127, 255, THRESH_BINARY_INV);
//    // Находим контуры
//    vector<vector<Point>> contours;
//    findContours(binaryImage, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
//    // Находим прямоугольники, описывающие контур
//    Rect boundingRect1 = boundingRect(contours[0]);
//    return boundingRect1;
//}
//HWND FindEmu() {
//    HWND hwnd = FindWindowA("Qt5154QWindowIcon", NULL);
//    HWND child = FindWindowExA(hwnd, NULL, NULL, "HD-Player");
//    return child;
//}