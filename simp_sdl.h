#ifndef SIMP_SDL_H
 #define SIMP_SDL_H

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

 void               check_SDL_Init(SDL_Surface* p_element);

 unsigned short*    int_to_color(unsigned short p_r,
                                    unsigned short p_g,
                                    unsigned short p_b);

 struct s_window*   init_s_window(unsigned int p_w,
                                    unsigned int p_h,
                                    char* p_title,
                                    unsigned short color[]);

 struct  s_surface* init_s_surface(SDL_Surface* p_window,
                                    unsigned int p_w,
                                    unsigned int p_h,
                                    unsigned int p_x,
                                    unsigned int p_y,
                                    unsigned short p_color[]);

 void   ev_loop(void);
 void   test(void);

#endif
