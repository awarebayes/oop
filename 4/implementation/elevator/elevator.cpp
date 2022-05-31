#include "elevator/elevator.h"

Elevator::Elevator() {
    QObject::connect(&cabin.pass_floor_timer, SIGNAL(timeout()), &controller, SLOT(callbackAfterFloorPassed()));
    QObject::connect(&controller, SIGNAL(tellCabinToGoOn()), &cabin, SLOT(cabinMoving()));
    QObject::connect(&controller, SIGNAL(targetIsSet(int, Direction)), &cabin, SLOT(cabinPreparing()));
    QObject::connect(&controller, SIGNAL(tellCabinToOpen()), &cabin, SLOT(cabinStopping()));
    QObject::connect(&cabin, SIGNAL(tellControllerIAmUnlocked()), &controller, SLOT(targetUpdating()));
}

void Elevator::click_btn(const int btn_number) {
    controller.setTarget(btn_number);
}
