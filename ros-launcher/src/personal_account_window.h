#ifndef PERSONAL_ACCOUNT_WINDOW_H
#define PERSONAL_ACCOUNT_WINDOW_H

#include <QMainWindow>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QProcess>

#include "api.hpp"


QT_BEGIN_NAMESPACE
namespace Ui { class PersonalAccountWindow; }
QT_END_NAMESPACE

class PersonalAccountWindow : public QMainWindow {
Q_OBJECT

public:
    PersonalAccountWindow(
        API::TokenPair tokenPair,
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

private:
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

};


#endif //PERSONAL_ACCOUNT_WINDOW_H
