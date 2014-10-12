#include <QGuiApplication>
#include <QApplication>
#include <QCursor>

#include "MainWindow.h"
#include "QmlHandler.h"


int main(int argc, char *argv[])
{
    bool isfakeMode = false;
    bool isMonitorMode = false;

    if (argc >= 2 && strcmp(argv[1], "-fakeMode") == 0){
        isfakeMode = true;
    }

    if (argc >= 2 && strcmp(argv[1], "-monitor") == 0){
        isMonitorMode = true;
    }

    printf("isfakeMode: %d\n", isfakeMode);
    printf("isMonitorMode: %d\n", isMonitorMode);


    if (isMonitorMode){
        QApplication app(argc, argv);
        MainWindow w(isfakeMode);
        w.show();
        return app.exec();

    }else{
        QByteArray data = "1";
        bool putOk = false;
        putOk = qputenv("QML_SHOW_FRAMERATE", data);
        printf("QML_SHOW_FRAMERATE is OK: %d\n", putOk);

        putOk = qputenv("QML_RENDER_TIMING", data);
        printf("QML_RENDER_TIMING is OK: %d\n", putOk);

        putOk = qputenv("QML_WINDOW_TIMING", data);
        printf("QML_WINDOW_TIMING is OK: %d\n", putOk);

        putOk = qputenv("QML_CANVAS_TIMING", data);
        printf("QML_CANVAS_TIMING is OK: %d\n", putOk);

        QGuiApplication app(argc, argv);
        app.setOverrideCursor((QCursor(Qt::ArrowCursor)));
        QmlHandler qmlHandler(isfakeMode);
        return app.exec();
    }
}
