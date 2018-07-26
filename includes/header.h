/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rolevy <rolevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 00:06:06 by rolevy            #+#    #+#             */
/*   Updated: 2018/07/26 10:39:42 by rolevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include "../import/minilibx/mlx.h"
# include "../import/libft/libft.h"
# include "../import/event/event.h"
# include "../import/GNL/get_next_line.h"
# include "../import/event/key_codes_macos.h"
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <stdbool.h>
# include <fcntl.h>
# include <stdint.h>
# include <pthread.h>
# include </Users/rolevy/.brew/Cellar/sdl2/2.0.8/include/SDL2/SDL.h>
# include "/Users/rolevy/.brew/Cellar/sdl2_image/2.0.3/include/SDL2/SDL_image.h"

/*
** #############################################################################
** #																		   #
** #							MACROS										   #
** #																		   #
** #############################################################################
*/

# define WIDTH		2560
# define HEIGHT		1440

# define TEXTWIDTH	100
# define TEXTHEIGHT	100

# define ABS(x) (x < 0) ? -x : x

# define HEIGHT_R	10

# define MOVE_SPEED .2
# define ROT_SPEED	.05

/*
** #############################################################################
** #																		   #
** #							Structures									   #
** #																		   #
** #############################################################################
*/

/*
*** ##############
*** #  Textures  #
*** ##############
*/

typedef struct		s_color
{
	int				r;
	int				g;
	int				b;
	int				a;
}					t_color;

typedef struct		s_texture
{
	SDL_Rect		*pos;
	SDL_Renderer	*rend;
	SDL_Surface		*srf;
	SDL_Texture		*texture;
	SDL_PixelFormat	pixel_format;
	Uint32			format;
	int				pitch;
	int				width;
	int				height;
	t_color			color;
	
}					t_texture;

/*
*** ##############
*** #   Parsing  #
*** ##############
*/

typedef struct		s_index
{
	int				x;
	int				y;
}					t_index;


typedef struct		s_map
{
	int				width;
	int				height;
	int				**tab;
	t_index			index;
}					t_map;

/*
*** ##############
*** # Raycasting #
*** ##############
*/


typedef struct		s_vector
{
	double			x;
	double			y;
}					t_vector;

typedef struct		s_player
{
	t_vector		pos;
	int				m_speed;
	int				r_speed;
}					t_player;

typedef struct		s_wall
{
	double			start;
	double			end;
	int				height;
}					t_wall;

typedef struct		s_ray
{
	double			wall_dist;
	t_vector		coord_dist;
	t_vector		dir;
	t_vector		step;
	t_vector		delta;
	t_vector		plane;
	t_vector		val;
	double			cam;
	int				hit;
	int				side;
	int				hit_height;
	int				tex_pos;
	t_wall			wall;

}					t_ray;

/*
*** ##############
*** #Environement#
*** ##############
*/

typedef struct		s_env
{
	int				w;
	int				h;
	int				fullscreen;
	bool			loop;
	SDL_Event		ev;
	SDL_Window		*win;
	t_player		*player;
	t_ray			*ray;
	t_map			*map;
	t_texture		*texture;
	t_texture		*render;
	int				curtime;
	int				oldtime;
	double			fps;
}					t_env;

/*
*** ##############
*** #   Input    #
*** ##############
*/

typedef enum		e_key_type
{
	ESCAPE = 0,
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	TOGGLE,
	KEY_MAX
}					t_key_type;

typedef struct		s_key
{
	int				input;
	t_key_type		type;
	int				(*function)(t_env *);
}					t_key;

/*
** #############################################################################
** #																		   #
** #							Functions Prototype							   #
** #																		   #
** #############################################################################
*/

/*
*** ##############
*** #    Init    #
*** ##############
*/

void				alloc_wolf3d(t_env *env);
void				init_env(t_env *env, char **src);
void				init_player_dir(t_ray *ray, t_player *player);
t_map				*gen_map(char *src);

/*
*** ##############
*** #  Textures  #
*** ##############
*/

void				gen_surface(t_env * env);
void				display(t_ray *ray, t_env *env);
void				clear_screen(t_env *env);

/*
*** ##############
*** # Raycasting #
*** ##############
*/

void				get_ray_coords(t_ray *ray, t_map *map, int x,
					t_player *player);
t_vector			get_coord_distance(t_player *player, t_ray *ray,
					t_map *map);
void				raycasting(t_map *map, t_env *env);
void				draw(int x, t_ray *ray, t_texture *texture, t_env *env);

/*
*** ##############
*** #   Input    #
*** ##############
*/

int					process_key(int input, t_env *env);
int					move_backward(t_env *env);
int					move_forward(t_env *env);
int					move_left(t_env *env);
int					move_right(t_env *env);
int					toggle_fullscreen(t_env *env);
int					quit(t_env *env);

#endif
