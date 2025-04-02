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