// importing libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h> //for loading images
#include <SDL/SDL_ttf.h>   //for loading fonts
#include <SDL/SDL_mixer.h> //for loading sounds

// including the headers
#include "../include/image.h"
#include "../include/music.h"
#include "../include/text.h"

// images
SDL_Surface *screen;
image background;
image playButton;
image settingsButton;
image exitButton;

// music
Mix_Music *music;
Mix_Chunk *clickFX;

// text
text score;

// logic
SDL_Event event;
int loop = 1;

/*
********************
*****GAME BEGIN*****
********************
*/

int main()
{
    // initializing SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("SDL_Init Error: %s.\n", SDL_GetError());
        return 1;
    }

    // creating the window
    screen = SDL_SetVideoMode(SCREEN_W, SCREEN_H, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    if (screen == NULL)
    {
        printf("Error creating the screen: %s\n", SDL_GetError());
        return 1;
    }

    // loading images
    imageLoad_background(&background);
    imageLoad_playbutton(&playButton);
    imageLoad_settingsbutton(&settingsButton);
    imageLoad_quitbutton(&exitButton);

    // loading music
    musicLoad(music);

    // loading text
    textLoad(&score);

    /*
     ********************
     *****GAME LOOP******
     ********************
     */

    while (loop)
    {
        // drawing images
        imageDraw_background(screen, background);
        imageDraw_playbutton(screen, playButton);
        imageDraw_settingsbutton(screen, settingsButton);
        imageDraw_quitbutton(screen, exitButton);

        // drawing text
        textDraw(screen, score, "Score: 0");

        // events
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_MOUSEMOTION:
                if (event.motion.x >= playButton.img_pos.x && event.motion.x <= playButton.img_pos.x + playButton.img_size.w && event.motion.y >= playButton.img_pos.y && event.motion.y <= playButton.img_pos.y + playButton.img_size.h)
                {
                    FXLoad(clickFX);
                }
                break;

            case SDL_QUIT: // if the user clicks on the close button
                loop = 0;
                break;

            default:
                break;
            }
        }

        // rereshing the screen
        SDL_Flip(screen);
    }

    // freeing memory
    imageFree(&background);
    imageFree(&playButton);
    imageFree(&settingsButton);
    imageFree(&exitButton);
    musicFree(music);

    SDL_Quit();
    return 0;
}