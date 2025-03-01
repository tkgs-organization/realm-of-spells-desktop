#include "login_window.h"

#include <iostream>
#include <ui_personal_account_window.h>

#include "personal_account_window.h"
#include "ui_login_window.h"

LoginWindow::LoginWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // create central widget
    centralWidget = new QWidget(this);
    this->setCentralWidget(centralWidget);

    // title
    titleLabel = new QLabel(centralWidget);
    titleLabel->setText("Realm of Spells");
    titleLabel->setStyleSheet("font-size: 56pt");
    titleLabel->setAlignment(Qt::AlignCenter);

    // subtitle
    subtitleLabel = new QLabel(centralWidget);
    subtitleLabel->setText("The Online Duelling Card Game");
    subtitleLabel->setStyleSheet("font-size: 24pt");
    subtitleLabel->setAlignment(Qt::AlignCenter);

    // login text field
    loginLineEdit = new QLineEdit(centralWidget);
    loginLineEdit->setMaximumWidth(150);
    loginLineEdit->setPlaceholderText("Username");
    loginLineEdit->setAlignment(Qt::AlignCenter);

    // password text field
    passwordLineEdit = new QLineEdit(centralWidget);
    passwordLineEdit->setEchoMode(QLineEdit::Password);
    passwordLineEdit->setMaximumWidth(150);
    passwordLineEdit->setPlaceholderText("Password");
    passwordLineEdit->setAlignment(Qt::AlignCenter);

    // login button
    loginButton = new QPushButton(centralWidget);
    loginButton->setText("Login");
    loginButton->setMaximumWidth(100);
    loginButton->setStyleSheet("font-size: 18pt;");

    // register link
    registrationLink = new QLabel(centralWidget);
    registrationLink->setText(R"(<a href="https://tkgs-organization.github.io/realm-of-spells-website/registration">Dont have an account yet?</a>)");
    registrationLink->setTextFormat(Qt::RichText);
    registrationLink->setTextInteractionFlags(Qt::TextBrowserInteraction);
    registrationLink->setOpenExternalLinks(true);
    registrationLink->setAlignment(Qt::AlignCenter);

    // layout
    layout = new QVBoxLayout(centralWidget);

    // adding all the widgets to the layout
    layout->addWidget(titleLabel);
    layout->addWidget(subtitleLabel);
    layout->addStretch();
    layout->addWidget(loginLineEdit, 0, Qt::AlignHCenter);
    layout->addWidget(passwordLineEdit, 0, Qt::AlignHCenter);
    layout->addWidget(loginButton, 0, Qt::AlignHCenter);
    layout->addStretch();
    layout->addWidget(registrationLink);

    // connecting login button release signal to a custom login handler
    connect(loginButton, &QPushButton::released, this, &LoginWindow::handleLogin);
}

LoginWindow::~LoginWindow() {
    delete ui;
    delete centralWidget; // also deletes all children
}

void LoginWindow::handleLogin() {
    qDebug() << "Assuming login was successful. Opening personal shelter.";

    this->close();

    // proceed to player's personal shelter
    auto *shelter = new PersonalAccountWindow(nullptr, loginLineEdit->text());
    shelter->setAttribute(Qt::WA_DeleteOnClose); // automatically frees memory allocated for this window
    shelter->show();
}
