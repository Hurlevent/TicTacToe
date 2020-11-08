#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>


#include <QStandardItemModel>

#include "TicTocTableModel.h"



// TODO: I think I should create the UI first, and the AI opponent second.

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);


    /*QStandardItemModel model(3,3);

    for(auto row = 0; row < model.rowCount(); ++row){
        for(auto column = 0; column < model.columnCount(); ++column){

        }
    }*/



    qmlRegisterType<TicTocTableModel>("TicTocTable", 1, 0, "TicTocTableModel");


    TicTocTableModel model;

    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty(QStringLiteral("_model"), &model);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
