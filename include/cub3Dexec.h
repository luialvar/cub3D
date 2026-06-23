/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3Dexec.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-ant <juan-ant@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 12:53:19 by juan-ant          #+#    #+#             */
/*   Updated: 2026/03/02 16:08:28 by juan-ant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3DEXEC_H
# define CUB3DEXEC_H

# include <math.h>
# include "cub3D.h"
# include "../MLX42/include/MLX42/MLX42.h"

# define WIDTH 1080
# define HEIGHT 520
# define WALL 52
# define FOV 60
# define SPEED 0.05
# define ROTATE_SPEED 50
# define DARKNESS 8

typedef struct t_txtu
{
	mlx_texture_t	*no_t;
	mlx_texture_t	*so_t;
	mlx_texture_t	*ea_t;
	mlx_texture_t	*we_t;
}	t_txtu;

typedef struct t_plr
{
	double	x;
	double	y;
	double	ang;
}	t_plr;

typedef struct t_ray
{
	double			radx;
	double			rady;
	int				stepx;
	int				stepy;
	double			deltax;
	double			deltay;
	double			distance;
	double			x;
	double			y;
	int				mapx;
	int				mapy;
	double			sidex;
	double			sidey;
	int				side;
	double			hit;
	double			dir;
	unsigned int	wallh;
	unsigned int	start;
	int				pixel;
}	t_ray;

typedef struct t_exec
{
	struct s_game_data	*cub;
	t_plr				player;
	mlx_t				*stance;
	mlx_image_t			*img;
	mlx_texture_t		*no;
	mlx_texture_t		*we;
	mlx_texture_t		*so;
	mlx_texture_t		*ea;
	t_ray				moveray;
}	t_exec;

double	sec_transform(double valone, double valtwo);

void	init_rays(t_exec *exec);

void	loop_rays(double ray[3], t_exec *exec);

void	cast_rays(double ray[3], t_exec *exec, int pixel);

void	init_player(t_exec *exec);

void	drawmlx(int pixel, double distance, t_exec *exec, t_ray raytrace);

void	rotate_l(t_exec *exec);

void	rotate_r(t_exec *exec);

void	move_up(t_exec *exec);

void	move_down(t_exec *exec);

void	move_left(t_exec *exec);

void	move_right(t_exec *exec);

t_ray	inicialize_side_step(t_ray raytrace);

t_ray	dda(t_exec *exec, t_ray raytrace);

int		ray_move(double play_rad, t_exec *exec);

void	move_final_calc(t_exec *exec);

int		angle_ifs(int side, double angle);

#endif