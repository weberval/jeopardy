/*
 * Copyright (c) 2011, Christian Lange
 * (chlange) <chlange@htwg-konstanz.de> <Christian_Lange@hotmail.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of Christian Lange nor the names of its
 *       contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL CHRISTIAN LANGE BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "gamefield.h"

GameField::GameField(QWidget *parent, int roundArg, int categoryNr, Player *players, int playerNrArr, bool sound) :
    QDialog(parent), round(roundArg), alreadyAnswered(NULL), lastWinner(NO_WINNER),
    lastPoints(0), playerNr(playerNrArr), categoryNr(categoryNr), sound(sound), answer(NULL), podium(NULL),
    randomCtx(NULL), editorCtx(NULL), loadCtx(NULL), saveCtx(NULL), endRoundCtx(NULL)
{
    for(int i = 0; i < NUMBER_MAX_PLAYERS; i++)
        this->playerNameLabels[i] = new QLabel();
 
    for(int i = 0; i < NUMBER_MAX_PLAYERS; i++)
        this->playerPointsLabels[i] = new QLabel();
    
    for(int i = 0; i < NUMBER_MAX_CATEGORIES; i++)
        this->categoryLabels[i] = new QLabel();

    for(int i = 0; i < NUMBER_MAX_ANSWERS; i++)
        this->buttons[i] = new QPushButton();

    this->players = players;

    this->init();
}

GameField::~GameField()
{
    if(this->answer != NULL)
        delete this->answer;
    if(this->randomCtx != NULL)
        delete this->randomCtx;
    if(this->editorCtx != NULL)
        delete this->editorCtx;
    if(this->loadCtx != NULL)
        delete this->loadCtx;
    if(this->saveCtx != NULL)
        delete this->saveCtx;
    if(this->endRoundCtx != NULL)
        delete this->endRoundCtx;
    if(this->podium != NULL)
        delete this->podium;

    delete this->window;
}

void GameField::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        break;
    default:
        break;
    }
}

void GameField::init()
{
    this->insertLayouts();
    this->assignButtons();
    this->assignPlayerNameLabels();
    this->assignPlayerPointsLabels();
    this->assignCategoryLabels();
    this->setCategoryNames();
    this->setNames();
    this->setPoints();
    this->setLabelColor();

    /* Declare new context menu and connect it with the right mouse button */
    this->window->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this->window, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(on_gameField_customContextMenuRequested(QPoint)));

    this->window->show();
}

void GameField::setRound(int round)
{
    this->round = round;
}

int GameField::getRound()
{
    return this->round;
}

void GameField::incAlreadyAnswered(int number)
{
    this->alreadyAnswered += number;
}

void GameField::setAlreadyAnswered(int number)
{
    this->alreadyAnswered = number;
}

int GameField::getAlreadyAnswered()
{
    return this->alreadyAnswered;
}

void GameField::insertLayouts()
{
    this->window = new QWidget();
    this->window->setGeometry(0, 0, GAMEFIELD_WIDTH, GAMEFIELD_HEIGHT);

    this->mainGrid = new QGridLayout();
    this->mainGrid->setSpacing(0);

    this->categoryLabelGrid = new QGridLayout();
    this->categoryLabelGrid->setSpacing(0);

    this->buttonGrid = new QGridLayout();
    this->buttonGrid->setSpacing(0);

    this->playerLabelGrid = new QGridLayout();
    this->playerLabelGrid->setSpacing(0);

    this->mainGrid->addLayout(this->categoryLabelGrid, 0, 0);
    this->mainGrid->addLayout(this->buttonGrid, 1, 0);
    this->mainGrid->addLayout(this->playerLabelGrid, 2, 0);

    this->mainGrid->setGeometry(QRect(0, 0, GAMEFIELD_WIDTH, GAMEFIELD_HEIGHT));
    this->categoryLabelGrid->setGeometry(QRect(0, 0, GAMEFIELD_WIDTH, CATEGORY_LABEL_HEIGHT));
    this->buttonGrid->setGeometry(QRect(0, CATEGORY_LABEL_HEIGHT, GAMEFIELD_WIDTH, GAMEFIELD_HEIGHT - CATEGORY_LABEL_HEIGHT - NAME_LABEL_HEIGHT - NAME_LABEL_HEIGHT));
    this->playerLabelGrid->setGeometry(QRect(0, GAMEFIELD_HEIGHT - NAME_LABEL_HEIGHT - NAME_LABEL_HEIGHT, GAMEFIELD_WIDTH, NAME_LABEL_HEIGHT + NAME_LABEL_HEIGHT));

    this->window->setLayout(this->mainGrid);
}

void GameField::assignCategoryLabels()
{
    int width, height;

    width = GAMEFIELD_WIDTH / this->categoryNr;
    height = CATEGORY_LABEL_HEIGHT;

    for(int i = 0; i < this->categoryNr; i++)
    {
        this->categoryLabels[i]->setGeometry(0, 0, width, height);
        this->categoryLabels[i]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        this->categoryLabelGrid->addWidget(this->categoryLabels[i], 0, i);
    }
}

void GameField::assignButtons()
{
    int width, height;

    QFont font;
    font.setPointSize(20);

    width = GAMEFIELD_WIDTH / this->categoryNr;
    height = (GAMEFIELD_HEIGHT - CATEGORY_LABEL_HEIGHT - NAME_LABEL_HEIGHT - NAME_LABEL_HEIGHT) / NUMBER_ANSWERS;

    for(int j = 0; j < this->categoryNr; j++)
    {
        for(int i = 0; i < NUMBER_ANSWERS; i++)
        {
            int currentButton = (NUMBER_MAX_CATEGORIES * i) + j;

            this->buttons[currentButton]->setFont(font);
            this->buttons[currentButton]->setText(QString("%1").arg((i + 1) * POINTS_FACTOR));
            this->buttons[currentButton]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            this->categoryLabelGrid->addWidget(this->buttons[currentButton], i+1, j);
        }
    }

        connect(this->buttons[0], SIGNAL(clicked()), this, SLOT(on_button_1_100_clicked()));
        connect(this->buttons[6], SIGNAL(clicked()), this, SLOT(on_button_1_200_clicked()));
        connect(this->buttons[12], SIGNAL(clicked()), this, SLOT(on_button_1_300_clicked()));
        connect(this->buttons[18], SIGNAL(clicked()), this, SLOT(on_button_1_400_clicked()));
        connect(this->buttons[24], SIGNAL(clicked()), this, SLOT(on_button_1_500_clicked()));

    if(this->categoryNr >= 2)
    {
        connect(this->buttons[1], SIGNAL(clicked()), this, SLOT(on_button_2_100_clicked()));
        connect(this->buttons[7], SIGNAL(clicked()), this, SLOT(on_button_2_200_clicked()));
        connect(this->buttons[13], SIGNAL(clicked()), this, SLOT(on_button_2_300_clicked()));
        connect(this->buttons[19], SIGNAL(clicked()), this, SLOT(on_button_2_400_clicked()));
        connect(this->buttons[25], SIGNAL(clicked()), this, SLOT(on_button_2_500_clicked()));
    }

    if(this->categoryNr >= 3)
    {
        connect(this->buttons[2], SIGNAL(clicked()), this, SLOT(on_button_3_100_clicked()));
        connect(this->buttons[8], SIGNAL(clicked()), this, SLOT(on_button_3_200_clicked()));
        connect(this->buttons[14], SIGNAL(clicked()), this, SLOT(on_button_3_300_clicked()));
        connect(this->buttons[20], SIGNAL(clicked()), this, SLOT(on_button_3_400_clicked()));
        connect(this->buttons[26], SIGNAL(clicked()), this, SLOT(on_button_3_500_clicked()));
    }

    if(this->categoryNr >= 4)
    {
        connect(this->buttons[3], SIGNAL(clicked()), this, SLOT(on_button_4_100_clicked()));
        connect(this->buttons[9], SIGNAL(clicked()), this, SLOT(on_button_4_200_clicked()));
        connect(this->buttons[15], SIGNAL(clicked()), this, SLOT(on_button_4_300_clicked()));
        connect(this->buttons[21], SIGNAL(clicked()), this, SLOT(on_button_4_400_clicked()));
        connect(this->buttons[27], SIGNAL(clicked()), this, SLOT(on_button_4_500_clicked()));
    }

    if(this->categoryNr >= 5)
    {
        connect(this->buttons[4], SIGNAL(clicked()), this, SLOT(on_button_5_100_clicked()));
        connect(this->buttons[10], SIGNAL(clicked()), this, SLOT(on_button_5_200_clicked()));
        connect(this->buttons[16], SIGNAL(clicked()), this, SLOT(on_button_5_300_clicked()));
        connect(this->buttons[22], SIGNAL(clicked()), this, SLOT(on_button_5_400_clicked()));
        connect(this->buttons[28], SIGNAL(clicked()), this, SLOT(on_button_5_500_clicked()));
    }

    if(this->categoryNr >= 6)
    {
        connect(this->buttons[5], SIGNAL(clicked()), this, SLOT(on_button_6_100_clicked()));
        connect(this->buttons[11], SIGNAL(clicked()), this, SLOT(on_button_6_200_clicked()));
        connect(this->buttons[17], SIGNAL(clicked()), this, SLOT(on_button_6_300_clicked()));
        connect(this->buttons[23], SIGNAL(clicked()), this, SLOT(on_button_6_400_clicked()));
        connect(this->buttons[29], SIGNAL(clicked()), this, SLOT(on_button_6_500_clicked()));
    }
}

void GameField::assignPlayerNameLabels()
{
    int row, column, width, height;

    height = NAME_LABEL_HEIGHT;

    for(int i = 0; i < this->playerNr; i++)
    {
        if((i + 1) <= NUMBER_MAX_PLAYERS / 2)
        {
            row = FIRST_LABEL_ROW;
            column = i * 2;
            width = GAMEFIELD_WIDTH / this->playerNr / SPLIT_FOR_TWO_LABELS;
        }
        else
        {
            row = FIRST_LABEL_ROW + 1;
            column = (i - 3) * 2;
            width = GAMEFIELD_WIDTH / (NUMBER_MAX_PLAYERS / 2) / SPLIT_FOR_TWO_LABELS;
        }

        this->playerNameLabels[i]->setGeometry(0, 0, width, height);
        this->playerNameLabels[i]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        this->playerLabelGrid->addWidget(this->playerNameLabels[i], row, column);
    }
}

void GameField::assignPlayerPointsLabels()
{
    int row, column, width, height;

    height = NAME_LABEL_HEIGHT;

    for(int i = 0; i < this->playerNr; i++)
    {
        if((i+1) <= NUMBER_MAX_PLAYERS / 2)
        {
            row = FIRST_LABEL_ROW;
            column = 2 * i + 1;
            width = GAMEFIELD_WIDTH / this->playerNr / SPLIT_FOR_TWO_LABELS;
        }
        else
        {
            row = FIRST_LABEL_ROW + 1;
            column = 2 * (i - 3) + 1;
            width = GAMEFIELD_WIDTH / (NUMBER_MAX_PLAYERS / 2) / SPLIT_FOR_TWO_LABELS;
        }

        this->playerPointsLabels[i]->setGeometry(0, 0, width, height);
        this->playerPointsLabels[i]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        this->playerLabelGrid->addWidget(this->playerPointsLabels[i], row, column);
    }
}

/* Todo: refactor */
void GameField::setCategoryNames()
{
    int categoryLine;
    QFont font;
    QString categoryName;

    this->fileString = QString("answers/%1.jrf").arg(this->round);
    QFile file(this->fileString);
    font.setBold(true);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::critical(this, tr("Error"), tr("Could not open round file, please select one by yourself"));

        this->fileString = QFileDialog::getOpenFileName(this, tr("Open File"), "answers/", tr("Jeopardy Round File (*.jrf)"));
    }

    for(int i = 0; i < this->categoryNr; i++)
    {
        QFile file(this->fileString);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
          QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
          return;
        }

        QTextStream in(&file);

        /* Calculate on which line the categories in the file start */
        categoryLine = NUMBER_MAX_CATEGORIES * i + 1;

        /* Step to appropriate category section */
        for(int lineNr = 0; lineNr != categoryLine; lineNr++)
            categoryName = in.readLine();

        this->categoryLabels[i]->setFont(font);
        this->categoryLabels[i]->setGeometry(0, 0, GAMEFIELD_WIDTH / this->categoryNr, CATEGORY_LABEL_HEIGHT);
        this->categoryLabels[i]->setAlignment(Qt::AlignHCenter);
        this->categoryLabels[i]->setText(categoryName);
    }
}

void GameField::setLabelColor()
{
    QString color;

    for(int i = 0; i < this->playerNr; i++)
    {
        color = QString("QLabel { background-color : %1; }").arg(this->players[i].getColor());
        this->playerNameLabels[i]->setStyleSheet(color);
    }
}

void GameField::setPoints()
{
    for(int i = 0; i < this->playerNr; i++)
        this->playerPointsLabels[i]->setText("0");
}

void GameField::setNames()
{
    for(int i = 0; i < this->playerNr; i++)
        this->playerNameLabels[i]->setText(this->players[i].getName());
}

void GameField::updateGameFieldValues()
{
    this->updatePointsLabels();
    this->updateNamesLabels();
    this->setLabelColor();
}

void GameField::updatePointsLabels()
{
    for(int i = 0; i < this->playerNr; i++)
        this->playerPointsLabels[i]->setText(QString::number(this->players[i].getPoints()));
}

void GameField::updateNamesLabels()
{
    for(int i = 0; i < this->playerNr; i++)
        this->playerNameLabels[i]->setText(this->players[i].getName());
}

void GameField::updateLabelsAfterAnswer()
{
    this->updatePointsLabels();
    this->updateNamesLabels();
}

void GameField::updateAfterAnswer()
{
    this->incAlreadyAnswered(1);
    this->updateLabelsAfterAnswer();
}

QString GameField::getButtonColorByLastWinner()
{
    QString color = "";

    if(this->lastWinner == NO_WINNER)
        return color;

    color = QString("QPushButton { background-color : %1; }").arg(this->players[this->lastWinner].getColor());

    return color;
}

void GameField::openAnswer(int category, int points)
{
    this->answer = new Answer(this, this->fileString, this->round, this->players, this->playerNr, this->sound);
    this->answer->setAnswer(category, points);

    this->lastWinner = this->answer->exec();
    this->buttons[NUMBER_MAX_CATEGORIES * (points / POINTS_FACTOR - OFFSET) + category - OFFSET]->setStyleSheet(this->getButtonColorByLastWinner());
    this->lastPoints = this->answer->getPoints();
    this->result = answer->getResult();

    this->processResult();
    this->updateAfterAnswer();

    if(this->getAlreadyAnswered() < this->categoryNr * NUMBER_ANSWERS)
    {
        /* Do backup after each answer */
        this->openFileSaver(true);
    }
    else
    {
        this->showPodium();
        this->window->close();
    }
}

void GameField::processResult()
{
    int playerId;

    while(this->result.length() > 0)
    {
        for(int i = 0; i < NUMBER_MAX_PLAYERS; i++)
            if(this->result.startsWith(QString::number(i+1)))
                playerId = i;

        this->result.remove(0, PLAYER_INDICATOR);

        if(this->result.startsWith(WON))
            this->players[playerId].incPoints(this->lastPoints);
        else
            this->players[playerId].decPoints(this->lastPoints);

        this->result.remove(0, RESULT_INDICATOR);
    }
}

void GameField::openFileLoader()
{
    int lineNr = 0;
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "gameStates/", tr("Jeopardy Game States (*.jgs)"));

    if(fileName != "")
    {
      QFile file(fileName);
      if (!file.open(QIODevice::ReadOnly))
      {
        QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
        return;
      }
      QTextStream in(&file);
      while(!in.atEnd())
      {
          QString line = in.readLine();

          if(0 <= lineNr && lineNr <= NUMBER_MAX_PLAYERS-1)
              this->players[lineNr].setName(line);

          else if(NUMBER_MAX_PLAYERS <= lineNr && lineNr <= (NUMBER_MAX_PLAYERS*2-1))
              this->players[lineNr - NUMBER_MAX_PLAYERS].setPoints(line.toInt());

          else if((NUMBER_MAX_PLAYERS*2) <= lineNr && lineNr <= (NUMBER_MAX_PLAYERS*3-1))
              this->players[lineNr - (NUMBER_MAX_PLAYERS*2)].setColor(line);

          /* Already questioned answers */
          else if((NUMBER_MAX_PLAYERS*3) <= lineNr && lineNr <= (NUMBER_MAX_PLAYERS*3-1)+NUMBER_MAX_ANSWERS)
              this->buttons[lineNr - (NUMBER_MAX_PLAYERS*3)]->setDisabled(line.toInt());

          /* Color buttons with player color */
          else if((NUMBER_MAX_PLAYERS*3+NUMBER_MAX_ANSWERS) <= lineNr && lineNr <= (NUMBER_MAX_PLAYERS*3-1)+(2*NUMBER_MAX_ANSWERS))
          {
              if(line == "r")
                  line = "red";
              else if (line == "g")
                  line = "green";
              else if(line == "y")
                  line = "yellow";
              else if(line == "b")
                  line = "blue";
              else if(line == "gr")
                  line = "gray";
              else if(line == "m")
                  line = "magenta";

              line.prepend("QPushButton { background-color : ");
              line.append("; }");
              this->buttons[lineNr - (NUMBER_MAX_PLAYERS*3+NUMBER_MAX_ANSWERS)]->setStyleSheet(line);
          }
          else if(lineNr == (NUMBER_MAX_PLAYERS*3)+(2*NUMBER_MAX_ANSWERS))
              this->alreadyAnswered = line.toInt();

          else if(lineNr == (NUMBER_MAX_PLAYERS*3)+(2*NUMBER_MAX_ANSWERS)+1)
          {
              if(this->playerNr != line.toInt())
                  QMessageBox::critical(this, tr("Error"), QString("PlayerNr of current round (%1) and saved game state PlayerNr (%2) aren't equal! This could lead to problems!").arg(this->playerNr).arg(line.toInt()));

              this->playerNr = line.toInt();
          }

          else if(lineNr == (NUMBER_MAX_PLAYERS*3)+(2*NUMBER_MAX_ANSWERS)+2)
          {
              if(this->categoryNr != line.toInt())
                  QMessageBox::critical(this, tr("Error"), QString("CategoryNr of current round (%1) and saved game state CategoryNr (%2) aren't equal! This could lead to problems!").arg(this->categoryNr).arg(line.toInt()));

              this->categoryNr = line.toInt();
          }

          lineNr++;
      }

      this->updateGameFieldValues();
      file.close();
    }
}

void GameField::openFileSaver(bool backup)
{
    QString fileName;
    QDateTime dateTime;

    if(backup == true)
    {
        fileName = QString("gameStates/backups/backup_%1_%2").arg(this->getRound()).arg(dateTime.currentDateTime().toTime_t());
    }
    else
        fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "gameStates/", tr("Jeopardy Game States (*.jgs)"));

    if(NOT == fileName.endsWith(".jgs"))
        fileName.append(".jgs");

    if (fileName != "")
    {
      QFile file(fileName);
      if (!file.open(QIODevice::WriteOnly))
      {
        QMessageBox::critical(this, tr("Error"), tr("File not writeable"));
        return;
      }
      else
      {
        QTextStream stream(&file);

        for(int i = 0; i < NUMBER_MAX_PLAYERS; i++)
            stream << this->players[i].getName() << '\n';

        for(int i = 0; i < NUMBER_MAX_PLAYERS; i++)
            stream << this->players[i].getPoints() << '\n';

        for(int i = 0; i < NUMBER_MAX_PLAYERS; i++)
            stream << this->players[i].getColor() << '\n';

        for(int i = 0; i < NUMBER_MAX_ANSWERS; i++)
            stream << !this->buttons[i]->isEnabled() << '\n';

        for(int i = 0; i < NUMBER_MAX_ANSWERS; i++)
        {
            /* Just save first character of color */
            QString stylesheet = this->buttons[i]->styleSheet();
            stylesheet.remove(0,COLOR_TEXT_LENGTH);
            if(stylesheet.startsWith("gray"))
            {
                stylesheet = "gr";
            }
            else
            {
                int len = stylesheet.length();
                stylesheet.chop(--len);
            }

            stream << stylesheet << '\n';
        }

        stream << this->alreadyAnswered << '\n';
        stream << this->playerNr << '\n';
        stream << this->categoryNr << '\n';

        stream.flush();
        file.close();
        }
    }
}

void GameField::openEditor()
{
    this->editor = new Editor(this, this->players, this->playerNr);
    editor->show();

    this->updateGameFieldValues();
}

void GameField::random()
{
    srand(time(NULL));

    int rn = rand() % this->playerNr;

    QMessageBox *msgbox = new QMessageBox();
    msgbox->setWindowTitle("R");
    QString text;

    if(this->players[rn].getName().endsWith("s"))
        text = QString("%1 turn").arg(this->players[rn].getName());
    else
        text = QString("%1's turn").arg(this->players[rn].getName());

    msgbox->setText(text);

    msgbox->exec();

    delete msgbox;
}

void GameField::on_gameField_customContextMenuRequested(QPoint pos)
{
    QPoint globalPos = this->window->mapToGlobal(pos);

    QMenu menu;
    this->randomCtx = new QAction("Random Generator", this);
    this->editorCtx = new QAction("Editor",this);
    this->loadCtx = new QAction("Load",this);
    this->saveCtx = new QAction("Save",this);
    this->endRoundCtx = new QAction("End Round", this);

    menu.addAction(this->randomCtx);
    menu.addSeparator();
    menu.addAction(this->editorCtx);
    menu.addSeparator();
    menu.addAction(this->loadCtx);
    menu.addAction(this->saveCtx);
    menu.addSeparator();
    menu.addAction(this->endRoundCtx);

    QAction *selectedItem = menu.exec(globalPos);

    if(selectedItem == this->randomCtx)
        this->random();
    else if(selectedItem == this->editorCtx)
        this->openEditor();
    else if(selectedItem == this->saveCtx)
        this->openFileSaver(false);
    else if(selectedItem == this->loadCtx)
        this->openFileLoader();
    else if(selectedItem == this->endRoundCtx)
    {
        this->showPodium();
        this->window->close();
    }
}

void GameField::showPodium()
{
    this->podium = new Podium(this, this->players, this->playerNr);
    this->podium->exec();
}

/* 100 points buttons */
void GameField::on_button_1_100_clicked()
{
    this->buttons[0]->setDisabled(true);
    this->openAnswer(1, 100);
}
void GameField::on_button_2_100_clicked()
{
    this->buttons[1]->setDisabled(true);
    this->openAnswer(2, 100);
}
void GameField::on_button_3_100_clicked()
{
    this->buttons[2]->setDisabled(true);
    this->openAnswer(3, 100);
}
void GameField::on_button_4_100_clicked()
{
    this->buttons[3]->setDisabled(true);
    this->openAnswer(4, 100);
}
void GameField::on_button_5_100_clicked()
{
    this->buttons[4]->setDisabled(true);
    this->openAnswer(5, 100);
}
void GameField::on_button_6_100_clicked()
{
    this->buttons[5]->setDisabled(true);
    this->openAnswer(6, 100);
}
/* 200 points buttons */
void GameField::on_button_1_200_clicked()
{
    this->buttons[6]->setDisabled(true);
    this->openAnswer(1, 200);
}
void GameField::on_button_2_200_clicked()
{
    this->buttons[7]->setDisabled(true);
    this->openAnswer(2, 200);
}
void GameField::on_button_3_200_clicked()
{
    this->buttons[8]->setDisabled(true);
    this->openAnswer(3, 200);
}
void GameField::on_button_4_200_clicked()
{
    this->buttons[9]->setDisabled(true);
    this->openAnswer(4, 200);
}
void GameField::on_button_5_200_clicked()
{
    this->buttons[10]->setDisabled(true);
    this->openAnswer(5, 200);
}
void GameField::on_button_6_200_clicked()
{
    this->buttons[11]->setDisabled(true);
    this->openAnswer(6, 200);
}
/* 300 points buttons */
void GameField::on_button_1_300_clicked()
{
    this->buttons[12]->setDisabled(true);
    this->openAnswer(1, 300);
}
void GameField::on_button_2_300_clicked()
{
    this->buttons[13]->setDisabled(true);
    this->openAnswer(2, 300);
}
void GameField::on_button_3_300_clicked()
{
    this->buttons[14]->setDisabled(true);
    this->openAnswer(3, 300);
}
void GameField::on_button_4_300_clicked()
{
    this->buttons[15]->setDisabled(true);
    this->openAnswer(4, 300);
}
void GameField::on_button_5_300_clicked()
{
    this->buttons[16]->setDisabled(true);
    this->openAnswer(5, 300);
}
void GameField::on_button_6_300_clicked()
{
    this->buttons[17]->setDisabled(true);
    this->openAnswer(6, 300);
}
/* 400 points buttons */
void GameField::on_button_1_400_clicked()
{
    this->buttons[18]->setDisabled(true);
    this->openAnswer(1, 400);
}
void GameField::on_button_2_400_clicked()
{
    this->buttons[19]->setDisabled(true);
    this->openAnswer(2, 400);
}
void GameField::on_button_3_400_clicked()
{
    this->buttons[20]->setDisabled(true);
    this->openAnswer(3, 400);
}
void GameField::on_button_4_400_clicked()
{
    this->buttons[21]->setDisabled(true);
    this->openAnswer(4, 400);
}
void GameField::on_button_5_400_clicked()
{
    this->buttons[22]->setDisabled(true);
    this->openAnswer(5, 400);
}
void GameField::on_button_6_400_clicked()
{
    this->buttons[23]->setDisabled(true);
    this->openAnswer(6, 400);
}
/* 500 points buttons */
void GameField::on_button_1_500_clicked()
{
    this->buttons[24]->setDisabled(true);
    this->openAnswer(1, 500);
}
void GameField::on_button_2_500_clicked()
{
    this->buttons[25]->setDisabled(true);
    this->openAnswer(2, 500);
}
void GameField::on_button_3_500_clicked()
{
    this->buttons[26]->setDisabled(true);
    this->openAnswer(3, 500);
}
void GameField::on_button_4_500_clicked()
{
    this->buttons[27]->setDisabled(true);
    this->openAnswer(4, 500);
}
void GameField::on_button_5_500_clicked()
{
    this->buttons[28]->setDisabled(true);
    this->openAnswer(5, 500);
}
void GameField::on_button_6_500_clicked()
{
    this->buttons[29]->setDisabled(true);
    this->openAnswer(6, 500);
}
