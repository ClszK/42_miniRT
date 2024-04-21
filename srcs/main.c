/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeholee <jeholee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 17:54:01 by jeholee           #+#    #+#             */
/*   Updated: 2024/04/21 09:54:35 by jeholee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <stdio.h>

int main()
{
	t_vars		vars;
	t_data		image;
	t_canvas	canvas;
	t_camera	camera;

	canvas = canvas_init(800, 640, 1.0);
	camera = camera_init(canvas, point3_init(0, 0, 0), vec3_init(0.8, 0, 0.1)); // 방향 벡터는 0,0,0을 가져서는 안됨. 로직 추가필요.

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, canvas.image_width, 
								canvas.image_height, "miniRT");
	image.img = mlx_new_image(vars.mlx, canvas.image_width, \
								canvas.image_height); // 이미지 객체 생성
	image.addr = mlx_get_data_addr(image.img, &image.bits_per_pixel, \
								&image.line_length, &image.endian); // 이미지 주소 할당
	render(canvas, camera, &image);
	mlx_put_image_to_window(vars.mlx, vars.win, image.img, 0, 0);
	mlx_key_hook(vars.win, key_hook, &vars); // esc key press event
	mlx_loop(vars.mlx);
	return (0);
}