#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    // Ходы                     Очки                        Данные ячеек
    int getMoveValue();         int getScoreValue();        int getGameData(int x, int y);
    int setMoveValue(int i);    int setScoreValue(int i);   int setGameData(int x, int y, int val);
    int moveValuePlus();        int scoreValuePlus(int i);

    // Управление
    void moveUp();              void moveDown();
    void moveLeft();            void moveRight();

    void delay();

    void generateCell(bool boolean);

    // Победитель
    bool setWinner(bool value); bool getWinner();
    void Winner();

    // Статус игры
    bool setGameStatus(bool status);   bool getGameStatus();

    void gameOver();

private:
    Ui::MainWindow *ui;

    // +---------------+
    // |   gameData    |
    // +---------------+
    // | 0 | 0 | 0 | 0 |
    // | 0 | 0 | 0 | 0 |
    // | 0 | 0 | 0 | 0 |
    // | 0 | 0 | 0 | 0 |
    // +---------------+

    // Шаги         Очки            Ячейки игрового поля
    int moves;      int scores;     int gameData[4][4];

    bool gameStatus;
    bool winner;

protected:
    void keyPressEvent(QKeyEvent *e);

public slots:
    void About();
    void NewGame();
    void Exit();
};

#endif // MAINWINDOW_H
