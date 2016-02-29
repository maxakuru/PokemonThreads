#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "workerthread.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    /*
    wThread = new WorkerThread(this);
    connect(wThread, SIGNAL(valueChanged(int)),
               this, SLOT(onValueChanged(int)));
               */
    
    //create socket
    theSocket = new Communication::Socket("127.0.0.1", 2000);

    //set up scenes for each user image
    myScene = new QGraphicsScene(this);
    opScene = new QGraphicsScene(this);
    //QGraphicsScene myScene;
    //QGraphicsView myView(&myScene);
    ui->myPic->setScene(myScene);
    //QGraphicsScene opScene;
    ui->opPic->setScene(opScene);
    //QGraphicsView opView(&opScene);
    //ui->myPic->setScene(myScene);
    //ui->opPic->setScene(opScene);

    //set up my scene rectangle
/*
    recto = (ui->myPic->geometry());
    double xp = recto.x();
    double yp = recto.y();
    recto.setTop(0);
    recto.setBottom(recto.height()-(yp+5));
    recto.setLeft(0);
    recto.setRight(recto.width()-(xp+5));
    myScene->setSceneRect(recto);

    //set up op scene rectangle
    recto2 = (ui->opPic->geometry());
    double xp2 = recto2.x();
    double yp2 = recto2.y();
    recto2.setTop(0);
    recto2.setBottom(recto2.height()-(yp2+5));
    recto2.setLeft(0);
    recto2.setRight(recto2.width()-(xp2+5));
    opScene->setSceneRect(recto2);
*/

    //QGraphicsPixmapItem *item = new QGraphicsPixmapItem(QPixmap("://alakazam.png"));


    //create the pokemon objects and add to vector of pokemon
    allPokemon.push_back(new Pokemon(1,  QString("Alakazam"), QString("Confusion"), QString("Psybeam"), QString("Psychic"), QPixmap("://alakazam.png")));
    allPokemon.push_back(new Pokemon(2,  QString("Blastoise"), QString("Bubble"), QString("Skull Bash"), QString("Hydro Pump"), QPixmap("://blastoise.png")));
    allPokemon.push_back(new Pokemon(3,  QString("Charizard"), QString("Flamethrower"), QString("Seismic Toss"), QString("Fire Blast"), QPixmap("://charizard.png")));
    allPokemon.push_back(new Pokemon(4,  QString("Dragonite"), QString("Blizzard"), QString("Dragon Tail"), QString("Hurricane"), QPixmap("://dragonite.png")));
    allPokemon.push_back(new Pokemon(5,  QString("Chansey"), QString("Pound"), QString("Take Down"), QString("Egg Bomb"), QPixmap("://chansey.png")));
    allPokemon.push_back(new Pokemon(6,  QString("Gengar"), QString("Lick"), QString("Nightshade"), QString("Dark Pulse"), QPixmap("://gengar.png")));
    allPokemon.push_back(new Pokemon(7,  QString("Tangela"), QString("Razor Leaf"), QString("Vine Whip"), QString("Solar Beam"), QPixmap("://tangela.png")));
    allPokemon.push_back(new Pokemon(8,  QString("Raichu"), QString("Body Slam"), QString("Iron Tail"), QString("Thunder"), QPixmap("://raichu.png")));
    allPokemon.push_back(new Pokemon(9,  QString("Gyarados"), QString("Splash"), QString("Waterfall"), QString("Dragon Rage"), QPixmap("://gyarados.png")));
    allPokemon.push_back(new Pokemon(10,  QString("Mr. Mime"), QString("Mimic"), QString("Double Slap"), QString("Psybeam"), QPixmap("://mr-mime.png")));
    allPokemon.push_back(new Pokemon(11,  QString("Nidoking"), QString("Slash"), QString("Horn Drill"), QString("Earthquake"), QPixmap("://nidoking.gif")));
    //allPokemon.push_back(new Pokemon(12,  QString("Alakazam"), QString("at1"), QString("at2"), QString("at3"), QPixmap("://alakazam.png")));
    //allPokemon.append(new Pokemon(0, QString("Alakazam"), QString("attack1"), QString("attack2"), QString("attack3"), QPixmap("://alakazam.png")));
}

void MainWindow::drawOpPokemon()
{
    if(opCurrentPNo < 3){
        qDebug() << "made it here";
        opScene->clear();
        QGraphicsPixmapItem *item = new QGraphicsPixmapItem(allPokemon.at(opPNumbers[opCurrentPNo])->image.scaled(300, 300));
        opScene->addItem(item);
        ui->opPic->show();
        ui->opPic->repaint();
    }
}

void MainWindow::drawMyPokemon()
{
    if(myCurrentPNo < 3){
        myScene->clear();
        QGraphicsPixmapItem *item = new QGraphicsPixmapItem(allPokemon.at(myPNumbers[myCurrentPNo])->image.scaled(300,300));
        myScene->addItem(item);
        ui->myPic->show();
        ui->myPic->repaint();
    }
}

void MainWindow::repaintAll()
{
    ui->myHealth->repaint();
    ui->opHealth->repaint();
    ui->attack1->repaint();
    ui->attack2->repaint();
    ui->attack3->repaint();
    ui->opPic->repaint();
    ui->myPic->repaint();
    ui->opPokemonName->repaint();
    ui->myPokemonName->repaint();
}

void MainWindow::setStatus(QString status)
{
    ui->statusLabel->setText(status);
}

void MainWindow::updateGame()
{

}

void MainWindow::receiveDmg(int dmg)
{
    //check if opponent's health is above dmg dealt
    if(dmg < ui->myHealth->text().split("/")[0].toInt()){
        //if it is, take damage from total
        bool ok;
        ui->myHealth->setText((QString::number(ui->myHealth->text().split("/")[0].toInt(&ok, 10)-dmg)) + "/200");
    }

    //if it isn't, pokemon is dead
    else{
        ui->myHealth->setText("0/200");
        sleep(0.2);
        setMyNextPokemon();
    }

    //enable attack buttons and refresh my health bar
    ui->attack1->setEnabled(true);
    ui->attack2->setEnabled(true);
    ui->attack3->setEnabled(true);
    ui->statusLabel->setText("Choose your attack");
    //repaintAll();
}

int MainWindow::getDamageToDeal(int buttonNumber)
{
    int dmg = 0;

    switch(buttonNumber){

    case 1:  //calculate damage of first attack, unlikey but powerful
        qsrand(time(NULL));
        if(qrand()%100 > 80) //20% chance
        {
            dmg = 100; //deals 100 damage
        }
        break;
    case 2:  //calculate damage of second attack, moderate damage and chance
        qsrand(time(NULL));
        if(qrand()%100 > 50) //50% chance
        {
            dmg = 50;
        }
        break;
    case 3: //calculate damage of third attack, common but weak
        qsrand(time(NULL));
        if(qrand()%100 > 20) //80% chance
        {
            dmg = 20; //deals 20 damage
        }
        break;
    }

    return dmg;
}

void MainWindow::dealDamage(int dmg)
{
    ui->attack1->setEnabled(false);
    ui->attack2->setEnabled(false);
    ui->attack3->setEnabled(false);
    //check if opponent's health is above dmg dealt
    if(dmg < ui->opHealth->text().split("/")[0].toInt()){
        //if it is, take damage from total
        bool ok;
        ui->opHealth->setText((QString::number(ui->opHealth->text().split("/")[0].toInt(&ok, 10)-dmg)) + "/200");
        ui->opHealth->repaint();
    }
    //if it isn't, pokemon is dead
    else{
        ui->opHealth->setText("0/200");
        sleep(0.2);
        setOpNextPokemon();
        repaintAll();
    }

    //WAITING HERE

    //send the damage dealt thru socket to opponent
    try{
        Communication::ByteArray writeBA(std::to_string(dmg));
        theSocket->Write(writeBA);
    }
    catch(...){
        qDebug() << "something caught";
    }

    //now block while the other person attacks
    Communication::FlexWait waiter(1, theSocket);
    Communication::Blockable *result = waiter.Wait();
    if(result == theSocket)
    {
        //parse stuff into int
        Communication::ByteArray BA;
        theSocket->Read(BA);
        int dmg = QString::fromStdString(BA.ToString()).toInt();
        qDebug() << "damage received: " << dmg;
        if(dmg <1000 && dmg >=0)
        {
            receiveDmg(dmg);
            repaintAll();
        }
        else if(dmg <= -1){ //other client wants to leave
            ui->statusLabel->setText("Opponent has left the game, please restart");
            ui->attack1->setEnabled(false);
            ui->attack2->setEnabled(false);
            ui->attack3->setEnabled(false);
            ui->leaveButton->setEnabled(false);
            ui->exitButton->setEnabled(true);
        }
        else if(dmg == 1001){ //client 1 won
            if(clientID==1){
                ui->statusLabel->setText("You win!");
                ui->attack1->setEnabled(false);
                ui->attack2->setEnabled(false);
                ui->attack3->setEnabled(false);
                ui->leaveButton->setEnabled(false);
                ui->exitButton->setEnabled(true);
                ui->opHealth->setText("0/200");
            }
            else{
                ui->statusLabel->setText("You lose!");
                ui->attack1->setEnabled(false);
                ui->attack2->setEnabled(false);
                ui->attack3->setEnabled(false);
                ui->leaveButton->setEnabled(false);
                ui->exitButton->setEnabled(true);
                ui->myHealth->setText("0/200");
            }
        }
        else if(dmg==1002){ //client 2 won
            if(clientID==2){
                ui->statusLabel->setText("You win!");
                ui->attack1->setEnabled(false);
                ui->attack2->setEnabled(false);
                ui->attack3->setEnabled(false);
                ui->leaveButton->setEnabled(false);
                ui->exitButton->setEnabled(true);
                ui->opHealth->setText("0/200");
            }
            else{
                ui->statusLabel->setText("You lose!");
                ui->attack1->setEnabled(false);
                ui->attack2->setEnabled(false);
                ui->attack3->setEnabled(false);
                ui->leaveButton->setEnabled(false);
                ui->exitButton->setEnabled(true);
                ui->myHealth->setText("0/200");
            }
        }
        else if(dmg==1000){ //server wants to quit
            ui->statusLabel->setText("Server is no longer running, please restart");
            ui->attack1->setEnabled(false);
            ui->attack2->setEnabled(false);
            ui->attack3->setEnabled(false);
            ui->exitButton->setEnabled(true);
            ui->leaveButton->setEnabled(false);
        }
    }
}

void MainWindow::setOpNextPokemon()
{
    //check if opponent is on his last pokemon on not
    if(opCurrentPNo < 3){
        opCurrentPNo++;
        //update ui labels
        ui->opHealth->setText("200/200");
        if(opCurrentPNo == 1){
            ui->opPokeCount->setText("[ O O   ]");
        }
        else if(opCurrentPNo == 2)
        {
            ui->opPokeCount->setText("[ O     ]");
        }
        ui->opPokemonName->setText(allPokemon.at(opPNumbers[opCurrentPNo])->name);
        drawOpPokemon();
    }
    else{
        ui->opPokeCount->setText("[       ]");
        ui->statusLabel->setText("You win!");
        theSocket->Write(Communication::ByteArray("1002"));
    }
}

void MainWindow::setMyNextPokemon()
{
    //check if opponent is on his last pokemon on not
    if(myCurrentPNo < 3){
        myCurrentPNo++;
        //update ui labels
        ui->myHealth->setText("200/200");
        if(myCurrentPNo == 1){
            ui->myPokeCount->setText("[ O O   ]");
        }
        else if(myCurrentPNo == 2)
        {
            ui->myPokeCount->setText("[ O     ]");
        }
        ui->myPokemonName->setText(allPokemon.at(myPNumbers[myCurrentPNo])->name);
        ui->attack1->setText(allPokemon.at(myPNumbers[myCurrentPNo])->attack1);
        ui->attack2->setText(allPokemon.at(myPNumbers[myCurrentPNo])->attack2);
        ui->attack3->setText(allPokemon.at(myPNumbers[myCurrentPNo])->attack3);
        drawMyPokemon();
    }
    else
    {
        ui->opPokeCount->setText("[       ]");
        ui->statusLabel->setText("You lose!");
        theSocket->Write(Communication::ByteArray("1001"));
    }
}

void MainWindow::updateUI()
{

}

void MainWindow::refreshHealth()
{

}

MainWindow::~MainWindow()
{
    //Communication::ByteArray wasKilled("1000");
    //theSocket->Write(wasKilled);
    delete ui;
}

void MainWindow::on_attack1_clicked()
{
    //check if player has right to go
    if(ui->statusLabel->text() == "Choose your attack"){
        //set status to something other than ready phrase to avoid multiple attacks
        ui->statusLabel->setText("Opponent attacking");

        //deal damage
        dealDamage(getDamageToDeal(1));
    }
}

void MainWindow::on_attack2_clicked()
{
    //check if player has right to go
    if(ui->statusLabel->text() == "Choose your attack"){
        //set status to something other than ready phrase to avoid multiple attacks
       ui->statusLabel->setText("Opponent attacking");

        //deal damage
        dealDamage(getDamageToDeal(2));
    }
}

void MainWindow::on_attack3_clicked()
{
    //check if player has right to go
    if(ui->statusLabel->text() == "Choose your attack"){
        //set status to something other than ready phrase to avoid multiple attacks
       ui->statusLabel->setText("Opponent attacking");

        //deal damage
        dealDamage(getDamageToDeal(3));
    }
}

void MainWindow::on_startButton_clicked()
{
    //activate leave game button, deactivate start button
    ui->leaveButton->setEnabled(true);
    ui->startButton->setEnabled(false);

    //try catch block to ensure success/graceful failure
    try
    {
        //Communication::Socket theSocket("127.0.0.1", 2000);
        qDebug() << "made it before open";
        theSocket->Open();
        qDebug() << "made it past open";
        std::string message = "";
        gameStarted = true;
        //connect(theSocket,SIGNAL,this,onSocketStuff());

        //set status to waiting message
        ui->statusLabel->setText(QString("Waiting for second player to join"));
        ui->statusLabel->repaint();

        //get a message from server containing clientID
        //bool ok;
        Communication::ByteArray inIDBA;
        theSocket->Read(inIDBA);
        clientID = QString::fromStdString(inIDBA.ToString()).toInt(); //sets client ID

        //change status label
        ui->statusLabel->setText(QString("Found game..."));

        qDebug() << clientID;

        //get the pokemon numbers to use
        if(clientID == 1)
        {
            //========= randomize pokemon
            for(int i=0;i<3;i++)
            {
                //get first 3 pokemon as myPokemon

                Communication::ByteArray inPokemon;
                theSocket->Read(inPokemon);
                myPNumbers[i] = QString::fromStdString(inPokemon.ToString()).toInt();
                qDebug() << QString::fromStdString(inPokemon.ToString()).toInt();

            }

            //get next three pokemon as opponents
            for(int i=0;i<3;i++)
            {
                Communication::ByteArray inPokemon;
                theSocket->Read(inPokemon);
                opPNumbers[i] = QString::fromStdString(inPokemon.ToString()).toInt();
                qDebug() << QString::fromStdString(inPokemon.ToString()).toInt();
            }
            // ======= end randomization

            //just set simple pokemon first
            /*
            myPNumbers[0] = 1;
            myPNumbers[1] = 2;
            myPNumbers[2] = 3;
            opPNumbers[0] = 4;
            opPNumbers[1] = 5;
            opPNumbers[2] = 6;
            */

            //show pokemon images
            drawOpPokemon();
            drawMyPokemon();

            //unlock first client's attack buttons
            ui->attack1->setEnabled(true);
            ui->attack2->setEnabled(true);
            ui->attack3->setEnabled(true);

            //set text for attacker
            ui->statusLabel->setText("Choose your attack");
            ui->attack1->setText(allPokemon.at(myPNumbers[myCurrentPNo])->attack1);
            ui->attack2->setText(allPokemon.at(myPNumbers[myCurrentPNo])->attack2);
            ui->attack3->setText(allPokemon.at(myPNumbers[myCurrentPNo])->attack3);
            ui->opPokemonName->setText(allPokemon.at(opPNumbers[opCurrentPNo])->name);
            ui->myPokemonName->setText(allPokemon.at(myPNumbers[myCurrentPNo])->name);
            repaintAll();

            //now wait on other user's attack
            qDebug() << "flexwait starting for 1";
            Communication::FlexWait waiter(1, theSocket);
            Communication::Blockable *result = waiter.Wait();
            if(result == theSocket)
            {
                turn = true;
                qDebug() << "flexwait over for 1";
                //parse stuff into int
                Communication::ByteArray BA;
                theSocket->Read(BA);
                int dmg = QString::fromStdString(BA.ToString()).toInt();
                receiveDmg(dmg);
            }
        }
        else if(clientID ==2) //second player does the opposite
        {

            //======begin random section
            for(int i=0;i<3;i++)
            {
                //get first 3 pokemon as opPokemon
                Communication::ByteArray inPokemon;
                theSocket->Read(inPokemon);
                opPNumbers[i] = QString::fromStdString(inPokemon.ToString()).toInt();
                qDebug() << QString::fromStdString(inPokemon.ToString()).toInt();
            }

            //get next three pokemon as myPokemon
            for(int i=0;i<3;i++)
            {
                Communication::ByteArray inPokemon;
                theSocket->Read(inPokemon);
                myPNumbers[i] = QString::fromStdString(inPokemon.ToString()).toInt();
                qDebug() << QString::fromStdString(inPokemon.ToString()).toInt();
            }
            //======end random section

            //simple pokemon selection
            /*
            myPNumbers[0] = 4;
            myPNumbers[1] = 5;
            myPNumbers[2] = 6;
            opPNumbers[0] = 1;
            opPNumbers[1] = 2;
            opPNumbers[2] = 3;
            */

            //draw pokemon images
            drawMyPokemon();
            drawOpPokemon();

            //set text for receiver
            ui->statusLabel->setText("Opponent attacking");
            ui->myHealth->setText("200/200");
            ui->opHealth->setText("200/200");
            ui->attack1->setText(allPokemon.at(myPNumbers[myCurrentPNo])->attack1);
            ui->attack2->setText(allPokemon.at(myPNumbers[myCurrentPNo])->attack2);
            ui->attack3->setText(allPokemon.at(myPNumbers[myCurrentPNo])->attack3);
            ui->opPokemonName->setText(allPokemon.at(opPNumbers[opCurrentPNo])->name);
            ui->myPokemonName->setText(allPokemon.at(myPNumbers[myCurrentPNo])->name);
            repaintAll();

            //now wait on other user's attack
            qDebug() << "flexwait starting for 2";
            Communication::FlexWait waiter(1, theSocket);
            Communication::Blockable *result = waiter.Wait();
            if(result == theSocket)
            {
                qDebug() << "flexwait over for 2";
                //parse stuff into int
                Communication::ByteArray BA;
                theSocket->Read(BA);
                int dmg = QString::fromStdString(BA.ToString()).toInt();
                receiveDmg(dmg);
            }
        }
        else //invalid client number
        {
            qDebug() << "Invalid clientID";
        }

        //main loop of program functionality, dependent on exit bool
        /*
        while(!quitGame)
        {
            qDebug() << "just inside while loop";
            //If it's client's turn
            if(turn)
            {
                ui->statusLabel->setText("Choose your attack");
            }
            else
            {
                ui->statusLabel->setText("Opponent attacking");
            }

            //flexwait here on button push or socket stream
            qDebug() << "Just before flex wait";

            Communication::FlexWait waiter(2,&Communication::cinWatcher, &theSocket);
            Communication::Blockable *result = waiter.Wait();
            qDebug() << result;

            if(result == &theSocket) //socket returned a value from other player
            {
                //parse stuff into int
                Communication::ByteArray BA;
                theSocket.Read(BA);
                int dmg = QString::fromStdString(BA.ToString()).toInt();
            }
            else //cin entry detected
            {
                qDebug() << "cin block";
            }

        }
        */
    }
    catch(std::string str)
    {
        qDebug("Caught exception: " + QString::fromStdString(str).toLatin1());
    }
    catch(...)
    {
        qDebug() << "Caught unknown exception.";
    }
}

void MainWindow::on_exitButton_clicked()
{
    //Communication::ByteArray wasKilled("1000");
    //theSocket->Write(wasKilled);
    theSocket->Close();
    QApplication::quit();
}

void MainWindow::on_leaveButton_clicked()
{
    if(gameStarted)
    {
        theSocket->Write(Communication::ByteArray("-1"));
        sleep(1);
        ui->statusLabel->setText("You rage quitter...");
        ui->leaveButton->setEnabled(false);
        ui->exitButton->setEnabled(true);
        gameStarted=false;
        ui->attack1->setEnabled(false);
        ui->attack2->setEnabled(false);
        ui->attack3->setEnabled(false);
    }
    else{
        ui->leaveButton->setEnabled(false);
        ui->attack1->setEnabled(false);
        ui->attack2->setEnabled(false);
        ui->attack3->setEnabled(false);
        ui->exitButton->setEnabled(true);
    }
}

void MainWindow::onSocketStuff()
{
    qDebug() << "made it to socketstuff";
}
