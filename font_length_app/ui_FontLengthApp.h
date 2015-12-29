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
#include <QtGui/QComboBox>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
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
    QPushButton *pushButton;
    QGroupBox *groupBox_3;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QLineEdit *PixcelOfFont;
    QLabel *label_5;

    void setupUi(QWidget *FontDialog)
    {
        if (FontDialog->objectName().isEmpty())
            FontDialog->setObjectName(QString::fromUtf8("FontDialog"));
        FontDialog->resize(356, 452);
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
        groupBox_2->setGeometry(QRect(30, 140, 301, 131));
        plainTextEdit = new QPlainTextEdit(groupBox_2);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));
        plainTextEdit->setGeometry(QRect(20, 30, 261, 71));
        pushButton = new QPushButton(FontDialog);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(130, 400, 75, 23));
        groupBox_3 = new QGroupBox(FontDialog);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(80, 280, 183, 102));
        layoutWidget1 = new QWidget(groupBox_3);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(20, 40, 143, 22));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(layoutWidget1);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_2->addWidget(label_3);

        PixcelOfFont = new QLineEdit(layoutWidget1);
        PixcelOfFont->setObjectName(QString::fromUtf8("PixcelOfFont"));
        PixcelOfFont->setReadOnly(true);

        horizontalLayout_2->addWidget(PixcelOfFont);

        label_5 = new QLabel(layoutWidget1);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_2->addWidget(label_5);

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
        pushButton->setText(QApplication::translate("FontDialog", "Analysis", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("FontDialog", "Font Information", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("FontDialog", "Font Width:", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("FontDialog", "Pixel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class FontDialog: public Ui_FontDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FONTLENGTHAPP_H
