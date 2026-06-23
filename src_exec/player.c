/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-ant <juan-ant@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 12:59:20 by juan-ant          #+#    #+#             */
/*   Updated: 2025/08/13 12:49:14 by juan-ant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3Dexec.h"

void	init_player(t_exec *exec)
{
	if (exec->cub->player.dir == 'S')
		exec->player.ang = 90;
	else if (exec->cub->player.dir == 'E')
		exec->player.ang = 0;
	else if (exec->cub->player.dir == 'W')
		exec->player.ang = 180;
	else if (exec->cub->player.dir == 'N')
		exec->player.ang = 270;
	exec->player.x = ((double) exec->cub->player.x) - 0.5;
	exec->player.y = ((double) exec->cub->player.y) - 0.5;
}

void	move_up(t_exec *exec)
{
	if (ray_move(exec->player.ang, exec) != 1)
		return ;
	move_final_calc(exec);
}

void	move_down(t_exec *exec)
{
	if (ray_move(exec->player.ang - 180, exec) != 1)
		return ;
	move_final_calc(exec);
}

void	move_left(t_exec *exec)
{
	if (ray_move(exec->player.ang - 90, exec) != 1)
		return ;
	move_final_calc(exec);
}

void	move_right(t_exec *exec)
{
	if (ray_move(exec->player.ang + 90, exec) != 1)
		return ;
	move_final_calc(exec);
}
