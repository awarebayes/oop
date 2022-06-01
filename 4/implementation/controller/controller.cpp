#include <controller/controller.h>
#include <QDebug>

Controller::Controller(QObject *parent) : QObject(parent), curr_floor(START_FLOOR), main_target(NO_TARGET),
                                          need_visit(NUM_OF_FLOORS, false), state(FREE),
                                          direction(STAY) {
}

int Controller::findNearestMainTarget() {
	bool is_updated = false;
	int min_distance = 9999;
	int potential_next_floor = -1;


	for (int i = 0; i < this->need_visit.size(); i++)
	{
		if (need_visit[i])
		{
			int distance = abs(i - curr_floor);
			if (distance < min_distance)
			{
				is_updated = true;
				min_distance = distance;
				potential_next_floor = i + 1;
			}
		}
	}

	if (is_updated)
		return potential_next_floor;
	return -1;
}

void Controller::handleNewTarget(const int floor)
{
	if (this->need_visit[floor - 1]) return;
	this->need_visit[floor - 1] = true;
	if (state != REACHED_TARGET_FLOOR)
		emit updatingTarget(); // сам вызывается после того, как пассажиры зашли!!!
}

// ___________________________________________

void Controller::handleMoving()
{
  if (state != UPDATING_TARGET and state != MOVING) return;
  state = MOVING;

  this->curr_floor += this->direction;
  qDebug() << "Этаж №" << this->curr_floor << "| Лифт приехал";

  if (this->curr_floor != this->main_target)
    emit tellCabinToGoOn();
  else
    emit reachedTargetFloor();
}

void Controller::handleFree()
{
	if (state != UPDATING_TARGET) return;
	this->state = FREE;
}

void Controller::reachedTargetFloor()
{
	if (state != MOVING) return;
	this->state = REACHED_TARGET_FLOOR;
	need_visit[curr_floor - 1] = false;
	qDebug() << "Этаж №" << this->curr_floor << "| Лифт остановился";
	emit tellCabinToOpen();
}

void Controller::updatingTarget()
{
	if (state != FREE and state != REACHED_TARGET_FLOOR) return;
	state = UPDATING_TARGET;

	int next_floor = findNearestMainTarget();
	if (next_floor != -1)
	{
		main_target = next_floor;
		direction = main_target < curr_floor ? DOWN : UP;
		emit tellCabinToPrepare();
	}
	else
		emit handleFree();
}


