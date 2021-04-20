#ifndef __weapon__h
#define __weapon__h

#include "header.h"
#include "texture.h"
#include "structs.h"

struct Gun {
    int ID;
    pair<int, int> reloadTime;
    pair<int, int> delayTime;

    int magazineAmmo;
    int reserveAmmo;
    int maxAmmo;

    int projectileID;
    int soundID;
    int effectID;


    int frameRate;

    float velocity;

    float scaleFrame;

    int nFrames;
};

class Weapon {

public:
    Weapon();

    void initGun(int ID);

    void update(int _x, int _y, int x_dst, int y_dst, float angle, bool _shooting, SDL_RendererFlip _flip);
    void render(SDL_Rect& camera);

    void reload();

    pair<int, int> getAmmunition();


    int x, y;
    float angle;

    SDL_RendererFlip flip;

    int currentGun;
    bool shooting;

    vector<Gun> guns;
    vector<Bullet> bullets;

private:

};

#endif // __weapon__h
