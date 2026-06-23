/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-ant <juan-ant@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 12:57:22 by juan-ant          #+#    #+#             */
/*   Updated: 2025/11/13 20:22:34 by juan-ant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3Dexec.h"

void	init_rays(t_exec *exec)
{
	double	ray[3];

	ray[0] = exec->player.ang - ((double)(FOV / 2));
	ray[1] = exec->player.x;
	ray[2] = exec->player.y;
	loop_rays(ray, exec);
}

void	loop_rays(double ray[3], t_exec *exec)
{
	int		pixel;
	double	pixfov;

	pixfov = ((float)FOV) / WIDTH;
	pixel = 0;
	while (pixel < WIDTH)
	{
		cast_rays(ray, exec, pixel);
		if (ray[0] >= 360)
			ray[0] -= 360;
		pixel ++;
		ray[0] += pixfov;
	}
}

void	cast_rays(double ray[3], t_exec *exec, int pixel)
{
	t_ray	raytrace;

	raytrace.hit = -1;
	raytrace.pixel = 0;
	raytrace.dir = ray[0];
	raytrace.radx = cos(ray[0] * (M_PI / 180.0));
	raytrace.rady = sin(ray[0] * (M_PI / 180.0));
	raytrace.x = ray[1];
	raytrace.y = ray[2];
	raytrace.mapx = (int)ray[1];
	raytrace.mapy = (int)ray[2];
	raytrace.distance = 0;
	raytrace = dda(exec, raytrace);
	if (raytrace.side == 0)
		raytrace.distance = raytrace.sidex - raytrace.deltax;
	else
		raytrace.distance = raytrace.sidey - raytrace.deltay;
	drawmlx(pixel, raytrace.distance, exec, raytrace);
}

t_ray	dda(t_exec *exec, t_ray raytrace)
{
	raytrace.deltax = fabs(1 / raytrace.radx);
	raytrace.deltay = fabs(1 / raytrace.rady);
	raytrace = inicialize_side_step(raytrace);
	while (raytrace.hit == -1)
	{
		if (raytrace.sidex < raytrace.sidey)
		{
			raytrace.sidex += raytrace.deltax;
			raytrace.mapx += raytrace.stepx;
			raytrace.side = 0;
		}
		else
		{
			raytrace.sidey += raytrace.deltay;
			raytrace.mapy += raytrace.stepy;
			raytrace.side = 1;
		}
		if (exec->cub->map.grid[(int)raytrace.mapy][(int)raytrace.mapx] == '1')
			raytrace.hit = 1;
	}
	return (raytrace);
}

t_ray	inicialize_side_step(t_ray raytrace)
{
	if (raytrace.radx < 0)
	{
		raytrace.stepx = -1;
		raytrace.sidex = (raytrace.x - raytrace.mapx) * raytrace.deltax;
	}
	else
	{
		raytrace.stepx = 1;
		raytrace.sidex = (raytrace.mapx + 1 - raytrace.x) * raytrace.deltax;
	}
	if (raytrace.rady < 0)
	{
		raytrace.stepy = -1;
		raytrace.sidey = (raytrace.y - raytrace.mapy) * raytrace.deltay;
	}
	else
	{
		raytrace.stepy = 1;
		raytrace.sidey = (raytrace.mapy + 1 - raytrace.y) * raytrace.deltay;
	}
	return (raytrace);
}
