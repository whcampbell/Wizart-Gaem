#include "renderrequest.h"
#include "screen.h"

SDL_sem* textsync;

void initRequestSystem() {
    textsync = SDL_CreateSemaphore(1);
}

void drawRequest(RenderRequest* request) {
    
    SDL_Rect quad, texquad;
    switch (request->request.type)
    {
    case REQ_IMAGE:
        SDL_RenderSetScale(getRenderer(), request->image.scale, request->image.scale);
        quad = {request->image.x, request->image.y, request->image.w, request->image.h};
        SDL_RenderCopy(getRenderer(), request->image.texture->sheet, request->image.texture->clips[request->image.frame], &quad);
        break;
    case REQ_SPRITE:
        SDL_RenderSetScale(getRenderer(), request->sprite.scale, request->sprite.scale);
        quad = {request->sprite.x, request->sprite.y, request->sprite.w, request->sprite.h};
        SDL_RenderCopyEx(getRenderer(), request->sprite.texture->sheet, request->sprite.texture->clips[request->sprite.frame], &quad, request->sprite.theta, &request->sprite.point, request->sprite.flip);
        break;
    case REQ_TEXT:
        SDL_SemWait(textsync);
        if (*request->text.valid) {
        SDL_RenderSetScale(getRenderer(), request->text.scale, request->text.scale);
        quad = {request->text.x, request->text.y, request->text.w, request->text.h};
        texquad = {0, 0, request->text.w, request->text.h};
        SDL_RenderCopyEx(getRenderer(), request->text.texture, &texquad, &quad, request->text.theta, &request->text.point, request->text.flip);
        (*request->text.reading)--;
        } else {
            (*request->text.reading)--;
            if (!(*request->text.reading)) {
                delete(request->text.valid);
                delete(request->text.reading);
            }
        }
        SDL_SemPost(textsync);
        break;    
    default:
        break;
    }
}