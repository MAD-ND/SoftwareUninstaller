#include "mainwindow.h"
#include <QMessageBox>
#include <QHeaderView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), uninstaller(new Uninstaller())
{
    setupUI();
    refreshSoftwareList();
}

MainWindow::~MainWindow()
{
    delete uninstaller;
}

void MainWindow::setupUI()
{
    setWindowTitle("Software Uninstaller");
    setMinimumSize(800, 600);

    // Central widget and main layout
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    // Software list
    softwareList = new QListWidget(this);
    softwareList->setSelectionMode(QAbstractItemView::ExtendedSelection);
    mainLayout->addWidget(softwareList);

    // Control buttons
    QHBoxLayout *btnLayout = new QHBoxLayout();
    
    selectAllBtn = new QPushButton("Select All", this);
    connect(selectAllBtn, &QPushButton::clicked, this, &MainWindow::onSelectAllClicked);
    btnLayout->addWidget(selectAllBtn);

    uninstallBtn = new QPushButton("Uninstall Selected", this);
    connect(uninstallBtn, &QPushButton::clicked, this, &MainWindow::onUninstallClicked);
    btnLayout->addWidget(uninstallBtn);

    mainLayout->addLayout(btnLayout);
    setCentralWidget(centralWidget);
}

void MainWindow::refreshSoftwareList()
{
    softwareList->clear();
    QList<SoftwareInfo> software = uninstaller->getInstalledSoftware();
    
    for (const auto &info : software) {
        QListWidgetItem *item = new QListWidgetItem(info.name);
        item->setData(Qt::UserRole, info.uninstallString);
        softwareList->addItem(item);
    }
}

void MainWindow::onSelectAllClicked()
{
    bool select = (softwareList->selectedItems().size() != softwareList->count());
    for (int i = 0; i < softwareList->count(); ++i) {
        softwareList->item(i)->setSelected(select);
    }
}

void MainWindow::onUninstallClicked()
{
    QList<QListWidgetItem*> selected = softwareList->selectedItems();
    if (selected.isEmpty()) {
        QMessageBox::information(this, "Info", "No software selected");
        return;
    }

    for (auto item : selected) {
        QString uninstallString = item->data(Qt::UserRole).toString();
        if (uninstaller->uninstallSoftware(uninstallString)) {
            delete item;
        }
    }
}
