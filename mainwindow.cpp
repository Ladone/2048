#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include "QKeyEvent"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Инициализация
    ui->lblScore->hide();
    ui->scoreValue->hide();
    ui->lblMove->hide();
    ui->moveValue->hide();
    setGameStatus(false);

    MainWindow::setWinner(false);

    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            MainWindow::setGameData(i, j, 0);
        }
    }

    // Обнуление счетчиков
    MainWindow::setMoveValue(0);
    MainWindow::setScoreValue(0);

    // Генерация пустых значений для gameGrid
    for (int x=0; x<4; x++)
           for (int y = 0; y<4; y++)
                   ui->gameGrid->setItem(x, y, new QTableWidgetItem(""));


    // Автоматическая ширина и высота ячеек
    ui->gameGrid->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->gameGrid->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->gameGrid->


    // Связь сигналов и слотов
    connect(ui->actionAbout, SIGNAL(triggered(bool)), this, SLOT(About())); // Окно about
    connect(ui->actionNew_game, SIGNAL(triggered(bool)), this, SLOT(NewGame()));
    connect(ui->actionExit, SIGNAL(triggered(bool)), this, SLOT(Exit()));

 }

MainWindow::~MainWindow()
{
    delete ui;
}

// Кнопка обо мне
void MainWindow::About(){
    //QMessageBox::information(this,"About","Game 2048\n"
    //                                     "By Pototskiy Vlad\n"
    //                                     "pototskiyvl@gmail.com\n\n"
    //                                     "Version 0.1 (09/19/2016)");
    QMessageBox messageBox;
    messageBox.setIconPixmap(QPixmap(":/images/photo.jpg"));
    messageBox.setWindowTitle("About");
    messageBox.setWindowIcon(QIcon(":/images/icons/ico.png"));
    messageBox.setText("Game 2048\n"
                       "By Pototskiy Vlad\n"
                       "pototskiyvl@gmail.com\n\n"
                       "Version 1.0 (10/22/2016)");
    messageBox.exec();
}

// Кнопка выхода
void MainWindow::Exit(){
    QApplication::quit();
}


// Кнопка новой игры
void MainWindow::NewGame(){
    // CSS
    ui->gameGrid->setStyleSheet("background: white;"
                                "color: black;"
                                "font-weight: bold;"
                                "font-size: 25px;"
                                );

    // Обнуление счетчиков
    MainWindow::setGameStatus(true);
    MainWindow::setWinner(false);
    MainWindow::setMoveValue(0);
    MainWindow::setScoreValue(0);

    // Инициализация
    ui->scoreValue->setText(QString::number(MainWindow::getScoreValue()));
    ui->moveValue->setText(QString::number(MainWindow::getMoveValue()));
    ui->lblScore->show();
    ui->scoreValue->show();
    ui->lblMove->show();
    ui->moveValue->show();


    for (int x=0; x<4; x++){
      for (int y = 0; y<4; y++){
          if (qrand()%5==0)
          {
              MainWindow::setGameData(x, y, 2);
          }
          else if (qrand()%10==0)
          {
              MainWindow::setGameData(x, y, 4);
          }
          else
          {
              MainWindow::setGameData(x, y, 0);
          }

          if(MainWindow::getGameData(x, y) == 0){
              ui->gameGrid->item(x, y)->setData(Qt::DisplayRole, QVariant(""));
          }
          else{
              ui->gameGrid->item(x, y)->setData(Qt::DisplayRole, QVariant(MainWindow::getGameData(x, y)));
          }
        }
    }

}

void MainWindow::keyPressEvent(QKeyEvent *e){
    if(MainWindow::getGameStatus() == true){
        switch(e->key()){
            case Qt::Key_Up:
            {
                MainWindow::moveUp();
                break;
            }
            case Qt::Key_Down:
            {
                MainWindow::moveDown();
                break;
            }
            case Qt::Key_Left:
            {
                MainWindow::moveLeft();
                break;
            }
            case Qt::Key_Right:
            {
                MainWindow::moveRight();
                break;
            }
        }
    }

    // Обновление счетчиков
    ui->moveValue->setText(QString::number(MainWindow::getMoveValue()));
    ui->scoreValue->setText(QString::number(MainWindow::getScoreValue()));
    MainWindow::gameOver();
    MainWindow::Winner();
}

// Шаги
int MainWindow::setMoveValue(int i){
    return this->moves = i;
}

int MainWindow::getMoveValue(){
    return this->moves;
}

int MainWindow::moveValuePlus(){
    return this->moves++;
}

// Очки
int MainWindow::setScoreValue(int i){
    return this->scores = i;
}

int MainWindow::getScoreValue(){
    return this->scores;
}

int MainWindow::scoreValuePlus(int i){
    return this->scores += i;
}

// Данные игры
int MainWindow::setGameData(int x, int y, int val){
    return this->gameData[x][y] = val;
}

int MainWindow::getGameData(int x, int y){
    int val = this->gameData[x][y];
    return val;
}

// Сдвиг чисел в верх
void MainWindow::moveUp(){

    bool move = false;

    // Сдвиг в верх
    for(int x =0; x<4; x++){
        for(int y=0; y<4; y++){
            if(MainWindow::getGameData(x, y) == 0){
                for (int i = x; i < 4; i++){
                    if(MainWindow::getGameData(i, y) != 0){
                        MainWindow::setGameData(x, y, MainWindow::getGameData(i, y));
                        MainWindow::setGameData(i, y, 0);
                        move = true;
                        break;
                    }
                }
            }
        }
    }

    // Сложение в верх
    for(int x = 0; x<4; x++){
        for(int y = 0; y<4; y++){
            if(x<3 && MainWindow::getGameData(x, y) == MainWindow::getGameData(x+1, y)){
                MainWindow::setGameData(x, y, MainWindow::getGameData(x, y)*2);
                MainWindow::scoreValuePlus(MainWindow::getGameData(x, y));
                MainWindow::setGameData(x+1, y, 0);
                move = true;
            }

            // Дополнительная проверка для того что бы не было пустых значений
            for(int x =0; x<4; x++){
                for(int y=0; y<4; y++){
                    if(MainWindow::getGameData(x, y) == 0){
                        for (int i = x; i < 4; i++){
                            if(MainWindow::getGameData(i, y) != 0){
                                MainWindow::setGameData(x, y, MainWindow::getGameData(i, y));
                                MainWindow::setGameData(i, y, 0);
                                break;
                            }
                        }
                    }
                }
            }

            if(MainWindow::getGameData(x, y) == 0){
                ui->gameGrid->item(x, y)->setData(Qt::DisplayRole, QVariant(""));;
            }
            else {
                ui->gameGrid->item(x, y)->setData(Qt::DisplayRole, QVariant(MainWindow::getGameData(x, y)));
            }
        }
    }

    if(move == true){
        MainWindow::generateCell(true);
        MainWindow::moveValuePlus();
    }

}

// Сдвиг чисел вниз
void MainWindow::moveDown(){

    bool move = false;

    // Сдвиг в вниз
    for(int x=3; x >= 0; x--){
        for(int y=3; y >= 0; y--){
            if(MainWindow::getGameData(x, y) == 0){
                for (int i = x; i >= 0; i--){
                    if(MainWindow::getGameData(i, y) != 0){
                        MainWindow::setGameData(x, y, MainWindow::getGameData(i, y));
                        MainWindow::setGameData(i, y, 0);
                        move = true;
                        break;
                    }
                }
            }
        }
    }

    // Сложение в Вниз
    for(int x = 3; x>=0; x--){
        for(int y = 3; y>=0; y--){
            if(x>0 &&MainWindow::getGameData(x, y) == MainWindow::getGameData(x-1, y)){
                MainWindow::setGameData(x, y, MainWindow::getGameData(x, y)*2);
                MainWindow::scoreValuePlus(MainWindow::getGameData(x, y));
                MainWindow::setGameData(x-1, y, 0);
                move = true;
            }

            // Дополнительная проверка для того что бы не было пустых значений
            for(int x=3; x >= 0; x--){
                for(int y=3; y >= 0; y--){
                    if(MainWindow::getGameData(x, y) == 0){
                        for (int i = x; i >= 0; i--){
                            if(MainWindow::getGameData(i, y) != 0){
                                MainWindow::setGameData(x, y, MainWindow::getGameData(i, y));
                                MainWindow::setGameData(i, y, 0);
                                break;
                            }
                        }
                    }
                }
            }


            if(MainWindow::getGameData(x, y) == 0){
                ui->gameGrid->item(x, y)->setData(Qt::DisplayRole, QVariant(""));;
            }
            else {
                ui->gameGrid->item(x, y)->setData(Qt::DisplayRole, QVariant(MainWindow::getGameData(x, y)));
            }
        }
    }

    if(move == true){
        MainWindow::generateCell(true);
        MainWindow::moveValuePlus();
    }
}

// Сдвиг чисел в влево
void MainWindow::moveLeft(){

    bool move = false;

    // Сдвиг в влево
    for(int x =0; x<4; x++){
        for(int y=0; y<4; y++){
            if(MainWindow::getGameData(x, y) == 0){
                for (int i = y; i < 4; i++){
                    if(MainWindow::getGameData(x, i) != 0){
                        MainWindow::setGameData(x, y, MainWindow::getGameData(x, i));
                        MainWindow::setGameData(x, i, 0);
                        move = true;
                        break;
                    }
                }
            }
        }
    }

    // Сложение в влево
    for(int x = 0; x<4; x++){
        for(int y = 0; y<4; y++){
            if(y<3 && MainWindow::getGameData(x, y) == MainWindow::getGameData(x, y+1)){
                MainWindow::setGameData(x, y, MainWindow::getGameData(x, y)*2);
                MainWindow::scoreValuePlus(MainWindow::getGameData(x, y));
                MainWindow::setGameData(x, y+1, 0);
                move = true;
            }
            // Дополнительная проверка для того что бы не было пустых значений
            for(int x =0; x<4; x++){
                for(int y=0; y<4; y++){
                    if(MainWindow::getGameData(x, y) == 0){
                        for (int i = y; i < 4; i++){
                            if(MainWindow::getGameData(x, i) != 0){
                                MainWindow::setGameData(x, y, MainWindow::getGameData(x, i));
                                MainWindow::setGameData(x, i, 0);
                                break;
                            }
                        }
                    }
                }
            }

            if(MainWindow::getGameData(x, y) == 0){
                ui->gameGrid->item(x, y)->setData(Qt::DisplayRole, QVariant(""));;
            }
            else {
                ui->gameGrid->item(x, y)->setData(Qt::DisplayRole, QVariant(MainWindow::getGameData(x, y)));
            }
        }
    }

    if(move == true){
        MainWindow::generateCell(true);
        MainWindow::moveValuePlus();
    }
}

// Сдвиг чисел в вправо
void MainWindow::moveRight(){

    bool move = false;

    // Сдвиг в вправо
    for(int x=0; x<4; x++){
        for(int y=3; y>=0; y--){
            if(MainWindow::getGameData(x, y) == 0){
                for (int i = y; i >= 0; i--){
                    if(MainWindow::getGameData(x, i) != 0){
                        MainWindow::setGameData(x, y, MainWindow::getGameData(x, i));
                        MainWindow::setGameData(x, i, 0);
                        move = true;
                        break;
                    }
                }
            }

            if(MainWindow::getGameData(x, y) == 0){
                ui->gameGrid->item(x, y)->setData(Qt::DisplayRole, QVariant(""));;
            }
            else {
                ui->gameGrid->item(x, y)->setData(Qt::DisplayRole, QVariant(MainWindow::getGameData(x, y)));
            }
        }
    }

    // Сложение в вправо
    for(int x = 0; x<4; x++){
        for(int y = 3; y>=0; y--){
            if(y>0 && MainWindow::getGameData(x, y) == MainWindow::getGameData(x, y-1)){
                MainWindow::setGameData(x, y, MainWindow::getGameData(x, y)*2);
                MainWindow::scoreValuePlus(MainWindow::getGameData(x, y));
                MainWindow::setGameData(x, y-1, 0);
                move = true;
            }
            // Дополнительная проверка для того что бы не было пустых значений
            for(int x =0; x<4; x++){
                for(int y=3; y>=0; y--){
                    if(MainWindow::getGameData(x, y) == 0){
                        for (int i = y; i >= 0; i--){
                            if(MainWindow::getGameData(x, i) != 0){
                                MainWindow::setGameData(x, y, MainWindow::getGameData(x, i));
                                MainWindow::setGameData(x, i, 0);
                                break;
                            }
                        }
                    }
                }
            }

            if(MainWindow::getGameData(x, y) == 0){
                ui->gameGrid->item(x, y)->setData(Qt::DisplayRole, QVariant(""));;
            }
            else {
                ui->gameGrid->item(x, y)->setData(Qt::DisplayRole, QVariant(MainWindow::getGameData(x, y)));
            }
        }
    }

    if(move == true){
        MainWindow::generateCell(true);
        MainWindow::moveValuePlus();
    }

}

// Генерация случайного числа
void MainWindow::generateCell(bool status){
    int x = qrand()%4;
    int y = qrand()%4;

    int availableCell = 0;

    for(int x=0; x<4; x++){
        for(int y=0; y<4; y++){
            if(MainWindow::getGameData(x, y) == 0){
                availableCell++;
            }
        }
    }

    int cellData = MainWindow::getGameData(x, y);
    if(status == true){
        if(cellData == 0){
            if(qrand()%5 == 0){
                MainWindow::setGameData(x, y, 2);
                ui->gameGrid->item(x, y)->setData(Qt::DisplayRole, QVariant(MainWindow::getGameData(x, y)));
                MainWindow::generateCell(false);
            }
            else
            {
                MainWindow::setGameData(x, y, 4);
                ui->gameGrid->item(x, y)->setData(Qt::DisplayRole, QVariant(MainWindow::getGameData(x, y)));
                MainWindow::generateCell(false);
            }
        }
        else {
            if(availableCell != 0){
                MainWindow::generateCell(true);
            }
        }
    }
}


// Статус игры
bool MainWindow::setGameStatus(bool status){
    return this->gameStatus = status;
}

bool MainWindow::getGameStatus(){
    return this->gameStatus;
}

bool MainWindow::setWinner(bool value){
    return this->winner = value;
}

bool MainWindow::getWinner(){
    return this->winner;
}

void MainWindow::Winner(){
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            if(MainWindow::getGameData(i, j) == 2048){
                MainWindow::setWinner(true);
                QMessageBox messageBox;
                //messageBox.setIconPixmap(QPixmap(":/images/photo.jpg"));
                messageBox.setWindowTitle("Congratulations!");
                messageBox.setWindowIcon(QIcon(":/images/icons/ico.png"));
                messageBox.setText("You Win!\n"
                                   "Score: " + QString::number(MainWindow::getScoreValue())
                                   + ", Move: " + QString::number(MainWindow::getMoveValue())
                                   + "\nPress \"OK\" to start new game!"
                                   );
                messageBox.exec();
                MainWindow::NewGame();
                break;
            }
        }
    }
}

void MainWindow::gameOver(){
    int combo = 0;

    for(int x=0; x<4; x++){
        for(int y=0; y<4; y++){
            if(MainWindow::getGameData(x, y) == MainWindow::getGameData(x+1, y) || MainWindow::getGameData(x, y) == 0){
                combo++;
            }
        }
    }

    for(int x=0; x<4; x++){
        for(int y=0; y<4; y++){
            if(MainWindow::getGameData(y, x) == MainWindow::getGameData(y+1, x) || MainWindow::getGameData(x, y) == 0){
                combo ++;
            }
        }
    }

    if(combo == 0){
        QMessageBox messageBox;
        //messageBox.setIconPixmap(QPixmap(":/images/photo.jpg"));
        messageBox.setWindowTitle("It's sou sad :c!");
        messageBox.setWindowIcon(QIcon(":/images/icons/ico.png"));
        messageBox.setText("Game over!\n"
                           "Score: " + QString::number(MainWindow::getScoreValue())
                           + ", Move: " + QString::number(MainWindow::getMoveValue())
                           + "\nPress \"OK\" to start new game!"
                           );
        messageBox.exec();
        MainWindow::NewGame();
    }
}
