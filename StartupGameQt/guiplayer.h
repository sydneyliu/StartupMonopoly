#include <QtGui>

#ifndef GUIPLAYER_H
#define GUIPLAYER_H

#include "player.h"

class GUIPlayer : public QDockWidget {
  Q_OBJECT

  protected:
    Player* player;
    QLabel *nameLabel;
    

  public:
    GUIPlayer( Player* p );
    void getPic(QString Photo);
    QImage Logo;
    QString Location;
    bool moved;
    int currentx;
    int currenty;
};

#endif
