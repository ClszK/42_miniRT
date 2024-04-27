/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeholee <jeholee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 17:54:01 by jeholee           #+#    #+#             */
/*   Updated: 2024/04/27 17:07:33 by jeholee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <stdio.h>

t_minirt	mini_init(void)
{
	t_minirt	mi;

	mi.canvas = canvas_init(860, 740, 70);
	mi.camera = camera_init(mi.canvas, point3_init(0, 0, 10), 
											vec3_init(0, 0, 1));
	mi.vars.mlx = mlx_init();
	mi.vars.win = mlx_new_window(mi.vars.mlx, mi.canvas.image_width, 
								mi.canvas.image_height, "miniRT");
	mi.image.img = mlx_new_image(mi.vars.mlx, mi.canvas.image_width, \
								mi.canvas.image_height); // 이미지 객체 생성
	mi.image.addr = mlx_get_data_addr(mi.image.img, &mi.image.bits_per_pixel, \
								&mi.image.line_length, &mi.image.endian); // 이미지 주소 할당
	mi.rendering = FALSE;
	mi.yaw = 0;
	mi.pitch = 0;
	mi.start_dir = mi.camera.cam_dir;
	mi.start_center = mi.camera.center;
	return (mi);
}

int	test(t_minirt *mini)
{
	if (mini->rendering == TRUE){
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
	mlx_key_hook(mini.vars.win, key_hook, &mini); // esc key press event
	mlx_loop_hook(mini.vars.mlx, test, &mini);
	mlx_loop(mini.vars.mlx);
	return (0);
}