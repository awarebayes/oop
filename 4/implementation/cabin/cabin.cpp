#include "cabin/cabin.h"

#include <QString>

#include <QDebug>


Cabin::Cabin(QObject *parent) : QObject(parent),
                                state(Cabin::State::UNLOCKED) {

    pass_floor_timer.setSingleShot(true);

    QObject::connect(this, SIGNAL(tellDoorsToOpen()), &this->doors, SLOT(doorsOpening()));
    QObject::connect(&this->doors, SIGNAL(closed()), this, SLOT(cabinUnlocking()));
}

void Cabin::cabinMoving() {
    if (this->state != State::PREPARING && this->state != State::MOVING) return;

    if (this->state == State::PREPARING)
        this->state = State::MOVING;

    this->pass_floor_timer.start(ONE_FLOOR_PASS_TIME);
}

void Cabin::cabinStopping() {
    if (this->state != State::MOVING) return;

    this->state = State::STOPPED;
    qDebug() << "Кабина остановилась";

    emit cabinLocking();
}

void Cabin::cabinPreparing() {
    if (this->state != State::UNLOCKED) return;

    this->state = State::PREPARING;

    qDebug() << "Кабина готовится двигаться";

    emit cabinMoving();
}

void Cabin::cabinLocking() {
    if (this->state != State::STOPPED) return;

    this->state = State::LOCKED;
    qDebug() << "Движение кабины заблокировано";

    emit tellDoorsToOpen();
}

void Cabin::cabinUnlocking() {
    if (this->state != State::LOCKED) return;

    this->state = State::UNLOCKED;
    qDebug() << "Движение кабины разблокировано";

    emit tellControllerIAmUnlocked();
}
