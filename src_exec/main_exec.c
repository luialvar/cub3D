/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mait_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-ant <juan-ant@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 12:58:11 by juan-ant          #+#    #+#             */
/*   Updated: 2025/06/30 12:58:11 by juan-ant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3Dexec.h"

int	fret_exec(t_exec *exec)
{
	if (exec->we != NULL)
		mlx_delete_texture(exec->we);
	if (exec->no != NULL)
		mlx_delete_texture(exec->no);
	if (exec->ea != NULL)
		mlx_delete_texture(exec->ea);
	if (exec->so != NULL)
		mlx_delete_texture(exec->so);
	if (exec->stance != NULL)
	{
		if (exec->stance->window != NULL)
			mlx_close_window(exec->stance);
		mlx_terminate(exec->stance);
	}
	free(exec);
	return (1);
}

void	gameplay(void *param)
{
	t_exec	*exec;

	exec = param;
	if (mlx_is_key_down(exec->stance, MLX_KEY_ESCAPE))
		mlx_close_window(exec->stance);
	if (mlx_is_key_down(exec->stance, MLX_KEY_W))
		move_up(exec);
	if (mlx_is_key_down(exec->stance, MLX_KEY_S))
		move_down(exec);
	if (mlx_is_key_down(exec->stance, MLX_KEY_A))
		move_left(exec);
	if (mlx_is_key_down(exec->stance, MLX_KEY_D))
		move_right(exec);
	if (mlx_is_key_down(exec->stance, MLX_KEY_LEFT))
		rotate_l(exec);
	if (mlx_is_key_down(exec->stance, MLX_KEY_RIGHT))
		rotate_r(exec);
	init_rays(exec);
}

int	get_images(t_exec *exec)
{
	exec->we = NULL;
	exec->ea = NULL;
	exec->no = NULL;
	exec->so = NULL;
	exec->stance = NULL;
	exec->img = NULL;
	exec->we = mlx_load_png(exec->cub->textures.we_path);
	if (exec->we == NULL)
		return (fret_exec(exec));
	exec->ea = mlx_load_png(exec->cub->textures.ea_path);
	if (exec->ea == NULL)
		return (fret_exec(exec));
	exec->no = mlx_load_png(exec->cub->textures.no_path);
	if (exec->no == NULL)
		return (fret_exec(exec));
	exec->so = mlx_load_png(exec->cub->textures.so_path);
	if (exec->so == NULL)
		return (fret_exec(exec));
	return (0);
}

int	main_exec(struct s_game_data *cub)
{
	t_exec	*exec;

	exec = malloc(sizeof(t_exec));
	if (exec == NULL)
		return (1);
	exec->cub = cub;
	if (get_images(exec) != 0)
		return (1);
	init_player(exec);
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	exec->stance = mlx_init(WIDTH, HEIGHT, "Cub3D", true);
	if (exec->stance == NULL)
		return (fret_exec(exec));
	exec->img = mlx_new_image(exec->stance, WIDTH, HEIGHT);
	if (exec->img == NULL)
		return (fret_exec(exec));
	init_rays(exec);
	mlx_image_to_window(exec->stance, exec->img, 0, 0);
	mlx_loop_hook(exec->stance, &gameplay, exec);
	mlx_loop(exec->stance);
	fret_exec(exec);
	return (0);
}
