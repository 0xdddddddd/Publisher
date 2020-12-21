#pragma once
#ifndef __Browser_Handler_H__
#define __Browser_Handler_H__

#include <platform.h>
#include <include/cef_client.h>
#include <include/cef_app.h>
//#include <include/cef_resource_request_handler.h>
#include <list>

namespace Cry
{
    namespace Chromium
    {
        class BrowserHandler :
            public CefClient,
            public CefDisplayHandler,
            public CefLifeSpanHandler,
            public CefContextMenuHandler,
            //public CefLoadHandler,
            public CefRequestHandler,
            public CefResourceRequestHandler,
            public CefResolveCallback
            //public CefRequestContext
        {
        public:
            explicit BrowserHandler(bool use_views, HWND hParent);
            virtual ~BrowserHandler();
        public:
            static BrowserHandler* GetInstance();
        public:
            CefBrowser* GetBrowser() { return  initBrowser ? originalBrowser.get() : nullptr; };
            bool IsClosing() { return false == closeingBrowser; };
            void CloseHostBrowser(bool force_close);
            void CloseHostBrowserEx(CefRefPtr<CefBrowser>browser, bool force_close);
            void OpenWebSite(const std::string& url);
            void OpenWebSiteEx(CefRefPtr<CefBrowser> browser, const std::string& url);
        private:
            // CefClient
            virtual CefRefPtr<CefDisplayHandler> GetDisplayHandler() override { return this; }
            virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() override { return this; }
            //virtual CefRefPtr<CefLoadHandler> GetLoadHandler() override { return this; }
            virtual CefRefPtr<CefContextMenuHandler> GetContextMenuHandler() override { return this; };
            virtual CefRefPtr<CefRequestHandler> GetRequestHandler() override { return this; }
            virtual CefRefPtr<CefResourceRequestHandler> GetResourceRequestHandler(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefRequest> request, bool is_navigation, bool is_download, const CefString& request_initiator, bool& disable_default_handling) override { return this; }
        private:
            // CefDisplayHandler
            //virtual void OnTitleChange(CefRefPtr<CefBrowser> browser, const CefString& title) override;
            virtual void OnFullscreenModeChange(CefRefPtr<CefBrowser> browser, bool fullscreen) override;
        private:
            // CefLifeSpanHandler
            virtual bool OnBeforePopup(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, const CefString& target_url, const CefString& target_frame_name, CefLifeSpanHandler::WindowOpenDisposition target_disposition, bool user_gesture, const CefPopupFeatures& popupFeatures, CefWindowInfo& windowInfo, CefRefPtr<CefClient>& client, CefBrowserSettings& settings, CefRefPtr<CefDictionaryValue>& extra_info, bool* no_javascript_access) override;
            virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser) override;
            virtual bool DoClose(CefRefPtr<CefBrowser> browser) override;
            virtual void OnBeforeClose(CefRefPtr<CefBrowser> browser) override;
        private:
            // CefContextMenuHandler 
            virtual void OnBeforeContextMenu(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefContextMenuParams> params, CefRefPtr<CefMenuModel> model) override;
        private:
            virtual bool OnBeforeBrowse(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefRequest> request, bool user_gesture, bool is_redirect) override;
            // CefResolveCallback
            virtual void OnResolveCompleted(cef_errorcode_t result, const std::vector<CefString>& resolved_ips) override;
        private:
            // CefLoadHandler
            //virtual void OnLoadError(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, ErrorCode errorCode, const CefString& errorText, const CefString& failedUrl) override;
            //virtual void OnLoadingStateChange(CefRefPtr<CefBrowser> browser, bool isLoading, bool canGoBack, bool canGoForward) override;
        private:
            void PlatformTitleChange(CefRefPtr<CefBrowser> browser, const CefString& title);
            void CloseAllBrowsers(bool force_close);
        private:
            // True if the application is using the Views framework.
            bool                                                                    useviews;
            HWND                                                                    hParent;
            CefRefPtr<CefBrowser>                                                   originalBrowser;
            bool                                                                    closeingBrowser;
            bool                                                                    initBrowser;
        private:
            IMPLEMENT_REFCOUNTING(BrowserHandler);
        };
    }
}
#endif // __Browser_Handler_H__