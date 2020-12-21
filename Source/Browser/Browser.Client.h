#pragma once
#ifndef __Browser_Client_H__
#define __Browser_Client_H__

#include <vector>
#include <include/cef_app.h>

namespace Cry
{
    namespace Chromium
    {
        class BrowserClient : public CefApp, public CefBrowserProcessHandler
        {
        public:
            explicit BrowserClient();
            virtual ~BrowserClient();
        private:
            virtual void OnBeforeCommandLineProcessing(const CefString& process_type, CefRefPtr<CefCommandLine> command_line) override;
            virtual void OnRegisterCustomSchemes(CefRawPtr<CefSchemeRegistrar> registrar) override;
            virtual void OnContextInitialized() override;
        private:
            virtual CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() override;
        private:
            IMPLEMENT_REFCOUNTING(BrowserClient);
        };
    }
}
#endif // __Browser_Client_H__