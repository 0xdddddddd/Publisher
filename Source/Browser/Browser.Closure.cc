#include <Browser/Browser.Closure.h>

#include <include/wrapper/cef_closure_task.h>

namespace Cry
{
    namespace Chromium
    {
        BrowserClosure::BrowserClosure()
        {

        }

        BrowserClosure::~BrowserClosure()
        {

        }

        bool BrowserClosure::PostClosure(const base::Closure& closure)
        {
            return CefPostTask(TID_UI, CefCreateClosureTask(closure));
        }

        bool BrowserClosure::PostDelayedClosure(const base::Closure& closure, int64 delay_ms)
        {
            return CefPostDelayedTask(TID_UI, CefCreateClosureTask(closure), delay_ms);
        }
    }
}