#include <Entrance/QWindows.Entry.h>
#include <iostream>
#include <QtPlugin>
#include <QApplication>
#include <QMetaType>

#include <qt-platform.h>

#include <Interface/ApplicationMain.h>

namespace Cry
{
    ProgramEntry::ProgramEntry()
    {
        
    }

    ProgramEntry::~ProgramEntry()
    {

    }

    int32 ProgramEntry::ExecApplication(int32 argc, String argv[])
    {
//         QApplication app(argc, argv);
//         Gui::ApplicationMain win;
//         win.show();
//         return app.exec();

        return 0;
    }
}