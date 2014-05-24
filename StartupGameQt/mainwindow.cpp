#include <iostream>
#include "mainwindow.h"
#include "centralwidget.h"
#include <QCoreApplication>
#include <QObject>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

MainWindow::MainWindow() {
  firstTime=1;
  rounds = 1;
  counter =0;
  playerTurn=0;
  setGeometry( 0, 0, 1006, 650 );

  //Display the board in the central widget
  centralWidget = new CentralWidget();
  setCentralWidget( centralWidget );

  QMenuBar *mb = menuBar(); //adds main menu
  fileMenu = new QMenu("File", this);
  mb->addMenu(fileMenu);
  QAction *exitAction = new QAction( "Exit", this );
  fileMenu->addAction( exitAction );
  connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));
//choose Players
  vector<char*> PlayerNames; //using char* to compare with tr
  PlayerNames.push_back("Steve Jobs");
  PlayerNames.push_back("Sean Rad");
  PlayerNames.push_back("Jim Clark");
  PlayerNames.push_back("Mark Zuckerberg");
  PlayerNames.push_back("Elon Musk");
  PlayerNames.push_back("Andrew Carnegie");
  PlayerNames.push_back("Richard Branson");
  PlayerNames.push_back("Larry Page");
  PlayerNames.push_back("Jack Dorsey");

  vector<QString> PlayerNames1; //using QString to find the correct selection
  PlayerNames1.push_back("Steve Jobs");
  PlayerNames1.push_back("Sean Rad");
  PlayerNames1.push_back("Jim Clark");
  PlayerNames1.push_back("Mark Zuckerberg");
  PlayerNames1.push_back("Elon Musk");
  PlayerNames1.push_back("Andrew Carnegie");
  PlayerNames1.push_back("Richard Branson");
  PlayerNames1.push_back("Larry Page");
  PlayerNames1.push_back("Jack Dorsey");
  
  Player_Num << tr("2") << tr("3") << tr("4");
 
  bool ok;
  QString item = QInputDialog::getItem(this, tr("QInputDialog::getItem()"),
                                          tr("Welcome! Please enter the number of players:"), Player_Num, 0, false, &ok);
  if (ok==1) { //if okay is pressed
    if (item == "2") {
      player_number = 2;
    } else if (item == "3") {
      player_number = 3;
    } else {
      player_number = 4;
    }

  for (int i = 0; i<player_number; i++) { //choose what player you want to be.
    Player_Name << tr(PlayerNames[0]) << tr(PlayerNames[1]) << tr(PlayerNames[2]) << tr(PlayerNames[3]) << tr(PlayerNames[4]) << tr(PlayerNames[5]);
    bool okay;
    QString name = QInputDialog::getItem(this, tr("QInputDialog::getItem()"),
                                          tr("Please choose your character!"), Player_Name, 0, false, &okay);
    players[i] = new Player( name );
    guiPlayers[i] = new GUIPlayer(players[i]);
    for (int j=0; j<5; j++) {
      if (players[i]->getName()==PlayerNames1[j]) {
        PlayerNames.erase(PlayerNames.begin()+j);
        PlayerNames1.erase(PlayerNames1.begin()+j);
        Player_Name.clear();
      }

    }

    if (players[i]->getName() == "Steve Jobs") {
        guiPlayers[i]->getPic(":/images/Apple.png");
    } else if (players[i]->getName() == "Sean Rad") {
        guiPlayers[i]->getPic(":/images/Tinder.png");
    } else if (players[i]->getName() == "Jim Clark") {
        guiPlayers[i]->getPic(":/images/NetScape.png");
    } else if (players[i]->getName() == "Mark Zuckerberg") {
        guiPlayers[i]->getPic(":/images/Facebook.png");
    } else if (players[i]->getName() == "Elon Musk") {
        guiPlayers[i]->getPic(":/images/SpaceX.png");
    } else if (players[i]->getName() == "Andrew Carnegie") {
        guiPlayers[i]->getPic(":/images/AndrewCarnegie.png");
    } else if (players[i]->getName() == "Richard Branson") {
        guiPlayers[i]->getPic(":/images/Virgin.png");
    } else if (players[i]->getName() == "Larry Page") {
        guiPlayers[i]->getPic(":/images/Google.png");
    } else if (players[i]->getName() == "Jack Dorsey") {
        guiPlayers[i]->getPic(":/images/Twitter.png");
    }

  }
    
  }
  if (ok==0) {

    connect(qApp, SIGNAL(lastWindowClosed()), qApp, SLOT(quit()));
  }

  Yes1 = new QPushButton( this );
  Yes1->setText("Yes");
  Yes1->setIconSize( QSize(25, 5) );
  Yes1->setGeometry( 10, 200, 150, 30 );

  No1 = new QPushButton( this );
  No1->setText("No");
  No1->setIconSize( QSize(25, 5) );
  No1->setGeometry( 10, 230, 150, 30 );

  Resign1 = new QPushButton( this );
  Resign1->setText("Resign");
  Resign1->setIconSize( QSize(25, 5) );
  Resign1->setGeometry( 10, 260, 150, 30 );

  Yes2 = new QPushButton( this );
  Yes2->setText("Yes");
  Yes2->setIconSize( QSize(25, 5) );
  Yes2->setGeometry( 10, 540, 150, 30 );

  No2 = new QPushButton( this );
  No2->setText("No");
  No2->setIconSize( QSize(25, 5) );
  No2->setGeometry( 10, 570, 150, 30 );

  Resign2 = new QPushButton( this );
  Resign2->setText("Resign");
  Resign2->setIconSize( QSize(25, 5) );
  Resign2->setGeometry( 10, 600, 150, 30 );

  Yes3 = new QPushButton( this );
  Yes3->setText("Yes");
  Yes3->setIconSize( QSize(25, 5) );
  Yes3->setGeometry( 840, 200, 150, 30 );

  No3 = new QPushButton( this );
  No3->setText("No");
  No3->setIconSize( QSize(25, 5) );
  No3->setGeometry( 840, 230, 150, 30 );

  Resign3 = new QPushButton( this );
  Resign3->setText("Resign");
  Resign3->setIconSize( QSize(25, 5) );
  Resign3->setGeometry( 840, 260, 150, 30 );

  Yes4 = new QPushButton( this );
  Yes4->setText("Yes");
  Yes4->setIconSize( QSize(25, 5) );
  Yes4->setGeometry( 840, 540, 150, 30 );

  No4 = new QPushButton( this );
  No4->setText("No");
  No4->setIconSize( QSize(25, 5) );
  No4->setGeometry( 840, 570, 150, 30 );

  Resign4 = new QPushButton( this );
  Resign4->setText("Resign");
  Resign4->setIconSize( QSize(25, 5) );
  Resign4->setGeometry( 840, 600, 150, 30 );

QSignalMapper* signalMapper = new QSignalMapper (this) ;
connect (Resign1, SIGNAL(clicked()), signalMapper, SLOT(map())) ;
connect (Resign2, SIGNAL(clicked()), signalMapper, SLOT(map())) ;
if(player_number>2) {
  connect (Resign3, SIGNAL(clicked()), signalMapper, SLOT(map())) ;

}
if(player_number>3) {
  connect (Resign4, SIGNAL(clicked()), signalMapper, SLOT(map())) ;

}
signalMapper -> setMapping (Resign1, 0) ;
signalMapper -> setMapping (Resign2, 1) ;
if(player_number>2) {
  signalMapper -> setMapping (Resign3, 2) ;
}
if(player_number>3) {
  signalMapper -> setMapping (Resign4, 3) ;
}
connect (signalMapper, SIGNAL(mapped(int)), this, SLOT(Resignation(int))) ;

  //set up for player 1
player1 = new QLabel(this);
 player1->setText(players[0]->getName());
 player1->setGeometry( 10, 50, 200, 30 );

  money1 = new QLabel(this);
 money1->setNum(players[0]->CashChecker());
 money1->setGeometry( 25, 90, 200, 30 );

  customer1 = new QLabel(this);
  customer1->setNum(players[0]->CustomerChecker());
  customer1->setGeometry( 99, 150, 200, 30 );
//set up for player 2
player2 = new QLabel(this);
 player2->setText(players[1]->getName());
 player2->setGeometry( 10, 380, 200, 30 );

money2 = new QLabel(this);
 money2->setNum(players[1]->CashChecker());
 money2->setGeometry( 25, 420, 200, 30 );

    customer2 = new QLabel(this);
  customer2->setNum(players[1]->CustomerChecker());
  customer2->setGeometry( 99, 490, 200, 30 );
//set up for player 3
 if(player_number>2) {
    player3 = new QLabel(this);
    player3->setText(players[2]->getName());
    player3->setGeometry( 840, 50, 200, 30 );
    money3 = new QLabel(this);
   money3->setNum(players[2]->CashChecker());
    money3->setGeometry( 855, 90, 200, 30 );

   customer3 = new QLabel(this);
  customer3->setNum(players[2]->CustomerChecker());
  customer3->setGeometry( 915, 140, 200, 30 );
 }
//set up for player 4
 if(player_number>3) {
    player4 = new QLabel(this);
    player4->setText(players[3]->getName());
    player4->setGeometry( 840, 380, 200, 30 );

    money4 = new QLabel(this);
    money4->setNum(players[3]->CashChecker());
    money4->setGeometry( 855, 410, 200, 30 );

    customer4 = new QLabel(this);
    customer4->setNum(players[3]->CustomerChecker());
    customer4->setGeometry( 915, 480, 200, 30 );
 }

 GameOver = new QLabel(this);
 GameOver->setPixmap( QPixmap(":/images/GameOver.png" ) );
 GameOver->setGeometry(0, 0, 1006, 650 );
 GameOver->lower();


QFont font;
font.setPointSize(50);
font.setBold(true);

QFont font1;
font1.setPointSize(100);
font1.setBold(true);

 GameWinner = new QLabel(this);
 GameWinner->setFont(font1);
 GameWinner->setGeometry( 0, 180, 1000, 330 );
 GameWinner->lower();


//die
  Dice = new QPushButton( this );
  Dice->setText("Click to Roll");
  Dice->setIconSize( QSize(25, 5) );
  Dice->setGeometry( 435, 410, 130, 30 );
  connect( Dice, SIGNAL(clicked()), this, SLOT(dice()) );



  Die = new QLabel(this);
  Die->setFont(font);
  Die->setGeometry( 485, 450, 50, 50);

  Round1 = new QLabel(this);
  Round1->setFont(font);
  Round1 -> setNum(rounds);
  Round1 -> setGeometry(100, 0, 200, 50);


  Round2 = new QLabel(this);
  Round2->setFont(font);
  Round2 -> setNum(rounds);
  Round2 -> setGeometry(100, 340, 200, 50);
  Round2 ->setVisible(0);

  Round3 = new QLabel(this);
  Round3->setFont(font);
  Round3 -> setNum(rounds);
  Round3 -> setGeometry(920, 0, 200, 50);
  Round3 ->setVisible(0);

  Round4 = new QLabel(this);
  Round4->setFont(font);
  Round4 -> setNum(rounds);
  Round4 -> setGeometry(920, 340, 200, 50);
  Round4 ->setVisible(0);

  icon1 = new QLabel(this);
  icon1 -> raise();
  icon1->setPixmap( QPixmap(guiPlayers[0]->Location) );
  icon1 -> setGeometry(775,574, 10, 10);

  icon2 = new QLabel(this);
  icon2 -> raise();
  icon2->setPixmap( QPixmap(guiPlayers[1]->Location) );
  icon2 -> setGeometry(765,574, 10, 10);

  if(player_number > 2) {
    icon3 = new QLabel(this);
    icon3 -> raise();
    icon3->setPixmap( QPixmap(guiPlayers[2]->Location) );
    icon3 -> setGeometry(755,574, 10, 10);
  }
  
  if(player_number>3) {
    icon4 = new QLabel(this);
    icon4 -> raise();
    icon4->setPixmap( QPixmap(guiPlayers[3]->Location) );
    icon4 -> setGeometry(745,574, 10, 10);
  }

  guiPlayers[0]->currentx=775;
  guiPlayers[0]->currenty=574;
  guiPlayers[1]->currentx=765;
  guiPlayers[1]->currenty=574;

  if(player_number>2) {
    guiPlayers[2]->currentx=755;
    guiPlayers[2]->currenty=574;
  }
  if(player_number>3) {
     guiPlayers[3]->currentx=745;
     guiPlayers[3]->currenty=574;
  }

 

  
  
}

void MainWindow::Resignation(int i) {
    players[i]->Lost();
    int temp1 = players[i]->CashChecker();
    players[i]->moneymove(-temp1);
    players[i]->SetCustomer(0);
    buttonCondition();

}

void MainWindow::dice() {
    srand(time(0));
    randnum = (rand() % 6)+1; //generates a random number 0-5 and adds one to make 1-6
    Die->setNum(randnum);

    //movement
    for(int i=0; i<player_number; i++) {
      if(players[i]->checkLost()==1) {
        if(guiPlayers[i]->moved == 0) {
          //movement along the bottom row
          if(guiPlayers[i]->currentx-52*randnum > 223 && guiPlayers[i]->currenty>557) {
            if(i==0){
              icon1->move(guiPlayers[i]->currentx-52*randnum, guiPlayers[i]->currenty);
            } else if (i==1) {
              icon2->move(guiPlayers[i]->currentx-52*randnum, guiPlayers[i]->currenty);
            } else if (i==2) {
              icon3->move(guiPlayers[i]->currentx-52*randnum, guiPlayers[i]->currenty);
            } else if (i==3) {
             icon4->move(guiPlayers[i]->currentx-52*randnum, guiPlayers[i]->currenty);
            }
          //movement around the corner
          } else if (guiPlayers[i]->currentx-52*randnum < 223 & guiPlayers[i]->currenty>557) {
              if(i==0){
                icon1->move(255, 574);
                icon1->move(255, 574-(255-guiPlayers[i]->currentx+52*randnum));
              } else if (i==1) {
                icon2->move(245, 574);
                icon2->move(245, 574-(245-guiPlayers[i]->currentx+52*randnum));
               } else if (i==2) {
                icon3->move(235, 574);
                icon3->move(235, 574-(235-guiPlayers[i]->currentx+52*randnum));
             } else if (i==3) {
                icon4->move(225, 574);
                icon4->move(225, 574-(225-guiPlayers[i]->currentx+52*randnum));
              }
            //movement in the y direction on the left
          } else if (guiPlayers[i]->currentx < 260 && (guiPlayers[i]->currenty-52*randnum)>86) {
            if(i==0){
              icon1->move(guiPlayers[i]->currentx, guiPlayers[i]->currenty-52*randnum);
            } else if (i==1) {
              icon2->move(guiPlayers[i]->currentx, guiPlayers[i]->currenty-52*randnum);
            } else if (i==2) {
              icon3->move(guiPlayers[i]->currentx, guiPlayers[i]->currenty-52*randnum);
            } else if (i==3) {
             icon4->move(guiPlayers[i]->currentx, guiPlayers[i]->currenty-52*randnum);
            }
            //movement in the corner
          } else if (guiPlayers[i]->currentx<260 && (guiPlayers[i]->currenty-52*randnum)<86) {
            if(i==0){
                icon1->move(255, 54);
                icon1->move(255+(54-guiPlayers[i]->currenty+52*randnum) , 54);
              } else if (i==1) {
                icon2->move(245, 54);
                icon2->move(245+(54-guiPlayers[i]->currenty+52*randnum) , 54);
               } else if (i==2) {
                icon3->move(235, 54);
                icon3->move(235+(54-guiPlayers[i]->currenty+52*randnum) , 54);
             } else if (i==3) {
                icon4->move(225, 54);
                icon4->move(225+(54-guiPlayers[i]->currenty+52*randnum) , 54);
              }
            //movement at the top
          } else if(guiPlayers[i]->currentx+52*randnum < 743 && guiPlayers[i]->currenty<80) {
            if(i==0){
              icon1->move(guiPlayers[i]->currentx+52*randnum, guiPlayers[i]->currenty);
            } else if (i==1) {
              icon2->move(guiPlayers[i]->currentx+52*randnum, guiPlayers[i]->currenty);
            } else if (i==2) {
              icon3->move(guiPlayers[i]->currentx+52*randnum, guiPlayers[i]->currenty);
            } else if (i==3) {
             icon4->move(guiPlayers[i]->currentx+52*randnum, guiPlayers[i]->currenty);
            }
            //movement around the corner at the top
          } else if (guiPlayers[i]->currentx+52*randnum>743 && guiPlayers[i]->currenty<80) {
              cout << "Holaa" << endl;
            if(i==0){
                icon1->move(775, 54);
                icon1->move(775, 54+(775-guiPlayers[i]->currentx+52*randnum));
              } else if (i==1) {
                icon2->move(765, 54);
                icon2->move(765, 54+(765-guiPlayers[i]->currentx+52*randnum));
               } else if (i==2) {
                icon3->move(755, 54);
                icon3->move(755, 54+(755-guiPlayers[i]->currentx+52*randnum));
             } else if (i==3) {
                icon4->move(745, 54);
                icon4->move(745, 54+(745-guiPlayers[i]->currentx+52*randnum));
                //move down
            } else if (guiPlayers[i]->currentx > 743 && (guiPlayers[i]->currenty+52*randnum)<557) {
                cout << "HI" << endl;
                if(i==0){
                  icon1->move(guiPlayers[i]->currentx, guiPlayers[i]->currenty+52*randnum);
                } else if (i==1) {
                  icon2->move(guiPlayers[i]->currentx, guiPlayers[i]->currenty+52*randnum);
                } else if (i==2) {
                  icon3->move(guiPlayers[i]->currentx, guiPlayers[i]->currenty+52*randnum);
                } else if (i==3) {
                  icon4->move(guiPlayers[i]->currentx, guiPlayers[i]->currenty+52*randnum);
                }
            //movement in the corner
           } else if (guiPlayers[i]->currentx<260 && (guiPlayers[i]->currenty-52*randnum)<86) {
              if(i==0){
                icon1->move(255, 54);
                icon1->move(255+(54-guiPlayers[i]->currenty+52*randnum) , 54);
              } else if (i==1) {
                icon2->move(245, 54);
                icon2->move(245+(54-guiPlayers[i]->currenty+52*randnum) , 54);
               } else if (i==2) {
                icon3->move(235, 54);
                icon3->move(235+(54-guiPlayers[i]->currenty+52*randnum) , 54);
             } else if (i==3) {
                icon4->move(225, 54);
                icon4->move(225+(54-guiPlayers[i]->currenty+52*randnum) , 54);
              }
          }
          }


          //moving along the bottom row
          if(guiPlayers[i]->currentx-52*randnum > 223 && guiPlayers[i]->currenty>557) {
              guiPlayers[i]->currentx-=52*randnum;
          } else if (guiPlayers[i]->currentx-52*randnum < 223 & guiPlayers[i]->currenty>557) {
              //moving around the corner
              if (i==0) {
                guiPlayers[i]->currentx=255;
                guiPlayers[i]->currenty=574-(255-guiPlayers[i]->currentx+52*randnum);
              } else if (i==1) {
                 guiPlayers[i]->currentx=245;
                 guiPlayers[i]->currenty=574-(245-guiPlayers[i]->currentx+52*randnum);
              } else if (i==2) {
                 guiPlayers[i]->currentx=235;
                 guiPlayers[i]->currenty=574-(235-guiPlayers[i]->currentx+52*randnum);
              } else if (i==3) {
                 guiPlayers[i]->currentx=225;
                 guiPlayers[i]->currenty=574-(225-guiPlayers[i]->currentx+52*randnum);
              }
              //moving around the side up
          } else if (guiPlayers[i]->currentx < 260 && (guiPlayers[i]->currenty-52*randnum)>86) {
              guiPlayers[i]->currenty-=52*randnum;
              //moving around the corner
          } else if(guiPlayers[i]->currentx<260 && (guiPlayers[i]->currenty-52*randnum)<86) {
            if (i==0) {
                guiPlayers[i]->currentx=255+(54-guiPlayers[i]->currenty+52*randnum);
                guiPlayers[i]->currenty=54;
              } else if (i==1) {
                 guiPlayers[i]->currentx=245+(54-guiPlayers[i]->currenty+52*randnum);
                 guiPlayers[i]->currenty=54;
              } else if (i==2) {
                 guiPlayers[i]->currentx=235+(54-guiPlayers[i]->currenty+52*randnum);
                 guiPlayers[i]->currenty=54;
              } else if (i==3) {
                 guiPlayers[i]->currentx=225+(54-guiPlayers[i]->currenty+52*randnum);
                 guiPlayers[i]->currenty=54;
              }
              //moving to the right
          }else if(guiPlayers[i]->currentx+52*randnum < 743 && guiPlayers[i]->currenty<80) {
              guiPlayers[i]->currenty=54;
              guiPlayers[i]->currentx+=52*randnum;
              //moving around the corner
          } else if(guiPlayers[i]->currentx+52*randnum>743 && guiPlayers[i]->currenty<80) {
            cout << "yep, I can move around" << endl;
            if (i==0) {
                guiPlayers[i]->currentx=775;
                guiPlayers[i]->currenty=54+(775-guiPlayers[i]->currentx+52*randnum);
              } else if (i==1) {
                 guiPlayers[i]->currentx=765;
                 guiPlayers[i]->currenty=54+(775-guiPlayers[i]->currentx+52*randnum);
              } else if (i==2) {
                 guiPlayers[i]->currentx=755;
                 guiPlayers[i]->currenty=54+(775-guiPlayers[i]->currentx+52*randnum);
              } else if (i==3) {
                 guiPlayers[i]->currentx=745;
                 guiPlayers[i]->currenty=54+(775-guiPlayers[i]->currentx+52*randnum);
              }
              //moving down
          }else if (guiPlayers[i]->currentx > 743 && (guiPlayers[i]->currenty-52*randnum)>557) {
              guiPlayers[i]->currenty+=52*randnum;
          }


          guiPlayers[i]->moved =1;
          cout << guiPlayers[i]->currentx << endl;
          cout << guiPlayers[i]->currenty << endl;
          break;
        }
      }
    }
    int j=0; //tracks the number of players who have moved
    for (int i =0; i<player_number; i++) {
      if(guiPlayers[i]->moved==0) {
        j++;
      }
    }
    if(j==0) {
      for(int i =0; i<player_number; i++) {
        guiPlayers[i]->moved=0;
      } //reset
    }

    buttonCondition();
    roundTracker();
    updateRounds();

}

void MainWindow::UpdateMoneyCustom() {
    player1cash=players[0]->CashChecker();
  player2cash=players[1]->CashChecker();
  if(player_number > 2) {
      player3cash=players[2]->CashChecker();
  }

  if(player_number > 3) {
    player4cash=players[3]->CashChecker();
  }

  player1cus=players[0]->CustomerChecker();
  player2cus=players[1]->CustomerChecker();
  if(player_number > 2) {
    player3cus=players[2]->CustomerChecker();
  }
  if(player_number > 3) {
  player4cus=players[3]->CustomerChecker();
  }
  money1->setNum(player1cash);
  money2->setNum(player2cash);
  if(player_number>2) {
     money3->setNum(player3cash);
  }
  if(player_number>3) {
    money4->setNum(player4cash);
  }
  
  customer1->setNum(player1cus);
  customer2->setNum(player2cus);
  if(player_number>2) {
    customer3->setNum(player3cus);
  }
  if(player_number>3) {
    customer4->setNum(player4cus);
  }
  
}

void MainWindow::declareWinners() { //checks for the winners
  int tracker = 0; //tracks the key numbers to check if the game is over or not.
  int temp =0;
  for(int i=0; i<player_number; i++) {
    tracker += players[i]->GameEnd();
  } // end of for loop
  for (int i=0; i<player_number; i++) {
    if(players[i]->CashChecker()>=100000) {
      for(int i=0; i<player_number; i++) {
        if(players[i]->CashChecker() < 100000) {
          players[i]->Lost();
        }
        tracker = 1;
      }
    } 
  }
  if(tracker == 1) {
 
    for (int i=0; i<player_number;i++) {
      temp = players[i]->GameEnd();
      if(temp==1) {
        //set something visible and make it say who won
        GameOver->raise();
        GameWinner->raise();
        GameWinner->setText(players[i]->getName() + '\n' + " wins!");
        break;
      }
    } //for loop to check who the winner is.
  }
} //end of declareWinners

void MainWindow::buttonCondition() {
  UpdateMoneyCustom();
  declareWinners();

}

void MainWindow::roundTracker() {
  counter++; //starts the game at 0
  int turnCounter=0;
  int activePlayers=0;
  if (firstTime==1) {
    for(int i =1; i<player_number; i++) {
    if(players[i]->checkLost()==1) {
      if (players[i]->turn==0) {
          if(i==0) { //moves the turn counter around
            Round1 -> setVisible(1);
            Round2 -> setVisible(0);
            Round3 -> setVisible(0);
            Round4 -> setVisible(0);
          } else if (i==1) {
            Round1 -> setVisible(0);
            Round2 -> setVisible(1);
            Round3 -> setVisible(0);
            Round4 -> setVisible(0);
          } else if (i==2) {
            Round1 -> setVisible(0);
            Round2 -> setVisible(0);
            Round3 -> setVisible(1);
            Round4 -> setVisible(0);
          } else if (i==3) {
            Round1 -> setVisible(0);
            Round2 -> setVisible(0);
            Round3 -> setVisible(0);
            Round4 -> setVisible(1);
          }
            players[i]->turn=1;
           break;
         }
        }
     }
    for(int i=0; i<player_number; i++) {
      if (players[i]->turn==1) {
       turnCounter++;
      }
   }
    if(turnCounter==player_number-1){
      
      for (int i=0; i<player_number ; i++) {

        players[i]->turn = 0;
      }
     firstTime=0;
     counter =0;
      //rounds++;
    }
  } else {
    for(int i =0; i<player_number; i++) {
    if(players[i]->checkLost()==1) {
      if (players[i]->turn==0) {
          if(i==0) { //moves the turn counter around
            Round1 -> setVisible(1);
            Round2 -> setVisible(0);
            Round3 -> setVisible(0);
            Round4 -> setVisible(0);
          } else if (i==1) {
            Round1 -> setVisible(0);
            Round2 -> setVisible(1);
            Round3 -> setVisible(0);
            Round4 -> setVisible(0);
          } else if (i==2) {
            Round1 -> setVisible(0);
            Round2 -> setVisible(0);
            Round3 -> setVisible(1);
            Round4 -> setVisible(0);
          } else if (i==3) {
            Round1 -> setVisible(0);
            Round2 -> setVisible(0);
            Round3 -> setVisible(0);
            Round4 -> setVisible(1);
          }

          players[i]->turn=1;
          break;
        }
      }
    }

  for(int i=0; i<player_number; i++) {
    if (players[i]->checkLost()==1) {
      activePlayers++;
    }
    if (players[i]->turn==1) {
      turnCounter++;
    }
  }
  if (turnCounter==activePlayers) {
    for(int i=0; i<player_number; i++) {
      players[i]->turn = 0;
    }
  }
  if(counter == activePlayers) {
    counter =0;
    rounds++;
  }
} // end of else statement
  
}

void MainWindow::updateRounds() {
  Round1 -> setNum(rounds);
  Round2 -> setNum(rounds);
  Round3 -> setNum(rounds);
  Round4 -> setNum(rounds);

}