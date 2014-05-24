#include <QtGui>

#ifndef GUIPLAYERVERTICAL_H
#define GUIPLAYERVERTICAL_H

#include "player.h"
#include "guiplayer.h"

class GUIPlayerVertical : public GUIPlayer {
  Q_OBJECT

  private:
    Player* player;

 public:
    GUIPlayerVertical( Player* p );

};

#endif
