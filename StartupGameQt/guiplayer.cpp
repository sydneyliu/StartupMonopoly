#include "guiplayer.h"

GUIPlayer::GUIPlayer( Player* p ) {
  player = p;
  nameLabel = new QLabel( this );
  nameLabel->setText( player->getName() );
  moved = 0;
}

void GUIPlayer::getPic(QString Photo) {
	Logo.load(Photo);
	Location = Photo;
}
