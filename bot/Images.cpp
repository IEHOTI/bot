//#include <baseapi.h> // tesseract
//#include <allheaders.h> // leptonica 
//#include <opencv.hpp> // opencv 
//#include <iostream>
//#include <Windows.h>
//using namespace cv;
//using namespace std;
//using namespace tesseract;
//Mat CutImg(Mat img, Rect boundingRect1) {
//    Rect regionOfInterest(boundingRect1.x, boundingRect1.y, boundingRect1.width, boundingRect1.height);
//    Mat croppedImage = img(regionOfInterest);
//    return croppedImage;
//}
//bool SaveImg(Mat img, string path) {
//    if(imwrite(path.c_str(), img)) return true;
//    return false;
//}
//bool LoadImg(Mat& img, string path) {
//    img = imread(path.c_str());
//    return true;
//}
//string ScanDig(Mat img) {
//    cvtColor(img, img, COLOR_BGR2GRAY); // обработка в серый
//    TessBaseAPI tess;
//    tess.Init(NULL, "hc_dig");
//    tess.SetImage(img.data, img.cols, img.rows, 1, img.cols);
//    char* Text = tess.GetUTF8Text();
//    for (int i = 0, n = strlen(Text); i < n; i++) {
//        if (Text[i] == ' ') {
//            for (int j = i; j < n; j++) Text[j] = Text[j + 1];
//        }
//    }
//    tess.End();
//    string str(Text);
//    return str;
//}
//string ScanLetEn(Mat img) {
//    cvtColor(img, img, COLOR_BGR2GRAY);
//    TessBaseAPI tess;
//    tess.Init(NULL, "eng");
//    tess.SetImage(img.data, img.cols, img.rows, 1, img.cols);
//    char* Text = tess.GetUTF8Text();
//    tess.End();
//    string str(Text);
//    return str;
//}
//string ScanLetRu(Mat img) {
//    cvtColor(img, img, COLOR_BGR2GRAY);
//    TessBaseAPI tess;
//    tess.Init(NULL, "rus");
//    tess.SetImage(img.data, img.cols, img.rows, 1, img.cols);
//    char* Text = tess.GetUTF8Text();
//    tess.End();
//    string str(Text);
//    return str;
//}
//Mat Screenshot(HWND hwnd, int weight, int height) {
//    //SetForegroundWindow(child);
//    //MoveWindow(child, 0, 0, 1280, 720, true);
//    //////////////////////////////////// 
//    // Получаем текущие размеры окна-родителя
//   // RECT parentRect;
//    //GetClientRect(hwnd, &parentRect);
//
//    // Расширяем дочернее окно до размеров, игнорируя рамки окна-родителя
//    //SetWindowPos(child, NULL, 0, 0, parentRect.right, parentRect.bottom, SWP_NOZORDER | SWP_NOMOVE | SWP_NOACTIVATE);
//    //SetWindowPos(child, HWND_TOPMOST, 0, 0, 1280, 720, SWP_NOZORDER | SWP_NOACTIVATE);
//   ///////////////////////// //Sleep(5000);
//    int xWeight = weight; // 1280
//    int xHeight = height; // 720
//    HDC hdcWindow = GetDC(hwnd);
//    Mat res(height, weight, CV_8UC4);
//    RECT rc;
//    GetClientRect(hwnd, &rc);
//    HDC hdcMem = CreateCompatibleDC(hdcWindow);
//    HBITMAP bitmap = CreateCompatibleBitmap(hdcWindow, rc.right - rc.left, rc.bottom - rc.top);
//    HGDIOBJ OBJ = SelectObject(hdcMem, bitmap);
//    SelectObject(hdcMem, bitmap);
//    BitBlt(hdcMem, 0, 0, rc.right - rc.left, rc.bottom - rc.top, hdcWindow, 0, 0, SRCCOPY);
//    SelectObject(hdcMem, OBJ);
//    HDC hdcRar = GetDC(NULL);
//    SelectObject(hdcRar, bitmap);
//    StretchBlt(hdcRar, 0, 0, xWeight, xHeight, hdcMem, 0, 0, xWeight, xHeight, SRCCOPY);
//    BITMAPINFOHEADER bi = { sizeof(BITMAPINFOHEADER), xWeight, xHeight, 1, 32 };
//    GetDIBits(hdcMem, bitmap, 0, xHeight, res.data, (BITMAPINFO*)&bi, DIB_RGB_COLORS);
//    DeleteObject(bitmap);
//    DeleteDC(hdcMem);
//    DeleteDC(hdcRar);
//    ReleaseDC(hwnd, hdcWindow);
//    //ShowWindow(hwnd, SW_MINIMIZE);
//    return res;
//}