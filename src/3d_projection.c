#include <SDL2/SDL.h>
#include "../inc/header.h"
#include "../inc/constants.h"

/**
 * generate3DProjection - creating 3d projection
 * Return: Nothing
 */
void generate3DProjection(void)
{
    int i, y;
    float perpDistance, distanceProjPlane, projectedWallHeight;
    int wallStripHeight, wallTopPixel, wallBottomPixel;
    int textureOffsetX;
    int distanceFromTop, textureOffsetY;
    Uint32 texelColor;
    (void)texelColor;
    int texNum;

    for (i = 0; i < NUM_RAYS; i++)
    {
        perpDistance = rays[i].distance * cos(rays[i].rayAngle - p.rotationAngle);
        distanceProjPlane = (WINDOW_WIDTH / 2) / tan(FOV_ANGLE / 2);
        projectedWallHeight = (TILE_SIZE / perpDistance) * distanceProjPlane;

        wallStripHeight = (int)projectedWallHeight;

        wallTopPixel = (WINDOW_HEIGHT / 2) - (wallStripHeight / 2);
        wallTopPixel = wallTopPixel < 0 ? 0 : wallTopPixel;

        wallBottomPixel = (WINDOW_HEIGHT / 2) + (wallStripHeight / 2);
        wallBottomPixel = wallBottomPixel > WINDOW_HEIGHT ? WINDOW_HEIGHT : wallBottomPixel;

        /* Ceiling */
        for (y = 0; y < wallTopPixel; y++)
            colorBuffer[(WINDOW_WIDTH * y) + i] = 0x190B33;

        /* calculate texture offset X */
        if (rays[i].wasHitVertical)
            textureOffsetX = (int)rays[i].wallHitY % TEXTURE_HEIGHT;
        else
            textureOffsetX = (int)rays[i].wallHitX % TEXTURE_WIDTH;

        /* getting the correct texture id number from the map */
        texNum = rays[i].wallHitContent - 1;

        /* rendering the wall from wallTopPixel to wallBottomPixel */
        for (y = wallTopPixel; y < wallBottomPixel; y++)
        {
            /* calculating texture offset Y */
            distanceFromTop = y + (wallStripHeight / 2) - (WINDOW_HEIGHT / 2);
            textureOffsetY = distanceFromTop * ((float)TEXTURE_HEIGHT / wallStripHeight);

            /* seting the color of the wall based on the color from the texture */
            Uint32 texelColor = textures[texNum][(TEXTURE_WIDTH * textureOffsetY) + textureOffsetX];
            colorBuffer[(WINDOW_WIDTH * y) + i] = texelColor;
        }

        /* set the color of the floor */
        for (y = wallBottomPixel; y < WINDOW_HEIGHT; y++)
            colorBuffer[(WINDOW_WIDTH * y) + i] = 0xC1C1C1;

        /* This For Having No Sky and Replacing It With Taller Walls */
        /*for (y = 0; y < wallTopPixel; y++)
        {
            colorBuffer[(WINDOW_WIDTH * y) + i] = rays[i].wasHitVertical ? 0xFFFFFFFF : 0xFFCCCCCC;
        }*/
    }
}
