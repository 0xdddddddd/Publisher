#pragma once
#ifndef __Browser_WinMain_H__
#define __Browser_WinMain_H__
#include <platform.h>

//#define CEF_USE_SANDBOX 1

namespace Cry
{
    namespace Gui
    {
        class ApplicationMain;
    }

    class QApplication;

    namespace Chromium
    {
        class BrowserHandler;
        class BrowserWinMain
        {
        public:
            explicit BrowserWinMain(int argc, char* argv[]);
            virtual ~BrowserWinMain();
        public:
            int InitializeBrowser(int argc, char* argv[], HINSTANCE hInstance = GetModuleHandle(nullptr));
        private:
            std::shared_ptr<QApplication>                                       qtApplication;
            std::shared_ptr<Gui::ApplicationMain>                               applicationMain;
        };
    }
}
#endif // __Browser.WinMain_H__