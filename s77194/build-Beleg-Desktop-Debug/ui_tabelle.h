/********************************************************************************
** Form generated from reading UI file 'tabelle.ui'
**
** Created by: Qt User Interface Compiler version 5.9.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TABELLE_H
#define UI_TABELLE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_tabelleWindow
{
public:
    QLabel *label;
    QTableWidget *tabelleWidget;
    QPushButton *load_person;
    QPushButton *saveButton;
    QPushButton *insertButton;
    QPushButton *deleteButton;
    QPushButton *load_media;
    QPushButton *load_ausleihe;
    QPushButton *helpButton;

    void setupUi(QDialog *tabelleWindow)
    {
        if (tabelleWindow->objectName().isEmpty())
            tabelleWindow->setObjectName(QStringLiteral("tabelleWindow"));
        tabelleWindow->resize(857, 526);
        label = new QLabel(tabelleWindow);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(300, 10, 301, 71));
        QFont font;
        font.setPointSize(20);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);
        tabelleWidget = new QTableWidget(tabelleWindow);
        tabelleWidget->setObjectName(QStringLiteral("tabelleWidget"));
        tabelleWidget->setGeometry(QRect(15, 91, 821, 341));
        load_person = new QPushButton(tabelleWindow);
        load_person->setObjectName(QStringLiteral("load_person"));
        load_person->setGeometry(QRect(10, 460, 141, 34));
        saveButton = new QPushButton(tabelleWindow);
        saveButton->setObjectName(QStringLiteral("saveButton"));
        saveButton->setEnabled(false);
        saveButton->setGeometry(QRect(460, 460, 131, 34));
        insertButton = new QPushButton(tabelleWindow);
        insertButton->setObjectName(QStringLiteral("insertButton"));
        insertButton->setEnabled(false);
        insertButton->setGeometry(QRect(600, 460, 121, 34));
        deleteButton = new QPushButton(tabelleWindow);
        deleteButton->setObjectName(QStringLiteral("deleteButton"));
        deleteButton->setEnabled(true);
        deleteButton->setGeometry(QRect(730, 460, 111, 34));
        load_media = new QPushButton(tabelleWindow);
        load_media->setObjectName(QStringLiteral("load_media"));
        load_media->setGeometry(QRect(310, 460, 141, 34));
        load_ausleihe = new QPushButton(tabelleWindow);
        load_ausleihe->setObjectName(QStringLiteral("load_ausleihe"));
        load_ausleihe->setGeometry(QRect(160, 460, 141, 34));
        helpButton = new QPushButton(tabelleWindow);
        helpButton->setObjectName(QStringLiteral("helpButton"));
        helpButton->setGeometry(QRect(790, 0, 61, 34));

        retranslateUi(tabelleWindow);

        QMetaObject::connectSlotsByName(tabelleWindow);
    } // setupUi

    void retranslateUi(QDialog *tabelleWindow)
    {
        tabelleWindow->setWindowTitle(QApplication::translate("tabelleWindow", "Tabelle", Q_NULLPTR));
        label->setText(QApplication::translate("tabelleWindow", "Medienverwaltung", Q_NULLPTR));
        load_person->setText(QApplication::translate("tabelleWindow", "Personen", Q_NULLPTR));
        saveButton->setText(QApplication::translate("tabelleWindow", "Speichern", Q_NULLPTR));
        insertButton->setText(QApplication::translate("tabelleWindow", "Einf\303\274gen", Q_NULLPTR));
        deleteButton->setText(QApplication::translate("tabelleWindow", "L\303\266schen", Q_NULLPTR));
        load_media->setText(QApplication::translate("tabelleWindow", "Medien", Q_NULLPTR));
        load_ausleihe->setText(QApplication::translate("tabelleWindow", "Ausleihe", Q_NULLPTR));
        helpButton->setText(QApplication::translate("tabelleWindow", "Hilfe", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class tabelleWindow: public Ui_tabelleWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TABELLE_H
