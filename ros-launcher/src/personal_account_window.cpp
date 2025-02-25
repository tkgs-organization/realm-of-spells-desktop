#include "personal_account_window.h"
#include "ui_personal_account_window.h"

#include <QMessageBox>

#include <chrono>

#include "login_window.h"

PersonalAccountWindow::PersonalAccountWindow(const API::TokenPair& tokenPair, const std::string& username, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PersonalAccountWindow)
    , tokenPair(tokenPair.getAccess(), tokenPair.getRefresh())
    , active(true)
    , tokenRefreshThread(&PersonalAccountWindow::tokenRefreshTask, this)
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
    connect(this, &PersonalAccountWindow::failure, this, &PersonalAccountWindow::onFailure);
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
            // Logout and close current window
            this->close();
            break;
        }
        default: break;
    }
}

void PersonalAccountWindow::onFailure(const std::string &detail) {
    QMessageBox::critical(
        this,
        "Error",
        (std::string("Something went wrong.\nDetails: ") + std::string(detail)).c_str()
    );
    this->close();
}

void PersonalAccountWindow::logout() {
    this->active = false;
    // Notifying all the waiting threads
    this->tokenRefreshCV.notify_all();
    // Joining token refresh task thread
    this->tokenRefreshThread.join();
}

void PersonalAccountWindow::tokenRefreshTask() {
    std::mutex tokenRefreshCVMutex;

    while (this->active) {
        // Wait with a condition variable
        std::unique_lock lock(tokenRefreshCVMutex);
        if (tokenRefreshCV.wait_for(lock, std::chrono::seconds(5), [this]() {
            return !this->active;
        })) {
            break; // End the task. User is no longer active
        }

        // Handle failure
        auto result = this->tokenPair.refresh();
        if (!result.ok) emit failure(result.message);
    }
}

void PersonalAccountWindow::closeEvent(QCloseEvent *event) {
    // Logging the user out
    this->logout();

    // Back to main window
    auto *loginWindow = new LoginWindow;
    loginWindow->setAttribute(Qt::WA_DeleteOnClose);
    loginWindow->show();

    QWidget::closeEvent(event);
}
