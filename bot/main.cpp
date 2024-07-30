#include <baseapi.h> // tesseract
#include <allheaders.h> // leptonica 
#include <opencv.hpp> // opencv 
#include <iostream>
#include <Windows.h>
#include <filesystem>
#include <fstream>

#include <tlhelp32.h>
#include <psapi.h>
//#include <winternl.h>

using namespace std;
using namespace cv;
using namespace tesseract;
using namespace std::filesystem;

#include <boost/format.hpp>
using namespace boost;

#include "Arena.h"
#include "Ocr.h"
////////////////////
/*
typedef struct _UNICODE_STRING
{
    USHORT Length;
    USHORT MaximumLength;
    PWSTR Buffer;
} UNICODE_STRING, * PUNICODE_STRING;

typedef struct _PROCESS_BASIC_INFORMATION
{
    LONG ExitStatus;
    PVOID PebBaseAddress;
    ULONG_PTR AffinityMask;
    LONG BasePriority;
    ULONG_PTR UniqueProcessId;
    ULONG_PTR ParentProcessId;
} PROCESS_BASIC_INFORMATION, * PPROCESS_BASIC_INFORMATION;

int get_cmd_line(HWND hwnd, PWSTR& buf)
{
    DWORD dwId;
    GetWindowThreadProcessId(hwnd, &dwId);
    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, dwId);
    DWORD err = 0;
    if (hProcess == NULL)
    {
        printf("OpenProcess %u failed\n", dwId);
        return GetLastError();
    }

    // determine if 64 or 32-bit processor
    SYSTEM_INFO si;
    GetNativeSystemInfo(&si);

    // determine if this process is running on WOW64
    BOOL wow;
    IsWow64Process(GetCurrentProcess(), &wow);

    // use WinDbg "dt ntdll!_PEB" command and search for ProcessParameters offset to find the truth out
    DWORD ProcessParametersOffset = si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64 ? 0x20 : 0x10;
    DWORD CommandLineOffset = si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64 ? 0x70 : 0x40;

    // read basic info to get ProcessParameters address, we only need the beginning of PEB
    DWORD pebSize = ProcessParametersOffset + 8;
    PBYTE peb = (PBYTE)malloc(pebSize);
    ZeroMemory(peb, pebSize);

    // read basic info to get CommandLine address, we only need the beginning of ProcessParameters
    DWORD ppSize = CommandLineOffset + 16;
    PBYTE pp = (PBYTE)malloc(ppSize);
    ZeroMemory(peb, pebSize);

    PWSTR cmdLine;

    if (wow)
    {
        // we're running as a 32-bit process in a 64-bit OS
        PROCESS_BASIC_INFORMATION pbi;
        ZeroMemory(&pbi, sizeof(pbi));

        // read ProcessParameters from 64-bit address space
        PBYTE* parameters = (PBYTE*)*(LPVOID*)(peb + ProcessParametersOffset); // address in remote process adress space

        // read CommandLine
        UNICODE_STRING* pCommandLine = (UNICODE_STRING*)(pp + CommandLineOffset);
        cmdLine = (PWSTR)malloc(pCommandLine->MaximumLength);
    }
    else
    {
        // we're running as a 32-bit process in a 32-bit OS, or as a 64-bit process in a 64-bit OS
        PROCESS_BASIC_INFORMATION pbi;
        ZeroMemory(&pbi, sizeof(pbi));

        // read ProcessParameters
        PBYTE* parameters = (PBYTE*)*(LPVOID*)(peb + ProcessParametersOffset); // address in remote process adress space
        if (!ReadProcessMemory(hProcess, parameters, pp, ppSize, NULL))
        {
            printf("ReadProcessMemory Parameters failed\n");
            CloseHandle(hProcess);
            return GetLastError();
        }

        // read CommandLine
        UNICODE_STRING* pCommandLine = (UNICODE_STRING*)(pp + CommandLineOffset);
        cmdLine = (PWSTR)malloc(pCommandLine->MaximumLength);
        if (!ReadProcessMemory(hProcess, pCommandLine->Buffer, cmdLine, pCommandLine->MaximumLength, NULL))
        {
            printf("ReadProcessMemory Parameters failed\n");
            CloseHandle(hProcess);
            return GetLastError();
        }
    }

    buf = cmdLine;
}
*/
////////////////////////
/*string GetCommandLineForProcess(HWND hwnd) {
//    DWORD processID;
//    GetWindowThreadProcessId(hwnd, &processID);
//    std::string commandLine;
//    wchar_t* x;
//    ULONG y;
//    ULONG z;
//    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processID);
//    //NtQueryInformationProcess(hProcess, ProcessBasicInformation, x, y, &z);
//    wcout << x << endl;
//    //if (hProcess) {
//    //    // Получаем буфер для команды
//    //    char buffer[4096];
//    //    SIZE_T bytesRead;
//
//    //    // Получаем адрес командной строки
//    //    HMODULE hModule = GetModuleHandleA("kernel32.dll");
//    //    if (hModule) {
//    //        // Получаем дескриптор процесса
//    //        HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
//    //        if (hSnapshot != INVALID_HANDLE_VALUE) {
//    //            PROCESSENTRY32 pe;
//    //            pe.dwSize = sizeof(PROCESSENTRY32);
//    //            if (Process32First(hSnapshot, &pe)) {
//    //                do {
//    //                    if (pe.th32ProcessID == processID) {
//    //                        // Открываем процесс для чтения памяти
//    //                        HANDLE hProc = OpenProcess(PROCESS_VM_READ | PROCESS_QUERY_INFORMATION, FALSE, pe.th32ProcessID);
//    //                        if (hProc) {
//    //                            // Читаем память процесса
//    //                            if (ReadProcessMemory(hProc, (LPCVOID)(pe.th32ProcessID), buffer, sizeof(buffer), &bytesRead)) {
//    //                                commandLine.assign(buffer, bytesRead);
//    //                            }
//    //                            CloseHandle(hProc);
//    //                        }
//    //                        break;
//    //                    }
//    //                } while (Process32Next(hSnapshot, &pe));
//    //            }
//    //            CloseHandle(hSnapshot);
//    //        }
//    // 
//    //    }
//    
//        CloseHandle(hProcess);
//    //}
//
//    return commandLine;
}*/

int main() {
    setlocale(0, "");
    /*uProfile::Start();
    Sleep(15000);*/
    Arena main;
    if (!main.isValidSize()) { main.setValidSize(); }
    main.Settings();
    int x = 0;
    do {
        if (main.Start()) {
            if (!main.checkFind()) {
                main.tacticFirst();
                x++;
            }
        }
    } while (x != 5);
    /*if (main.getData()) {
        main.Print();
        cout << main.getPhase() << endl;
    }*/
    /*main.getData();
    main.Print();*/
    ////screenshotter
    //main.Screenshot();
    //main.SaveImg((string)"G:/sample_defeat.png");
    ////
    //main.ClickLong(683, 504, 683 - 287, 504);
    ////getter masks
    //main.MaskImg(665, 590, 140, 40);
    //main.SaveImg("C:/bot/data/pages/arena/arena_battles/battle_button_qstart.png");
    ////// 

    ////// checker masks
    //main.LoadSample("C:/bot/data/pages/arena/arena_main/sample.png"/*"G:/sample.png"*/);
    //main.LoadMask("C:/bot/data/pages/arena/arena_main/compare.png");
    ////main.TakeImg(main.getSample());
    //main.Screenshot();
    //main.FindObj();
    //main.TakeImg(main.CutImg());
    //imshow("1", main.getImg());
    //waitKey(0);
    //if (main.Compare()) cout << "true" << endl;
    //
    ////
    //"C:\Program Files(\BlueStacks_nxt\HD-Player.exe" --instance Nougat32 --cmd launchApp --package "com.my.hc.rpg.kingdom.simulator"
    /*Mat img = imread("C:\\bot\\data\\pages\\arena\\arena_battles\\battle_enemy_power.png");
    main.Screenshot();
    Mat img1 = imread("C:\\bot\\кв\\ограничение бойцов.png");
    main.TakeImg(imread("C:\\bot\\data\\pages\\arena\\arena_battles\\battle_sample.png"));
    main.TakeMask(img);
    main.FindObj();
    imshow("1", main.CutImg());
    waitKey(0);
    int x = main.Recognize(main.CutImg());
    cout << x << endl;*/
    return 0;
}