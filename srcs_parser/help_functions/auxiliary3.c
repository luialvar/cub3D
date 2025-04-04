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
	int		count = 0;
	char	*line;

	while ((line = get_next_line(*fd)))
	{
		count++;
		free(line);
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
    int i = 0;

    // Copiamos mientras haya caracteres de src y no superemos 'width'
    while (src[i] != '\0' && i < width)
    {
        dest[i] = src[i];
        i++;
    }
    // Rellenamos con ' ' el resto
    while (i < width)
    {
        dest[i] = ' ';
        i++;
    }
    // No ponemos '\0' si no lo necesitas para nada más
    // (Si quieres '\0', harías 'dest[width] = '\0';' siempre y ya está.)
}

void	print_game_data(t_game_data *game_data)
{
	int i = 0;

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

	printf("\n=== Map (%d x %d) ===\n", game_data->map.height, game_data->map.width);
	while (game_data->map.grid[i])
	{
		printf("%s\n", game_data->map.grid[i]);
		i++;
	}
}