/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luialvar <luialvar@student.42malaga.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 11:48:09 by luialvar          #+#    #+#             */
/*   Updated: 2025/08/07 11:48:28 by luialvar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

/*
int	main(int argc, char **argv)
{
	int				fd_cub;
	char			*line;
	t_line_info		*line_infos;
	int				count_lines;
	size_t			len;
	t_game_data		game_data;


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
		infoln(line, &line_infos[count_lines], line_infos, &fd_cub);
		count_lines++;
		free(line);
	}
	close(fd_cub); //ahora mismo solo hay line_infos alocado
	//print_line_infos_testing(line_infos, count_lines);
	if (check_valid_info(line_infos) == 1)
	{
		free(line_infos);
printf("The map will only be checked in case there are no errors above this\n");
		return (1);
	}
	free(line_infos);
	store_final_structure(argv[1], &game_data);
	print_game_data(&game_data);
	if (validate_map(&game_data) == 1) 
	{
		free_all_second(&game_data);
		return (1);
	}
	main_exec(&game_data);
	free_all_second(&game_data);
	return (0);
}
*/

static int	init_line_infos(int fd, int *lines, t_line_info **line_infos)
{
	*lines = count_lines_and_close(&fd);
	*line_infos = malloc(sizeof(t_line_info) * (*lines + 1));
	if (!*line_infos)
	{
		perror("malloc failed");
		close(fd);
		exit(1);
	}
	(*line_infos)[*lines].type = -2;
	return (fd);
}

static void	read_and_store_lines(int fd, t_line_info *infos)
{
	char	*line;
	size_t	len;
	int		i;

	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		len = ft_strlen(line);
		if (len && line[len - 1] == '\n')
			line[len - 1] = '\0';
		infoln(line, &infos[i], infos, &fd);
		i++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

static void	final_stage(t_line_info *infos, char **argv)
{
	t_game_data	game_data;

	if (check_valid_info(infos) == 1)
	{
		free(infos);
		printf("The map will only be checked if there are no errors above\n");
		exit(1);
	}
	free(infos);
	store_final_structure(argv[1], &game_data);
	if (validate_map(&game_data) == 1)
	{
		free_all_second(&game_data);
		exit(1);
	}
	main_exec(&game_data);
	free_all_second(&game_data);
}

int	main(int argc, char **argv)
{
	int			fd;
	int			lines;
	t_line_info	*line_infos;

	fd = check_valid_params(argc, argv);
	fd = init_line_infos(fd, &lines, &line_infos);
	read_and_store_lines(open(argv[1], O_RDONLY), line_infos);
	final_stage(line_infos, argv);
	return (0);
}
