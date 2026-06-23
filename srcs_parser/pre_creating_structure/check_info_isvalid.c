/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_info_isvalid.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luialvar <luialvar@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 21:17:07 by luialvar          #+#    #+#             */
/*   Updated: 2025/08/09 21:17:08 by luialvar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static void	check_map_together_two(t_line_info *li, int pos[3],
			int *maps, int *ret)
{
	if (li[pos[0]].type == 1)
	{
		(*maps)++;
		(*ret)++;
		if (*maps > 1)
		{
			printf("Error\n More than a map: Map %i between lines %i and %i\n",
				(*maps) - 1, pos[1] + 1, pos[2] + 1);
			*ret = 1;
		}
		pos[1] = pos[0];
		while (li[pos[0]].type == 1)
		{
			pos[2] = pos[0];
			pos[0]++;
		}
	}
	else
		pos[0]++;
}

/*
	pos[0] = 0; // i
	pos[1] = 0; // start
	pos[2] = 0; // end
*/
int	check_map_together(t_line_info *li)
{
	int	pos[3];
	int	maps;
	int	ret;

	pos[0] = 0;
	pos[1] = 0;
	pos[2] = 0;
	maps = 0;
	ret = -1;
	while (li[pos[0]].type != -2)
		check_map_together_two(li, pos, &maps, &ret);
	if (maps > 1)
		printf("Error\n More than one map: Map %i between lines %i and %i\n",
			maps, pos[1] + 1, pos[2] + 1);
	return (ret);
}

/*
int	check_map_together(t_line_info *line_infos)
{
	int	i;
	int	start_line;
	int	end_line;
	int	map_counter;
	int	return_value;

	i = 0;
	start_line = 0;
	end_line = 0;
	map_counter = 0;
	return_value = -1;
	while (line_infos[i].type != -2)
	{
		if (line_infos[i].type == 1)
		{
			map_counter++;
			return_value++;
			if (map_counter > 1)
			{
				printf("Error: More than one map: Map %i between lines 
				%i and %i\n",
					map_counter - 1, start_line + 1, end_line + 1);
				return_value = 1;
			}
			start_line = i;
			while (line_infos[i].type == 1)
			{
				end_line = i;
				i++;
			}
		}
		else
			i++;
	}
	if (map_counter > 1)
	{
		printf("Error: More than one map: Map %i between lines %i and %i\n",
			map_counter, start_line + 1, end_line + 1);
	}
	return (return_value);
}
*/
/*
Pseudocode to check the info:

First we check that the map is together, if not, print also errors
except from the one that checks if there is info after the map.

If the map is together, check that there is no info after it, 
if there is info print the error, and also all the rest errors

If the map is alone together at the bottom, print all the errors
If there are no errors,
*/

int	check_after_map(t_line_info *line_infos)
{
	int	return_value;
	int	i;

	return_value = 0;
	i = 0;
	while (line_infos[i].type != 1)
		i++;
	while (line_infos[i].type == 1)
		i++;
	while (line_infos[i].type != -2)
	{
		if (line_infos[i].type != 0)
		{
			printf("Error\n Non empty line after the map: Line %i\n", i + 1);
			return_value = 1;
		}
		i++;
	}
	return (return_value);
}

static void	check_error_repetitions_loop(int error, t_line_info *li,
			char *name, int vars[4])
{
	while (li[vars[0]].type != -2)
	{
		if (li[vars[0]].type == error)
		{
			if (vars[1] == 1)
			{
				vars[2] = 1;
				printf("Error\n Same line type (%s) found in line %i, ",
					name, vars[3] + 1);
			}
			if (vars[1] > 1)
				printf("%i, ", vars[3] + 1);
			vars[1]++;
			vars[3] = vars[0];
		}
		vars[0]++;
	}
}

/* vars[0] = i, vars[1] = count, vars[2] = return_value, vars[3] = 
previous_error */
int	check_error_repetitions(int error, t_line_info *li, char *name)
{
	int	vars[4];

	vars[0] = 0;
	vars[1] = 0;
	vars[2] = 0;
	vars[3] = 0;
	check_error_repetitions_loop(error, li, name, vars);
	if (vars[1] == 0)
	{
		printf("Error\n Type (%s) not found in file\n", name);
		vars[2] = 1;
	}
	if (vars[1] > 1)
		printf("%i\n", vars[3] + 1);
	return (vars[2]);
}

/*
int	check_error_repetitions(int error, t_line_info *line_infos, char *name)
{
	int	i;
	int	count;
	int	return_value;
	int	previous_error;

	i = 0;
	count = 0;
	return_value = 0;
	previous_error = 0;
	while (line_infos[i].type != -2)
	{
		if (line_infos[i].type == error)
		{
			if (count == 1)
			{
				return_value = 1;
				printf("Error: Same line type (%s) found in line %i, ",
					name, previous_error + 1);
			}
			if (count > 1)
				printf("%i, ", previous_error + 1);
			count++;
			previous_error = i;
		}
		i++;
	}
	if (count == 0)
	{
		printf("Error: Type (%s) not found in file\n", name);
		return_value = 1;
	}
	if (count > 1)
		printf("%i\n", previous_error + 1);
	return (return_value);
}
*/
