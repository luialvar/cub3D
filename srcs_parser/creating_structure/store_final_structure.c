/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_final_structure.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luialvar <luialvar@student.42malaga.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 12:01:38 by luialvar          #+#    #+#             */
/*   Updated: 2025/08/07 12:01:46 by luialvar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static void	handle_tex(char *line, t_game_data *g, int *fd, char **dst)
{
	char	**parts;

	parts = ft_split(line, ' ');
	if (!parts)
		free_all(line, g, fd);
	*dst = ft_strdup(parts[1]);
	if (!*dst)
	{
		free_array(parts);
		free_all(line, g, fd);
	}
	free_array(parts);
}

static void	handle_color(char *line, t_game_data *g, int *fd, t_color *dst)
{
	char	**parts;
	char	**rgb;

	parts = ft_split(line, ' ');
	if (!parts)
		free_all(line, g, fd);
	rgb = ft_split(parts[1], ',');
	if (!rgb)
	{
		free_array(parts);
		free_all(line, g, fd);
	}
	dst->r = ft_atoi_rgb(rgb[0]);
	dst->g = ft_atoi_rgb(rgb[1]);
	dst->b = ft_atoi_rgb(rgb[2]);
	free_array(parts);
	free_array(rgb);
}

void	str_line(char *line, t_game_data *game_data, int *fd, int max_width_map)
{
	static int	map_line_count = 0;

	if (line_is_empty(line))
		return ;
	else if (ft_strncmp(line, "NO ", 3) == 0)
		handle_tex(line, game_data, fd, &game_data->textures.no_path);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		handle_tex(line, game_data, fd, &game_data->textures.so_path);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		handle_tex(line, game_data, fd, &game_data->textures.ea_path);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		handle_tex(line, game_data, fd, &game_data->textures.we_path);
	else if (ft_strncmp(line, "C ", 2) == 0)
		handle_color(line, game_data, fd, &game_data->ceiling_color);
	else if (ft_strncmp(line, "F ", 2) == 0)
		handle_color(line, game_data, fd, &game_data->floor_color);
	else if (is_map_line(line))
	{
		copy_line_with_padding(game_data->map.grid[map_line_count],
			line, max_width_map);
		map_line_count++;
	}
}

static void	alloc_grid_rows(t_game_data *g, int lines, int width)
{
	int	i;

	i = 0;
	while (i < lines)
	{
		g->map.grid[i] = malloc(sizeof(char) * (width + 1));
		if (!g->map.grid[i])
		{
			while (--i >= 0)
				free(g->map.grid[i]);
			free(g->map.grid);
			perror("(malloc) failed");
			exit(1);
		}
		g->map.grid[i][width] = '\0';
		i++;
	}
}

void	start_data(t_game_data *game_data, int lines_map, int max_width_map)
{
	game_data->textures.no_path = NULL;
	game_data->textures.so_path = NULL;
	game_data->textures.we_path = NULL;
	game_data->textures.ea_path = NULL;
	game_data->map.grid = malloc(sizeof(char *) * (lines_map + 1));
	if (!game_data->map.grid)
	{
		perror("(malloc) failed");
		exit(1);
	}
	game_data->map.grid[lines_map] = NULL;
	alloc_grid_rows(game_data, lines_map, max_width_map);
}
