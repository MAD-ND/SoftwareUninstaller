#include "uninstaller.h"
#include <QSettings>
#include <QDebug>

Uninstaller::Uninstaller()
{
}

QList<SoftwareInfo> Uninstaller::getInstalledSoftware()
{
    QList<SoftwareInfo> softwareList;
    
    // Read both 32-bit and 64-bit registry locations
    softwareList += readRegistry("HKEY_LOCAL_MACHINE\\Software\\Microsoft\\Windows\\CurrentVersion\\Uninstall");
    softwareList += readRegistry("HKEY_LOCAL_MACHINE\\Software\\Wow6432Node\\Microsoft\\Windows\\CurrentVersion\\Uninstall");
    softwareList += readRegistry("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Uninstall");

    return softwareList;
}

QList<SoftwareInfo> Uninstaller::readRegistry(const QString &registryPath)
{
    QList<SoftwareInfo> list;
    QSettings settings(registryPath, QSettings::NativeFormat);
    
    foreach (const QString &subKey, settings.childGroups()) {
        settings.beginGroup(subKey);
        
        SoftwareInfo info;
        info.name = settings.value("DisplayName").toString();
        info.uninstallString = settings.value("UninstallString").toString();
        
        if (!info.name.isEmpty() && !info.uninstallString.isEmpty()) {
            list.append(info);
        }
        
        settings.endGroup();
    }
    
    return list;
}

bool Uninstaller::uninstallSoftware(const QString &uninstallString)
{
    if (uninstallString.isEmpty()) return false;

    // Extract command and arguments
    QString cmd = uninstallString;
    QString args;
    
    if (cmd.startsWith('"')) {
        cmd = cmd.mid(1, cmd.indexOf('"', 1) - 1);
        args = uninstallString.mid(cmd.length() + 2).trimmed();
    } else {
        int spaceIndex = cmd.indexOf(' ');
        if (spaceIndex != -1) {
            args = cmd.mid(spaceIndex + 1);
            cmd = cmd.left(spaceIndex);
        }
    }

    // Execute uninstall command
    QProcess process;
    process.start(cmd, args.split(' '));
    return process.waitForFinished(-1) && process.exitCode() == 0;
}
