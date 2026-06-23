/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_aux.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-ant <juan-ant@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 12:58:34 by juan-ant          #+#    #+#             */
/*   Updated: 2025/08/13 12:47:08 by juan-ant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3Dexec.h"

void	move_dda_calc(t_exec *exec)
{
	if (exec->moveray.sidex < exec->moveray.sidey)
	{
		exec->moveray.sidex += exec->moveray.deltax;
		exec->moveray.mapx += exec->moveray.stepx;
		exec->moveray.side = 0;
	}
	else
	{
		exec->moveray.sidey += exec->moveray.deltay;
		exec->moveray.mapy += exec->moveray.stepy;
		exec->moveray.side = 1;
	}
	if (exec->moveray.side == 0)
		exec->moveray.distance = exec->moveray.sidex - exec->moveray.deltax;
	else
		exec->moveray.distance = exec->moveray.sidey - exec->moveray.deltay;
}

int	move_dda(t_exec *exec)
{
	exec->moveray.deltax = fabs(1 / exec->moveray.radx);
	exec->moveray.deltay = fabs(1 / exec->moveray.rady);
	exec->moveray = inicialize_side_step(exec->moveray);
	while (exec->moveray.hit == -1)
	{
		move_dda_calc(exec);
		if (exec->cub->map.grid[(int)(exec->moveray.mapy)]
			[(int)(exec->moveray.mapx)] == '1')
			exec->moveray.hit = 1;
	}
	if (exec->moveray.distance > 0.2)
		return (1);
	return (0);
}

int	cast_ray_move(double ray[4], t_exec *exec)
{
	t_ray	mray;

	mray.hit = -1;
	exec->moveray = mray;
	exec->moveray.pixel = 0;
	exec->moveray.dir = ray[0];
	exec->moveray.radx = cos(ray[0] * (M_PI / 180.0));
	exec->moveray.rady = sin(ray[0] * (M_PI / 180.0));
	exec->moveray.x = ray[1];
	exec->moveray.y = ray[2];
	exec->moveray.mapx = (int)ray[1];
	exec->moveray.mapy = (int)ray[2];
	exec->moveray.distance = 0;
	return (move_dda(exec));
}

int	loop_rayt_move(double ray[4], t_exec *exec)
{
	int		pixel;
	double	pixfov;

	pixel = 0;
	pixfov = 5;
	while (pixel <= 90)
	{
		if (cast_ray_move(ray, exec) == 1)
			return (1);
		if (ray[0] >= 360)
			ray[0] -= 360;
		pixel += 2;
		if (ray[3] == 1)
			ray[0] += pixfov;
		else
			ray[0] -= pixfov;
	}
	return (0);
}

int	ray_move(double play_rad, t_exec *exec)
{
	double	ray[4];

	if (play_rad > 360)
		play_rad -= 360;
	if (play_rad < 0)
		play_rad += 360;
	ray[0] = play_rad;
	ray[1] = exec->player.x;
	ray[2] = exec->player.y;
	cast_ray_move(ray, exec);
	ray[3] = angle_ifs(exec->moveray.side, play_rad);
	return (loop_rayt_move(ray, exec));
}
