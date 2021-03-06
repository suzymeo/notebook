#include "texture.h"
#include "game.h"

Texture::Texture() {
    renderer = Game::getInstance()->getRenderer();
}

void Texture::load(string ID, int row, int col) {

    if (textureMap.find(ID) != textureMap.end()) {
        return;
    }

    textureData u;

    u.texture = IMG_LoadTexture(renderer, ID.c_str());

    if (u.texture == nullptr) {
        logSDLError("Load Texture " + ID);
    }

    SDL_QueryTexture(u.texture, 0, 0, &u.width, &u.height);

    u.nFrames = row * col;
    u.width /= col;
    u.height /= row;
    u.col = col;
    u.row = row;

    textureMap[ID] = u;

}

void Texture::render(string ID, int x, int y, int currentFrames, float angle, SDL_RendererFlip flip, float scale, SDL_Point* point) {

    if (textureMap.find(ID) == textureMap.end()) {
        cerr << ID + " has not been loaded" << '\n';
        return;
    }

    SDL_Rect src, dst;

    textureData& temp = textureMap[ID];

    src.x = (currentFrames % temp.col);
    if (src.x == 0)
        src.x = temp.col;
    src.x = (src.x - 1) * temp.width;
    src.y = (ceil(currentFrames * 1.0f / temp.col) - 1) * temp.height;
    src.w = temp.width;
    src.h = temp.height;

    dst.w = temp.width * scale;
    dst.h = temp.height * scale;
    dst.x = x - dst.w / 2;
    dst.y = y - dst.h / 2;

    SDL_RenderCopyEx(renderer, temp.texture, &src, &dst, angle, point, flip);
}

void Texture::render(string ID, SDL_Rect src, SDL_Rect dst) {
    textureData& temp = textureMap[ID];
    SDL_RenderCopy(renderer, temp.texture, &src, &dst);
}

void Texture::render(string ID, int x, int y, float scale) {
    textureData& temp = textureMap[ID];
    SDL_Rect dst;
    dst.w = temp.width;
    dst.h = temp.height;

    if (scale != 1) {
        dst.w *= scale;
        dst.h *= scale;
    }
    dst.x = x - dst.w / 2;
    dst.y = y - dst.h / 2;
    SDL_RenderCopy(renderer, temp.texture, 0, &dst);
}

void Texture::render(string ID) {
    textureData& temp = textureMap[ID];
    SDL_RenderCopy(renderer, temp.texture, NULL, NULL);
}

void Texture::setColor(string ID, SDL_Color color) {
    textureData& temp = textureMap[ID];
    SDL_SetTextureColorMod(temp.texture, color.r, color.g, color.b);
}

void Texture::setAlpha(string ID, int alpha) {
    textureData& temp = textureMap[ID];
    SDL_SetTextureAlphaMod(temp.texture, alpha);
}

SDL_Renderer* Texture::getRenderer() {
    return renderer;
}

SDL_Texture* Texture::getTexture(string ID) {
    return textureMap[ID].texture;
}

void Texture::destroy(string ID) {
    auto it = textureMap.find(ID);
    if (it == textureMap.end()) {
        return;
    }
    SDL_DestroyTexture(it->second.texture);
    textureMap.erase(ID);
}

void Texture::release() {
    for (auto it = textureMap.begin(); it != textureMap.end(); ++it) {
        SDL_DestroyTexture(it->second.texture);
        it->second.texture = nullptr;
    }
    textureMap.clear();
}
