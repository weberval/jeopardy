/********************************************************************************
** Form generated from reading UI file 'answer.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ANSWER_H
#define UI_ANSWER_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <phonon/videoplayer.h>

QT_BEGIN_NAMESPACE

class Ui_Answer
{
public:
    QPushButton *buttonRight;
    QPushButton *buttonEnd;
    QPushButton *buttonWrong;
    QLabel *answer;
    QLabel *currentPlayer;
    QPushButton *buttonCancel;
    QGraphicsView *graphicsView;
    Phonon::VideoPlayer *videoPlayer;
    QLabel *time;

    void setupUi(QDialog *Answer)
    {
        if (Answer->objectName().isEmpty())
            Answer->setObjectName(QString::fromUtf8("Answer"));
        Answer->resize(998, 615);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Answer->sizePolicy().hasHeightForWidth());
        Answer->setSizePolicy(sizePolicy);
        Answer->setMinimumSize(QSize(998, 615));
        Answer->setMaximumSize(QSize(998, 615));
        Answer->setCursor(QCursor(Qt::WhatsThisCursor));
        Answer->setContextMenuPolicy(Qt::NoContextMenu);
        QIcon icon;
        icon.addFile(QString::fromUtf8("Initialize"), QSize(), QIcon::Normal, QIcon::Off);
        Answer->setWindowIcon(icon);
        buttonRight = new QPushButton(Answer);
        buttonRight->setObjectName(QString::fromUtf8("buttonRight"));
        buttonRight->setGeometry(QRect(690, 570, 85, 32));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(buttonRight->sizePolicy().hasHeightForWidth());
        buttonRight->setSizePolicy(sizePolicy1);
        QFont font;
        font.setFamily(QString::fromUtf8("Andale Mono"));
        font.setPointSize(14);
        font.setBold(false);
        font.setWeight(50);
        buttonRight->setFont(font);
        buttonRight->setCursor(QCursor(Qt::WhatsThisCursor));
        buttonEnd = new QPushButton(Answer);
        buttonEnd->setObjectName(QString::fromUtf8("buttonEnd"));
        buttonEnd->setGeometry(QRect(10, 570, 85, 32));
        sizePolicy1.setHeightForWidth(buttonEnd->sizePolicy().hasHeightForWidth());
        buttonEnd->setSizePolicy(sizePolicy1);
        buttonEnd->setFont(font);
        buttonEnd->setCursor(QCursor(Qt::WhatsThisCursor));
        buttonWrong = new QPushButton(Answer);
        buttonWrong->setObjectName(QString::fromUtf8("buttonWrong"));
        buttonWrong->setGeometry(QRect(800, 570, 85, 32));
        sizePolicy1.setHeightForWidth(buttonWrong->sizePolicy().hasHeightForWidth());
        buttonWrong->setSizePolicy(sizePolicy1);
        buttonWrong->setFont(font);
        buttonWrong->setCursor(QCursor(Qt::WhatsThisCursor));
        answer = new QLabel(Answer);
        answer->setObjectName(QString::fromUtf8("answer"));
        answer->setGeometry(QRect(9, 9, 981, 521));
        sizePolicy1.setHeightForWidth(answer->sizePolicy().hasHeightForWidth());
        answer->setSizePolicy(sizePolicy1);
        QFont font1;
        font1.setFamily(QString::fromUtf8("Andale Mono"));
        font1.setPointSize(28);
        font1.setBold(false);
        font1.setWeight(50);
        answer->setFont(font1);
        answer->setCursor(QCursor(Qt::WhatsThisCursor));
        answer->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        answer->setTextFormat(Qt::RichText);
        answer->setScaledContents(false);
        answer->setAlignment(Qt::AlignCenter);
        answer->setWordWrap(true);
        currentPlayer = new QLabel(Answer);
        currentPlayer->setObjectName(QString::fromUtf8("currentPlayer"));
        currentPlayer->setGeometry(QRect(740, 530, 208, 31));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Andale Mono"));
        font2.setPointSize(20);
        currentPlayer->setFont(font2);
        currentPlayer->setCursor(QCursor(Qt::WhatsThisCursor));
        currentPlayer->setAlignment(Qt::AlignCenter);
        buttonCancel = new QPushButton(Answer);
        buttonCancel->setObjectName(QString::fromUtf8("buttonCancel"));
        buttonCancel->setGeometry(QRect(910, 570, 85, 32));
        sizePolicy1.setHeightForWidth(buttonCancel->sizePolicy().hasHeightForWidth());
        buttonCancel->setSizePolicy(sizePolicy1);
        buttonCancel->setFont(font);
        buttonCancel->setCursor(QCursor(Qt::WhatsThisCursor));
        graphicsView = new QGraphicsView(Answer);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setGeometry(QRect(1, 1, 997, 531));
        graphicsView->viewport()->setProperty("cursor", QVariant(QCursor(Qt::WhatsThisCursor)));
        videoPlayer = new Phonon::VideoPlayer(Answer);
        videoPlayer->setObjectName(QString::fromUtf8("videoPlayer"));
        videoPlayer->setGeometry(QRect(9, 9, 981, 511));
        videoPlayer->setCursor(QCursor(Qt::WhatsThisCursor));
        videoPlayer->setStyleSheet(QString::fromUtf8(""));
        time = new QLabel(Answer);
        time->setObjectName(QString::fromUtf8("time"));
        time->setGeometry(QRect(20, 540, 221, 16));
        QFont font3;
        font3.setPointSize(14);
        time->setFont(font3);

        retranslateUi(Answer);

        QMetaObject::connectSlotsByName(Answer);
    } // setupUi

    void retranslateUi(QDialog *Answer)
    {
        Answer->setWindowTitle(QCoreApplication::translate("Answer", "Jeopardy", nullptr));
        buttonRight->setText(QCoreApplication::translate("Answer", "Right", nullptr));
        buttonEnd->setText(QCoreApplication::translate("Answer", "End", nullptr));
        buttonWrong->setText(QCoreApplication::translate("Answer", "Wrong", nullptr));
        answer->setText(QCoreApplication::translate("Answer", "listen...", nullptr));
        currentPlayer->setText(QCoreApplication::translate("Answer", "currentPlayer", nullptr));
        buttonCancel->setText(QCoreApplication::translate("Answer", "Cancel", nullptr));
        time->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Answer: public Ui_Answer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ANSWER_H
