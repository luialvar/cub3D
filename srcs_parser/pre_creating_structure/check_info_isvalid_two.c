/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_info_isvalid_two.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luialvar <luialvar@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 12:56:37 by luialvar          #+#    #+#             */
/*   Updated: 2025/08/10 12:56:39 by luialvar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

/*
	if (line_infos.error == 2)
	{
		printf("Error: Line %i of type (%s) has bad format xpm\n", i + 1, color);
		return (1);
	}
*/
int	check_texture(t_line_info line_infos, int i)
{
	char	*color;

	color = get_texture_color(line_infos.type);
	if (line_infos.error == 1)
	{
		printf("Error\n Line %i of type (%s) has invalid number of arguments\n",
			i + 1, color);
		return (1);
	}
	if (line_infos.error == 3)
	{
		printf("Error\n Line %i of type (%s) has a problem opening the file, "
			"ex. no rights or doesnt exist\n", i + 1, color);
		return (1);
	}
	if (line_infos.error == 4)
	{
		printf("Error\n Line %i of type (%s) is a directory\n",
			i + 1, color);
		return (1);
	}
	return (0);
}

int	check_color(t_line_info line_infos, int i)
{
	char	*type;

	if (line_infos.type == 6)
		type = "C";
	if (line_infos.type == 7)
		type = "F";
	if (line_infos.error == 1)
	{
		printf("Error\n Line %i of type (%s) has invalid number of arguments\n",
			i + 1, type);
		return (1);
	}
	if (line_infos.error == 2)
	{
		printf("Error\n Line %i of type (%s) has bad  ", i + 1, type);
		printf("format number of commas or elements inside commas\n");
		return (1);
	}
	if (line_infos.error == 3)
	{
		printf("Error\n Line %i of type (%s) has bad format ", i + 1, type);
		printf("in its inside arguments xxx,xxx,xxx\n");
		return (1);
	}
	return (0);
}

int	check_specific_errors(t_line_info *line_infos)
{
	int	return_value;
	int	i;

	return_value = 0;
	i = 0;
	while (line_infos[i].type != -2)
	{
		if (line_infos[i].type == 2)
			return_value = check_texture(line_infos[i], i) || return_value;
		if (line_infos[i].type == 3)
			return_value = check_texture(line_infos[i], i) || return_value;
		if (line_infos[i].type == 4)
			return_value = check_texture(line_infos[i], i) || return_value;
		if (line_infos[i].type == 5)
			return_value = check_texture(line_infos[i], i) || return_value;
		if (line_infos[i].type == 6)
			return_value = check_color(line_infos[i], i) || return_value;
		if (line_infos[i].type == 7)
			return_value = check_color(line_infos[i], i) || return_value;
		i++;
	}
	return (return_value);
}

int	print_errors(t_line_info *line_infos)
{
	int	i;
	int	return_value;

	i = 0;
	return_value = 0;
	while (line_infos[i].type != -2)
	{
		if (line_infos[i].type == -1)
		{
			printf("Error\n Line of undefined type %i\n", i + 1);
			return_value = 1;
		}
		i++;
	}
	return_value = check_error_repetitions(2, line_infos, "NO") || return_value;
	return_value = check_error_repetitions(3, line_infos, "SO") || return_value;
	return_value = check_error_repetitions(4, line_infos, "EA") || return_value;
	return_value = check_error_repetitions(5, line_infos, "WE") || return_value;
	return_value = check_error_repetitions(6, line_infos, "C") || return_value;
	return_value = check_error_repetitions(7, line_infos, "F") || return_value;
	if (check_specific_errors(line_infos) == 1)
		return (1);
	return (return_value);
}

int	check_valid_info(t_line_info *line_infos)
{
	int	return_map;

	return_map = check_map_together(line_infos);
	if (return_map == -1)
	{
		printf("Error\n No map detected in file\n");
		print_errors(line_infos);
		return (1);
	}
	if (return_map == 1)
	{
		print_errors(line_infos);
		return (1);
	}
	if (return_map == 0)
		return_map = check_after_map(line_infos);
	if (return_map == 1)
	{
		print_errors(line_infos);
		return (1);
	}
	if (return_map == 0)
		return (print_errors(line_infos));
	return (0);
}
