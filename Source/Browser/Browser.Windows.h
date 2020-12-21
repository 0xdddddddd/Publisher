#pragma once
#ifndef __Browser_Window_H__
#define __Browser_Window_H__
#include <platform.h>

#include <QWindow>
#include <QWidget>

#include <include/cef_browser.h>
#include <include/cef_task.h>

namespace Cry
{
    namespace Chromium
    {
        class BrowserWindows : public QWidget, public CefTask
        {
        public:
            Q_OBJECT;
        public:
            explicit BrowserWindows(QWidget* Widget = nullptr);
            virtual ~BrowserWindows();
        public:
            static BrowserWindows* GetInstance();
        public:
            virtual void Execute() override {};
        public:
            static bool InitiaBrowser(const std::string& url);
            static bool CreateBrowser(const std::string& url, HWND hWnd, RECT rect);
        private:
            static void CreateBrowserEx(const std::string& url, HWND hWnd, RECT rect);
        private:
            HWND                                                        parent;
            QRect                                                       qtRect;
            RECT                                                        clientRect;
        private:
            IMPLEMENT_REFCOUNTING(BrowserWindows);
        };
    }
}
#endif // __Browser_Window_H__