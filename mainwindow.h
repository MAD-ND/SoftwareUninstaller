#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QPushButton>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "uninstaller.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onSelectAllClicked();
    void onUninstallClicked();
    void refreshSoftwareList();

private:
    QListWidget *softwareList;
    QPushButton *selectAllBtn;
    QPushButton *uninstallBtn;
    Uninstaller *uninstaller;
    void setupUI();
};

#endif // MAINWINDOW_H
