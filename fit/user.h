#ifndef USER_H
#define USER_H

#include <QString>
#include <QVector>
#include "workout.h"

struct User {
    QString name;
    int age;
    double weight;
    double height;
    QString gender;
    QVector<Workout> workouts;
};

#endif // USER_H
