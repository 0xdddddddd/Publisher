#include <iostream>
#include <Objbase.h>

#include <Entrance/QWindows.Entry.h>

#include <Browser/Browser.WinMain.h>

#if !(defined(DEBUG) || defined(_DEBUG))
#pragma comment(linker, R"(/SubSystem:Windows /Entry:mainCRTStartup)")
#endif // DEBUG

//#pragma comment(linker, R"(/DelayLoad:libcef.dll /DelayLoad:libEGL.dll)")

int main(int argc, char* argv[])
{
    Chromium::BrowserWinMain run(argc, argv);
    return run.InitializeBrowser(argc, argv, GetModuleHandle(nullptr));
}