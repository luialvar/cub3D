#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h> 
# include <errno.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif


typedef struct s_color {
	int r;
	int g;
	int b;
	} t_color;
	
typedef struct s_textures {
	char *no_path;
	char *so_path; 
	char *ea_path;
	char *we_path;
	} t_textures;
	
typedef struct s_player {
	int x;
	int y;
	char dir;       // 'N', 'S', 'E' o 'W'
	} t_player;
	
typedef struct s_map {
	char **grid;    // matriz del mapa, con '1', '0', ' ', 'N', importante tener en cuenta que se pasan ' '
	int height;     // número de líneas
	int width;
	} t_map;
	
typedef struct s_game_data {
	t_textures textures;
	t_color floor_color;
	t_color ceiling_color;
	t_map map;
	t_player player;
	} t_game_data;

typedef struct s_line_info {
	int	type;
	int	error;
	} t_line_info;

	char	*get_next_line(int fd);
	char	*ft_strdup(const char *s1);
	char	*ft_strjoin(char const *s1, char const *s2);
	size_t	ft_strlen(const char *s);
	char	*ft_strchr(const char *s, int c);
	char	*ft_substr(char const *s, unsigned int start, size_t len);
	void	*ft_memcpy(void *dest, const void *src, size_t n);
	int		ft_strncmp(const char *s1, const char *s2, size_t n);
	void	store_info_line(char *line, t_line_info *info, t_line_info	*line_infos, int *fd);
	int		line_is_empty(char *line);
	int 	is_texture_line(char *line, t_line_info *info);
	int 	is_color_line(char *line, t_line_info *info);
	int 	is_map_line(char *line);
	void	check_cub(char **argv);
	int		check_valid_params(int argc, char **argv);
	char	**ft_split(char const *s, char c);
	int		count_array_elements(char **array);
	void	free_array(char **directories);
	int		count_char(char *str, char c);
	int		ft_atoi_rgb(const char *str);
	void	print_line_infos_testing(t_line_info *line_infos, int total_lines);
	int		count_lines_and_close(int *fd);
	int 	check_map_together(t_line_info *line_infos);
	int		check_valid_info(t_line_info *line_infos);
	int		print_errors(t_line_info *line_infos);
	int		check_specific_errors(t_line_info *line_infos);
	int 	check_color(t_line_info line_infos, int i);
	int 	check_texture(t_line_info line_infos, int i);
	int		check_errors_repetitions(int error, t_line_info *line_infos, char *name);
	int		check_after_map(t_line_info *line_infos);
	int 	check_map_together(t_line_info *line_infos);
	int		count_all_char(char *line);
	void	print_game_data(t_game_data *game_data);
	void	store_final_structure(char *file, t_game_data *game_data);
	void	copy_line_with_padding(char *dest, const char *src, int width);
	int 	validate_map(t_game_data *game_data);
	

#endif