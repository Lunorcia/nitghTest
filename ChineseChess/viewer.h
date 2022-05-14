#ifndef VIEWER_H
#define VIEWER_H

#include "board.h"

class Viewer
{
public:
    Viewer();
    ~Viewer();
    void viewMenu();
    void viewBoard(Board &board);
};

#endif // VIEWER_H
