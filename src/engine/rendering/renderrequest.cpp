#include "renderrequest.h"
#include "screen.h"

void drawRequest(RenderRequest request) {
    
    SDL_Rect quad;
    switch (request.request.type)
    {
    case REQ_IMAGE:
        SDL_RenderSetScale(getRenderer(), request.image.scale, request.image.scale);
        quad = {request.image.x, request.image.y, request.image.w, request.image.h};
        SDL_RenderCopy(getRenderer(), request.image.texture->sheet, request.image.texture->clips[request.image.frame], &quad);
        break;
    case REQ_SPRITE:
        SDL_RenderSetScale(getRenderer(), request.sprite.scale, request.sprite.scale);
        quad = {request.sprite.x, request.sprite.y, request.sprite.w, request.sprite.h};
        SDL_RenderCopyEx(getRenderer(), request.sprite.texture->sheet, request.sprite.texture->clips[request.sprite.frame], &quad, request.sprite.theta, &request.sprite.point, request.sprite.flip);
        break;
    case REQ_TEXT:
        /* code */
        break;    
    default:
        break;
    }
}