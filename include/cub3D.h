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
	char *we_path;
	char *ea_path;
	} t_textures;
	
typedef struct s_player {
	int x;
	int y;
	char dir;       // 'N', 'S', 'E' o 'W'
	} t_player;
	
typedef struct s_map {
	char **grid;    // matriz del mapa, con '1', '0', ' ', 'N', importante tener en cuenta que se pasan ' '
	int height;     // número de líneas
	int weight;
	} t_map;
	
typedef struct s_game_data {
	t_textures textures;
	t_color floor_color;
	t_color ceiling_color;
	t_map map;
	t_player player;
	} t_game_data;

typedef struct s_valid_data {
	int no_valid;
	int so_valid; 
	int we_valid;
	int ea_valid;
	int no_invalid;
	int so_invalid; 
	int we_invalid;
	int ea_invalid;
	int c_valid;
	int c_invalid; 
	int f_valid;
	int f_invalid;
	} t_valid_data;

	char	*get_next_line(int fd, int *last);
	char	*ft_strdup(const char *s1);
	char	*ft_strjoin(char const *s1, char const *s2);
	size_t	ft_strlen(const char *s);
	char	*ft_strchr(const char *s, int c);
	char	*ft_substr(char const *s, unsigned int start, size_t len);
	void	*ft_memcpy(void *dest, const void *src, size_t n);
	int		ft_strncmp(const char *s1, const char *s2, size_t n);



#endif