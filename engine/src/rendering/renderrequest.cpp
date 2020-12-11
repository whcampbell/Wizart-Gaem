#include "internal/renderrequest.h"
#include "internal/screen.h"
#include "globals.h"

void drawRequest(RenderRequest* request) {
    
    SDL_Rect quad, texquad;
    switch (request->request.type)
    {
    case REQ_IMAGE:
        SDL_RenderSetScale(getRenderer(), request->image.scalex, request->image.scaley);
        quad = {(int)(request->image.x * GAMESCALE_X / request->image.scalex), (int)(request->image.y * GAMESCALE_Y / request->image.scaley),
         request->image.w, request->image.h};
        texquad = {request->image.x0 + request->image.texture->clips[request->image.frame]->x,
        request->image.y0 + request->image.texture->clips[request->image.frame]->y,
        request->image.w, request->image.h};
        SDL_RenderCopy(getRenderer(), request->image.texture->sheet, &texquad, &quad);
        break;
    case REQ_SPRITE:
        SDL_RenderSetScale(getRenderer(), request->sprite.scalex, request->sprite.scaley);
        quad = {(int)(request->sprite.x * GAMESCALE_X / request->sprite.scalex), (int)(request->sprite.y * GAMESCALE_Y / request->sprite.scaley),
         request->sprite.w, request->sprite.h};
        SDL_RenderCopyEx(getRenderer(), request->sprite.texture->sheet, request->sprite.texture->clips[request->sprite.frame], &quad, request->sprite.theta, &request->sprite.point, request->sprite.flip);
        break;
    case REQ_TEXT:
        SDL_RenderSetScale(getRenderer(), request->text.scalex, request->text.scaley);
        quad = {(int)(request->text.x * GAMESCALE_X / request->text.scalex), (int)(request->text.y * GAMESCALE_Y / request->text.scaley),
         request->text.w, request->text.h};
        texquad = {0, 0, request->text.w, request->text.h};
        SDL_RenderCopyEx(getRenderer(), request->text.texture, &texquad, &quad, request->text.theta, &request->text.point, request->text.flip);
        break;    
    case REQ_RECT:
        SDL_RenderSetScale(getRenderer(), request->rect.scalex, request->rect.scaley);
        quad = {request->rect.x, request->rect.y, request->rect.w, request->rect.h};
        SDL_SetRenderDrawColor(getRenderer(), request->rect.color1.r, request->rect.color1.g, request->rect.color1.b, request->rect.color1.a);
        SDL_RenderDrawRect(getRenderer(), &quad);
        SDL_SetRenderDrawColor(getRenderer(), 0, 0, 0, 255);
        break;
    case REQ_FRECT:
        SDL_RenderSetScale(getRenderer(), request->rect.scalex, request->rect.scaley);
        quad = {request->rect.x, request->rect.y, request->rect.w, request->rect.h};
        SDL_SetRenderDrawColor(getRenderer(), request->rect.color2.r, request->rect.color2.g, request->rect.color2.b, request->rect.color2.a);
        SDL_RenderFillRect(getRenderer(), &quad);
        SDL_SetRenderDrawColor(getRenderer(), request->rect.color1.r, request->rect.color1.g, request->rect.color1.b, request->rect.color1.a);
        SDL_RenderDrawRect(getRenderer(), &quad);
        SDL_SetRenderDrawColor(getRenderer(), 0, 0, 0, 255);
        break;
    default:
        break;
    }
}