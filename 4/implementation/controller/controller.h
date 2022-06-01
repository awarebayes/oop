#pragma once

#include <QObject>
#include <QVector>

#include <cabin/cabin.h>
#include <constants.h>

class Controller : public QObject {
Q_OBJECT
    enum PanelState { FREE, MOVING, REACHED_TARGET_FLOOR, UPDATING_TARGET };

public:
    explicit Controller(QObject *parent = nullptr);

	void handleNewTarget(int floor);

signals:

    void tellCabinToOpen();

	void tellCabinToPrepare();

	void tellCabinToGoOn();


public slots:

	void updatingTarget();

    void handleMoving();

	void handleFree();

	void reachedTargetFloor();

private:
    int curr_floor;
    int main_target;

    std::vector<bool> need_visit;
    PanelState state;
    Direction direction;

	int findNearestMainTarget();
};
