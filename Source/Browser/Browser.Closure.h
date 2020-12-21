#pragma once
#ifndef __Browser_Closure_H__
#define __Browser_Closure_H__

#include <platform.h>

#include <include/cef_task.h>
#include <include/base/cef_callback_forward.h>

namespace Cry
{
    namespace Chromium
    {
        class BrowserClosure
        {
        public:
            explicit BrowserClosure();
            virtual ~BrowserClosure();
        public:
            static bool PostClosure(const base::Closure& closure);
            static bool PostDelayedClosure(const base::Closure& closure, int64 delay_ms = 3);
        };
    }
}
#endif // __Browser_Closure_H__