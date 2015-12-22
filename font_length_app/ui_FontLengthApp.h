/********************************************************************************
** Form generated from reading UI file 'FontLengthApp.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FONTLENGTHAPP_H
#define UI_FONTLENGTHAPP_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FontDialog
{
public:
    QGroupBox *groupBox;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *comboBox;
    QLabel *label_2;
    QComboBox *comboBox_2;
    QGroupBox *groupBox_2;
    QPlainTextEdit *plainTextEdit;
    QCheckBox *checkBox;
    QPushButton *pushButton;
    QGroupBox *groupBox_3;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;

    void setupUi(QWidget *FontDialog)
    {
        if (FontDialog->objectName().isEmpty())
            FontDialog->setObjectName(QString::fromUtf8("FontDialog"));
        FontDialog->resize(356, 506);
        groupBox = new QGroupBox(FontDialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(30, 30, 304, 82));
        layoutWidget = new QWidget(groupBox);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 30, 264, 22));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        comboBox = new QComboBox(layoutWidget);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        horizontalLayout->addWidget(comboBox);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        comboBox_2 = new QComboBox(layoutWidget);
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));

        horizontalLayout->addWidget(comboBox_2);

        groupBox_2 = new QGroupBox(FontDialog);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(30, 140, 301, 171));
        plainTextEdit = new QPlainTextEdit(groupBox_2);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));
        plainTextEdit->setGeometry(QRect(20, 30, 261, 71));
        checkBox = new QCheckBox(groupBox_2);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setGeometry(QRect(200, 120, 81, 21));
        pushButton = new QPushButton(FontDialog);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(150, 330, 75, 23));
        groupBox_3 = new QGroupBox(FontDialog);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(30, 370, 301, 101));
        label_3 = new QLabel(groupBox_3);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 40, 71, 20));
        label_4 = new QLabel(groupBox_3);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(90, 40, 21, 16));
        label_5 = new QLabel(groupBox_3);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(130, 40, 56, 12));
        pushButton->raise();
        groupBox_2->raise();
        groupBox->raise();
        groupBox_3->raise();
#ifndef QT_NO_SHORTCUT
        label->setBuddy(comboBox);
        label_2->setBuddy(comboBox_2);
#endif // QT_NO_SHORTCUT

        retranslateUi(FontDialog);

        QMetaObject::connectSlotsByName(FontDialog);
    } // setupUi

    void retranslateUi(QWidget *FontDialog)
    {
        FontDialog->setWindowTitle(QApplication::translate("FontDialog", "FontDialog", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("FontDialog", "GP Model & Font Type", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("FontDialog", "Model", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("FontDialog", "Font Type", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("FontDialog", "Input String", 0, QApplication::UnicodeUTF8));
        checkBox->setText(QApplication::translate("FontDialog", "Ignore CRLF", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("FontDialog", "Analysis", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("FontDialog", "Font Information", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("FontDialog", "Font Width:", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("FontDialog", "0", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("FontDialog", "Pixel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class FontDialog: public Ui_FontDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FONTLENGTHAPP_H
