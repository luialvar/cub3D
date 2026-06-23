/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auxiliary_four.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-ant <juan-ant@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 11:18:58 by luialvar          #+#    #+#             */
/*   Updated: 2025/08/13 15:33:48 by juan-ant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	print_game_data(t_game_data *game_data)
{
	int	i;

	i = 0;
	printf("=== Textures ===\n");
	printf("NO: %s\n", game_data->textures.no_path);
	printf("SO: %s\n", game_data->textures.so_path);
	printf("WE: %s\n", game_data->textures.we_path);
	printf("EA: %s\n", game_data->textures.ea_path);
	printf("\n=== Colors ===\n");
	printf("Ceiling: R=%d G=%d B=%d\n",
		game_data->ceiling_color.r,
		game_data->ceiling_color.g,
		game_data->ceiling_color.b);
	printf("Floor:   R=%d G=%d B=%d\n",
		game_data->floor_color.r,
		game_data->floor_color.g,
		game_data->floor_color.b);
	printf("\n=== Map (%d x %d) ===\n",
		game_data->map.height, game_data->map.width);
	while (game_data->map.grid[i])
	{
		printf("%s\n", game_data->map.grid[i]);
		i++;
	}
}

char	*get_texture_color(int type)
{
	if (type == 2)
		return ("NO");
	if (type == 3)
		return ("SO");
	if (type == 4)
		return ("EA");
	if (type == 5)
		return ("WE");
	return ("");
}

void	free_all_second(t_game_data *game_data)
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

int	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

void	free_all(char *line, t_game_data *game_data, int *fd)
{
	free (line);
	close(*fd);
	if (game_data->textures.no_path != NULL)
		free (game_data->textures.no_path);
	if (game_data->textures.so_path != NULL)
		free (game_data->textures.so_path);
	if (game_data->textures.ea_path != NULL)
		free (game_data->textures.ea_path);
	if (game_data->textures.we_path != NULL)
		free (game_data->textures.we_path);
	free_array(game_data->map.grid);
	perror("Error\n");
	exit(1);
}
