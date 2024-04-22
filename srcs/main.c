/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeholee <jeholee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 17:54:01 by jeholee           #+#    #+#             */
/*   Updated: 2024/04/23 04:21:49 by jeholee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <stdio.h>

t_minirt	mini_init(void)
{
	t_minirt	mini;
	t_vars		vars;
	t_data		image;
	t_canvas	canvas;
	t_camera	camera;

	canvas = canvas_init(800, 640, 1.0);
	camera = camera_init(canvas, point3_init(0, 0, 0), 
											vec3_init(0, 0, 1));
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, canvas.image_width, 
								canvas.image_height, "miniRT");
	image.img = mlx_new_image(vars.mlx, canvas.image_width, \
								canvas.image_height); // 이미지 객체 생성
	image.addr = mlx_get_data_addr(image.img, &image.bits_per_pixel, \
								&image.line_length, &image.endian); // 이미지 주소 할당
	mini.rendering = FALSE;
	mini.camera = camera;
	mini.canvas = canvas;
	mini.image = image;
	mini.vars = vars;
	return (mini);
}

int	test(t_minirt *mini)
{
	if (mini->rendering == TRUE){
		printf("%f %f %f\n", mini->canvas.viewport_u.x, mini->canvas.viewport_u.y, mini->canvas.viewport_u.z);
		render(mini->canvas, mini->camera, &mini->image);
		mlx_put_image_to_window(mini->vars.mlx, mini->vars.win, \
														mini->image.img, 0, 0);
		mini->rendering = FALSE;
	}
	return (0);
}

int main()
{
	t_minirt	mini;

	mini = mini_init();
	render(mini.canvas, mini.camera, &mini.image);
	mlx_put_image_to_window(mini.vars.mlx, mini.vars.win, mini.image.img, 0, 0);
	// mlx_key_hook(vars.win, key_hook, &vars); // esc key press event
	mlx_key_hook(mini.vars.win, key_hook, &mini); // esc key press event
	mlx_loop_hook(mini.vars.mlx, test, &mini);
	mlx_loop(mini.vars.mlx);
	return (0);
}