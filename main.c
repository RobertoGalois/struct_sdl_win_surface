#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>

struct  s_surface
{
        SDL_Surface     *sdl_surf;
        SDL_Rect        coord;
};

struct  s_window
{
        SDL_Surface*    sdl_win;
        char*           title;
};

void    check_SDL_Init(SDL_Surface* p_element)
{
        if (p_element == NULL)
        {
            fprintf(stderr, "Impossible de charger le mode vidéo : %s\n",
                    SDL_GetError());

            exit(EXIT_FAILURE);
        }
}

/* transform 3 unsigned short into an unsigned short[]) */
unsigned short*     int_to_color(unsigned short p_r, unsigned short p_g, unsigned short p_b)
{
    unsigned short* ret_tab;

    ret_tab = malloc(3 * sizeof(unsigned short));
    *(ret_tab) = p_r;
    *(ret_tab+1) = p_g;
    *(ret_tab+2) = p_b;
    return (ret_tab);
}

struct  s_window*   init_s_window()
{
        struct s_window* ret_window;

        ret_window = malloc(sizeof(struct s_window));
        ret_window->sdl_win = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE);
        check_SDL_Init(ret_window->sdl_win);
        SDL_WM_SetCaption("Ma super fenêtre SDL !", NULL);
        SDL_FillRect(ret_window->sdl_win, NULL, 
                    SDL_MapRGB((ret_window->sdl_win)->format, 255, 255, 255));

        return (ret_window);
}

void    ev_loop(void)
{
        signed short    bool_continue = 1;
        SDL_Event ev;

        while (bool_continue)
        {
            SDL_WaitEvent(&ev);
            switch(ev.type)
            {
                case SDL_QUIT:
                bool_continue = 0;
            }
        }
}


int     main(int argc, char *argv[])
{
        SDL_Surface         *window = NULL;     /* main window */
        SDL_Surface         *rectangle;         /* surface */
        SDL_Rect            position;           /* coord of surface  */

        struct s_surface*   surface;
        struct s_window*    yolo_window;

        /* init SDL */
        SDL_Init(SDL_INIT_VIDEO);

        /* define main window */
        yolo_window = init_s_window();

        /* init test surface */
        surface = init_s_surface(yolo_window->sdl_win, 50, 200, 10, 10,
                                    int_to_color(0, 0, 0));

        /* update show main window */
        SDL_Flip(yolo_window->sdl_win);

        /* ev_loop */
        ev_loop();

        /* free memory */
        SDL_FreeSurface(surface->sdl_surf);
        SDL_Quit();

        return EXIT_SUCCESS;
}
