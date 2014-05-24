#include <QApplication>

#include "mainwindow.h"

int main( int argv, char* argc[] ) {
  QApplication app( argv, argc );
  MainWindow mw;
  mw.show();

  return app.exec();
}
