#include "../include/cub3D.h"

void	print_line_infos(t_line_info *line_infos, int total_lines)
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

int	main(int argc, char **argv) //hacer que el gnl exitee, y ver que pasa con archivos vacios
{
	int				fd_cub;
	char			*line;
	t_line_info		*line_infos;
	int				count_lines;
	size_t	len;

	fd_cub = check_valid_params(argc, argv);
	count_lines = count_lines_and_close(&fd_cub);
	line_infos = malloc(sizeof(t_line_info) * count_lines);
	if (!line_infos)
	{
		perror("malloc failed");
		close(fd_cub);
		exit(1);
	}
	count_lines = 0;
	fd_cub = open(argv[1], O_RDONLY);
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
		store_info_line(line, &line_infos[count_lines], line_infos, &fd_cub);
		count_lines++;
		free(line);
	}
	close(fd_cub);
	print_line_infos(line_infos, count_lines);
	free(line_infos);
}