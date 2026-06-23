/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   storing_lines_type.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luialvar <luialvar@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 21:11:03 by luialvar          #+#    #+#             */
/*   Updated: 2025/08/09 21:11:46 by luialvar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

	//size_t	len;
//len = ft_strlen(parts[1]);
	/*if (len <= 4 || ft_strncmp(parts[1] + len - 4, ".xpm", 4) != 0)
	{
		free_array(parts);
		return (2);
	}*/
int	sub_texture(char **parts, char *line, t_line_info *line_infos, int *fd_cub)
{
	if (!parts)
	{
		perror("malloc failed");
		close(*fd_cub);
		free(line);
		free(line_infos);
		exit(1);
	}
	if (count_array_elements(parts) != 2)
	{
		free_array(parts);
		return (1);
	}
	return (0);
}

int	error_checker_texture(char *line, t_line_info *line_infos, int *fd_cub)
{
	char	**parts;
	int		fd;
	int		return_sub;

	parts = ft_split(line, ' ');
	return_sub = sub_texture(parts, line, line_infos, fd_cub);
	if (return_sub != 0)
		return (return_sub);
	fd = open(parts[1], O_RDONLY);
	if (fd == -1)
	{
		free_array(parts);
		return (3);
	}
	if (read(fd, NULL, 0) == -1 && errno == EISDIR)
	{
		close(fd);
		free_array(parts);
		return (4);
	}
	close(fd);
	free_array(parts);
	return (0);
}

//
int	sub_color(char **parts, char *line, t_line_info *line_infos, int *fd_cub)
{
	char	**second_parts;

	second_parts = ft_split(parts[1], ',');
	if (!second_parts)
	{
		perror("malloc failed");
		free_array(parts);
		close(*fd_cub);
		free(line);
		free(line_infos);
		exit(1);
	}
	free_array(parts);
	if (count_array_elements(second_parts) != 3)
		return (free_array(second_parts), 2);
	if (ft_atoi_rgb(second_parts[0]) == -1 || ft_atoi_rgb(second_parts[1]) == -1
		|| ft_atoi_rgb(second_parts[2]) == -1)
	{
		free_array(second_parts);
		return (3);
	}
	free_array(second_parts);
	return (0);
}

int	error_checker_color(char *line, t_line_info	*line_infos, int *fd_cub)
{
	char	**parts;

	parts = ft_split(line, ' ');
	if (!parts)
	{
		perror("malloc failed");
		close(*fd_cub);
		free(line);
		free(line_infos);
		exit(1);
	}
	if (count_array_elements(parts) != 2)
	{
		free_array(parts);
		return (1);
	}
	if (count_char(parts[1], ',') != 2)
	{
		free_array(parts);
		return (2);
	}
	return (sub_color(parts, line, line_infos, fd_cub));
}

void	infoln(char *line, t_line_info *info, t_line_info *line_infos, int *fd)
{
	if (line_is_empty(line))
	{
		info->type = 0;
		info->error = 0;
	}
	else if (is_map_line(line))
	{
		info->type = 1;
		info->error = 0;
	}
	else if (is_texture_line(line, info))
		info->error = error_checker_texture(line, line_infos, fd);
	else if (is_color_line(line, info))
		info->error = error_checker_color(line, line_infos, fd);
	else
	{
		info->type = -1;
		info->error = 0;
	}
}
