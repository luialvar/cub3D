/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luialvar <luialvar@student.42malaga.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 12:02:17 by luialvar          #+#    #+#             */
/*   Updated: 2025/08/07 12:02:19 by luialvar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

/*

int	check_determine_player_position(t_game_data *game_data)
{
	int		i;
	int		j;
	int		line;
	int		column;
	char	dir;
	int		count;
	int		return_value;

	i = 0;
	j = 0;
	count = 0;
	return_value = 0;
	while (game_data->map.grid[i] != NULL)
	{
		while (game_data->map.grid[i][j] != '\0')
		{
			if (game_data->map.grid[i][j] == 'N' || 
			game_data->map.grid[i][j] == 'S'
				|| game_data->map.grid[i][j] == 'E' ||
				 game_data->map.grid[i][j] == 'W')
			{
				if (count == 1)
				{
					printf("Error\n There is more than one player,
					 %c in line %i and column %i, ", dir, line + 1, column + 1);
					return_value = 1;
				}
				if (count > 1)
					printf("%c in line %i and column %i, ",
						dir, line + 1, column + 1);
				line = i;
				column = j;
				dir = game_data->map.grid[i][j];
				count++;
			}
			j++;
		}
		i++;
		j = 0;
	}
	if (count > 1)
		printf("%c in line %i and column %i\n", dir, line + 1, column + 1);
	else if (count == 0)
	{
		printf("Error\n There is no player in the map\n");
		return_value = 1;
	}
	else
	{
		game_data->map.grid[line][column] = '0';
		game_data->player.x = column + 1;
		game_data->player.y = line + 1;
		game_data->player.dir = dir;
	}
	return (return_value);
}
*/

/* 0:i, 1:j, 2:line, 3:column, 4:ret */
static void	internal_loop(t_game_data *g,
					int var[5], char *dir, int *count)
{
	while (g->map.grid[var[0]] != NULL)
	{
		while (g->map.grid[var[0]][var[1]] != '\0')
		{
			if (is_player(g->map.grid[var[0]][var[1]]))
			{
				if (*count == 1)
				{
					printf("Error\n More than 1 player, %c line %i column %i, ",
						*dir, var[2] + 1, var[3] + 1);
					var[4] = 1;
				}
				if (*count > 1)
					printf("%c line %i column %i, ",
						*dir, var[2] + 1, var[3] + 1);
				var[2] = var[0];
				var[3] = var[1];
				*dir = g->map.grid[var[0]][var[1]];
				(*count)++;
			}
			var[1]++;
		}
		var[0]++;
		var[1] = 0;
	}
}

int	check_determine_player_position(t_game_data *g)
{
	int		var[5];
	char	dir;
	int		count;

	var[0] = 0;
	var[1] = 0;
	count = 0;
	var[4] = 0;
	internal_loop(g, var, &dir, &count);
	if (count > 1)
		printf("%c line %i column %i\n", dir, var[2] + 1, var[3] + 1);
	else if (count == 0)
	{
		printf("Error\n There is no player in the map\n");
		var[4] = 1;
	}
	else
	{
		g->map.grid[var[2]][var[3]] = '0';
		g->player.x = var[3] + 1;
		g->player.y = var[2] + 1;
		g->player.dir = dir;
	}
	return (var[4]);
}

int	minimum_eigth_ones(t_game_data *game_data)
{
	int	number;
	int	i;
	int	j;

	number = 0;
	i = 0;
	while (game_data->map.grid[i] != NULL)
	{
		j = 0;
		while (game_data->map.grid[i][j] != '\0')
		{
			if (game_data->map.grid[i][j] == '1')
				number++;
			j++;
		}
		i++;
	}
	return (number);
}

int	algorithm_validating_map(t_game_data *game_data)
{
	int		i;
	int		j;
	char	**grid;

	grid = game_data->map.grid;
	i = 0;
	while (i < game_data->map.height)
	{
		j = 0;
		while (j < game_data->map.width)
		{
			if (grid[i][j] == '0')
			{
				if (i == 0 || i == game_data->map.height - 1
					|| j == 0 || j == game_data->map.width - 1)
					return (1);
				if (grid[i - 1][j] == ' ' || grid[i + 1][j] == ' '
					|| grid[i][j - 1] == ' ' || grid[i][j + 1] == ' ')
					return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	validate_map(t_game_data *game_data)
{
	if (minimum_eigth_ones(game_data) < 8)
	{
		printf("Error\n Less than 8 ones\n");
		return (1);
	}
	if (check_determine_player_position(game_data) == 1)
	{
		printf("Except for the information in the map, ");
		printf("the data in the file is correct\n");
		return (1);
	}
	else
	{
		if (algorithm_validating_map(game_data) == 1)
		{
			printf("Error\n There is a 0 touching a space or ");
			printf("in a border which is invalid\n");
			return (1);
		}
		else
			printf("Everything is correct\n");
	}
	return (0);
}
