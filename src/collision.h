#ifndef __collision__h
#define __collision__h

#include "player.h"
#include "enemy.h"
#include "tilemap.h"

void checkCollision(Player* player, vector<Enemy*>& enemies);

#endif // __collision__h
