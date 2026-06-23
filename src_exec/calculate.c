/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-ant <juan-ant@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:53:50 by juan-ant          #+#    #+#             */
/*   Updated: 2025/08/13 12:46:46 by juan-ant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3Dexec.h"

double	sec_transform(double valone, double valtwo)
{
	double	toret;

	toret = cos((valone * (M_PI / 180) - (valtwo * (M_PI / 180))));
	if (toret < 0)
		toret *= -1;
	return (toret);
}

void	move_final_calc_aux(t_exec *exec, float tomovex)
{
	if (exec->cub->map.grid[(int)exec->player.y]
		[(int)exec->player.x - 1] == '0' && exec->moveray.stepx < 0)
		exec->player.x = tomovex;
	else if (1 - (((int)(tomovex)) - (tomovex - 1)) > 0.2
		&& exec->moveray.stepx < 0)
		exec->player.x = tomovex;
	if (exec->cub->map.grid[(int)exec->player.y]
		[(int)exec->player.x + 1] == '0' && exec->moveray.stepx > 0)
		exec->player.x = tomovex;
	else if (((int)(tomovex)) - (tomovex - 1) > 0.2
		&& exec->moveray.stepx > 0)
		exec->player.x = tomovex;
}

void	move_final_calc(t_exec *exec)
{
	float	tomovex;
	float	tomovey;

	tomovey = exec->player.y + SPEED * exec->moveray.rady;
	tomovex = exec->player.x + SPEED * exec->moveray.radx;
	if (exec->cub->map.grid[(int)exec->player.y - 1]
		[(int)exec->player.x] == '0' && exec->moveray.stepy < 0)
		exec->player.y = tomovey;
	else if (1 - (((int)(tomovey)) - (tomovey - 1)) > 0.2
		&& exec->moveray.stepy < 0)
		exec->player.y = tomovey;
	if (exec->cub->map.grid[(int)exec->player.y + 1]
		[(int)exec->player.x] == '0' && exec->moveray.stepy > 0)
		exec->player.y = tomovey;
	else if (((int)(tomovey)) - (tomovey - 1) > 0.2
		&& exec->moveray.stepy > 0)
		exec->player.y = tomovey;
	move_final_calc_aux(exec, tomovex);
}
