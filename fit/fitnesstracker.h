#ifndef FITNESSTRACKER_H
#define FITNESSTRACKER_H

#include <QtWidgets>
#include "user.h"
#include "workout.h"
#include "profilemanager.h"

class FitnessTracker : public QMainWindow {
    Q_OBJECT

public:
    FitnessTracker(QWidget* parent = nullptr);

private slots:
    void createProfile();
    void deleteProfile();
    void onProfileSelected(int index);
    void recordWorkout();

private:
    QTabWidget* tabWidget;
    QWidget* profileTab;
    QWidget* workoutTab;
    QComboBox* profileSelector;
    QPushButton* newProfileButton;
    QPushButton* deleteProfileButton;
    QLineEdit* nameEdit;
    QSpinBox* ageSpinBox;
    QDoubleSpinBox* weightSpinBox;
    QDoubleSpinBox* heightSpinBox;
    QLineEdit* genderEdit;
    QListWidget* workoutList;
    QPushButton* recordButton;

    ProfileManager profileManager;
    QVector<User> users;
    int currentUserID;

    void loadProfiles();
    void updateProfileUI();
};

#endif
