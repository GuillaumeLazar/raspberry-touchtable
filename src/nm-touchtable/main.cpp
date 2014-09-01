#include <QGuiApplication>
#include <QCursor>

#include "qmlhandler.h"

int main(int argc, char *argv[])
{

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

    bool isfakeMode = false;



    if (argc == 2 && strcmp(argv[1], "-fakeMode") == 0){
        isfakeMode = true;
    }
    printf("isfakeMode: %d\n", isfakeMode);



    QmlHandler qmlHandler(isfakeMode);



    return app.exec();
}
