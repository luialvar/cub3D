#include "../../include/cub3D.h"

int	line_is_empty(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != 9 && line[i])
			return (0);
		i++;
	}
	return (1);
}

int is_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '0' && line[i] != '1' 
			&& line[i] != 'N' && line[i] != 'S'
			&& line[i] != 'E' && line[i] != 'W')
			return (0);
		i++;
	}
	return (1);
}

int is_texture_line(char *line, t_line_info *info)
{
	if (ft_strlen(line) < 3)
		return (0);
	else if (ft_strncmp(line, "NO ", 3) == 0)
	{
		info->type = 2;
		return (1);
	}
	else if (ft_strncmp(line, "SO ", 3) == 0)
	{
		info->type = 3;
		return (1);
	}
	else if (ft_strncmp(line, "EA ", 3) == 0)
	{
		info->type = 4;
		return (1);
	}
	else if (ft_strncmp(line, "WE ", 3) == 0)
	{
		info->type = 5;
		return (1);
	}
	else
		return (0);
}

int is_color_line(char *line, t_line_info *info)
{
	if (ft_strlen(line) < 2)
		return (0);
	else if (ft_strncmp(line, "C ", 2) == 0)
	{
		info->type = 6;
		return (1);
	}
	else if (ft_strncmp(line, "F ", 2) == 0)
	{
		info->type = 7;
		return (1);
	}
	else
		return (0);
}
