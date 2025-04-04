#include "../../include/cub3D.h"

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
	perror("Error");
	exit(1);
}

void	store_struct_line(char *line, t_game_data *game_data, int *fd, int max_width_map)
{
	char **parts;
	char **second_parts;
	static int map_line_count = 0;

	if (line_is_empty(line))
		return;
	else if (ft_strncmp(line, "NO ", 3) == 0)
	{
		parts = ft_split(line, ' ');
		if (!parts)
			free_all(line, game_data, fd);
		game_data->textures.no_path = ft_strdup(parts[1]);
		if (!game_data->textures.no_path)
		{
			free_array(parts);
			free_all(line, game_data, fd);
		}
		free_array(parts);
	}
	else if (ft_strncmp(line, "SO ", 3) == 0)
	{
		parts = ft_split(line, ' ');
		if (!parts)
			free_all(line, game_data, fd);
		game_data->textures.so_path = ft_strdup(parts[1]);
		if (!game_data->textures.so_path)
		{
			free_array(parts);
			free_all(line, game_data, fd);
		}
		free_array(parts);
	}
	else if (ft_strncmp(line, "EA ", 3) == 0)
	{
		parts = ft_split(line, ' ');
		if (!parts)
			free_all(line, game_data, fd);
		game_data->textures.ea_path = ft_strdup(parts[1]);
		if (!game_data->textures.ea_path)
		{
			free_array(parts);
			free_all(line, game_data, fd);
		}
		free_array(parts);
	}
	else if (ft_strncmp(line, "WE ", 3) == 0)
	{
		parts = ft_split(line, ' ');
		if (!parts)
			free_all(line, game_data, fd);
		game_data->textures.we_path = ft_strdup(parts[1]);
		if (!game_data->textures.we_path)
		{
			free_array(parts);
			free_all(line, game_data, fd);
		}
		free_array(parts);
	}
	else if (ft_strncmp(line, "C ", 2) == 0)
	{
		parts = ft_split(line, ' ');
		if (!parts)
			free_all(line, game_data, fd);
		second_parts = ft_split(parts[1], ',');
		if (!second_parts)
		{
			free_array(parts);
			free_all(line, game_data, fd);
		}
		game_data->ceiling_color.r = ft_atoi_rgb(second_parts[0]);
		game_data->ceiling_color.g = ft_atoi_rgb(second_parts[1]);
		game_data->ceiling_color.b = ft_atoi_rgb(second_parts[2]);
		free_array(parts);
		free_array(second_parts);
	}
	else if (ft_strncmp(line, "F ", 2) == 0)
	{
		parts = ft_split(line, ' ');
		if (!parts)
			free_all(line, game_data, fd);
		second_parts = ft_split(parts[1], ',');
		if (!second_parts)
		{
			free_array(parts);
			free_all(line, game_data, fd);
		}
		game_data->floor_color.r = ft_atoi_rgb(second_parts[0]);
		game_data->floor_color.g = ft_atoi_rgb(second_parts[1]);
		game_data->floor_color.b = ft_atoi_rgb(second_parts[2]);
		free_array(parts);
		free_array(second_parts);
	}
	else if (is_map_line(line))
	{
		copy_line_with_padding(game_data->map.grid[map_line_count], line, max_width_map);
		map_line_count++;
	}
}

void	start_data(t_game_data *game_data, int lines_map, int max_width_map)
{
	int i;

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
	i = 0;
	while (i < lines_map)
	{
		game_data->map.grid[i] = malloc(sizeof(char) * (max_width_map + 1));
		if (!game_data->map.grid[i])
		{
			while (--i >= 0)
				free(game_data->map.grid[i]);
			free(game_data->map.grid);
			perror("(malloc) failed");
			exit(1);
		}
		game_data->map.grid[i][max_width_map] = '\0'; // opcional: inicializar como string vacío
		i++;
	}
}

int	count_lines_map_update_width(char *file, int *max_width_map)
{
	int	fd_cub;
	int	count;
	int	line_size;
	int	len;
	char *line;

	count = 0;
	fd_cub = open(file, O_RDONLY);
	if (fd_cub == -1)
	{
		perror("Error: Input");
		exit(1);
	}
	while ((line = get_next_line(fd_cub)))
	{
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
		if (!line_is_empty(line) && is_map_line(line))
		{
			line_size = count_all_char(line);
			if (line_size > *max_width_map)
				*max_width_map = line_size;
			count++;
		}
		free(line);
	}
	close(fd_cub);
	return (count);
}

void	store_final_structure(char *file, t_game_data *game_data)
{
	int fd_cub;
	char *line;
	int	lines_map;
	int	max_width_map;
	int	len;

	max_width_map = 0;
	lines_map = count_lines_map_update_width(file, &max_width_map);
	if (lines_map < 3)
	{
		printf("The number of map lines must be greater than 2\n");
		exit(1);
	}
	game_data->map.height = lines_map;
	game_data->map.width = max_width_map;
	start_data(game_data, lines_map, max_width_map);
	fd_cub = open(file, O_RDONLY);
	if (fd_cub == -1)
	{
		perror("Error: Input");
		exit(1);
	}
	while ((line = get_next_line(fd_cub)))
	{
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
		store_struct_line(line, game_data, &fd_cub, max_width_map);
		free(line);
	}
	close(fd_cub);
}
