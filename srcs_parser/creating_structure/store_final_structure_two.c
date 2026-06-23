/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_final_structure_two.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-ant <juan-ant@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 20:04:20 by luialvar          #+#    #+#             */
/*   Updated: 2025/08/13 13:26:32 by juan-ant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static void	accumulate_line_metrics(char *line, int *count, int *max_width_map)
{
	int	len;
	int	line_size;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	if (!line_is_empty(line) && is_map_line(line))
	{
		line_size = count_all_char(line);
		if (line_size > *max_width_map)
			*max_width_map = line_size;
		(*count)++;
	}
}

int	count_lines_map_update_width(const char *file, int *max_width_map)
{
	int		fd_cub;
	int		count;
	char	*line;

	count = 0;
	fd_cub = open(file, O_RDONLY);
	if (fd_cub == -1)
	{
		perror("Error\n Input");
		exit(1);
	}
	line = get_next_line(fd_cub);
	while (line)
	{
		accumulate_line_metrics(line, &count, max_width_map);
		free(line);
		line = get_next_line(fd_cub);
	}
	close(fd_cub);
	return (count);
}

static int	prepare_map(t_game_data *g, const char *file, int *max_w)
{
	int	lines;

	*max_w = 0;
	lines = count_lines_map_update_width(file, max_w);
	if (lines < 3)
	{
		printf("Error\n The number of map lines must be greater than 2\n");
		exit(1);
	}
	g->map.height = lines;
	g->map.width = *max_w;
	start_data(g, lines, *max_w);
	return (lines);
}

void	store_final_structure(char *file, t_game_data *game_data)
{
	int		fd_cub;
	char	*line;
	int		max_width_map;
	int		len;

	prepare_map(game_data, file, &max_width_map);
	fd_cub = open(file, O_RDONLY);
	if (fd_cub == -1)
	{
		perror("Error: Input");
		exit(1);
	}
	line = get_next_line(fd_cub);
	while (line)
	{
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
		str_line(line, game_data, &fd_cub, max_width_map);
		free(line);
		line = get_next_line(fd_cub);
	}
	close(fd_cub);
}
