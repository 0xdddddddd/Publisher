#include <Browser/Browser.Client.h>
#include <Browser/Browser.Handler.h>
namespace Cry
{
    namespace Chromium
    {
        BrowserClient::BrowserClient()
        {

        }

        BrowserClient::~BrowserClient()
        {

        }

        void BrowserClient::OnBeforeCommandLineProcessing(const CefString& process_type, CefRefPtr<CefCommandLine> command_line)
        {
            command_line->AppendSwitchWithValue("--lang", "zh-CN");
            command_line->AppendSwitchWithValue("--enable-features", "OverlayScrollbar"); 
            command_line->AppendSwitch("disable-extensions");

//             command_line->AppendSwitch("disable-gpu");
//             command_line->AppendSwitch("disable-gpu-compositing");
        }

        void BrowserClient::OnRegisterCustomSchemes(CefRawPtr<CefSchemeRegistrar> registrar)
        {
            registrar->AddCustomScheme("Client", CEF_SCHEME_OPTION_STANDARD | CEF_SCHEME_OPTION_CORS_ENABLED);
        }

        CefRefPtr<CefBrowserProcessHandler> BrowserClient::GetBrowserProcessHandler()
        {
            return this;
        }

        void BrowserClient::OnContextInitialized()
        {
            return;
        }
    }
}