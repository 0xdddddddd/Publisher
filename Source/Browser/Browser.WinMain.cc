#include <Browser/Browser.WinMain.h>

#include <objbase.h>
#include <include/cef_app.h>
#include <include/cef_command_line.h>
#include <include/cef_sandbox_win.h>

#include <Browser/Browser.Client.h>

#include <QApplication>
#include <Interface/ApplicationMain.h>

#if defined(CEF_USE_SANDBOX)
// The cef_sandbox.lib static library may not link successfully with all VS
// versions.
#pragma comment(lib, "cef_sandbox.lib")
#pragma comment(lib, "Dbghelp.lib")
#pragma comment(lib, "Propsys.lib")
#endif
#pragma comment(lib, "libcef.lib")
namespace Cry
{
    namespace Chromium
    {
        BrowserWinMain::BrowserWinMain(int argc, char* argv[])
        {

        }

        BrowserWinMain::~BrowserWinMain()
        {

        }

        int BrowserWinMain::InitializeBrowser(int argc, char* argv[], HINSTANCE hInstance)
        {
            CefEnableHighDPISupport();
            void* sandbox_info = nullptr;

            CefMainArgs main_args(hInstance);

            if (CefExecuteProcess(main_args, nullptr, sandbox_info) >= 0)
            {
                return -1;
            }

            CefRefPtr<CefCommandLine> command_line = CefCommandLine::CreateCommandLine();
            command_line->InitFromString(argv[0]);

            CefSettings settings;

            settings.no_sandbox = true;

            settings.multi_threaded_message_loop = true; //多线程消息循环
            settings.log_severity = LOGSEVERITY_DISABLE;
            settings.pack_loading_disabled = false;

            CefRefPtr<BrowserClient> client(new BrowserClient);

            if (CefInitialize(main_args, settings, client, sandbox_info))
            {
                qtApplication.reset(new QApplication(argc, argv));
                applicationMain.reset(new Gui::ApplicationMain);
                qtApplication->installEventFilter(applicationMain.get());
                applicationMain->show();
                int r = qtApplication->exec();
                qtApplication.reset();
                applicationMain.reset();

                CefQuitMessageLoop();
                CefShutdown();
                return r;
            }
            return -1;
        }
    }
}