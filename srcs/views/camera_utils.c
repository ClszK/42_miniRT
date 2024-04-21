/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeholee <jeholee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 05:44:41 by jeholee           #+#    #+#             */
/*   Updated: 2024/04/21 09:59:15 by jeholee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "sphere.h"

t_canvas	canvas_init(int width, int height, double focal_length)
{
	t_canvas	canvas;

	canvas.image_width = width;
	canvas.image_height = height;
	canvas.aspect_ratio = (double)width / (double)height;
	canvas.focal_length = focal_length;
	canvas.viewport_height = 2.0;
	canvas.viewport_width = canvas.viewport_height * canvas.aspect_ratio;
	canvas.viewport_u = vec3_init(canvas.viewport_width, 0, 0);
	canvas.viewport_v = vec3_init(0, -canvas.viewport_height, 0);
	return (canvas);
}

t_camera	camera_init(t_canvas cvs, t_point3 center, t_vec3 cam_dir)
{
	t_camera	cam;
	t_vec3		upper_left;

	(void)cam_dir;
	cam.delta_u = vec3_init(cvs.viewport_u.x / cvs.image_width, \
							cvs.viewport_u.y / cvs.image_width, \
							cvs.viewport_u.z / cvs.image_width);
	cam.delta_v = vec3_init(cvs.viewport_v.x / cvs.image_height, \
						cvs.viewport_v.y / cvs.image_height, \
						cvs.viewport_v.z / cvs.image_height);
	upper_left = vec3_init(\
		center.x - cvs.viewport_u.x / 2 - cvs.viewport_v.x / 2, \
		center.y - cvs.viewport_u.y / 2 - cvs.viewport_v.y / 2, \
		center.z - cvs.viewport_u.z / 2 - cvs.viewport_v.z / 2 - cvs.focal_length);
	cam.pixel00 = vec3_init(\
		upper_left.x + 0.5 * (cam.delta_u.x + cam.delta_v.x), \
		upper_left.y + 0.5 * (cam.delta_u.y + cam.delta_v.y), \
		upper_left.z + 0.5 * (cam.delta_u.z + cam.delta_v.z));
	return (cam);
}

t_render	render_init(void)
{
	t_render	render;
	t_color		color;
	double		ka;
	// ambient lighting의 색과 ambient lighting의 강도(ambient strength) 계수인 ka 의 곱으로 표현

	render.i = 0;
	render.j = 0;
	obj_init(&render.world);
	obj_add(&render.world, sphere_gen(point3_init(-2, 0, -5), \
				color_init(1,1,1), 2, color_init(0.5, 0, 0)));
	obj_add(&render.world, sphere_gen(point3_init(2, 0, -5), \
				color_init(1,1,1), 2, color_init(0, 0.5, 0)));
	obj_add(&render.world, sphere_gen(point3_init(0, -1000, 0), \
				color_init(0,1,1), 995, color_init(1, 1, 1)));
	obj_init(&render.light);
	obj_add(&render.light, light_gen(point3_init(0, 20, 0), \
				color_init(1, 1, 1), 0.3, LIGHT_POINT));
	ka = 0.1;
	color = color_init(1,1,1);
	render.ambient = vec3_mul_scal(&color, ka);
	return (render);
}

void	render(t_canvas cvs, t_camera cam, t_data *img)
{
	t_render	inf;

	inf = render_init();
	while (inf.i < cvs.image_height)
	{
		inf.j = 0;
		while (inf.j < cvs.image_width)
		{
			inf.pixel_center = vec3_init(\
				cam.pixel00.x + inf.j * cam.delta_u.x + inf.i * cam.delta_v.x, \
				cam.pixel00.y + inf.j * cam.delta_u.y + inf.i * cam.delta_v.y, \
				cam.pixel00.z + inf.j * cam.delta_u.z + inf.i * cam.delta_v.z);
			inf.ray_dir = vec3_sub(&inf.pixel_center, &cam.center);
			ray_init(&inf.ray, &cam.center, &inf.ray_dir);
			inf.color = ray_color(&inf);
			my_mlx_pixel_put(img, inf.j, inf.i, rgb_to_int(0, &inf.color));
			++inf.j;
		}
		++inf.i;
	}
}
