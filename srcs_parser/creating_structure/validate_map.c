#include "../../include/cub3D.h"

void	free_all2(t_game_data *game_data)
{
	if (game_data->textures.no_path != NULL)
		free (game_data->textures.no_path);
	if (game_data->textures.so_path != NULL)
		free (game_data->textures.so_path);
	if (game_data->textures.ea_path != NULL)
		free (game_data->textures.ea_path);
	if (game_data->textures.we_path != NULL)
		free (game_data->textures.we_path);
	free_array(game_data->map.grid);
}

int	check_determine_player_position(t_game_data *game_data)
{
	int		i;
	int		j;
	int 	line;
	int 	column;
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
			if (game_data->map.grid[i][j] == 'N' || game_data->map.grid[i][j] == 'S'
				|| game_data->map.grid[i][j] == 'E' || game_data->map.grid[i][j] == 'W')
			{
				if (count == 1)
				{
					printf("There is more than one player, %c in line %i and column %i, ", dir, line + 1, column + 1);
					return_value = 1;
				}
				if (count > 1)
					printf("%c in line %i and column %i, ", dir, line + 1, column + 1);
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
		printf("There is no player in the map\n");
		return_value = 1;
	}
	else
	{
		game_data->map.grid[line][column] = '0'; //ver si el personaje esta solo rodeado por unos que hacer
		game_data->player.x = column + 1;
		game_data->player.y = line + 1;
		game_data->player.dir = dir;
	}
	return (return_value);
}

int	minimum_eigth_ones(t_game_data *game_data)
{
	int	number;
	int	i;
	int j;

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
	int	i;
	int	j;
	char	**grid = game_data->map.grid;

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

int validate_map(t_game_data *game_data)
{
	if (minimum_eigth_ones(game_data) < 8)
	{
		printf("Less than 8 ones\n");
		return (1);
	}
	if (check_determine_player_position(game_data) == 1)
	{
		free_all2(game_data);
		printf("Except for the information in the map, the data in the file is correct\n");
		return (1);
	}
	else
	{
		if (algorithm_validating_map(game_data) == 1)
			printf("There is a 0 touching a space or in a border which is invalid\n");//poner mejores mensajes
		else
			printf("Everything is correct\n");//poner mejores mensajes
		free_all2(game_data);
	}
	return (0);
}