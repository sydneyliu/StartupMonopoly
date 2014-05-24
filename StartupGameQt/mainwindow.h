#include <QtGui>

#include "guiplayerhorizontal.h"
#include "guiplayervertical.h"
#include "centralwidget.h"

class MainWindow : public QMainWindow {
  Q_OBJECT

  private:
  QLabel *boardLabel;
  Player* players[4];
  GUIPlayer* guiPlayers[4];
  //QPushButton* cardDeckButton;
  QWidget* centralWidget;
  QMenuBar *mb;
  QMenu* fileMenu;
  QStringList Player_Num;
  QStringList Player_Name;
  QLabel* player1;
  QLabel* player2;
  QLabel* player3;
  QLabel* player4;
  QLabel* money1;
  QLabel* money2;
  QLabel* money3;
  QLabel* money4;
  QLabel* customer1;
  QLabel* customer2;
  QLabel* customer3;
  QLabel* customer4;
  QLabel* GameOver;
  QPushButton* Yes1;
  QPushButton* Yes2;
  QPushButton* Yes3;
  QPushButton* Yes4;
  QPushButton* No1;
  QPushButton* No2;
  QPushButton* No3;
  QPushButton* No4;
  QPushButton* Resign1;
  QPushButton* Resign2;
  QPushButton* Resign3;
  QPushButton* Resign4;
  QPushButton* Dice;
  QLabel* Die; //displays the number of the die
  QLabel* GameWinner;
  QLabel* Round1;
  QLabel* Round2;
  QLabel* Round3;
  QLabel* Round4;
  QLabel* icon1;
  QLabel* icon2;
  QLabel* icon3;
  QLabel* icon4;
  int player1cash;
  int player2cash;
  int player3cash;
  int player4cash;
  int player1cus;
  int player2cus;
  int player3cus;
  int player4cus;
  int counter; //tracks the number of moves have happened in the turn
  int playerTurn; //tracks whose turn it is
  bool firstTime; //tracks if first time in the loop

  private slots:
    void dice();
    void Resignation(int);
    void UpdateMoneyCustom();
    void declareWinners();
    void buttonCondition();
    void updateRounds();
  public:
    MainWindow();
    int randnum;
    int player_number; //tracks the number of players playing the game
    int rounds; //tracks the number of turns
    void roundTracker(); //keeps track of rounds
};
