/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-ant <juan-ant@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 14:44:43 by juan-ant          #+#    #+#             */
/*   Updated: 2025/11/17 12:51:56 by juan-ant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3Dexec.h"

uint32_t	transform_color(t_exec *exec, int mode, int i, int pixel)
{
	t_color		touse;
	uint32_t	transformed;
	float	t;
	int	darkval;
	
	if (pixel == 0)
		pixel = 1;
	if (i > HEIGHT / 2)
		i = ((HEIGHT / 2) - (i - (HEIGHT / 2)));
	if (i != 0)
		i = (float)((float)i / (float)(HEIGHT / 2)) * 100;
	if (pixel > WIDTH / 2)
		pixel = ((WIDTH / 2) - (pixel - (WIDTH / 2)));
	if (pixel != 0)
		pixel = (float)((float)pixel / (float)(WIDTH / 2)) * 100;
	darkval = (i * 1.2) - (pixel * 0.2);
	if (darkval < 0)
		darkval = 0;
	if (mode == 1)
		touse = exec->cub->ceiling_color;
	else
		touse = exec->cub->floor_color;
	transformed = 0;
	t = touse.r;
	if (touse.g > t)
		t = touse.g;
	if (touse.b > t)
		t = touse.b;
	t /= 100;
	darkval *= t;

	if (touse.r > darkval)
		transformed += (touse.r - darkval) << 24;
	if (touse.g > darkval)
		transformed += (touse.g - darkval) << 16;
	if (touse.b > darkval)
		transformed += (touse.b - darkval) << 8;
	transformed += 255;
	return (transformed);
}

uint32_t	get_texture_pixel(mlx_texture_t *tex, int size, int i, double coord, t_ray raytrace)
{
	uint32_t	img_h;
	uint32_t	img_w;
	uint32_t	pixel;
	uint32_t	transformed;

	img_h = (((tex->height - 1) * i) / size) * tex->width;
	img_w = tex->width - (int)(tex->width * (coord - (int)coord));
	pixel = (img_h + img_w) * tex->bytes_per_pixel;

	if (tex->pixels[pixel] < (((uint32_t)raytrace.distance)) * DARKNESS)
		transformed = 0 << 24;
	else
		transformed = (tex->pixels[pixel] - (((uint32_t)raytrace.distance)) * DARKNESS) << 24;

	if (tex->pixels[pixel + 1] < (((uint32_t)raytrace.distance)) * DARKNESS)
		transformed += 0 << 16;
	else
		transformed += (tex->pixels[pixel + 1] - (((uint32_t)raytrace.distance)) * DARKNESS) << 16;

	if (tex->pixels[pixel + 2] < (((uint32_t)raytrace.distance)) * DARKNESS)
		transformed += 0 << 8;
	else
		transformed += (tex->pixels[pixel + 2] - (((uint32_t)raytrace.distance)) * DARKNESS) << 8;

	transformed += 255;
	return (transformed);
}


uint32_t	texture_pixel(t_ray raytrace, t_exec *exec, int i, int pixel)
{
	if (raytrace.side == 0 && raytrace.stepx < 0)
	{
		return (get_texture_pixel(exec->we,
				raytrace.wallh, i - raytrace.start, raytrace.hit, raytrace));
	}
	else if (raytrace.side == 0 && raytrace.stepx > 0)
	{
		return (get_texture_pixel(exec->ea,
				raytrace.wallh, i - raytrace.start, raytrace.hit, raytrace));
	}
	else if (raytrace.side == 1 && raytrace.stepy < 0)
	{
		return (get_texture_pixel(exec->no,
				raytrace.wallh, i - raytrace.start, raytrace.hit, raytrace));
	}
	else if (raytrace.side == 1 && raytrace.stepy > 0)
	{
		return (get_texture_pixel(exec->so,
				raytrace.wallh, i - raytrace.start, raytrace.hit, raytrace));
	}
	else
		return (transform_color(exec, 1, i, pixel));
}

void	start_drawing(int start, int end, t_exec *exec, t_ray raytrace, int pixel)
{
	int	i;

	i = 0;
	while (i < start)
	{
		mlx_put_pixel(exec->img, raytrace.pixel, i, transform_color(exec, 1, i, pixel));
		i ++;
	}
	while (i < end)
	{
		mlx_put_pixel(exec->img,
			raytrace.pixel, i, texture_pixel(raytrace, exec, i, pixel));
		i ++;
	}
	while (i < HEIGHT)
	{
		mlx_put_pixel(exec->img, raytrace.pixel, i, transform_color(exec, 0, i, pixel));
		i ++;
	}
}

void	drawmlx(int pixel, double distance, t_exec *exec, t_ray raytrace)
{
	int	start;
	int	end;

	raytrace.pixel = pixel;
	if (distance <= 0.01)
		distance = 0.01;
	if (raytrace.side == 0)
		raytrace.hit = raytrace.y + (distance * raytrace.rady);
	else
		raytrace.hit = raytrace.x + (distance * raytrace.radx);
	distance *= sec_transform(raytrace.dir, exec->player.ang);
	raytrace.wallh = (int)(HEIGHT / distance);
	start = (HEIGHT / 2) - (raytrace.wallh / 2);
	raytrace.start = start;
	end = (HEIGHT / 2) + (raytrace.wallh / 2);
	if (start <= 0)
		start = 0;
	if (end > HEIGHT)
		end = HEIGHT;
	start_drawing(start, end, exec, raytrace, pixel);
}
