#include <Interface/ApplicationMain.h>
#include <Interface/Improt/ApplicationMain.h>

#include <include/cef_client.h>
#include <include/cef_app.h>

#include <QDesktopWidget>

#include <QtPlugin>

#include <include/cef_browser.h>
#include <include/cef_command_line.h>
#include <include/views/cef_browser_view.h>
#include <include/views/cef_window.h>
#include <include/wrapper/cef_helpers.h>
#include <include/wrapper/cef_closure_task.h>

#include <Browser/Browser.Closure.h>
#include <Browser/Browser.Windows.h>
#include <Browser/Browser.Handler.h>

Q_IMPORT_PLUGIN(QWindowsVistaStylePlugin)
Q_IMPORT_PLUGIN(QWindowsIntegrationPlugin)

namespace Cry
{
    namespace Gui
    {
        ApplicationMain::ApplicationMain(QWidget* Widget) :
            QMainWindow(Widget),
            application(std::make_unique<Ui::ApplicationMain>()),
            browserWindows(std::make_unique<Chromium::BrowserWindows>(this))
        {
            application->setupUi(this);
            QObject::connect(application->pushButton, &QPushButton::clicked, this, &ApplicationMain::OpenBrowser);
            QObject::connect(this, &ApplicationMain::SubmitNoticeMessage, this, &ApplicationMain::AcceptNoticeMessage);

        }

        ApplicationMain::~ApplicationMain()
        {
            // CefRunMessageLoop();
        }

        void ApplicationMain::OpenBrowser()
        {
            SubmitNoticeMessage();
        }

        bool ApplicationMain::nativeEvent(const QByteArray& EventType, void* pMessage, long* pResult)
        {
            LPMSG pMsg = reinterpret_cast<LPMSG>(pMessage);
            return QWidget::nativeEvent(EventType, pMessage, pResult);
        }

        bool ApplicationMain::nativeEventFilter(const QByteArray& EventType, void* pMessage, long* pResult)
        {
            LPMSG pMsg = reinterpret_cast<LPMSG>(pMessage); 

            return QMainWindow::nativeEvent(EventType, pMessage, pResult);
        }

        void ApplicationMain::resizeEvent(QResizeEvent* event)
        {
            if (Chromium::BrowserHandler::GetInstance() && Chromium::BrowserHandler::GetInstance()->IsClosing())
            {
                CefRefPtr<CefBrowser> browser = Chromium::BrowserHandler::GetInstance()->GetBrowser();
                if (browser)
                {
                    QRect qtrect = application->browserWidget->rect();
                    if (SetWindowPos(browser->GetHost()->GetWindowHandle(), HWND_TOPMOST, qtrect.left(), qtrect.top(), qtrect.right(), qtrect.bottom(), SWP_NOZORDER))
                    {
                        return __super::resizeEvent(event);
                    }
                }
            }
            return __super::resizeEvent(nullptr);
        }

        void ApplicationMain::closeEvent(QCloseEvent* event)
        {
            if (Chromium::BrowserHandler::GetInstance() && Chromium::BrowserHandler::GetInstance()->IsClosing())
            {
                Chromium::BrowserHandler::GetInstance()->CloseHostBrowser(false);
                event->ignore();
            }
        }

        void ApplicationMain::showEvent(QShowEvent* event)
        {
            QRect qtrect = application->browserWidget->rect();
            Chromium::BrowserWindows::CreateBrowser("http://www.baidu.com", reinterpret_cast<HWND>(application->browserWidget->winId()), { qtrect.left(), qtrect.top(), qtrect.right(), qtrect.bottom() });
        }

        bool ApplicationMain::eventFilter(QObject* object, QEvent* event)
        {
            if (event->type() == QEvent::Show)
            {
                return false;
            }
            return QMainWindow::eventFilter(object, event);
        }

        void ApplicationMain::AcceptNoticeMessage()
        {
            
        }
    }
}