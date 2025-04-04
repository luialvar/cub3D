#include "../../include/cub3D.h"

int check_map_together(t_line_info *line_infos)
{
	int i;
	int start_line;
	int end_line;
	int map_counter;
	int return_value;

	i = 0;
	start_line = 0;
	end_line = 0;
	map_counter = 0;
	return_value = -1;
	while (line_infos[i].type != -2)
	{
		if (line_infos[i].type == 1)
		{
			map_counter++;
			return_value++;
			if (map_counter > 1)
			{
				printf("Error: More than one map: Map %i between lines %i and %i\n",
					   map_counter - 1, start_line + 1, end_line + 1);
				return_value = 1;
			}
			start_line = i;
			while (line_infos[i].type == 1)
			{
				end_line = i;
				i++;
			}
		}
		else
			i++;
	}
	if (map_counter > 1)
	{
		printf("Error: More than one map: Map %i between lines %i and %i\n",
		   map_counter, start_line + 1, end_line + 1);
	}
	return (return_value);
}


/*
Pseudocode to check the info:

First we check that the map is together, if not, print also errors
except from the one that checks if there is info after the map.

If the map is together, check that there is no info after it, 
if there is info print the error, and also all the rest errors

If the map is alone together at the bottom, print all the errors
If there are no errors,
*/

int check_after_map(t_line_info *line_infos)
{
	int return_value;
	int	i;

	return_value = 0;
	i = 0;
	while (line_infos[i].type != 1)
		i++;
	while (line_infos[i].type == 1)
		i++;
	while (line_infos[i].type != -2)
	{
		if (line_infos[i].type != 0)
		{
			printf("Error: Non empty line after the map: Line %i\n", i + 1);
			return_value = 1;
		}
		i++;
	}
	return (return_value);
}

int check_errors_repetitions(int error, t_line_info *line_infos, char *name)
{
	int	i;
	int	count;
	int	return_value = 0;
	int	previous_error;

	i = 0;
	count = 0;
	previous_error = 0;
	while (line_infos[i].type != -2)
	{
		if (line_infos[i].type == error)
		{
			if (count == 1)
			{
				return_value = 1;
				printf("Error: Same line type (%s) found in line %i, ", name, previous_error + 1);
			}
			if (count > 1)
				printf("%i, ", previous_error + 1);
			count++;
			previous_error = i;
		}
		i++;
	}
	if (count == 0)
	{
		printf("Error: Type (%s) not found in file\n", name);
		return_value = 1;
	}
	if (count > 1)
		printf("%i\n", previous_error + 1);
	return (return_value);
}


int check_texture(t_line_info line_infos, int i)
{
	char *color;

	if (line_infos.type == 2)
		color = "NO";
	if (line_infos.type == 3)
		color = "NO";
	if (line_infos.type == 4)
		color = "EA";
	if (line_infos.type == 5)
		color = "WE";
	if (line_infos.error == 1)
	{
		printf("Error: Line %i of type (%s) has an invalid number of arguments\n", i + 1, color);
		return (1);
	}
	if (line_infos.error == 2)
	{
		printf("Error: Line %i of type (%s) has bad format xpm\n", i + 1, color);
		return (1);
	}
	if (line_infos.error == 3)
	{
		printf("Error: Line %i of type (%s) has a problem opening the file, ex. no rights or doesnt exist\n", i + 1, color);
		return (1);
	}
	if (line_infos.error == 4)
	{
		printf("Error: Line %i of type (%s) is a directory\n", i + 1, color);
		return (1);
	}
	return (0);
}

int check_color(t_line_info line_infos, int i)
{
	char *type;

	if (line_infos.type == 6)
		type = "C";
	if (line_infos.type == 7)
		type = "F";
	if (line_infos.error == 1)
	{
		printf("Error: Line %i of type (%s) has an invalid number of arguments\n", i + 1, type);
		return (1);
	}
	if (line_infos.error == 2)
	{
		printf("Error: Line %i of type (%s) has bad format number of commas or elements inside commas\n", i + 1, type);
		return (1);
	}
	if (line_infos.error == 3)
	{
		printf("Error: Line %i of type (%s) has bad format in its inside arguments xxx,xxx,xxx\n", i + 1, type);
		return (1);
	}
	return (0);
}

int	check_specific_errors(t_line_info *line_infos)
{
	int	return_value;
	int	i;

	return_value = 0;
	i = 0;
	while (line_infos[i].type != -2)
	{
		if (line_infos[i].type == 2)
			return_value = check_texture(line_infos[i], i) || return_value;
		if (line_infos[i].type == 3)
			return_value = check_texture(line_infos[i], i) || return_value;
		if (line_infos[i].type == 4)
			return_value = check_texture(line_infos[i], i) || return_value;
		if (line_infos[i].type == 5)
			return_value = check_texture(line_infos[i], i) || return_value;
		if (line_infos[i].type == 6)
			return_value = check_color(line_infos[i], i) || return_value;
		if (line_infos[i].type == 7)
			return_value = check_color(line_infos[i], i) || return_value;
		i++;
	}
	return (return_value);
}

int	print_errors(t_line_info *line_infos)
{
	int	i;
	int	return_value;

	i = 0;
	return_value = 0;
	while (line_infos[i].type != -2)
	{
		if (line_infos[i].type == -1)
		{
			printf("Error: Line of undefined type %i\n", i + 1);
			return_value = 1;
		}
		i++;
	}
	return_value = check_errors_repetitions(2, line_infos, "NO") || return_value;
	return_value = check_errors_repetitions(3, line_infos, "SO") || return_value;
	return_value = check_errors_repetitions(4, line_infos, "EA") || return_value;
	return_value = check_errors_repetitions(5, line_infos, "WE") || return_value;
	return_value = check_errors_repetitions(6, line_infos, "C")  || return_value;
	return_value = check_errors_repetitions(7, line_infos, "F")  || return_value;
	if (check_specific_errors(line_infos) == 1)
		return (1);
	return (return_value);
}

int	check_valid_info(t_line_info *line_infos)
{
	int	return_map;

	return_map = check_map_together(line_infos);
	if (return_map == -1)
	{
		printf("Error: No map detected in file\n");
		print_errors(line_infos);
		return (1);
	}
	if (return_map ==  1)
	{
		print_errors(line_infos);
		return (1);
	}
	if (return_map == 0)
		return_map = check_after_map(line_infos);
	if (return_map ==  1)
	{
		print_errors(line_infos);
		return (1);
	}
	if (return_map == 0)
		return (print_errors(line_infos));
	return (0);
}
