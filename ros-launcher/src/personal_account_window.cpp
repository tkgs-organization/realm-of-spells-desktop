#include "personal_account_window.h"
#include "ui_personal_account_window.h"

#include <QMessageBox>

#include "login_window.h"

PersonalAccountWindow::PersonalAccountWindow(QWidget *parent, const QString& username) :
    QMainWindow(parent), ui(new Ui::PersonalAccountWindow) {
    ui->setupUi(this);

    this->setWindowTitle(username + "'s shelter");

    // create central widget
    centralWidget = new QWidget(this);
    this->setCentralWidget(centralWidget);

    // main layout
    mainLayout = new QVBoxLayout(centralWidget);

    // top section layout
    topLayout = new QHBoxLayout;

    // logout button
    logoutButton = new QPushButton(centralWidget);
    logoutButton->setText("Log me out");
    logoutButton->setStyleSheet("font-size: 18pt");
    logoutButton->move(10, 10);
    logoutButton->resize(100, 50);

    // welcome title
    welcomeLabel = new QLabel(centralWidget);
    welcomeLabel->setText("Welcome back, " + username + ".");
    welcomeLabel->setStyleSheet("font-size: 36pt");

    topLayout->addWidget(logoutButton);
    topLayout->addStretch();
    topLayout->addWidget(welcomeLabel);
    topLayout->addStretch();

    mainLayout->addLayout(topLayout);
    mainLayout->addStretch();

    bottomLayout = new QHBoxLayout;
    mainLayout->addLayout(bottomLayout);

    // play button
    playButton = new QPushButton(centralWidget);
    playButton->setText("Continue your journey");
    playButton->setStyleSheet("font-size: 24pt");
    bottomLayout->addWidget(playButton, 0, Qt::AlignHCenter);

    gameProcess = nullptr;

    // connecting buttons release signals to handler slots
    connect(playButton, &QPushButton::released, this, &PersonalAccountWindow::OnPlayButtonPressed);
    connect(logoutButton, &QPushButton::released, this, &PersonalAccountWindow::OnLogoutButtonPressed);
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

void PersonalAccountWindow::OnLogoutButtonPressed() {
    // warning message box
    QMessageBox msgBox;
    msgBox.setText("Are you sure you want to logout?");
    msgBox.addButton("Yes", QMessageBox::YesRole);
    msgBox.addButton("No", QMessageBox::NoRole);

    const auto reply = QMessageBox::question(
        this,
        "Logout",
        "Are you sure you want to logout?",
        QMessageBox::Yes | QMessageBox::No
    );

    switch (reply) {
        case QMessageBox::Yes: {
            this->close();

            auto *loginWindow = new LoginWindow;
            loginWindow->setAttribute(Qt::WA_DeleteOnClose);
            loginWindow->show();

            // todo: potentially other logout logic
            break;
        }
        default: break;
    }
}
