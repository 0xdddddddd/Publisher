#ifndef __ApplicationMain_H__
#define __ApplicationMain_H__
#include <platform.h>
#include <memory>

#include <QMainWindow>
#include <QWidget>

#include <QAbstractNativeEventFilter>
#include <QAbstractEventDispatcher>
#include <QCloseEvent>
#include <include/cef_task.h>
#include <include/base/cef_callback_forward.h>
namespace Cry
{
    namespace Chromium
    {
        class BrowserWindows;
    }

    namespace Ui
    {
        class ApplicationMain;
    }

    namespace Gui
    {
        class ApplicationMain : public QMainWindow, public QAbstractNativeEventFilter
        {
        public:
            Q_OBJECT;
        public:
            explicit ApplicationMain(QWidget* Widget = nullptr);
            virtual ~ApplicationMain();
        public:
            void OpenBrowser();
        private:
            virtual bool nativeEvent(const QByteArray& EventType, void* pMessage, long* pResult) override;
            virtual bool nativeEventFilter(const QByteArray& EventType, void* pMessage, long* pResult) override;
            virtual void resizeEvent(QResizeEvent* event) override;
            virtual void closeEvent(QCloseEvent* event) override;
            virtual void showEvent(QShowEvent* event) override;
        private:
            virtual bool eventFilter(QObject* object, QEvent* event) override;
        signals:
            void SubmitNoticeMessage();
        private:
            void AcceptNoticeMessage();
        private:
            QString                                                     args;
            std::unique_ptr<Ui::ApplicationMain>                        application;
            std::unique_ptr<Chromium::BrowserWindows>                   browserWindows;
        };
    }
}
#endif // __ApplicationMain_H__