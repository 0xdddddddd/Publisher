#include <Browser/Browser.Windows.h>


#include <include/cef_command_line.h>
#include <include/views/cef_browser_view.h>
#include <include/views/cef_window.h>
#include <include/wrapper/cef_helpers.h>

#include <Browser/Browser.Handler.h>
#include <Browser/Browser.Closure.h>

#include <QDesktopWidget>
#include <QApplication>
#include <QColor>
namespace Cry
{
    namespace Chromium
    {
        static BrowserWindows* BrowserWindowsInstance = nullptr;
        

        BrowserWindows::BrowserWindows(QWidget* Widget) : QWidget(Widget)
        {
            BrowserWindowsInstance = this;
        }

        BrowserWindows::~BrowserWindows()
        {
            BrowserWindowsInstance = nullptr;
        }

        BrowserWindows* BrowserWindows::GetInstance()
        {
            return BrowserWindowsInstance;
        }

        bool BrowserWindows::InitiaBrowser(const std::string& url)
        {
            return true;
        }

        bool BrowserWindows::CreateBrowser(const std::string& url, HWND hWnd, RECT rect)
        {
            if (CefCurrentlyOn(TID_UI))
            {
                if (Chromium::BrowserHandler::GetInstance() && nullptr != Chromium::BrowserHandler::GetInstance()->GetBrowser())
                {
                    Chromium::BrowserHandler::GetInstance()->OpenWebSite(url);
                    return true;
                }

                CEF_REQUIRE_UI_THREAD();

                CefRefPtr<Chromium::BrowserHandler> handler = new Chromium::BrowserHandler(false, hWnd);

                CefWindowInfo window_info;

                window_info.SetAsChild(hWnd, rect);
                CefString(&window_info.window_name).FromString("BrowserClient(wwww.zhao.ee)");
                CefBrowserSettings browserSettings;
                browserSettings.plugins = STATE_DISABLED; 
                browserSettings.background_color = RGB(0, 0, 0);

                return CefBrowserHost::CreateBrowserSync(window_info, handler, url, browserSettings, nullptr, nullptr);
            }

            return BrowserClosure::PostClosure(base::Bind(&BrowserWindows::CreateBrowserEx, url, hWnd, rect));
        }
        void BrowserWindows::CreateBrowserEx(const std::string& url, HWND hWnd, RECT rect)
        {
            CreateBrowser(url, hWnd, rect);
        }
    }
}