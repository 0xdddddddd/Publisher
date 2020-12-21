#ifndef __QWindows_Entry_H__
#define __QWindows_Entry_H__
#include <platform.h>
#include <memory>

namespace Cry
{
    namespace Gui
    {
        class ApplicationMain;
    }
    
    class QApplication;
    class ProgramEntry
    {
    public:
        explicit ProgramEntry();
        virtual ~ProgramEntry();
    public:
        int32 ExecApplication(int32 argc, String argv[]);
    private:
    };
}
#endif // __QWindows_Entry_H__

