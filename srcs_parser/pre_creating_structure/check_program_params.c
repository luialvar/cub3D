/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_program_params.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-ant <juan-ant@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 22:21:36 by luialvar          #+#    #+#             */
/*   Updated: 2025/08/13 15:37:05 by juan-ant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	check_cub(char **argv)
{
	char	*checkcub;

	if (ft_strlen(argv[1]) <= 4)
	{
		write(2, "Error\n Invalid format of .cub file\n", 36);
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
			write(2, "Error\n Invalid format of .cub file\n", 36);
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
		write(2, "Error\n Invalid n of arguments passed to the program\n", 53);
		exit (1);
	}
	check_cub(argv);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		perror("Error\n Input");
		exit(1);
	}
	if (read(fd, NULL, 0) == -1 && errno == EISDIR)
	{
		perror("Error\n Input");
		close(fd);
		exit(1);
	}
	return (fd);
}
