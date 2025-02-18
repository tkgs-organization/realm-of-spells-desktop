#include "personal_account_window.h"
#include "ui_personal_account_window.h"

PersonalAccountWindow::PersonalAccountWindow(QWidget *parent, const QString& username) :
    QMainWindow(parent), ui(new Ui::PersonalAccountWindow) {
    ui->setupUi(this);

    this->setWindowTitle(username + "'s shelter");

    // create central widget
    centralWidget = new QWidget(this);
    this->setCentralWidget(centralWidget);

    // welcome title
    welcomeLabel = new QLabel(centralWidget);
    welcomeLabel->setText("Welcome back, " + username + ".");
    welcomeLabel->setStyleSheet("font-size: 36pt");

    // play button
    playButton = new QPushButton(centralWidget);
    playButton->setText("Play");
    playButton->setStyleSheet("font-size: 18pt");

    // layout
    layout = new QVBoxLayout(centralWidget);

    // adding all the widgets
    layout->addWidget(welcomeLabel, 0, Qt::AlignCenter);
    layout->addStretch();
    layout->addWidget(playButton, 0, Qt::AlignCenter);
}

PersonalAccountWindow::~PersonalAccountWindow() {
    delete ui;
}
