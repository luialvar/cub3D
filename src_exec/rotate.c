/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-ant <juan-ant@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 11:17:04 by juan-ant          #+#    #+#             */
/*   Updated: 2025/08/13 12:49:53 by juan-ant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3Dexec.h"

void	rotate_r(t_exec *exec)
{
	exec->player.ang += 1;
	if (exec->player.ang > 360)
		exec->player.ang = 1;
}

void	rotate_l(t_exec *exec)
{
	exec->player.ang -= 1;
	if (exec->player.ang < 0)
		exec->player.ang = 359;
}
