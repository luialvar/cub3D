#include "../include/cub3D.h"

void	check_cub(char **argv)
{
	char	*checkcub;

	if (ft_strlen(argv[1]) <= 4)
	{
		write(2, "Invalid format of .cub file\n", 29);
		exit(1);
	}
	else
	{
		checkcub = ft_substr(argv[1], ft_strlen(argv[1]) - 4, 4);
		if (!checkcub)
		{
			perror("ft_substr (malloc) failed");
			exit(1);
		}
		if (ft_strncmp(checkcub, ".cub", 4) != 0)
		{
			free(checkcub);
			write(2, "Invalid format of .cub file\n", 29);
			exit(1);
		}
		free(checkcub);
	}
}

int	check_valid_params(int argc, char **argv)
{
	int		fd;

	if (argc != 2)
	{
		write(2, "Invalid number of arguments passed to the program\n", 51);
		exit (1);
	}	
	check_cub(argv);
 	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		perror("Error: Input");
		exit(1);
	}
	if (read(fd, NULL, 0) == -1 && errno == EISDIR)
	{
		perror("Error: Input");
		close(fd);
		exit(1);
	}
	return (fd);
}

int	main(int argc, char **argv)
{
	int		fd_cub;
	char	*line;
	t_valid_data validate_data;

	fd_cub = check_valid_params(argc, argv);
	while (1)
	{
		line = get_next_line(fd_cub); //hay que cambiar el get_next_line para que solo de null cuando se acaba de leer y que en otro caso se haga exit
		if (!line)
			break ;
		check_valid_lines(line, )
	}
}