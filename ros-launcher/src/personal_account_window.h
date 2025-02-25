#ifndef PERSONAL_ACCOUNT_WINDOW_H
#define PERSONAL_ACCOUNT_WINDOW_H

#include <QMainWindow>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QProcess>

#include "ros-library/token_pair.h"

#include <thread>


QT_BEGIN_NAMESPACE
namespace Ui { class PersonalAccountWindow; }
QT_END_NAMESPACE

class PersonalAccountWindow : public QMainWindow {
Q_OBJECT

public:
    PersonalAccountWindow(
        const API::TokenPair& tokenPair,
        const std::string& username,
        QWidget *parent = nullptr
    );

    ~PersonalAccountWindow() override;

private slots:
    // Handles play button click signal.
    // Hides player's shelter window and launches the game.
    void onPlayButtonClicked();

    // Handles Logout button click signal.
    // Logs user out.
    void onLogoutButtonClicked();

    // Handles failure.
    // Shows message box and logs user out.
    void onFailure(const std::string& detail);

signals:
    void failure(const std::string& detail);

private:
    // Logs user out
    void logout();

    // Tries refreshing access token
    void tokenRefreshTask();

    // Overrides base window close event
    void closeEvent(QCloseEvent *event) override;

    Ui::PersonalAccountWindow *ui;
    QWidget *centralWidget;

    // Main window layout
    QVBoxLayout *mainLayout;

    // Sections layouts
    QHBoxLayout *topLayout;
    QHBoxLayout *bottomLayout;

    QLabel *welcomeLabel;

    QPushButton *playButton;
    QPushButton *logoutButton;

    QProcess *gameProcess;

    // Token pair
    API::TokenPair tokenPair;

    // A flag indicating whether the user is active or not.
    // Used in multiple threads.
    std::atomic<bool> active;

    std::thread tokenRefreshThread;
    // Condition variable for token refresh loop
    std::condition_variable tokenRefreshCV;

};


#endif //PERSONAL_ACCOUNT_WINDOW_H
