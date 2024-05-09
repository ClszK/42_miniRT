/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljh <ljh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 17:54:01 by jeholee           #+#    #+#             */
/*   Updated: 2024/05/07 01:26:51 by ljh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdio.h>

t_minirt	mini_init(char *argv[])
{
	t_minirt	mi;

	mi.camera = NULL;
	obj_init(&mi.render.world);
	obj_init(&mi.render.light);
	file_parse(argv, &mi);
	if (mi.camera == NULL || mi.render.has_amb == FALSE \
		|| dlst_count(&mi.render.light) == 0 \
		|| dlst_count(&mi.render.world) == 0)
		error_exit("Error\nInvalid elements\n");
	mi.canvas = canvas_init(1280, 720);
	camera_init(mi.canvas, mi.camera);
	printf("C\t%f, %f, %f\t%f, %f, %f\t%d\n", mi.camera->center.x, \
												mi.camera->center.y, \
												mi.camera->center.z, \
												mi.camera->cam_dir.x, \
												mi.camera->cam_dir.y, \
												mi.camera->cam_dir.z, \
												mi.camera->fov);
	mi.vars.mlx = mlx_init();
	mi.vars.win = mlx_new_window(mi.vars.mlx, mi.canvas.image_width, \
								mi.canvas.image_height, "minirt");
	mi.image.img = mlx_new_image(mi.vars.mlx, mi.canvas.image_width, \
								mi.canvas.image_height);
	mi.image.addr = mlx_get_data_addr(mi.image.img, &mi.image.bits_per_pixel, \
								&mi.image.line_length, &mi.image.endian);
	mi.rendering = FALSE;
	mi.render.has_amb = FALSE;
	mi.yaw = 0;
	mi.pitch = 0;
	mi.start_dir = mi.camera->cam_dir;
	mi.start_center = mi.camera->center;
	return (mi);
}

int	re_render(t_minirt *mini)
{
	if (mini->rendering == TRUE)
	{
		render(&mini->render, &mini->canvas, mini->camera, &mini->image);
		mlx_put_image_to_window(mini->vars.mlx, mini->vars.win, \
														mini->image.img, 0, 0);
		mini->rendering = FALSE;
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_minirt	mini;

	if (argc != 2)
	{
		ft_printf("Error\nUsage: ./miniRT filename.rt\n");
		return (1);
	}
	mini = mini_init(argv);
	render(&mini.render, &mini.canvas, mini.camera, &mini.image);
	mlx_put_image_to_window(mini.vars.mlx, mini.vars.win, mini.image.img, 0, 0);
	mlx_key_hook(mini.vars.win, key_hook, &mini);
	mlx_loop_hook(mini.vars.mlx, re_render, &mini);
	mlx_loop(mini.vars.mlx);
	return (0);
}
