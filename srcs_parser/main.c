#include "../include/cub3D.h"

int	main(int argc, char **argv) //hacer que el gnl exitee, y ver que pasa con archivos vacios
{
	int				fd_cub;
	char			*line;
	t_line_info		*line_infos;
	int				count_lines;
	size_t			len;

	fd_cub = check_valid_params(argc, argv);
	count_lines = count_lines_and_close(&fd_cub);
	line_infos = malloc(sizeof(t_line_info) * (count_lines + 1));
	if (!line_infos)
	{
		perror("malloc failed");
		close(fd_cub);
		exit(1);
	}
	line_infos[count_lines].type = -2;
	count_lines = 0;
	fd_cub = open(argv[1], O_RDONLY);
	if (fd_cub == -1)
	{
		free(line_infos);
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
	close(fd_cub); //ahora mismo solo hay line_infos alocado
	//print_line_infos_testing(line_infos, count_lines);
	check_valid_info(line_infos);
	free(line_infos);
}