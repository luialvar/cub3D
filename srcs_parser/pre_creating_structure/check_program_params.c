#include "../../include/cub3D.h"

void	check_cub(char **argv)
{
	char	*checkcub;

	if (ft_strlen(argv[1]) <= 4)
	{
		write(2, "Invalid format of .cub file\n", 28);
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
			write(2, "Invalid format of .cub file\n", 28);
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
		write(2, "Invalid number of arguments passed to the program\n", 50);
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