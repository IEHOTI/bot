//#include <baseapi.h> // tesseract
//#include <allheaders.h> // leptonica 
//#include <opencv.hpp> // opencv 
//#include <iostream>
//#include <Windows.h>
//using namespace cv;
//using namespace std;
//using namespace tesseract;
//void ClickShort(HWND hwnd, int x, int y, int sleep) {
//    PostMessage(hwnd, WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(x, y));
//    Sleep(sleep);
//    PostMessage(hwnd, WM_LBUTTONUP, 0, MAKELPARAM(x, y));
//    Sleep(1000);
//}
//void ClickReturn(HWND hwnd) {
//    PostMessage(hwnd, WM_KEYDOWN, VK_RETURN, 0);
//    Sleep(1000);
//    PostMessage(hwnd, WM_KEYUP, VK_RETURN, 0);
//    Sleep(1000);
//}
//bool WriteMsg(HWND hwnd, const char* text) {
//    MoveWindow(hwnd, 0, 0, 1280, 720, true);
//    if (OpenClipboard(NULL)) {
//        EmptyClipboard();
//        HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, strlen(text) + 1);
//        if (hMem != NULL) {
//            char* pMem = (char*)GlobalLock(hMem);
//            strcpy_s(pMem, strlen(text) + 1, text);
//            GlobalUnlock(hMem);
//
//            SetClipboardData(CF_TEXT, hMem);
//        }
//        CloseClipboard();
//    }
//    else {
//        std::cout << "Не удалось открыть буфер обмена." << std::endl;
//        return false;
//    }
//    int x[6] = { 582,21,591,591,104,710 };
//    int y[6] = { 269,330,667,667,600,332 };
//    if (hwnd) {
//        SendMessage(hwnd, WM_SETFOCUS, 0, 0);
//        for (int i = 1; i < 6; i++) {
//            if (i == 3) ClickShort(hwnd, x[i], y[i],5000);
//            else if (i == 4) ClickReturn(hwnd);
//            else ClickShort(hwnd, x[i], y[i],1000);
//        }
//    }
//    ShowWindow(hwnd, SW_MINIMIZE);
//    return true;
//}