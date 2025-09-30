#ifndef UNINSTALLER_H
#define UNINSTALLER_H

#include <QString>
#include <QList>
#include <QProcess>

struct SoftwareInfo {
    QString name;
    QString uninstallString;
};

class Uninstaller
{
public:
    Uninstaller();
    QList<SoftwareInfo> getInstalledSoftware();
    bool uninstallSoftware(const QString &uninstallString);

private:
    QList<SoftwareInfo> readRegistry(const QString &registryPath);
};

#endif // UNINSTALLER_H
