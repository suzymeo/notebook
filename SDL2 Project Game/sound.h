#ifndef __sound__h
#define __sound__h

#include "header.h"

class Sound {

public:

    static Sound* getInstance() {
        static Sound* instance;
        if (instance == nullptr) {
            instance = new Sound();
        }
        return instance;
    }

    Sound();

    void playMusic();
    void playChunks(int id, int channel);

    void release();

private:

    Mix_Music* music = nullptr;
    vector<Mix_Chunk*> chunks;
};


#endif // __sound_h
