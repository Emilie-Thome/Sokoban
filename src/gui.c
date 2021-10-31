#include <signal.h>

#include "gui.h"

#define ICON_SIZE 32

static SDL_Surface* Loading_Surf;
static SDL_Texture* image[18];
static SDL_Window* sokoban_window;
static SDL_Renderer* renderer;

/**
 * @brief An enumeration to represent all symbols.
 *
 * It can be used to ease the readibility of your code.
 *
 */
enum object { BOY, BOY_ON, BOX, BOX_ON, PARK, WALL, EMPTY, CLICK_BUTTON, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, ZERO };

/**
 * @brief The set of `char` values used to represent maps.
 *
 */
static char symbols[] = { '@', '+', '$', '*', '.', '#', ' ','c', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0' };

/**
 * @brief The locations of the bitmap images to use.
 *
 * The files must be given in the same order as the symbols.
 */
static char* image_filename[] = {
    "my_images/yoshi-32-my-worker.bmp",
    "my_images/yoshi-32-my-worker-docked.bmp",
    "my_images/yoshi-32-pikachu.bmp",
    "my_images/yoshi-32-closed_pokeball.bmp",
    "my_images/yoshi-32-opened_pokeball.bmp",
    "my_images/yoshi-32-tree.bmp",
    "my_images/yoshi-32-garden.bmp",
    "my_images/yoshi-click_button.bmp",
    "my_images/yoshi-32-1.bmp",
    "my_images/yoshi-32-2.bmp",
    "my_images/yoshi-32-3.bmp",
    "my_images/yoshi-32-4.bmp",
    "my_images/yoshi-32-5.bmp",
    "my_images/yoshi-32-6.bmp",
    "my_images/yoshi-32-7.bmp",
    "my_images/yoshi-32-8.bmp",
    "my_images/yoshi-32-9.bmp",
    "my_images/yoshi-32-0.bmp"
};

void GUI_Close(int code) {
    for (int obj=BOY; obj<=ZERO; obj++) {
        SDL_DestroyTexture(image[obj]);
    }
    SDL_DestroyRenderer(renderer); 
    SDL_DestroyWindow(sokoban_window);
    SDL_Quit();
    exit(code);
}

void GUI_Init(char *title, int width, int height)
{
    if (SDL_Init(SDL_INIT_VIDEO)!=0) {
        fprintf(stderr,"Error in SDL_Init : %s\n",SDL_GetError());
        exit(-1);
    }
    
    sokoban_window = SDL_CreateWindow(title,
                          SDL_WINDOWPOS_CENTERED,
                          SDL_WINDOWPOS_CENTERED,
                          width*ICON_SIZE, height*ICON_SIZE,
                          0);
    if(sokoban_window==NULL){
        printf("Error during window creation: %s",SDL_GetError());
        return exit(-1);
    }
    Loading_Surf = SDL_LoadBMP(image_filename[BOY]);
    SDL_SetWindowIcon(sokoban_window, Loading_Surf);
    SDL_FreeSurface(Loading_Surf);

    renderer = SDL_CreateRenderer(sokoban_window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer==NULL){
        printf("Error during renderer creation: %s",SDL_GetError());
        return exit(-1);
    }
    SDL_RenderClear(renderer);
    Loading_Surf = SDL_LoadBMP(image_filename[PARK]);
    SDL_Texture* Background_Tx = SDL_CreateTextureFromSurface(renderer, Loading_Surf);
    SDL_FreeSurface(Loading_Surf);
    SDL_RenderCopy(renderer, Background_Tx, NULL, NULL);
    SDL_RenderPresent(renderer);
    SDL_Delay(1000);


    SDL_EventState(SDL_KEYDOWN,         SDL_ENABLE);
    SDL_EventState(SDL_QUIT,            SDL_ENABLE);
    SDL_EventState(SDL_SYSWMEVENT,      SDL_ENABLE);
    atexit(SDL_Quit);
    signal(SIGINT,GUI_Close);
    signal(SIGTERM,GUI_Close);

    for (int obj=BOY; obj<=ZERO; obj++) {
        Loading_Surf = SDL_LoadBMP(image_filename[obj]);
        if (!Loading_Surf) {
            fprintf(stderr, "Missing image %s\n", image_filename[obj]);
            exit(1);
        }
        image[obj] = SDL_CreateTextureFromSurface(renderer, Loading_Surf);
        if(NULL == image[obj]){
            fprintf(stderr, "Error SDL_CreateTextureFromSurface : %s", SDL_GetError());
            exit(-1);
        }
        SDL_FreeSurface(Loading_Surf);
    }
}

void GUI_Prep(int x, int y, char symbol)
{
    SDL_Rect area = { x * ICON_SIZE, y * ICON_SIZE, ICON_SIZE, ICON_SIZE };
    for (int obj=BOY; obj<=ZERO; obj++) if (symbol == symbols[obj]) SDL_RenderCopy(renderer, image[obj], NULL, &area);
}


void GUI_Show()
{
    SDL_RenderPresent(renderer);
}




void GUI_click_button(int width, int height){
    int x = width/2 - 2;
    int y = height/2 + 1;

    SDL_Rect area = { x * ICON_SIZE , y * ICON_SIZE, ICON_SIZE*4, ICON_SIZE*2 };

    //SDL_BlitSurface(image[CLICK_BUTTON], NULL, screen, &area);
    //SDL_Flip(screen);

    SDL_RenderCopy(renderer, image[CLICK_BUTTON], NULL, &area);
    SDL_RenderPresent(renderer);
}


int GUI_GetKey(void)
{
    SDL_Event event;
    do {
        SDL_WaitEvent(&event);
        if (event.type==SDL_QUIT) GUI_Close(0);
    } while (event.type != SDL_KEYDOWN);

    return event.key.keysym.sym;
}

void WaitClick()
{
    SDL_EventState(SDL_MOUSEBUTTONDOWN, SDL_ENABLE);
    SDL_Event event;
    do {
        SDL_WaitEvent(&event);
    } while (event.type!=SDL_MOUSEBUTTONDOWN);
    SDL_EventState(SDL_MOUSEBUTTONDOWN, SDL_IGNORE);
}

void Pause(int time)
{
    SDL_Delay(time);
}
