#include "profilemanager.h"

ProfileManager::ProfileManager() : settings("YourCompany", "FitnessTracker") {}

QVector<User> ProfileManager::loadProfiles() {
    QVector<User> users;
    int size = settings.beginReadArray("users");
    for (int i = 0; i < size; ++i) {
        settings.setArrayIndex(i);
        User user;
        user.name = settings.value("name").toString();
        user.age = settings.value("age").toInt();
        user.weight = settings.value("weight").toDouble();

        // Load the new fields: height and gender
        user.height = settings.value("height").toDouble();
        user.gender = settings.value("gender").toString();

        // Load workouts for each user
        int workoutsSize = settings.beginReadArray("workouts");
        for (int j = 0; j < workoutsSize; ++j) {
            settings.setArrayIndex(j);
            Workout workout;
            workout.date = settings.value("date").toString();
            workout.exercise = settings.value("exercise").toString();
            workout.duration = settings.value("duration").toDouble();
            workout.caloriesBurned = settings.value("caloriesBurned").toDouble();
            user.workouts.push_back(workout);
        }
        settings.endArray(); // End of workouts

        users.push_back(user);
    }
    settings.endArray(); // End of users
    return users;
}

void ProfileManager::saveProfiles(const QVector<User>& users) {
    settings.beginWriteArray("users");
    for (int i = 0; i < users.size(); ++i) {
        settings.setArrayIndex(i);
        settings.setValue("name", users[i].name);
        settings.setValue("age", users[i].age);
        settings.setValue("weight", users[i].weight);

        // Save the new fields: height and gender
        settings.setValue("height", users[i].height);
        settings.setValue("gender", users[i].gender);

        // Save workouts for each user
        settings.beginWriteArray("workouts");
        for (int j = 0; j < users[i].workouts.size(); ++j) {
            settings.setArrayIndex(j);
            settings.setValue("date", users[i].workouts[j].date);
            settings.setValue("exercise", users[i].workouts[j].exercise);
            settings.setValue("duration", users[i].workouts[j].duration);
            settings.setValue("caloriesBurned", users[i].workouts[j].caloriesBurned);
        }
        settings.endArray(); // End of workouts
    }
    settings.endArray(); // End of users
}
