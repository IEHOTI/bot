#pragma once
#include "bluestacks.h"
#include "Ocr.h"
class controller :
    public bluestacks, public Ocr
{
public:
    controller();
    ~controller();
    bool isWindow();
    bool isValidSize();
    bool setValidSize();
    //client
    bool FindObj();
    bool FindObj(Mat mask);
    bool Compare(double rightVal = 0.01);
    bool Compare(Mat img, double rightVal = 0.01);
    bool CompareSample(path page,string sample, string mask, double rightVal = 0.01);
    // 
    //img
    void Screenshot();
    void TakeImg(Mat img);
    void TakeMask(Mat img);
    void TakeSample(Mat img);
    bool SaveImg(string path);
    bool SaveImg(string path, Mat img);
    bool LoadSample(string path);
    bool LoadMask(string path);
    bool LoadImg(string path, Mat& img);
    bool CheckGreenCol();
    bool MaskImg(int x = 0, int y = 0, int width = 1, int height = 1);
    string ScanDig();
    string ScanLetEn();
    string ScanLetRu();//?
    string ScanDig(Mat img);
    string ScanLetEn(Mat img);
    string ScanLetRu(Mat img);//?
    Mat getImg();
    Mat getSample();
    Mat getMask();
    Mat CutImg();
    // 
    //button
    void ClickShort(int sleep = 300);
    void ClickShort(int x,int y, int sleep = 300);
    void ClickReturn();
    void ClickEsc();
    void ClickLong(int x, int y, int x1, int y1);// map{683 504 683-287 504}
    bool WriteMsg(const char* text/*,string path*/); // path поменять
    bool ClickButton(path page,string button);
    //
    //filesystem
    void pathPages();
    path getPath();
    /*
    vector<int> LoadBL(string path); // -
    bool takePath(string path);
    string givePath();
    */
    //
private:
    Mat img, sample, mask;
    RECT rect;
    Rect xrect;
    Point point;
    path xPath;
};

