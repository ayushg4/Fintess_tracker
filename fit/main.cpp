#include <QApplication>
#include "fitnesstracker.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    FitnessTracker mainWindow;
    mainWindow.setWindowTitle("Fitness Tracker");
    mainWindow.show();

    return app.exec();
}
