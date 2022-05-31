#pragma once

#include <QObject>

#include <constants.h>
#include <controller/controller.h>
#include <doors/doors.h>

class Cabin : public QObject {
Q_OBJECT
private:

friend class Elevator;
QTimer pass_floor_timer;

public:
    explicit Cabin(QObject *parent = nullptr);
    enum class State { MOVING, STOPPED, LOCKED, UNLOCKED, PREPARING };

signals:

    void tellControllerIAmUnlocked();

    void tellDoorsToOpen();

public slots:

    void cabinLocking();

    void cabinUnlocking();

    void cabinPreparing();

    void cabinMoving();

    void cabinStopping();


private:
    Cabin::State state;
    Doors doors;
};
