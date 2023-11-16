#include <iostream>
#include <string>
#include <vector>
#include "fitnesstracker.h"


FitnessTracker::FitnessTracker(QWidget* parent) : QMainWindow(parent) {
    this->setFixedSize(800, 600);
    tabWidget = new QTabWidget(this);

    QLabel* projectTitleLabel = new QLabel("Fitness Tracker", this);
    projectTitleLabel->setStyleSheet("QLabel { font-weight: bold; font-size: 24px; }");

    profileTab = new QWidget(this);
    QVBoxLayout* profileLayout = new QVBoxLayout(profileTab);

    profileSelector = new QComboBox(profileTab);
    profileSelector->setStyleSheet("QComboBox { background-color: #f0f0f0;font-size: 14px; }");
    newProfileButton = new QPushButton("New Profile", profileTab);
    newProfileButton->setStyleSheet("QPushButton { background-color: #4caf50; color: white; }");
    deleteProfileButton = new QPushButton("Delete Profile", profileTab);
    deleteProfileButton->setStyleSheet("QPushButton { background-color: #f44336; color: white; }");
    nameEdit = new QLineEdit(profileTab);
    ageSpinBox = new QSpinBox(profileTab);
    weightSpinBox = new QDoubleSpinBox(profileTab);
    heightSpinBox = new QDoubleSpinBox(profileTab);
    genderEdit = new QLineEdit(profileTab);


    QLabel* nameLabel = new QLabel("Name:", profileTab);
    QLabel* ageLabel = new QLabel("Age:", profileTab);
    QLabel* weightLabel = new QLabel("Weight (kg):", profileTab);
    QLabel* heightLabel = new QLabel("Height (ft):", profileTab);
    QLabel* genderLabel = new QLabel("Gender (M/F):", profileTab);


    nameLabel->setStyleSheet("QLabel { font-weight: bold; font-size: 14px; }");
    ageLabel->setStyleSheet("QLabel { font-weight: bold; font-size: 14px; }");
    weightLabel->setStyleSheet("QLabel { font-weight: bold; font-size: 14px; }");
    heightLabel->setStyleSheet("QLabel { font-weight: bold; font-size: 14px; }");
    genderLabel->setStyleSheet("QLabel { font-weight: bold; font-size: 14px; }");

    profileLayout->addWidget(projectTitleLabel); // Add the project title label
    profileLayout->addWidget(new QLabel("<b style='font-size: 14px'>Profiles:</b>", profileTab));
    profileLayout->addWidget(profileSelector);
    profileLayout->addWidget(new QLabel("If a new user,click on New Profile button below:", profileTab));
    profileLayout->addWidget(newProfileButton);
    profileLayout->addWidget(deleteProfileButton);
    profileLayout->addWidget(nameLabel);
    profileLayout->addWidget(nameEdit);
    profileLayout->addWidget(ageLabel);
    profileLayout->addWidget(ageSpinBox);
    profileLayout->addWidget(weightLabel);
    profileLayout->addWidget(weightSpinBox);
    profileLayout->addWidget(heightLabel);
    profileLayout->addWidget(heightSpinBox);
    profileLayout->addWidget(genderLabel);
    profileLayout->addWidget(genderEdit);

    profileTab->setLayout(profileLayout);

    workoutTab = new QWidget(this);
    QVBoxLayout* workoutLayout = new QVBoxLayout(workoutTab);
    workoutList = new QListWidget(workoutTab);
    recordButton = new QPushButton("Record Workout", workoutTab);
    recordButton->setStyleSheet("QPushButton { background-color: #2196f3; color: white; }");

    workoutLayout->addWidget(workoutList);
    workoutLayout->addWidget(recordButton);
    workoutTab->setLayout(workoutLayout);

    tabWidget->addTab(profileTab, "Profile");
    tabWidget->addTab(workoutTab, "Workout");

    setCentralWidget(tabWidget);

    loadProfiles();

    connect(newProfileButton, SIGNAL(clicked()), this, SLOT(createProfile()));
    connect(deleteProfileButton, SIGNAL(clicked()), this, SLOT(deleteProfile()));
    connect(profileSelector, SIGNAL(currentIndexChanged(int)), this, SLOT(onProfileSelected(int)));
    connect(recordButton, SIGNAL(clicked()), this, SLOT(recordWorkout()));
}

class Workout {
public:
    std::string date;
    std::string exercise;
    double duration;
    double caloriesBurned;
};

class User {
public:
    std::string name;
    int age;
    double weight;
    double height;
    std::string gender;
    std::vector<Workout> workouts;
};


class CustomLinkedList {
private:
    struct Node {
        User data;
        Node* next;
    };

    Node* head;

public:
    CustomLinkedList() : head(nullptr) {}

    ~CustomLinkedList() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void append(const User& user) {
        Node* newNode = new Node;
        newNode->data = user;
        newNode->next = nullptr;

        if (!head) {
            head = newNode;
        } else {
            Node* current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    User& get(int index) {
        Node* current = head;
        int count = 0;
        while (current) {
            if (count == index) {
                return current->data;
            }
            count++;
            current = current->next;
        }
        return head->data;
    }

    int size() const {
        int count = 0;
        Node* current = head;
        while (current) {
            count++;
            current = current->next;
        }
        return count;
    }
};

class FitnessTracker {
private:
    CustomLinkedList profiles;

public:
    void createProfile() {
        User user;
        std::cout << "Enter Name: ";
        std::cin >> user.name;
        std::cout << "Enter Age: ";
        std::cin >> user.age;
        std::cout << "Enter Weight (kg): ";
        std::cin >> user.weight;
        std::cout << "Enter Height (ft): ";
        std::cin >> user.height;
        std::cout << "Enter Gender (M/F): ";
        std::cin >> user.gender;

        profiles.append(user);
        std::cout << "Profile created successfully." << std::endl;
    }

    void recordWorkout() {
        int index;
        std::cout << "Select a profile (enter profile index): ";
        std::cin >> index;

        if (index < 0 || index >= profiles.size()) {
            std::cout << "Invalid profile index." << std::endl;
            return;
        }

        Workout workout;
        workout.date = QDate::currentDate().toString("yyyy-MM-dd");
        bool ok;
        std::cout << "Enter exercise type: ";
        std::cin >> workout.exercise;
        std::cout << "Enter workout duration (minutes): ";
        std::cin >> workout.duration;
        std::cout << "Enter calories burned: ";
        std::cin >> workout.caloriesBurned;

        profiles.get(index).workouts.push_back(workout);
        std::cout << "Workout recorded successfully." << std::endl;
    }

    void displayProfiles() {
        int count = profiles.size();
        if (count == 0) {
            std::cout << "No profiles found." << std::endl;
        } else {
            std::cout << "Profiles:" << std::endl;
            for (int i = 0; i < count; i++) {
                std::cout << i << ". " << profiles.get(i).name << std::endl;
            }
        }
    }

    void displayWorkouts() {
        int index;
        std::cout << "Select a profile (enter profile index): ";
        std::cin >> index;

        if (index < 0 || index >= profiles.size()) {
            std::cout << "Invalid profile index." << std::endl;
            return;
        }

        const User& user = profiles.get(index);
        int workoutCount = user.workouts.size();

        if (workoutCount == 0) {
            std::cout << "No workouts found for " << user.name << std::endl;
        } else {
            std::cout << "Workouts for " << user.name << ":" << std::endl;
            for (int i = 0; i < workoutCount; i++) {
                const Workout& workout = user.workouts[i];
                std::cout << "Date: " << workout.date << ", Exercise: " << workout.exercise
                          << ", Duration: " << workout.duration << " mins, Calories Burned: " << workout.caloriesBurned
                          << " kcal" << std::endl;
            }
        }

    }

};

