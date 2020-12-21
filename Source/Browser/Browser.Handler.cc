#include <Browser/Browser.Handler.h>

#include <include/base/cef_bind.h>
#include <include/cef_app.h>
#include <include/cef_parser.h>
#include <include/views/cef_browser_view.h>
#include <include/views/cef_window.h>
#include <include/wrapper/cef_closure_task.h>
#include <include/wrapper/cef_helpers.h>

#include <Browser/Browser.Closure.h>

namespace Cry
{
    namespace Chromium
    {
        static BrowserHandler* BrowserHandlerInstance = nullptr;

        std::string GetDataURI(const std::string& data, const std::string& mime_type)
        {
            return "data:" + mime_type + ";base64," + CefURIEncode(CefBase64Encode(data.data(), data.size()), false).ToString();
        }

        BrowserHandler::BrowserHandler(bool use_views, HWND hParent) : useviews(use_views), hParent(hParent), closeingBrowser(false), originalBrowser(nullptr), initBrowser(false)
        {
            BrowserHandlerInstance = this;
        }

        BrowserHandler::~BrowserHandler()
        {
            BrowserHandlerInstance = nullptr;
        }

        BrowserHandler* BrowserHandler::GetInstance()
        {
            return BrowserHandlerInstance;
        }

        void BrowserHandler::CloseHostBrowser(bool force_close)
        {
            if (CefCurrentlyOn(TID_UI))
            {
                if (originalBrowser)
                {
                    originalBrowser->GetHost()->CloseBrowser(force_close);
                    return;
                }
            }

            BrowserClosure::PostClosure(base::Bind(&BrowserHandler::CloseHostBrowser, this, force_close));
        }

        void BrowserHandler::CloseHostBrowserEx(CefRefPtr<CefBrowser>browser, bool force_close)
        {
            if (CefCurrentlyOn(TID_UI))
            {
                if (browser->GetIdentifier() == originalBrowser->GetIdentifier())
                {
                    browser->GetHost()->CloseBrowser(force_close);
                    return;
                }
            }

            BrowserClosure::PostClosure(base::Bind(&BrowserHandler::CloseHostBrowserEx, this, browser, force_close));

        }

        void BrowserHandler::OpenWebSite(const std::string& url)
        {
            if (CefCurrentlyOn(TID_UI))
            {
                if (originalBrowser->IsLoading())
                {
                    originalBrowser->StopLoad();
                }

                if (originalBrowser && CefString(url) != originalBrowser->GetMainFrame()->GetURL())
                {
                    originalBrowser->GetMainFrame()->LoadURL(url.empty() ? "about:blank" : url);
                }
                else
                {
                    originalBrowser->StopLoad();
                    originalBrowser->Reload();
                }

                return;
            }

            BrowserClosure::PostClosure(base::Bind(&BrowserHandler::OpenWebSite, this, url));
        }

        void BrowserHandler::OpenWebSiteEx(CefRefPtr<CefBrowser> browser, const std::string& url)
        {
            if (CefCurrentlyOn(TID_UI))
            {
                if (browser->IsSame(originalBrowser))
                {
                    if (originalBrowser && CefString(url) != originalBrowser->GetMainFrame()->GetURL())
                    {
                        originalBrowser->GetMainFrame()->LoadURL(url.empty() ? "about:blank" : url);
                    }
                    else
                    {
                        originalBrowser->StopLoad();
                        originalBrowser->Reload();
                    }
                }

                return;
            }

            BrowserClosure::PostClosure(base::Bind(&BrowserHandler::OpenWebSiteEx, this, browser, url));
        }

        void BrowserHandler::OnFullscreenModeChange(CefRefPtr<CefBrowser> browser, bool fullscreen)
        {
            static RECT preWinRect = { 0 };

            //The parent window of the inner browser

            if (hParent == NULL)
            {
                return;
            }

            if (fullscreen)
            {
                //Title bar height
                int nHeadHeight = 34;
                //The number of px between parent window and inner browser
                int nOffset = 1;
                int nW = GetSystemMetrics(SM_CXSCREEN);
                int nH = GetSystemMetrics(SM_CYSCREEN);
                //Store the rectangle of old window
                GetWindowRect(hParent, &preWinRect);
                SetWindowPos(hParent, HWND_TOPMOST, 0, -nHeadHeight, nW, nH + nHeadHeight + nOffset, SWP_NOACTIVATE | SWP_NOSENDCHANGING);
            }
            else
            {
                int nW = preWinRect.right - preWinRect.left;
                int nH = preWinRect.bottom - preWinRect.top;
                int nX = preWinRect.left;
                int nY = preWinRect.top;

                if (nW <= 0 || nH <= 0)
                {
                    return;
                }

                SetWindowPos(hParent, HWND_NOTOPMOST, nX, nY, nW, nH, SWP_NOACTIVATE);
            }

            return;
        }

        bool BrowserHandler::OnBeforePopup(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, const CefString& target_url, const CefString& target_frame_name, CefLifeSpanHandler::WindowOpenDisposition target_disposition, bool user_gesture, const CefPopupFeatures& popupFeatures, CefWindowInfo& windowInfo, CefRefPtr<CefClient>& client, CefBrowserSettings& settings, CefRefPtr<CefDictionaryValue>& extra_info, bool* no_javascript_access)
        {
            switch (target_disposition)
            {
            case WOD_NEW_FOREGROUND_TAB:
            case WOD_NEW_BACKGROUND_TAB:
            case WOD_NEW_POPUP:
            case WOD_NEW_WINDOW:
            {
                browser->GetMainFrame()->LoadURL(target_url);
                return true;
            }
            }
            return false;
        }
        // CefLifeSpanHandler Methods:
        void BrowserHandler::OnAfterCreated(CefRefPtr<CefBrowser> browser)
        {
            CEF_REQUIRE_UI_THREAD();
            if (!initBrowser)
            {
                initBrowser = true;
            }
            //browser->GetHost()->SetAutoResizeEnabled(true, CefSize(20, 20), CefSize(1000, 1000));
            if (originalBrowser != browser)
            {
                originalBrowser = browser;
            }
        }

        bool BrowserHandler::DoClose(CefRefPtr<CefBrowser> browser)
        {
            CEF_REQUIRE_UI_THREAD();
            if (nullptr != originalBrowser && !closeingBrowser && originalBrowser->GetIdentifier() == browser->GetIdentifier())
            {
                closeingBrowser = true;
            }
            return false;
        }

        void BrowserHandler::OnBeforeClose(CefRefPtr<CefBrowser> browser)
        {
            CEF_REQUIRE_UI_THREAD();

            if (nullptr != originalBrowser && originalBrowser->GetIdentifier() == browser->GetIdentifier())
            {
                if (closeingBrowser)
                {
                    if (browser->IsLoading())
                    {
                        browser->StopLoad();
                    }
                    originalBrowser = nullptr;
                    PostMessage(0, WM_QUIT, 0, 0);
                }
            }
        }

        void BrowserHandler::OnBeforeContextMenu(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefContextMenuParams> params, CefRefPtr<CefMenuModel> model)
        {
            if ((params->GetTypeFlags() & (CM_TYPEFLAG_PAGE | CM_TYPEFLAG_FRAME)) != 0)
            {
                if (model->GetCount() > 0)
                {
                    model->Clear();
                }
            }
        }

        bool BrowserHandler::OnBeforeBrowse(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefRequest> request, bool user_gesture, bool is_redirect)
        {
            CefRefPtr<CefRequestContext> context = browser->GetHost()->GetRequestContext();
            context->ResolveHost(request->GetURL(), this);
            return false;
        }

        void BrowserHandler::OnResolveCompleted(cef_errorcode_t result, const std::vector<CefString>& resolved_ips)
        {
            for (uint32 i = 0; i < resolved_ips.size(); ++i)
            {
                CefString ips = resolved_ips[i];
                printf("当前解析：%ls\n", ips.c_str());
            }
            return;
        }
        // 
        //         // CefDisplayHandler Methods:
        //         void BrowserHandler::OnTitleChange(CefRefPtr<CefBrowser> browser, const CefString& title)
        //         {
        //             CEF_REQUIRE_UI_THREAD();
        //             printf("内核线程：%d\n", GetCurrentThreadId());
        //             if (use_views_)
        //             {
        //                 // Set the title of the window using the Views framework.
        //                 CefRefPtr<CefBrowserView> browser_view = CefBrowserView::GetForBrowser(browser);
        //                 if (browser_view)
        //                 {
        //                     CefRefPtr<CefWindow> window = browser_view->GetWindow();
        //                     if (window)
        //                         window->SetTitle(title);
        //                 }
        //             }
        //             else
        //             {
        //                 // Set the title of the window using platform APIs.
        //                 //PlatformTitleChange(browser, title);
        //             }
        //         }
        // 
        //         void BrowserHandler::PlatformTitleChange(CefRefPtr<CefBrowser> browser, const CefString& title)
        //         {
        //             CEF_REQUIRE_UI_THREAD();
        //             CefWindowHandle hwnd = browser->GetHost()->GetWindowHandle();
        //             if (hwnd)
        //             {
        //                 SetWindowText(hwnd, std::wstring(title).c_str());
        //             }
        //         }
        // 
        //         void BrowserHandler::CloseAllBrowsers(bool force_close)
        //         {
        //             if (!CefCurrentlyOn(TID_UI))
        //             {
        //                 // Execute on the UI thread.
        //                 CefPostTask(TID_UI, base::Bind(&BrowserHandler::CloseAllBrowsers, this, force_close));
        //                 return;
        //             }
        // 
        //             if (browser_list_.empty())
        //             {
        //                 return;
        //             }
        // 
        //             BrowserList::iterator bit = browser_list_.begin();
        //             for (; bit != browser_list_.end(); ++bit)
        //             {
        //                 if ((*bit)->IsSame((*bit)))
        //                 {
        //                     (*bit)->GetHost()->CloseBrowser(true);
        //                     browser_list_.erase(bit);
        //                     break;
        //                 }
        //             }
        //         }
        // 
        // 
        //         // CefLoadHandler Methods:
        //         void BrowserHandler::OnLoadError(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, ErrorCode errorCode, const CefString& errorText, const CefString& failedUrl)
        //         {
        //             CEF_REQUIRE_UI_THREAD();
        // 
        //             // Don't display an error for downloaded files.
        //             if (errorCode == ERR_ABORTED)
        //                 return;
        // 
        //             // Display a load error message using a data: URI.
        //             std::stringstream ss;
        //             ss << "<html><body bgcolor=\"white\">"
        //                 "<h2>Failed to load URL "
        //                 << std::string(failedUrl) << " with error " << std::string(errorText)
        //                 << " (" << errorCode << ").</h2></body></html>";
        // 
        //             frame->LoadURL(GetDataURI(ss.str(), "text/html"));
        //         }
        // 
        //         void BrowserHandler::OnLoadingStateChange(CefRefPtr<CefBrowser> browser, bool isLoading, bool canGoBack, bool canGoForward)
        //         {
        // //             if (isLoading && is_closing_)
        // //             {
        // //                 browser->StopLoad();
        // //             }
        //             return;
        //         }
    }
}