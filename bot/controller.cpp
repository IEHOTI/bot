#include "controller.h"
controller::controller()
 : Ocr(xPath, (path)"C:\\bot\\ocr\\known\\test", (path)"C:\\bot\\ocr\\known\\train", (path)"C:\\bot\\ocr\\known\\digits") 
{
	point = { 0,0 };
	rect = { 0,0,0,0 };
    xrect = { 0,0,0,0 };
    xPath = "C:\\bot\\data\\pages"; // later -> xPath = current_path();
    Ocr::Initialize();
}
controller::~controller() {

}
bool controller::isWindow() {
	if (getmHandle() == (HWND)0) return false;
	return true;
}
bool controller::isValidSize() {
	rect = getmWin();
	point = getmSize();
	if ((rect.right - rect.left) != point.x || (rect.bottom - rect.top) != point.y) return false;
	return true;
}
bool controller::setValidSize() {
	HWND hwnd = FindWindowA("Qt5154QWindowIcon", NULL);
	HWND wnd = FindWindowExA(hwnd, NULL, NULL, "HD-Player");
	if(!MoveWindow(hwnd, 50, 0, 1280+34, 720+34, true)) return false;
	if(!MoveWindow(wnd, 1, 33, 1280, 720, true)) return false;
	return true;
}
// Client
bool controller::Compare(double rightVal) {
    Mat img1(img), sample1(sample);
    cvtColor(img1, img1, COLOR_BGR2GRAY);
    cvtColor(sample1, sample1, COLOR_BGR2GRAY);
    // Создание матрицы результата
    int res_col = sample1.cols - img1.cols + 1;
    int res_row = sample1.rows - img1.rows + 1;
    Mat result(res_row, res_col, CV_32FC1);
    // Сравнение шаблона с изображением
    matchTemplate(img1, sample1, result, TM_SQDIFF_NORMED);

    // Нахождение наилучшего совпадения
    double minVal = 0;
    Point minLoc;
    minMaxLoc(result, &minVal, nullptr, &minLoc, nullptr);
    Sleep(500);
    // Проверка наилучшего совпадения
    if (minVal < rightVal) {
        return true;
    }
    return false;
}
bool controller::Compare(Mat img, double rightVal) {
    Mat img1(img), sample1(sample);
    cvtColor(img1, img1, COLOR_BGR2GRAY);
    cvtColor(sample1, sample1, COLOR_BGR2GRAY);
    // Создание матрицы результата
    int res_col = sample1.cols - img1.cols + 1;
    int res_row = sample1.rows - img1.rows + 1;
    Mat result(res_row, res_col, CV_32FC1);
    // Сравнение шаблона с изображением
    matchTemplate(img1, sample1, result, TM_SQDIFF_NORMED);

    // Нахождение наилучшего совпадения
    double minVal = 0;
    Point minLoc;
    minMaxLoc(result, &minVal, nullptr, &minLoc, nullptr);
    Sleep(500);
    // Проверка наилучшего совпадения
    if (minVal < rightVal) {
        return true;
    }
    return false;
}
bool controller::CompareSample(path page, string sample, string mask, double rightVal) {
    Screenshot();

    Mat img1 = imread((page / mask).generic_string());
    Mat sample1(720, 1280, CV_8UC4);
    cvtColor(img1, img1, COLOR_BGR2GRAY);
    threshold(img1, sample1, 127, 255, THRESH_BINARY_INV);
    vector<vector<Point>> contours;
    findContours(sample1, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    xrect = boundingRect(contours[0]);

    img1 = img(xrect);
    sample1 = imread((page / sample).generic_string());
    /*
    imshow("1", img1);
    imshow("2", sample1);
    waitKey(0);
    */
    cvtColor(img1, img1, COLOR_BGR2GRAY);
    cvtColor(sample1, sample1, COLOR_BGR2GRAY);
    int res_col = sample1.cols - img1.cols + 1;
    int res_row = sample1.rows - img1.rows + 1;
    Mat result(res_row, res_col, CV_32FC1);
    matchTemplate(img1, sample1, result, TM_SQDIFF_NORMED);
    double minVal = 0;
    Point minLoc;
    minMaxLoc(result, &minVal, nullptr, &minLoc, nullptr);
    Sleep(500);
    if (minVal < rightVal) {
        return true;
    }
    return false;
}
bool controller::FindObj() {
    // Преобразуем изображение в оттенки серого
    Mat grayImage;
    cvtColor(mask, grayImage, COLOR_BGR2GRAY);
    // Бинаризуем изображение
    Mat binaryImage;
    threshold(grayImage, binaryImage, 127, 255, THRESH_BINARY_INV);
    // Находим контуры
    vector<vector<Point>> contours;
    findContours(binaryImage, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    // Находим прямоугольники, описывающие контур
    xrect = boundingRect(contours[0]);
    if (xrect.width == 0) return false;
    return true;
}
bool controller::FindObj(Mat mask) {
    // Преобразуем изображение в оттенки серого
    Mat grayImage;
    cvtColor(mask, grayImage, COLOR_BGR2GRAY);
    // Бинаризуем изображение
    Mat binaryImage;
    threshold(grayImage, binaryImage, 127, 255, THRESH_BINARY_INV);
    // Находим контуры
    vector<vector<Point>> contours;
    findContours(binaryImage, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    // Находим прямоугольники, описывающие контур
    xrect = boundingRect(contours[0]);
    if (xrect.width == 0) return false;
    return true;
}
//
//Img
Mat controller::CutImg() {
    Rect regionOfInterest(xrect.x, xrect.y, xrect.width, xrect.height);
    Mat croppedImage = img(regionOfInterest);
    return croppedImage; 
}

bool controller::CheckGreenCol() {
    bool green_found = false;
    for (int x = xrect.x; x < xrect.x + xrect.width; x++) {
        for (int y = xrect.y; y < xrect.y + xrect.height; y++) {
            Vec3b pixel_color = img.at<Vec3b>(y, x);
            if (pixel_color[1] == 255) {
                green_found = true;
                break;
            }
        }
        if (green_found) {
            break;
        }
    }

    if (!green_found) {
        return false;
    }
    return true;
}
bool controller::MaskImg(int x,int y, int width, int height) {
    Mat Mask(720, 1280, CV_8UC3, Scalar(255, 255, 255));
    Rect square(x, y, width, height);
    rectangle(Mask, square, Scalar(0, 0, 0), -1);
    img = Mask;
    return true;
}
bool controller::LoadSample(string path) {
    sample = imread(path.c_str());
    return true;
}
bool controller::LoadMask(string path) {
    mask = imread(path.c_str());
    return true;
}
bool controller::LoadImg(string path, Mat& img) {
    img = imread(path.c_str());
    return true;
}
bool controller::SaveImg(string path) {
    if (imwrite(path.c_str(), img)) return true;
    return false;
}
bool controller::SaveImg(string path, Mat img) {
    if (imwrite(path.c_str(), img)) return true;
    return false;
}

void controller::TakeImg(Mat example) {
    img = example;
}
void controller::TakeMask(Mat example) {
    mask = example;
}
void controller::TakeSample(Mat example) {
    sample = example;
}
void controller::Screenshot() {
    point = getgSize();
    HWND hwnd = getgHandle();
    int xWidth = point.x; // 1280
    int xHeight = point.y; // 720
    HDC hdcWindow = GetDC(hwnd);
    Mat res(xHeight, xWidth, CV_8UC4);
    RECT rc;
    GetClientRect(hwnd, &rc);
    HDC hdcMem = CreateCompatibleDC(hdcWindow);
    HBITMAP bitmap = CreateCompatibleBitmap(hdcWindow, rc.right - rc.left, rc.bottom - rc.top);
    HGDIOBJ OBJ = SelectObject(hdcMem, bitmap);
    SelectObject(hdcMem, bitmap);
    BitBlt(hdcMem, 0, 0, rc.right - rc.left, rc.bottom - rc.top, hdcWindow, 0, 0, SRCCOPY);
    SelectObject(hdcMem, OBJ);
    HDC hdcRar = GetDC(NULL);
    SelectObject(hdcRar, bitmap);
    StretchBlt(hdcRar, 0, 0, xWidth, xHeight, hdcMem, 0, 0, xWidth, xHeight, SRCCOPY);
    BITMAPINFOHEADER bi = { sizeof(BITMAPINFOHEADER), xWidth, xHeight, 1, 32 };
    GetDIBits(hdcMem, bitmap, 0, xHeight, res.data, (BITMAPINFO*)&bi, DIB_RGB_COLORS);
    DeleteObject(bitmap);
    DeleteDC(hdcMem);
    DeleteDC(hdcRar);
    ReleaseDC(hwnd, hdcWindow);
    flip(res, img, 0);
}

string controller::ScanDig() {
    Mat img1(img);
    cvtColor(img1, img1, COLOR_BGR2GRAY); // обработка в серый
    TessBaseAPI tess;
    tess.Init(NULL, "hc_dig");
    tess.SetImage(img1.data, img1.cols, img1.rows, 1, img1.cols);
    char* Text = tess.GetUTF8Text();
    for (int i = 0, n = strlen(Text); i < n; i++) {
        if (Text[i] == ' ') {
            for (int j = i; j < n; j++) Text[j] = Text[j + 1];
        }
    }
    tess.End();
    string str(Text);
    for (int i = 0; i < str.length(); ++i) {
        if (str[i] == '\n') {
            str.erase(i, 1);
            break;
        }
    }
    return str;
}
string controller::ScanLetEn() {
    Mat img1(img);
    cvtColor(img1, img1, COLOR_BGR2GRAY); // обработка в серый
    TessBaseAPI tess;
    tess.Init(NULL, "eng");
    tess.SetImage(img1.data, img1.cols, img1.rows, 1, img1.cols);
    char* Text = tess.GetUTF8Text();
    tess.End();
    string str(Text);
    for (int i = 0; i < str.length(); ++i) {
        if (str[i] == '\n') {
            str.erase(i, 1);
            break;
        }
    }
    return str;
}
string controller::ScanLetRu() {
    Mat img1(img);
    cvtColor(img1, img1, COLOR_BGR2GRAY); // обработка в серый
    TessBaseAPI tess;
    tess.Init(NULL, "rus");
    tess.SetImage(img1.data, img1.cols, img1.rows, 1, img1.cols);
    char* Text = tess.GetUTF8Text();
    tess.End();
    string str(Text);
    for (int i = 0; i < str.length(); ++i) {
        if (str[i] == '\n') {
            str.erase(i, 1);
            break;
        }
    }
    return str;
}
string controller::ScanDig(Mat img) {
    cvtColor(img, img, COLOR_BGR2GRAY); // обработка в серый
    TessBaseAPI tess;
    tess.Init(NULL, "hc_dig");
    tess.SetImage(img.data, img.cols, img.rows, 1, img.cols);
    char* Text = tess.GetUTF8Text();
    for (int i = 0, n = strlen(Text); i < n; i++) {
        if (Text[i] == ' ') {
            for (int j = i; j < n; j++) Text[j] = Text[j + 1];
        }
    }
    tess.End();
    string str(Text);
    for (int i = 0; i < str.length(); ++i) {
        if (str[i] == '\n') {
            str.erase(i, 1);
            break;
        }
    }
    return str;
}
string controller::ScanLetEn(Mat img) {
    cvtColor(img, img, COLOR_BGR2GRAY);
    TessBaseAPI tess;
    tess.Init(NULL, "eng");
    tess.SetImage(img.data, img.cols, img.rows, 1, img.cols);
    char* Text = tess.GetUTF8Text();
    tess.End();
    string str(Text);
    for (int i = 0; i < str.length(); ++i) {
        if (str[i] == '\n') {
            str.erase(i, 1);
            break;
        }
    }
    return str;
}
string controller::ScanLetRu(Mat img) {
    cvtColor(img, img, COLOR_BGR2GRAY);
    TessBaseAPI tess;
    tess.Init(NULL, "rus");
    tess.SetImage(img.data, img.cols, img.rows, 1, img.cols);
    /*char* Text = tess.GetUTF8Text();*/
    const char* utf8Text = tess.GetUTF8Text();
    iconv_t cd = iconv_open("WINDOWS-1251", "UTF-8");
    size_t inbytesleft = strlen(utf8Text);
    size_t outbytesleft = inbytesleft * 2; // Windows-1251 может занимать больше места
    char* Text = new char[outbytesleft];
    char* inbuf = const_cast<char*>(utf8Text);
    char* outbuf = Text;
    size_t result = iconv(cd, &inbuf, &inbytesleft, &outbuf, &outbytesleft);
    iconv_close(cd);
    tess.End();
    string str(Text);
    for (int i = 0; i < str.length(); ++i) {
        if (str[i] == '\n') {
            str.erase(i, 1);
            break;
        }
    }
    return str;
}
//

//filesystem

void controller::pathPages() {
    do {
        xPath = xPath.parent_path();
    } while (xPath.filename() != "bot");
    xPath /= "data\\pages";
}

path controller::getPath() {
    do {
        xPath = xPath.parent_path();
    } while (xPath.filename() != "bot");
    xPath /= "data\\pages";
    return xPath;
}
/*
vector<int> controller::LoadBL(string path) {
    for (const auto& entry : directory_iterator(path)) {
        if (entry.is_regular_file()) {
            xPath = entry.path();
            img = imread(xPath.generic_string());

        }
    }
}
*/
//
//Button
void controller::ClickShort(int sleep) {
    HWND hwnd = getgHandle();
    HWND wnd = getmHandle();
    SendMessage(wnd, WM_SETFOCUS, 0, 0);
    PostMessage(hwnd, WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(xrect.x+2 , xrect.y+2 ));
    Sleep(sleep);
    PostMessage(hwnd, WM_LBUTTONUP, 0, MAKELPARAM(xrect.x+2, xrect.y+2));
    Sleep(1000);
}
void controller::ClickShort(int x,int y,int sleep) {
    HWND hwnd = getgHandle();
    HWND wnd = getmHandle();
    SendMessage(wnd, WM_SETFOCUS, 0, 0);
    PostMessage(hwnd, WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(x + 2, y + 2));
    Sleep(sleep);
    PostMessage(hwnd, WM_LBUTTONUP, 0, MAKELPARAM(x + 2, y + 2));
    Sleep(1000);
}
void controller::ClickLong(int x, int y, int x1, int y1) {
    HWND hwnd = getgHandle();
    HWND wnd = getmHandle();
    auto start = Vec2i(x, y);
    auto stop = Vec2i(x1, y1);
    auto path = stop - start;
    Vec2f path_dir = path;
    path_dir = normalize(path_dir);
    SendMessage(wnd, WM_SETFOCUS, 0, 0);
    BYTE arr[256];
    memset(arr, 0, sizeof(256));
    GetKeyboardState(arr);
    auto old = arr[VK_LBUTTON];
    arr[VK_LBUTTON] = 128;
    SetKeyboardState(arr);


    SendMessage(hwnd, WM_MOUSEACTIVATE, (WPARAM)wnd, MAKELPARAM(HTCLIENT, WM_LBUTTONDOWN));
    Sleep(10);

    SendMessage(hwnd, WM_SETCURSOR, (WPARAM)hwnd, MAKELPARAM(HTCLIENT, WM_LBUTTONDOWN));
    Sleep(10);

    PostMessage(hwnd, WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(start[0], start[1]));
    Sleep(10);

    const int count = int(norm(path));

    Vec2i last_pos;

    for (int i = 0; i < count; ++i)
    {
        auto pos = Vec2i(path_dir * float(i));
        last_pos = start + pos;

        SetKeyboardState(arr);
        PostMessage(hwnd, WM_MOUSEMOVE, MK_LBUTTON, MAKELPARAM(last_pos[0], last_pos[1]));

        const int pause = 50;
        const int offset = 15;
        if (i < offset)
        {
            auto p = 10 + ((offset - (i + 1)) * pause) / offset;
            Sleep(p);
        }
        else if (i > count - offset)
        {
            auto p = 30 + ((offset - (count - i)) * pause) / offset;
            Sleep(p);
        }
        else if (i % 5 == 0)
            Sleep(1);
    }

    PostMessage(hwnd, WM_LBUTTONUP, 0, MAKELPARAM(last_pos[0], last_pos[1]));
    Sleep(10);

    SendMessage(hwnd, WM_SETCURSOR, (WPARAM)hwnd, MAKELPARAM(HTCLIENT, WM_MOUSEMOVE));
    Sleep(10);

    arr[VK_LBUTTON] = old;
    SetKeyboardState(arr);
}
void controller::ClickReturn() {
    HWND hwnd = getgHandle();
    PostMessage(hwnd, WM_KEYDOWN, VK_RETURN, 0);
    Sleep(500);
    PostMessage(hwnd, WM_KEYUP, VK_RETURN, 0);
    Sleep(500);
}
void controller::ClickEsc() {
    HWND hwnd = getgHandle();
    PostMessage(hwnd, WM_KEYDOWN, VK_ESCAPE, MapVirtualKey(VK_ESCAPE, MAPVK_VK_TO_VSC));
    Sleep(500);
    PostMessage(hwnd, WM_KEYUP, VK_ESCAPE, MapVirtualKey(VK_ESCAPE, MAPVK_VK_TO_VSC));
    Sleep(500);
}

bool controller::ClickButton(path page, string button) {
    mask = imread((page/button).generic_string());//button_?
    if (FindObj()) {
        ClickShort();
        return true;
    }
    return false;
}
bool controller::WriteMsg(const char* text/*,string path*/) {
    HWND hwnd = getgHandle();
    if (OpenClipboard(NULL)) {
        EmptyClipboard();
        HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, strlen(text) + 1);
        if (hMem != NULL) {
            char* pMem = (char*)GlobalLock(hMem);
            strcpy_s(pMem, strlen(text) + 1, text);
            GlobalUnlock(hMem);

            SetClipboardData(CF_TEXT, hMem);
        }
        CloseClipboard();
    }
    else {
        return false;
    }
    mask = imread("G:\\разная хрень\\исходники бота\\mycom_bot-master\\build\\data\\pages\\main\\button_chat.png");
    FindObj();
    Screenshot();
    ClickShort();
    Screenshot();
    LoadSample((string)"G:\\chat_main.png");
    if (Compare(0.5)) {
        mask = imread("G:\\разная хрень\\исходники бота\\mycom_bot-master\\build\\data\\pages\\chat\\compare_1.png");
        FindObj();
        ClickShort();
        ClickShort(4000);
        //xrect = { 76,609,0,0 };
        ClickShort(76,609);
        ClickReturn();
        ClickEsc();
    }
    return true;
}

//
Mat controller::getImg() { return img; }
Mat controller::getMask() { return mask; }
Mat controller::getSample() { return sample; }
