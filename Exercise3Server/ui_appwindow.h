/********************************************************************************
** Form generated from reading UI file 'appwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_APPWINDOW_H
#define UI_APPWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AppWindow
{
public:
    QWidget *centralwidget;
    QTabWidget *tabWidget;
    QWidget *tab;
    QLabel *label_14;
    QPushButton *pushButton_5;
    QListWidget *listWidget_6;
    QLabel *label_22;
    QListWidget *listWidget_11;
    QListWidget *listWidget_12;
    QLabel *label_7;
    QListWidget *listWidget_13;
    QLabel *label_23;
    QLabel *label_8;
    QWidget *tab_2;
    QPushButton *pushButton;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QPushButton *pushButton_2;
    QListWidget *listWidget;
    QListWidget *listWidget_7;
    QListWidget *listWidget_8;
    QPushButton *pushButton_13;
    QPushButton *pushButton_14;
    QLabel *label_3;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_12;
    QLineEdit *lineEdit_3;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *lineEdit;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QLineEdit *lineEdit_2;
    QWidget *tab_3;
    QPushButton *pushButton_6;
    QLabel *label_15;
    QLabel *label_16;
    QPushButton *pushButton_7;
    QListWidget *listWidget_2;
    QListWidget *listWidget_9;
    QPushButton *pushButton_3;
    QWidget *tab_7;
    QPushButton *pushButton_8;
    QWidget *layoutWidget_5;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_17;
    QLineEdit *lineEdit_8;
    QLabel *label_18;
    QLabel *label_19;
    QLabel *label_20;
    QListWidget *listWidget_3;
    QListWidget *listWidget_4;
    QListWidget *listWidget_5;
    QListWidget *listWidget_10;
    QPushButton *pushButton_16;
    QLabel *label_21;
    QWidget *layoutWidget3;
    QHBoxLayout *horizontalLayout_9;
    QPushButton *pushButton_11;
    QLineEdit *lineEdit_9;
    QMenuBar *menubar;
    QMenu *menuOptions;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *AppWindow)
    {
        if (AppWindow->objectName().isEmpty())
            AppWindow->setObjectName(QStringLiteral("AppWindow"));
        AppWindow->resize(800, 600);
        centralwidget = new QWidget(AppWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(0, 0, 1013, 561));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        label_14 = new QLabel(tab);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setGeometry(QRect(460, 20, 101, 16));
        pushButton_5 = new QPushButton(tab);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));
        pushButton_5->setGeometry(QRect(330, 320, 111, 51));
        listWidget_6 = new QListWidget(tab);
        listWidget_6->setObjectName(QStringLiteral("listWidget_6"));
        listWidget_6->setGeometry(QRect(410, 50, 191, 192));
        label_22 = new QLabel(tab);
        label_22->setObjectName(QStringLiteral("label_22"));
        label_22->setGeometry(QRect(630, 20, 71, 20));
        listWidget_11 = new QListWidget(tab);
        listWidget_11->setObjectName(QStringLiteral("listWidget_11"));
        listWidget_11->setGeometry(QRect(640, 50, 51, 192));
        listWidget_12 = new QListWidget(tab);
        listWidget_12->setObjectName(QStringLiteral("listWidget_12"));
        listWidget_12->setGeometry(QRect(220, 50, 151, 192));
        label_7 = new QLabel(tab);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(250, 20, 59, 14));
        listWidget_13 = new QListWidget(tab);
        listWidget_13->setObjectName(QStringLiteral("listWidget_13"));
        listWidget_13->setGeometry(QRect(10, 50, 191, 192));
        label_23 = new QLabel(tab);
        label_23->setObjectName(QStringLiteral("label_23"));
        label_23->setGeometry(QRect(50, 20, 91, 16));
        label_8 = new QLabel(tab);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(450, 330, 241, 20));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        pushButton = new QPushButton(tab_2);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(260, 120, 80, 22));
        label_4 = new QLabel(tab_2);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(90, 10, 111, 20));
        label_5 = new QLabel(tab_2);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(410, 10, 59, 14));
        label_6 = new QLabel(tab_2);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(700, 10, 71, 20));
        pushButton_2 = new QPushButton(tab_2);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(340, 410, 91, 51));
        listWidget = new QListWidget(tab_2);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setGeometry(QRect(50, 40, 191, 192));
        listWidget_7 = new QListWidget(tab_2);
        listWidget_7->setObjectName(QStringLiteral("listWidget_7"));
        listWidget_7->setGeometry(QRect(360, 40, 151, 192));
        listWidget_8 = new QListWidget(tab_2);
        listWidget_8->setObjectName(QStringLiteral("listWidget_8"));
        listWidget_8->setGeometry(QRect(710, 40, 51, 192));
        pushButton_13 = new QPushButton(tab_2);
        pushButton_13->setObjectName(QStringLiteral("pushButton_13"));
        pushButton_13->setGeometry(QRect(390, 250, 80, 22));
        pushButton_14 = new QPushButton(tab_2);
        pushButton_14->setObjectName(QStringLiteral("pushButton_14"));
        pushButton_14->setGeometry(QRect(700, 250, 80, 22));
        label_3 = new QLabel(tab_2);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(460, 430, 321, 20));
        layoutWidget = new QWidget(tab_2);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(530, 120, 161, 24));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_12 = new QPushButton(layoutWidget);
        pushButton_12->setObjectName(QStringLiteral("pushButton_12"));

        horizontalLayout->addWidget(pushButton_12);

        lineEdit_3 = new QLineEdit(layoutWidget);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));

        horizontalLayout->addWidget(lineEdit_3);

        layoutWidget1 = new QWidget(tab_2);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(230, 310, 281, 24));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget1);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_2->addWidget(label);

        lineEdit = new QLineEdit(layoutWidget1);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        horizontalLayout_2->addWidget(lineEdit);

        layoutWidget2 = new QWidget(tab_2);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(230, 350, 321, 24));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(layoutWidget2);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_3->addWidget(label_2);

        lineEdit_2 = new QLineEdit(layoutWidget2);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));

        horizontalLayout_3->addWidget(lineEdit_2);

        tabWidget->addTab(tab_2, QString());
        layoutWidget->raise();
        layoutWidget->raise();
        layoutWidget->raise();
        pushButton->raise();
        label_4->raise();
        label_5->raise();
        label_6->raise();
        pushButton_2->raise();
        listWidget->raise();
        listWidget_7->raise();
        listWidget_8->raise();
        pushButton_13->raise();
        pushButton_14->raise();
        label_3->raise();
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        pushButton_6 = new QPushButton(tab_3);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));
        pushButton_6->setGeometry(QRect(340, 140, 80, 22));
        label_15 = new QLabel(tab_3);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setGeometry(QRect(180, 30, 59, 14));
        label_16 = new QLabel(tab_3);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setGeometry(QRect(440, 30, 101, 20));
        pushButton_7 = new QPushButton(tab_3);
        pushButton_7->setObjectName(QStringLiteral("pushButton_7"));
        pushButton_7->setGeometry(QRect(330, 330, 101, 51));
        listWidget_2 = new QListWidget(tab_3);
        listWidget_2->setObjectName(QStringLiteral("listWidget_2"));
        listWidget_2->setGeometry(QRect(120, 60, 201, 192));
        listWidget_9 = new QListWidget(tab_3);
        listWidget_9->setObjectName(QStringLiteral("listWidget_9"));
        listWidget_9->setGeometry(QRect(440, 60, 201, 192));
        pushButton_3 = new QPushButton(tab_3);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(500, 260, 80, 22));
        tabWidget->addTab(tab_3, QString());
        tab_7 = new QWidget();
        tab_7->setObjectName(QStringLiteral("tab_7"));
        pushButton_8 = new QPushButton(tab_7);
        pushButton_8->setObjectName(QStringLiteral("pushButton_8"));
        pushButton_8->setGeometry(QRect(360, 150, 80, 22));
        layoutWidget_5 = new QWidget(tab_7);
        layoutWidget_5->setObjectName(QStringLiteral("layoutWidget_5"));
        layoutWidget_5->setGeometry(QRect(320, 100, 121, 24));
        horizontalLayout_8 = new QHBoxLayout(layoutWidget_5);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        horizontalLayout_8->setContentsMargins(0, 0, 0, 0);
        label_17 = new QLabel(layoutWidget_5);
        label_17->setObjectName(QStringLiteral("label_17"));

        horizontalLayout_8->addWidget(label_17);

        lineEdit_8 = new QLineEdit(layoutWidget_5);
        lineEdit_8->setObjectName(QStringLiteral("lineEdit_8"));

        horizontalLayout_8->addWidget(lineEdit_8);

        label_18 = new QLabel(tab_7);
        label_18->setObjectName(QStringLiteral("label_18"));
        label_18->setGeometry(QRect(120, 250, 59, 14));
        label_19 = new QLabel(tab_7);
        label_19->setObjectName(QStringLiteral("label_19"));
        label_19->setGeometry(QRect(260, 250, 101, 20));
        label_20 = new QLabel(tab_7);
        label_20->setObjectName(QStringLiteral("label_20"));
        label_20->setGeometry(QRect(210, 20, 59, 14));
        listWidget_3 = new QListWidget(tab_7);
        listWidget_3->setObjectName(QStringLiteral("listWidget_3"));
        listWidget_3->setGeometry(QRect(185, 40, 121, 192));
        listWidget_4 = new QListWidget(tab_7);
        listWidget_4->setObjectName(QStringLiteral("listWidget_4"));
        listWidget_4->setGeometry(QRect(80, 280, 151, 192));
        listWidget_5 = new QListWidget(tab_7);
        listWidget_5->setObjectName(QStringLiteral("listWidget_5"));
        listWidget_5->setGeometry(QRect(240, 280, 141, 192));
        listWidget_10 = new QListWidget(tab_7);
        listWidget_10->setObjectName(QStringLiteral("listWidget_10"));
        listWidget_10->setGeometry(QRect(570, 280, 51, 192));
        pushButton_16 = new QPushButton(tab_7);
        pushButton_16->setObjectName(QStringLiteral("pushButton_16"));
        pushButton_16->setGeometry(QRect(270, 490, 80, 22));
        label_21 = new QLabel(tab_7);
        label_21->setObjectName(QStringLiteral("label_21"));
        label_21->setGeometry(QRect(560, 250, 71, 20));
        layoutWidget3 = new QWidget(tab_7);
        layoutWidget3->setObjectName(QStringLiteral("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(390, 360, 171, 24));
        horizontalLayout_9 = new QHBoxLayout(layoutWidget3);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        horizontalLayout_9->setContentsMargins(0, 0, 0, 0);
        pushButton_11 = new QPushButton(layoutWidget3);
        pushButton_11->setObjectName(QStringLiteral("pushButton_11"));

        horizontalLayout_9->addWidget(pushButton_11);

        lineEdit_9 = new QLineEdit(layoutWidget3);
        lineEdit_9->setObjectName(QStringLiteral("lineEdit_9"));

        horizontalLayout_9->addWidget(lineEdit_9);

        tabWidget->addTab(tab_7, QString());
        AppWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(AppWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 19));
        menuOptions = new QMenu(menubar);
        menuOptions->setObjectName(QStringLiteral("menuOptions"));
        AppWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(AppWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        AppWindow->setStatusBar(statusbar);

        menubar->addAction(menuOptions->menuAction());

        retranslateUi(AppWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(AppWindow);
    } // setupUi

    void retranslateUi(QMainWindow *AppWindow)
    {
        AppWindow->setWindowTitle(QApplication::translate("AppWindow", "MainWindow", 0));
        label_14->setText(QApplication::translate("AppWindow", "Images", 0));
        pushButton_5->setText(QApplication::translate("AppWindow", "View Image", 0));
        label_22->setText(QApplication::translate("AppWindow", "Views Left", 0));
        label_7->setText(QApplication::translate("AppWindow", "Users", 0));
        label_23->setText(QApplication::translate("AppWindow", "Owned Images", 0));
        label_8->setText(QApplication::translate("AppWindow", "TextLabel", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("AppWindow", "Images", 0));
        pushButton->setText(QApplication::translate("AppWindow", "Add", 0));
        label_4->setText(QApplication::translate("AppWindow", "Share with users", 0));
        label_5->setText(QApplication::translate("AppWindow", "Users", 0));
        label_6->setText(QApplication::translate("AppWindow", "Max Views", 0));
        pushButton_2->setText(QApplication::translate("AppWindow", "Upload", 0));
        pushButton_13->setText(QApplication::translate("AppWindow", "Remove", 0));
        pushButton_14->setText(QApplication::translate("AppWindow", "Remove", 0));
        label_3->setText(QApplication::translate("AppWindow", "TextLabel", 0));
        pushButton_12->setText(QApplication::translate("AppWindow", "Add View Count", 0));
        label->setText(QApplication::translate("AppWindow", "Image Name", 0));
        label_2->setText(QApplication::translate("AppWindow", "Image Path", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("AppWindow", "Upload Image", 0));
        pushButton_6->setText(QApplication::translate("AppWindow", "Add", 0));
        label_15->setText(QApplication::translate("AppWindow", "Images", 0));
        label_16->setText(QApplication::translate("AppWindow", "To be removed", 0));
        pushButton_7->setText(QApplication::translate("AppWindow", "Remove Images", 0));
        pushButton_3->setText(QApplication::translate("AppWindow", "Remove", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("AppWindow", "Remove Images", 0));
        pushButton_8->setText(QApplication::translate("AppWindow", "Add User", 0));
        label_17->setText(QApplication::translate("AppWindow", "View Count", 0));
        label_18->setText(QApplication::translate("AppWindow", "Images", 0));
        label_19->setText(QApplication::translate("AppWindow", "Allowed Viewers", 0));
        label_20->setText(QApplication::translate("AppWindow", "All Users", 0));
        pushButton_16->setText(QApplication::translate("AppWindow", "Remove", 0));
        label_21->setText(QApplication::translate("AppWindow", "Max Views", 0));
        pushButton_11->setText(QApplication::translate("AppWindow", "Change View Count", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_7), QApplication::translate("AppWindow", "Edit Viewer Data", 0));
        menuOptions->setTitle(QApplication::translate("AppWindow", "Options", 0));
    } // retranslateUi

};

namespace Ui {
    class AppWindow: public Ui_AppWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_APPWINDOW_H
