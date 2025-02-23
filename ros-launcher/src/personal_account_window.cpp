#include "personal_account_window.h"
#include "ui_personal_account_window.h"

#include <QMessageBox>
#include <utility>

#include "login_window.h"

PersonalAccountWindow::PersonalAccountWindow(API::TokenPair tokenPair, const std::string& username, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PersonalAccountWindow)
    , tokenPair(std::move(tokenPair))
{
    ui->setupUi(this);

    this->setWindowTitle(QString::fromStdString(username + "'s shelter"));

    // Create central widget
    centralWidget = new QWidget(this);
    this->setCentralWidget(centralWidget);

    // Main layout
    mainLayout = new QVBoxLayout(centralWidget);

    // Top section layout
    topLayout = new QHBoxLayout;

    // Logout button
    logoutButton = new QPushButton(centralWidget);
    logoutButton->setText("Log me out");
    logoutButton->setStyleSheet("font-size: 18pt");
    logoutButton->move(10, 10);
    logoutButton->resize(100, 50);

    // Welcome title
    welcomeLabel = new QLabel(centralWidget);
    welcomeLabel->setText(QString::fromStdString("Welcome back, " + username + "."));
    welcomeLabel->setStyleSheet("font-size: 36pt");

    topLayout->addWidget(logoutButton);
    topLayout->addStretch();
    topLayout->addWidget(welcomeLabel);
    topLayout->addStretch();

    mainLayout->addLayout(topLayout);
    mainLayout->addStretch();

    bottomLayout = new QHBoxLayout;
    mainLayout->addLayout(bottomLayout);

    // Play button
    playButton = new QPushButton(centralWidget);
    playButton->setText("Continue your journey");
    playButton->setStyleSheet("font-size: 24pt");
    bottomLayout->addWidget(playButton, 0, Qt::AlignHCenter);

    gameProcess = nullptr;

    // Connecting buttons click signals to handler slots
    connect(playButton, &QPushButton::clicked, this, &PersonalAccountWindow::onPlayButtonClicked);
    connect(logoutButton, &QPushButton::clicked, this, &PersonalAccountWindow::onLogoutButtonClicked);
}

PersonalAccountWindow::~PersonalAccountWindow() {
    delete ui;
    delete centralWidget;
}

void PersonalAccountWindow::onPlayButtonClicked() {
    this->hide();

    // Try launch game
    gameProcess = new QProcess;
    gameProcess->start("../ros-game/realm-of-spells-game");

    // Check if launched successfully
    if (!gameProcess->waitForStarted()) {
        QMessageBox::critical(this, "Error", "Failed to launch the game,.");
        this->show();
        return;
    }

    // Connecting game exit signal to handler slot
    connect(
        gameProcess, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
        this, [this]() { this->show(); }
    );
}

void PersonalAccountWindow::onLogoutButtonClicked() {
    // Ask user if sure
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
