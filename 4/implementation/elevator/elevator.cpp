#include "elevator/elevator.h"

Elevator::Elevator() {
    QObject::connect(&cabin.pass_floor_timer, SIGNAL(timeout()), &controller, SLOT(handleMoving()));
	QObject::connect(&cabin, SIGNAL(tellControllerIAmUnlocked()), &controller, SLOT(updatingTarget()));
	QObject::connect(&controller, SIGNAL(tellCabinToGoOn()), &cabin, SLOT(cabinMoving()));
    QObject::connect(&controller, SIGNAL(tellCabinToPrepare()), &cabin, SLOT(cabinPreparing()));
    QObject::connect(&controller, SIGNAL(tellCabinToStop()), &cabin, SLOT(cabinStopping()));
	QObject::connect(&controller, SIGNAL(tellCabinDoorsToOpen()), &cabin, SIGNAL(tellDoorsToOpen()));
}

void Elevator::click_btn(const int btn_number) {
    controller.handleNewTarget(btn_number);
}
