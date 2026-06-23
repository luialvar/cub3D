/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_ifs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-ant <juan-ant@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 18:20:41 by juan-ant          #+#    #+#             */
/*   Updated: 2025/08/13 12:41:49 by juan-ant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3Dexec.h"

int	angle_ifs(int side, double angle)
{
	if (side == 0 && angle > 0 && angle <= 90)
		return (1);
	else if (side == 0 && angle > 180 && angle <= 270)
		return (1);
	else if (side == 1 && angle > 90 && angle <= 180)
		return (1);
	else if (side == 1 && angle > 270 && angle <= 360)
		return (1);
	else
		return (0);
}
