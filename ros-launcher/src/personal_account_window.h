#ifndef PERSONAL_ACCOUNT_WINDOW_H
#define PERSONAL_ACCOUNT_WINDOW_H

#include <QMainWindow>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QProcess>


QT_BEGIN_NAMESPACE
namespace Ui { class PersonalAccountWindow; }
QT_END_NAMESPACE

class PersonalAccountWindow : public QMainWindow {
Q_OBJECT

public:
    explicit PersonalAccountWindow(QWidget *parent = nullptr, const QString& username = "unknown traveler");
    ~PersonalAccountWindow() override;

private slots:
    void OnPlayButtonPressed();
    void OnLogoutButtonPressed();

private:
    Ui::PersonalAccountWindow *ui;
    QWidget *centralWidget;

    //main window layout
    QVBoxLayout *mainLayout;

    // sections layouts
    QHBoxLayout *topLayout;
    QHBoxLayout *bottomLayout;

    QLabel *welcomeLabel;

    QPushButton *playButton;
    QPushButton *logoutButton;

    QProcess *gameProcess;

};


#endif //PERSONAL_ACCOUNT_WINDOW_H
