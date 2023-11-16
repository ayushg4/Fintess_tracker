#ifndef PROFILEMANAGER_H
#define PROFILEMANAGER_H

#include "user.h"
#include <QVector>
#include <QSettings>

class ProfileManager {
public:
    ProfileManager();
    QVector<User> loadProfiles();
    void saveProfiles(const QVector<User>& users);

private:
    QSettings settings;
};

#endif
