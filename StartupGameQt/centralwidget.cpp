#include "centralwidget.h"
#include "player.h"
#include "mainwindow.h"



CentralWidget::CentralWidget(): QWidget() {
  setGeometry( 0, 0, 1006, 650 );
  boardLabel = new QLabel( this );
  boardLabel->setPixmap( QPixmap("GameBoard.png") );

  //Create the two card images
  cardFaceUp = new QPixmap( ":/images/CardBacking.png" );
  cardFaceDown = new QPixmap( ":/images/CompetitionCard.png" );
  cardCashup = new QPixmap(":/images/CashCard.png");
  


  //Create the button for the card deck
  cardDeckButton1 = new QPushButton( this );
  cardDeckButton1->setIcon( *cardCashup);
  cardDeckButton1->setIconSize( QSize(97, 152) );
  cardDeckButton1->setGeometry( 300, 205, 97, 152 );

  connect( cardDeckButton1, SIGNAL(clicked()), this, SLOT(drawCard1()) );
  isFaceDown = true;

  cardDeckButton = new QPushButton( this );
  cardDeckButton->setIcon( *cardFaceDown );
  cardDeckButton->setIconSize( QSize(97, 152) );
  cardDeckButton->setGeometry( 610, 205, 97, 152 );

  //Connect the button to drawCard
  connect( cardDeckButton, SIGNAL(clicked()), this, SLOT(drawCard()) );
  isFaceDown = true;
}

void CentralWidget::drawCard() {
  //Show the face up card
  if ( isFaceDown ) {
    cardDeckButton->setIcon( *cardFaceUp );
    isFaceDown = false;
  } else {
    cardDeckButton->setIcon( *cardFaceDown );
    isFaceDown = true;
  }
}

void CentralWidget::drawCard1() {
  //Show the face up card
  if ( isFaceDown ) {
    cardDeckButton1->setIcon( *cardFaceUp );
    isFaceDown = false;
  } else {
    cardDeckButton1->setIcon( *cardCashup );
    isFaceDown = true;
  }
}

