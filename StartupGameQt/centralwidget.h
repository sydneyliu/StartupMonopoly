
#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include <QtGui>
#include "player.h"

class CentralWidget: public QWidget {
  Q_OBJECT

  private:
    QPushButton* cardDeckButton;
    QPushButton* cardDeckButton1;
   
    QLabel* boardLabel;
    QPixmap* cardFaceDown;
    QPixmap* cardFaceUp;
    QPixmap* cardCashup;
    bool isFaceDown;

  private slots:
    void drawCard();
    void drawCard1();
    

 public:
    CentralWidget();



};

#endif
