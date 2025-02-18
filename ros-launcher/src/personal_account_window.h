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

private:
    Ui::PersonalAccountWindow *ui;
    QWidget *centralWidget;
    QVBoxLayout *layout;

    // welcome title
    QLabel *welcomeLabel;

    // play button
    QPushButton *playButton;

    // game process
    QProcess *gameProcess;

};


#endif //PERSONAL_ACCOUNT_WINDOW_H
