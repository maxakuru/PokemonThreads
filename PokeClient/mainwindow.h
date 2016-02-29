#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QStack>
#include <QVector>
#include <QGraphicsView>
#include <QPixmap>
#include "Pokemon.h"
#include <sstream>
#include <iostream>
#include "socket.h"
#include "stdio.h"
#include <QDebug>
#include <string>
#include <time.h>
#include <QtNetwork/QLocalSocket>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    //WorkerThread *wThread;
    void drawOpPokemon();
    void drawMyPokemon();
    void repaintAll();
    void setStatus(QString status);
    void updateGame();
    void receiveDmg(int dmg);
    int getDamageToDeal(int buttonNumber);
    void dealDamage(int dmg);
    void setOpNextPokemon();
    void setMyNextPokemon();
    void updateUI();
    void refreshHealth();
    int myCurrentPokemon;
    int opCurrentPokemon;
    int myCurrentHealth;
    int opCurrentHealth;
    int myCurrentPNo = 0;
    int opCurrentPNo = 0;
    int myPhealths[3] = {200,200,200};
    int opPhealths[3] = {200,200,200};
    QVector<Pokemon*> allPokemon;
    QStack<Pokemon> myPokemon;
    QStack<Pokemon> opPokemon;
    ~MainWindow();
    
public slots:
    //void onValueChanged(int);

private slots:
    void on_attack1_clicked();

    void on_attack2_clicked();

    void on_attack3_clicked();

    void on_startButton_clicked();

    void on_exitButton_clicked();

    void on_leaveButton_clicked();
    void onSocketStuff();

private:
    Ui::MainWindow *ui;
    QVector<Pokemon*> opPokemonSet;
    QVector<Pokemon*> myPokemonSet;
    QGraphicsScene *myScene;
    QGraphicsScene *opScene;
    QGraphicsView myView;
    QGraphicsView opView;
    QRectF recto;
    QRectF recto2;
    bool gameStarted = false;
    std::stringstream stream;
    int myPNumbers[3];
    int opPNumbers[3];
    bool quitGame = false;
    int clientID = 0;
    bool turn = true;
    Communication::Socket *theSocket;
};

#endif // MAINWINDOW_H
