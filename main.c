#include    <stdlib.h>
#include    <stdio.h>
#include    <SDL/SDL.h>
#include    "simp_sdl.h"

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
