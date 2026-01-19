/********************************************************************************
** Form generated from reading UI file 'applicgaragewindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_APPLICGARAGEWINDOW_H
#define UI_APPLICGARAGEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ApplicGarageWindow
{
public:
    QAction *actionLogin;
    QAction *actionLogout;
    QAction *actionQuit;
    QAction *actionNewModel;
    QAction *actionNewOption;
    QAction *actionNouveau;
    QAction *actionCharger;
    QAction *actionEnregistrer;
    QAction *actionAddEmployee;
    QAction *actionDeleteEmployeeById;
    QAction *actionDeleteEmployeeByIndex;
    QAction *actionAddClient;
    QAction *actionDeleteClientById;
    QAction *actionDeleteClientByIndex;
    QAction *actionResetPassword;
    QWidget *centralwidget;
    QFrame *frame;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QLabel *label_2;
    QLineEdit *lineEditProjectName;
    QLabel *label_3;
    QLineEdit *lineEditModelName;
    QLabel *label_4;
    QLineEdit *lineEditPower;
    QRadioButton *radioButtonPetrol;
    QRadioButton *radioButtonElectric;
    QRadioButton *radioButtonDiesel;
    QRadioButton *radioButtonHybrid;
    QLabel *label_5;
    QLineEdit *lineEditBasePrice;
    QComboBox *comboBoxAvailableModels;
    QLabel *label_6;
    QPushButton *pushButtonSelectModel;
    QLabel *label_7;
    QComboBox *comboBoxAvailableOptions;
    QPushButton *pushButtonAddOption;
    QLabel *label_8;
    QTableWidget *tableWidgetOptions;
    QPushButton *pushButtonRemoveOption;
    QPushButton *pushButtonReduction;
    QLabel *label_9;
    QLineEdit *lineEditPrice;
    QPushButton *pushButtonOpenProject;
    QPushButton *pushButtonSaveProject;
    QPushButton *pushButtonNewProject;
    QLabel *label;
    QLabel *label_10;
    QTableWidget *tableWidgetEmployees;
    QLabel *label_11;
    QTableWidget *tableWidgetClients;
    QLabel *label_12;
    QTableWidget *tableWidgetContracts;
    QPushButton *pushButtonNewContract;
    QPushButton *pushButtonDeleteContract;
    QPushButton *pushButtonShowCar;
    QMenuBar *menubar;
    QMenu *menuConnexion;
    QMenu *menuCar;
    QMenu *menuEmployees;
    QMenu *menuClients;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ApplicGarageWindow)
    {
        if (ApplicGarageWindow->objectName().isEmpty())
            ApplicGarageWindow->setObjectName(QString::fromUtf8("ApplicGarageWindow"));
        ApplicGarageWindow->resize(750, 700);
        ApplicGarageWindow->setStyleSheet(QString::fromUtf8(""));
        actionLogin = new QAction(ApplicGarageWindow);
        actionLogin->setObjectName(QString::fromUtf8("actionLogin"));
        actionLogout = new QAction(ApplicGarageWindow);
        actionLogout->setObjectName(QString::fromUtf8("actionLogout"));
        actionLogout->setEnabled(false);
        actionQuit = new QAction(ApplicGarageWindow);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        actionNewModel = new QAction(ApplicGarageWindow);
        actionNewModel->setObjectName(QString::fromUtf8("actionNewModel"));
        actionNewOption = new QAction(ApplicGarageWindow);
        actionNewOption->setObjectName(QString::fromUtf8("actionNewOption"));
        actionNouveau = new QAction(ApplicGarageWindow);
        actionNouveau->setObjectName(QString::fromUtf8("actionNouveau"));
        actionCharger = new QAction(ApplicGarageWindow);
        actionCharger->setObjectName(QString::fromUtf8("actionCharger"));
        actionEnregistrer = new QAction(ApplicGarageWindow);
        actionEnregistrer->setObjectName(QString::fromUtf8("actionEnregistrer"));
        actionAddEmployee = new QAction(ApplicGarageWindow);
        actionAddEmployee->setObjectName(QString::fromUtf8("actionAddEmployee"));
        actionDeleteEmployeeById = new QAction(ApplicGarageWindow);
        actionDeleteEmployeeById->setObjectName(QString::fromUtf8("actionDeleteEmployeeById"));
        actionDeleteEmployeeByIndex = new QAction(ApplicGarageWindow);
        actionDeleteEmployeeByIndex->setObjectName(QString::fromUtf8("actionDeleteEmployeeByIndex"));
        actionAddClient = new QAction(ApplicGarageWindow);
        actionAddClient->setObjectName(QString::fromUtf8("actionAddClient"));
        actionDeleteClientById = new QAction(ApplicGarageWindow);
        actionDeleteClientById->setObjectName(QString::fromUtf8("actionDeleteClientById"));
        actionDeleteClientByIndex = new QAction(ApplicGarageWindow);
        actionDeleteClientByIndex->setObjectName(QString::fromUtf8("actionDeleteClientByIndex"));
        actionResetPassword = new QAction(ApplicGarageWindow);
        actionResetPassword->setObjectName(QString::fromUtf8("actionResetPassword"));
        centralwidget = new QWidget(ApplicGarageWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        frame = new QFrame(centralwidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(10, 30, 731, 381));
        frame->setStyleSheet(QString::fromUtf8("border-left-color: rgb(138, 226, 52);"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        scrollArea = new QScrollArea(frame);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setGeometry(QRect(10, 10, 281, 151));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 279, 149));
        scrollArea->setWidget(scrollAreaWidgetContents);
        label_2 = new QLabel(frame);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(310, 10, 64, 21));
        lineEditProjectName = new QLineEdit(frame);
        lineEditProjectName->setObjectName(QString::fromUtf8("lineEditProjectName"));
        lineEditProjectName->setGeometry(QRect(390, 10, 331, 25));
        label_3 = new QLabel(frame);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(310, 50, 64, 21));
        lineEditModelName = new QLineEdit(frame);
        lineEditModelName->setObjectName(QString::fromUtf8("lineEditModelName"));
        lineEditModelName->setGeometry(QRect(390, 50, 331, 25));
        lineEditModelName->setReadOnly(true);
        label_4 = new QLabel(frame);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(310, 90, 121, 21));
        lineEditPower = new QLineEdit(frame);
        lineEditPower->setObjectName(QString::fromUtf8("lineEditPower"));
        lineEditPower->setGeometry(QRect(420, 90, 91, 25));
        lineEditPower->setReadOnly(true);
        radioButtonPetrol = new QRadioButton(frame);
        radioButtonPetrol->setObjectName(QString::fromUtf8("radioButtonPetrol"));
        radioButtonPetrol->setEnabled(true);
        radioButtonPetrol->setGeometry(QRect(310, 130, 81, 23));
        radioButtonPetrol->setCheckable(true);
        radioButtonPetrol->setChecked(false);
        radioButtonElectric = new QRadioButton(frame);
        radioButtonElectric->setObjectName(QString::fromUtf8("radioButtonElectric"));
        radioButtonElectric->setGeometry(QRect(530, 130, 91, 23));
        radioButtonElectric->setCheckable(true);
        radioButtonDiesel = new QRadioButton(frame);
        radioButtonDiesel->setObjectName(QString::fromUtf8("radioButtonDiesel"));
        radioButtonDiesel->setGeometry(QRect(430, 130, 71, 23));
        radioButtonDiesel->setCheckable(true);
        radioButtonHybrid = new QRadioButton(frame);
        radioButtonHybrid->setObjectName(QString::fromUtf8("radioButtonHybrid"));
        radioButtonHybrid->setGeometry(QRect(650, 130, 71, 23));
        radioButtonHybrid->setCheckable(true);
        label_5 = new QLabel(frame);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(520, 90, 101, 21));
        lineEditBasePrice = new QLineEdit(frame);
        lineEditBasePrice->setObjectName(QString::fromUtf8("lineEditBasePrice"));
        lineEditBasePrice->setGeometry(QRect(630, 90, 91, 25));
        lineEditBasePrice->setReadOnly(true);
        comboBoxAvailableModels = new QComboBox(frame);
        comboBoxAvailableModels->setObjectName(QString::fromUtf8("comboBoxAvailableModels"));
        comboBoxAvailableModels->setGeometry(QRect(10, 190, 291, 25));
        label_6 = new QLabel(frame);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(10, 170, 151, 17));
        pushButtonSelectModel = new QPushButton(frame);
        pushButtonSelectModel->setObjectName(QString::fromUtf8("pushButtonSelectModel"));
        pushButtonSelectModel->setGeometry(QRect(310, 190, 61, 25));
        pushButtonSelectModel->setStyleSheet(QString::fromUtf8("background-color: lightblue"));
        label_7 = new QLabel(frame);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(390, 170, 151, 17));
        comboBoxAvailableOptions = new QComboBox(frame);
        comboBoxAvailableOptions->setObjectName(QString::fromUtf8("comboBoxAvailableOptions"));
        comboBoxAvailableOptions->setGeometry(QRect(390, 190, 261, 25));
        pushButtonAddOption = new QPushButton(frame);
        pushButtonAddOption->setObjectName(QString::fromUtf8("pushButtonAddOption"));
        pushButtonAddOption->setGeometry(QRect(660, 190, 61, 25));
        pushButtonAddOption->setStyleSheet(QString::fromUtf8("background-color: lightblue"));
        label_8 = new QLabel(frame);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(10, 220, 131, 17));
        tableWidgetOptions = new QTableWidget(frame);
        tableWidgetOptions->setObjectName(QString::fromUtf8("tableWidgetOptions"));
        tableWidgetOptions->setGeometry(QRect(10, 240, 421, 131));
        pushButtonRemoveOption = new QPushButton(frame);
        pushButtonRemoveOption->setObjectName(QString::fromUtf8("pushButtonRemoveOption"));
        pushButtonRemoveOption->setGeometry(QRect(440, 240, 111, 25));
        pushButtonRemoveOption->setStyleSheet(QString::fromUtf8("background-color: orange"));
        pushButtonReduction = new QPushButton(frame);
        pushButtonReduction->setObjectName(QString::fromUtf8("pushButtonReduction"));
        pushButtonReduction->setGeometry(QRect(570, 240, 151, 25));
        pushButtonReduction->setStyleSheet(QString::fromUtf8("background-color: lightgreen"));
        label_9 = new QLabel(frame);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(460, 290, 131, 21));
        lineEditPrice = new QLineEdit(frame);
        lineEditPrice->setObjectName(QString::fromUtf8("lineEditPrice"));
        lineEditPrice->setGeometry(QRect(600, 290, 121, 25));
        lineEditPrice->setReadOnly(true);
        pushButtonOpenProject = new QPushButton(frame);
        pushButtonOpenProject->setObjectName(QString::fromUtf8("pushButtonOpenProject"));
        pushButtonOpenProject->setGeometry(QRect(540, 340, 71, 25));
        pushButtonOpenProject->setStyleSheet(QString::fromUtf8("background-color: lightblue"));
        pushButtonSaveProject = new QPushButton(frame);
        pushButtonSaveProject->setObjectName(QString::fromUtf8("pushButtonSaveProject"));
        pushButtonSaveProject->setGeometry(QRect(632, 340, 91, 25));
        pushButtonSaveProject->setStyleSheet(QString::fromUtf8("background-color: lightblue"));
        pushButtonNewProject = new QPushButton(frame);
        pushButtonNewProject->setObjectName(QString::fromUtf8("pushButtonNewProject"));
        pushButtonNewProject->setGeometry(QRect(440, 340, 83, 25));
        pushButtonNewProject->setStyleSheet(QString::fromUtf8("background-color: lightblue"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 10, 131, 17));
        label_10 = new QLabel(centralwidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(10, 420, 151, 17));
        tableWidgetEmployees = new QTableWidget(centralwidget);
        tableWidgetEmployees->setObjectName(QString::fromUtf8("tableWidgetEmployees"));
        tableWidgetEmployees->setGeometry(QRect(10, 440, 351, 91));
        label_11 = new QLabel(centralwidget);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(10, 540, 64, 17));
        tableWidgetClients = new QTableWidget(centralwidget);
        tableWidgetClients->setObjectName(QString::fromUtf8("tableWidgetClients"));
        tableWidgetClients->setGeometry(QRect(10, 560, 351, 91));
        label_12 = new QLabel(centralwidget);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(380, 420, 64, 17));
        tableWidgetContracts = new QTableWidget(centralwidget);
        tableWidgetContracts->setObjectName(QString::fromUtf8("tableWidgetContracts"));
        tableWidgetContracts->setGeometry(QRect(380, 440, 361, 171));
        pushButtonNewContract = new QPushButton(centralwidget);
        pushButtonNewContract->setObjectName(QString::fromUtf8("pushButtonNewContract"));
        pushButtonNewContract->setGeometry(QRect(380, 620, 91, 25));
        pushButtonDeleteContract = new QPushButton(centralwidget);
        pushButtonDeleteContract->setObjectName(QString::fromUtf8("pushButtonDeleteContract"));
        pushButtonDeleteContract->setGeometry(QRect(490, 620, 91, 25));
        pushButtonShowCar = new QPushButton(centralwidget);
        pushButtonShowCar->setObjectName(QString::fromUtf8("pushButtonShowCar"));
        pushButtonShowCar->setGeometry(QRect(600, 620, 141, 25));
        ApplicGarageWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(ApplicGarageWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 750, 22));
        menuConnexion = new QMenu(menubar);
        menuConnexion->setObjectName(QString::fromUtf8("menuConnexion"));
        menuCar = new QMenu(menubar);
        menuCar->setObjectName(QString::fromUtf8("menuCar"));
        menuEmployees = new QMenu(menubar);
        menuEmployees->setObjectName(QString::fromUtf8("menuEmployees"));
        menuClients = new QMenu(menubar);
        menuClients->setObjectName(QString::fromUtf8("menuClients"));
        ApplicGarageWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(ApplicGarageWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        ApplicGarageWindow->setStatusBar(statusbar);

        menubar->addAction(menuConnexion->menuAction());
        menubar->addAction(menuEmployees->menuAction());
        menubar->addAction(menuClients->menuAction());
        menubar->addAction(menuCar->menuAction());
        menuConnexion->addAction(actionLogin);
        menuConnexion->addAction(actionLogout);
        menuConnexion->addSeparator();
        menuConnexion->addAction(actionResetPassword);
        menuConnexion->addSeparator();
        menuConnexion->addAction(actionQuit);
        menuCar->addAction(actionNewModel);
        menuCar->addAction(actionNewOption);
        menuEmployees->addAction(actionAddEmployee);
        menuEmployees->addSeparator();
        menuEmployees->addAction(actionDeleteEmployeeById);
        menuEmployees->addAction(actionDeleteEmployeeByIndex);
        menuClients->addAction(actionAddClient);
        menuClients->addSeparator();
        menuClients->addAction(actionDeleteClientById);
        menuClients->addAction(actionDeleteClientByIndex);

        retranslateUi(ApplicGarageWindow);

        QMetaObject::connectSlotsByName(ApplicGarageWindow);
    } // setupUi

    void retranslateUi(QMainWindow *ApplicGarageWindow)
    {
        ApplicGarageWindow->setWindowTitle(QApplication::translate("ApplicGarageWindow", "Application Garage", nullptr));
        actionLogin->setText(QApplication::translate("ApplicGarageWindow", "Login", nullptr));
        actionLogout->setText(QApplication::translate("ApplicGarageWindow", "Logout", nullptr));
        actionQuit->setText(QApplication::translate("ApplicGarageWindow", "Quitter", nullptr));
        actionNewModel->setText(QApplication::translate("ApplicGarageWindow", "Nouveau mod\303\250le", nullptr));
        actionNewOption->setText(QApplication::translate("ApplicGarageWindow", "Nouvelle option", nullptr));
        actionNouveau->setText(QApplication::translate("ApplicGarageWindow", "Nouveau", nullptr));
        actionCharger->setText(QApplication::translate("ApplicGarageWindow", "Ouvrir", nullptr));
        actionEnregistrer->setText(QApplication::translate("ApplicGarageWindow", "Enregistrer", nullptr));
        actionAddEmployee->setText(QApplication::translate("ApplicGarageWindow", "Ajouter", nullptr));
        actionDeleteEmployeeById->setText(QApplication::translate("ApplicGarageWindow", "Supprimer par id", nullptr));
        actionDeleteEmployeeByIndex->setText(QApplication::translate("ApplicGarageWindow", "Supprimer s\303\251lection", nullptr));
        actionAddClient->setText(QApplication::translate("ApplicGarageWindow", "Ajouter", nullptr));
        actionDeleteClientById->setText(QApplication::translate("ApplicGarageWindow", "Supprimer par id", nullptr));
        actionDeleteClientByIndex->setText(QApplication::translate("ApplicGarageWindow", "Supprimer s\303\251lection", nullptr));
        actionResetPassword->setText(QApplication::translate("ApplicGarageWindow", "Reset Mot de passe", nullptr));
        label_2->setText(QApplication::translate("ApplicGarageWindow", "Nom :", nullptr));
        label_3->setText(QApplication::translate("ApplicGarageWindow", "Mod\303\250le :", nullptr));
        label_4->setText(QApplication::translate("ApplicGarageWindow", "Puissance (Ch) :", nullptr));
        radioButtonPetrol->setText(QApplication::translate("ApplicGarageWindow", "Essence", nullptr));
        radioButtonElectric->setText(QApplication::translate("ApplicGarageWindow", "Electrique", nullptr));
        radioButtonDiesel->setText(QApplication::translate("ApplicGarageWindow", "Diesel", nullptr));
        radioButtonHybrid->setText(QApplication::translate("ApplicGarageWindow", "Hybride", nullptr));
        label_5->setText(QApplication::translate("ApplicGarageWindow", "Prix de base :", nullptr));
        label_6->setText(QApplication::translate("ApplicGarageWindow", "Mod\303\250les disponibles :", nullptr));
        pushButtonSelectModel->setText(QApplication::translate("ApplicGarageWindow", "Choisir", nullptr));
        label_7->setText(QApplication::translate("ApplicGarageWindow", "Options disponibles :", nullptr));
        pushButtonAddOption->setText(QApplication::translate("ApplicGarageWindow", "Ajouter", nullptr));
        label_8->setText(QApplication::translate("ApplicGarageWindow", "Options choisies :", nullptr));
        pushButtonRemoveOption->setText(QApplication::translate("ApplicGarageWindow", "Supprimer", nullptr));
        pushButtonReduction->setText(QApplication::translate("ApplicGarageWindow", "Accorder r\303\251duction", nullptr));
        label_9->setText(QApplication::translate("ApplicGarageWindow", "Prix avec options :", nullptr));
        pushButtonOpenProject->setText(QApplication::translate("ApplicGarageWindow", "Ouvrir", nullptr));
        pushButtonSaveProject->setText(QApplication::translate("ApplicGarageWindow", "Enregistrer", nullptr));
        pushButtonNewProject->setText(QApplication::translate("ApplicGarageWindow", "Nouveau", nullptr));
        label->setText(QApplication::translate("ApplicGarageWindow", "Projet en cours :", nullptr));
        label_10->setText(QApplication::translate("ApplicGarageWindow", "Employ\303\251s du garage :", nullptr));
        label_11->setText(QApplication::translate("ApplicGarageWindow", "Clients :", nullptr));
        label_12->setText(QApplication::translate("ApplicGarageWindow", "Contrats :", nullptr));
        pushButtonNewContract->setText(QApplication::translate("ApplicGarageWindow", "Nouveau", nullptr));
        pushButtonDeleteContract->setText(QApplication::translate("ApplicGarageWindow", "Supprimer", nullptr));
        pushButtonShowCar->setText(QApplication::translate("ApplicGarageWindow", "Visualiser Voiture", nullptr));
        menuConnexion->setTitle(QApplication::translate("ApplicGarageWindow", "Connexion", nullptr));
        menuCar->setTitle(QApplication::translate("ApplicGarageWindow", "Voiture", nullptr));
        menuEmployees->setTitle(QApplication::translate("ApplicGarageWindow", "Employ\303\251s", nullptr));
        menuClients->setTitle(QApplication::translate("ApplicGarageWindow", "Clients", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ApplicGarageWindow: public Ui_ApplicGarageWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_APPLICGARAGEWINDOW_H
