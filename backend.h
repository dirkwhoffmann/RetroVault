#pragma once

#include <QObject>
#include <QDebug>
#include <QTimer>

class Backend : public QObject
{
    Q_OBJECT
public:
    explicit Backend(QObject *parent = nullptr) : QObject(parent)
    {
        QTimer *timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, [this]() {
            static int count = 0;
            emit statusChanged("Update #" + QString::number(++count));
        });
        timer->start(3000);
    }

    // Q_INVOKABLE makes this function callable from QML
    Q_INVOKABLE void handleButtonClick(const QString &message) {
        qDebug() << "C++ received message from QML:" << message;
        updateFinished("Holla, die Waldfee");
    }

    signals:
    // This signal carries the new text for our text field
    void statusChanged(QString newStatus);
    void updateFinished(QString newText);
};
