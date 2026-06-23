/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auxiliary3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luialvar <luialvar@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 22:24:25 by luialvar          #+#    #+#             */
/*   Updated: 2025/08/09 22:24:28 by luialvar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

int	ft_atoi_rgb(const char *str)
{
	int	i;
	int	num;

	i = 0;
	num = 0;
	if (!str || str[0] == '\0')
		return (-1);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		num = num * 10 + (str[i] - '0');
		if (num > 255)
			return (-1);
		i++;
	}
	return (num);
}

void	print_line_infos_testing(t_line_info *line_infos, int total_lines)
{
	int	i;

	i = 0;
	while (i < total_lines)
	{
		printf("Línea %d → Tipo: %d, Error: %d\n",
			i + 1,
			line_infos[i].type,
			line_infos[i].error);
		i++;
	}
}

int	count_lines_and_close(int *fd)
{
	int		count;
	char	*line;

	count = 0;
	line = get_next_line(*fd);
	while (line)
	{
		count++;
		free(line);
		line = get_next_line(*fd);
	}
	close(*fd);
	return (count);
}

int	count_all_char(char *line)
{
	int	i;

	i = 0;
	while (line[i])
		i++;
	return (i);
}

void	copy_line_with_padding(char *dest, const char *src, int width)
{
	int	i;

	i = 0;
	while (src[i] != '\0' && i < width)
	{
		dest[i] = src[i];
		i++;
	}
	while (i < width)
	{
		dest[i] = ' ';
		i++;
	}
}
