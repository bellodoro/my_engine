/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_engine.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhammerc <mhammerc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 13:33:51 by mhammerc          #+#    #+#             */
/*   Updated: 2017/01/05 12:05:33 by mhammerc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_ENGINE_H
# define MY_ENGINE_H

# include "me_keys.h"
# include "libft/libft.h"

/*
** Constants
*/
# define FPS_30 (1. / 30.)
# define FPS_60 (1. / 60.)
# define FPS_120 (1. / 120.)
# define THREAD_NUMBER 4

/*
** Semantic type definitions
*/
typedef double			t_me_ms;

/*
** MATH FUNCTIONS/STRUCTURES
*/
typedef struct			s_me_vector2i
{
	int					x;
	int					y;
}						t_me_vector2i;

typedef struct			s_me_vector2d
{
	double				x;
	double				y;
}						t_me_vector2d;

/*
** MLX LAYER
*/
typedef struct			s_me_mlx_img
{
	void				*img;
	int					*pixel;
	int					bits_per_pixel;
	int					size_line;
	int					endian;
}						t_me_mlx_img;

typedef struct			s_me_mlx
{
	void				*mlx;
	void				*win;
	t_me_mlx_img		img;
}						t_me_mlx;

/*
** HIGH LEVEL ENGINE
*/

typedef struct s_me_engine	t_me_engine;

/*
** Render function prototype and predefined render functions.
** Called every frame to draw a new image onto the window.
*/
typedef void			(*t_me_render)(t_me_engine *engine, void *data,
		int begin, int end);

/*
** Update function.
** Called when the logic have to be re-computed.
*/
typedef void			(*t_me_update)(t_me_engine *engine, t_me_ms delta_time,
		void *data);

/*
** Error management
*/
void					me_die(char *error);

/*
*** States management
*/
typedef struct			s_me_state
{
	char				*name;
	void				*data;
	t_me_render			render;
	t_me_update			update;
}						t_me_state;

typedef struct			s_me_state_list
{
	char				*running_state;
	t_list				*list;
}						t_me_state_list;

void					me_add_state(t_me_engine *engine, t_me_state *state);
t_me_state				*me_get_state(t_me_engine *engine, char *name);

/*
** Animated sprites
*/
typedef struct			s_me_animation
{
	int					number_of_frame;
	int					current_frame;
	int					first_texture_id;
	double				millis_between_frames;
	double				time_of_last_frame;
}						t_me_animation;

void					me_process_animation(t_me_animation *animation,
		t_me_ms delta_time);
int						me_get_texture_for_animation(t_me_animation *animation);

/*
** Double animator
*/
typedef struct			s_me_animator
{
	double				value;
	double				amount_every_seconds;
	double				velocity;
	double				delta_min;
	double				delta_max;
}						t_me_animator;

void					me_animator_give_velocity(t_me_animator *animator,
		double velocity);
void					me_process_animator(t_me_animator *animator,
		t_me_ms delta_time);

/*
** Maps management
*/
typedef struct			s_me_map
{
	char				*name;
	char				*tileset;
	t_me_vector2i		size;
	int					**wmap;
	int					**bmap;
	int					**fmap;
	int					**cmap;
	t_list				*tmap;
}						t_me_map;

typedef struct			s_thing
{
	t_me_vector2d		pos;
	int					texture;
	int					is_animated;
	t_me_animation		animation;
}						t_me_thing;

void					parse_map_equal(t_me_map *map, char *line);
t_me_thing				*create_thing(size_t j, size_t i, int texture);
t_me_map				*me_load_map(char *file);
void					norme1(int j, t_me_map *map, char **split, int *i);
void					norme2(int j, t_me_map *map, int *i, char *line);

/*
** Events
*/
typedef struct			s_me_events_key_press
{
	int					keycode;
	char				is_pressed;
}						t_me_events_key_press;

typedef struct			s_me_mouse_move
{
	t_me_vector2i		last_move;
}						t_me_mouse_move;

typedef struct			s_me_events
{
	t_list				*key_pressed;
	t_me_mouse_move		mouse_move;
}						t_me_events;

int						me_game_loop(void *param);
int						me_key_press(int keycode, void *param);
int						me_key_release(int keycode, void *param);
int						me_mouse_move(int x, int y, void *param);
int						me_is_key_pressed(int keycode, t_me_engine *engine);

/*
** Texture manager
*/
typedef struct			s_me_texture
{
	char				*name;
	int					id;
	void				*img;
	int					*pixel;
	int					bpp;
	int					sl;
	int					endian;
	t_me_vector2i		size;
}						t_me_texture;

void					me_load_texture(char *name, int id, char *filename,
		t_me_engine *engine);
t_me_texture			*me_get_texture_information_by_name(char *name,
		t_me_engine *engine);
int						*me_get_texture_data_by_name(char *name,
		t_me_engine *engine);
t_me_texture			*me_get_texture_information_by_id(int id,
		t_me_engine *engine);
int						*me_get_texture_data_by_id(int id,
		t_me_engine *engine);

/*
*** Engine basic functions
*/
typedef struct			s_me_config
{
	int					fov;
	t_me_vector2i		window_size;
	char				*window_name;
	double				framerate;
}						t_me_config;

struct					s_me_engine
{
	t_me_config			config;
	t_me_events			events;
	t_me_mlx			mlx;
	t_me_state_list		state_list;
	t_list				*textures;
};

void					print_fps_counter(double time_in_mill);
void					print_image(t_me_engine *engine);
double					compute_time(t_me_engine *engine, double *start,
		double *end);
t_me_engine				*me_init(t_me_config config);
void					me_create_main_window(t_me_engine *engine);
void					me_run_game_loop(t_me_engine *engine);
void					clear_image(t_me_engine *engine);

int						me_exit_game(t_me_engine *engine);

/*
** Raycasting engine
*/
typedef struct			s_raycasting_player
{
	t_me_vector2d		pos;
	t_me_vector2d		dir;
	t_me_vector2d		plane;
}						t_raycasting_player;

typedef struct			s_raycasting_data
{
	t_me_map			*map;
	t_raycasting_player player;
	double				*z_buffer;
}						t_raycasting_data;

typedef struct			s_raycasting_rendering_data
{
	t_me_vector2i		coord;
	double				camera_x;
	t_me_vector2d		ray_pos;
	t_me_vector2d		ray_dir;
	t_me_vector2i		map;
	t_me_vector2d		side_dist;
	t_me_vector2d		delta_dist;
	t_me_vector2i		step;
	int					hit;
	int					side;
	double				perp_wall_dist;
	int					line_height;
	int					draw_start;
	int					draw_end;
	int					tex_num;
	t_me_texture		*tex_info;
	double				wall_x;
	int					tex_x;
	int					y;
	int					*pixel;
	int					*tex;
	int					d;
	int					tex_y;
	int					color;
	t_me_vector2d		floor_wall;
	double				dist_wall;
	double				dist_player;
	double				current_dist;
	int					*ftex;
	int					*ctex;
	t_me_texture		*ftex_info;
	t_me_texture		*ctex_info;
	t_me_vector2d		floor_tex;
	t_me_vector2d		cloor_tex;
	double				weight;
	t_me_vector2d		current_floor;
	int					num_sprites;
	int					*sprite_order;
	double				*sprite_distance;
	t_list				*things;
	t_me_thing			*thing;
	double				sprite_x;
	double				sprite_y;
	double				inv_det;
	double				transform_y;
	double				transform_x;
	int					sprite_screen_x;
	int					sprite_height;
	int					draw_start_y;
	int					draw_end_y;
	int					sprite_width;
	int					draw_start_x;
	int					draw_end_x;
	int					texture_id;
	t_me_texture		*tex2;
}						t_me_raycasting_rendering_data;

typedef struct			s_me_thread_render
{
	int					id;
	t_me_engine			*engine;
}						t_me_thread_render;

void					me_raycaster_process_key_pressed(t_me_engine *engine,
		t_raycasting_data *info, t_me_ms delta_time);

void					me_thing_combsort(int *order, double *dist, int amount);
void					me_raycaster_wall_loop1(t_me_engine *engine,
		t_raycasting_data *info, t_me_raycasting_rendering_data *x);
void					me_raycaster_wall_loop2(
		t_me_raycasting_rendering_data *x);
void					me_raycaster_wall_loop3(t_raycasting_data *info,
		t_me_raycasting_rendering_data *x);
void					me_raycaster_wall_loop4(t_me_engine *engine,
		t_raycasting_data *info, t_me_raycasting_rendering_data *x);
void					me_raycaster_wall_loop5(t_me_engine *engine,
		t_raycasting_data *info, t_me_raycasting_rendering_data *x);
void					me_raycaster_wall_loop6(
		t_me_raycasting_rendering_data *x);
void					me_raycaster_wall_loop7(t_me_engine *engine,
		t_raycasting_data *info, t_me_raycasting_rendering_data *x);
void					me_raycaster_wall_loop8_1(t_me_engine *engine,
		t_me_raycasting_rendering_data *x);
void					me_raycaster_wall_loop8(t_me_engine *engine,
		t_raycasting_data *info, t_me_raycasting_rendering_data *x);
void					me_raycaster_wall_loop(t_me_engine *engine,
		t_raycasting_data *info, t_me_raycasting_rendering_data *x);
void					me_raycaster_thing1(t_raycasting_data *info,
		t_me_raycasting_rendering_data *x);
void					me_raycaster_thing_loop1(t_me_engine *engine,
		t_raycasting_data *info, t_me_raycasting_rendering_data *x, int i);
void					me_raycaster_thing_loop2(t_me_engine *engine,
		t_me_raycasting_rendering_data *x);
void					me_raycaster_thing_loop3(t_me_engine *engine,
		t_raycasting_data *info, t_me_raycasting_rendering_data *x);

void					me_raycaster_render(t_me_engine *engine, void *data,
		int begin, int end);
void					me_raycaster_update(t_me_engine *engine,
		t_me_ms delta_time, void *data);

#endif
