#include "personal_account_window.h"
#include "ui_personal_account_window.h"

#include <QMessageBox>

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
    playButton->setText("Continue your journey");
    playButton->setStyleSheet("font-size: 24pt");

    // layout
    layout = new QVBoxLayout(centralWidget);

    // adding all the widgets
    layout->addWidget(welcomeLabel, 0, Qt::AlignCenter);
    layout->addStretch();
    layout->addWidget(playButton, 0, Qt::AlignCenter);

    connect(playButton, &QPushButton::released, this, &PersonalAccountWindow::OnPlayButtonPressed);
}

PersonalAccountWindow::~PersonalAccountWindow() {
    delete ui;
}

void PersonalAccountWindow::OnPlayButtonPressed() {
    this->hide();

    // launch game
    gameProcess = new QProcess;
    gameProcess->start("../ros-game/realm-of-spells-game");

    // check if launched successfully
    if (!gameProcess->waitForStarted()) {
        QMessageBox::critical(this, "Error", "Failed to launch the game,.");
        this->show();
        return;
    }

    // handling game exit
    connect(
        gameProcess, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
        this, [this]() { this->show(); }
    );
}
