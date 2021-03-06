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

struct  s_window*   init_s_window(unsigned int p_w, unsigned int p_h, char* p_title, unsigned short color[])
{
        struct s_window* ret_window;

        ret_window = malloc(sizeof(struct s_window));
        ret_window->sdl_win = SDL_SetVideoMode(p_w, p_h, 32, SDL_HWSURFACE);
        check_SDL_Init(ret_window->sdl_win);
        SDL_WM_SetCaption(p_title, NULL);
        SDL_FillRect(ret_window->sdl_win, NULL, 
                    SDL_MapRGB((ret_window->sdl_win)->format,
                                color[0], color[1], color[2]));

        return (ret_window);
}

struct  s_surface* init_s_surface(SDL_Surface* p_window, unsigned int p_w, unsigned int p_h, unsigned int p_x, unsigned int p_y, unsigned short p_color[])
{
        struct s_surface*   ret_s_surface;  /* ptr ret sur la structure init */

        /* creation de la structure */
        ret_s_surface = malloc(sizeof(struct s_surface));

        /* initialisation de la surface sdl de la struct */
        ret_s_surface->sdl_surf = SDL_CreateRGBSurface(SDL_HWSURFACE, p_w, p_h,
                                                        32, 0, 0, 0, 0); 

        /* coloration de la surface sdl */
        SDL_FillRect(ret_s_surface->sdl_surf, 
                        NULL, SDL_MapRGB(p_window->format,
                        p_color[0], p_color[1], p_color[2]));

        /* definition des coordonnees */
        (*ret_s_surface).coord.x = p_x;
        (*ret_s_surface).coord.y = p_y;

        /* append */
        SDL_BlitSurface(ret_s_surface->sdl_surf,
                        NULL, p_window, &(ret_s_surface->coord));

        return (ret_s_surface);
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
        struct s_surface*   surface2;

        /* init SDL */
        SDL_Init(SDL_INIT_VIDEO);

        /* define main window */
        yolo_window = init_s_window(640, 480, "Super titre !",
                                    int_to_color(255, 255, 255));

        /* init test surface */
        surface = init_s_surface(yolo_window->sdl_win, 50, 200, 10, 10,
                                    int_to_color(0, 0, 0));
        surface2 = init_s_surface(yolo_window->sdl_win, 50,50, 30, 20,
                                    int_to_color(20, 20, 20));

        /* update show main window */
        SDL_Flip(yolo_window->sdl_win);

        /* ev_loop */
        ev_loop();

        /* free memory */
        SDL_FreeSurface(surface->sdl_surf);
        SDL_FreeSurface(surface2->sdl_surf);
        SDL_Quit();

        return EXIT_SUCCESS;
}


