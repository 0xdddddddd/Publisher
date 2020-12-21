/********************************************************************************
** Form generated from reading UI file 'ApplicationMainnlCJAj.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef APPLICATIONMAINNLCJAJ_H
#define APPLICATIONMAINNLCJAJ_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ApplicationMain
{
public:
    QWidget* centralwidget;
    QVBoxLayout* verticalLayout;
    QGroupBox* groupBox;
    QGridLayout* gridLayout;
    QPushButton* pushButton;
    QPushButton* pushButton_2;
    QPushButton* pushButton_3;
    QLineEdit* lineEdit;
    QWidget* browserWidget;
    QGroupBox* groupBox_2;
    QGridLayout* gridLayout_2;
    QLabel* label;
    QStatusBar* statusBar;
    QMenuBar* menuBar;

    void setupUi(QMainWindow* ApplicationMain)
    {
        if (ApplicationMain->objectName().isEmpty())
            ApplicationMain->setObjectName(QString::fromUtf8("ApplicationMain"));
        ApplicationMain->resize(1400, 800);
        ApplicationMain->setMinimumSize(QSize(1400, 800));
        centralwidget = new QWidget(ApplicationMain);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        groupBox->setMinimumSize(QSize(0, 0));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy1);
        pushButton->setMinimumSize(QSize(0, 0));

        gridLayout->addWidget(pushButton, 0, 0, 1, 1);

        pushButton_2 = new QPushButton(groupBox);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        sizePolicy1.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
        pushButton_2->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(pushButton_2, 0, 1, 1, 1);

        pushButton_3 = new QPushButton(groupBox);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        sizePolicy1.setHeightForWidth(pushButton_3->sizePolicy().hasHeightForWidth());
        pushButton_3->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(pushButton_3, 0, 2, 1, 1);

        lineEdit = new QLineEdit(groupBox);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(lineEdit->sizePolicy().hasHeightForWidth());
        lineEdit->setSizePolicy(sizePolicy2);
        lineEdit->setMinimumSize(QSize(520, 0));

        gridLayout->addWidget(lineEdit, 0, 3, 1, 1);


        verticalLayout->addWidget(groupBox);

        browserWidget = new QWidget(centralwidget);
        browserWidget->setObjectName(QString::fromUtf8("browserWidget"));
        browserWidget->setEnabled(true);
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(browserWidget->sizePolicy().hasHeightForWidth());
        browserWidget->setSizePolicy(sizePolicy3);

        verticalLayout->addWidget(browserWidget);

        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        sizePolicy.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy);
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label = new QLabel(groupBox_2);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy4(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy4);

        gridLayout_2->addWidget(label, 0, 0, 1, 1);


        verticalLayout->addWidget(groupBox_2);

        ApplicationMain->setCentralWidget(centralwidget);
        statusBar = new QStatusBar(ApplicationMain);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        ApplicationMain->setStatusBar(statusBar);
        menuBar = new QMenuBar(ApplicationMain);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1400, 23));
        ApplicationMain->setMenuBar(menuBar);

        retranslateUi(ApplicationMain);

        QMetaObject::connectSlotsByName(ApplicationMain);
    } // setupUi

    void retranslateUi(QMainWindow* ApplicationMain)
    {
        ApplicationMain->setWindowTitle(QCoreApplication::translate("ApplicationMain", "\347\275\251\347\275\251\345\244\251\345\240\202(www.zhao.ee)", nullptr));
        groupBox->setTitle(QString());
        pushButton->setText(QCoreApplication::translate("ApplicationMain", "\345\220\216\351\200\200", nullptr));
        pushButton_2->setText(QCoreApplication::translate("ApplicationMain", "\345\211\215\350\277\233", nullptr));
        pushButton_3->setText(QCoreApplication::translate("ApplicationMain", "\345\210\267\346\226\260", nullptr));
        lineEdit->setText(QString());
        lineEdit->setPlaceholderText(QCoreApplication::translate("ApplicationMain", "Web.Site.Address", nullptr));
        groupBox_2->setTitle(QString());
        label->setText(QCoreApplication::translate("ApplicationMain", "[Server.Select] [More Features Are Being Developed]", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ApplicationMain : public Ui_ApplicationMain {};
} // namespace Ui

QT_END_NAMESPACE

#endif // APPLICATIONMAINNLCJAJ_H
