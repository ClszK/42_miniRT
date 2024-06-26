/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljh <ljh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 05:44:41 by jeholee           #+#    #+#             */
/*   Updated: 2024/05/06 21:13:40 by ljh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

t_canvas	canvas_init(int width, int height)
{
	t_canvas	cvs;

	cvs.image_width = width;
	cvs.image_height = height;
	cvs.aspect_ratio = (double)width / (double)height;
	cvs.viewport_height = 2.0;
	cvs.viewport_width = cvs.viewport_height * cvs.aspect_ratio;
	cvs.world_up = vec3_init(0, 1, 0);
	return (cvs);
}

void	camera_init(t_canvas cvs, t_camera *cam)
{
	t_vec3		upper_left;
	t_vec3		down;
	double		fov_radians;

	fov_radians = degrees_to_radians(cam->fov / 2);
	cvs.focal_length = cvs.viewport_width / (2.0 * tan(fov_radians));
	cam->right = vec3_unit(vec3_cross(&cam->cam_dir, &cvs.world_up));
	down = vec3_unit(vec3_cross(&cam->cam_dir, &cam->right));
	cam->viewport_u = vec3_mul_scal(&cam->right, cvs.viewport_width);
	cam->viewport_v = vec3_mul_scal(&down, cvs.viewport_height);
	cam->delta_u = vec3_div_scal(&cam->viewport_u, cvs.image_width);
	cam->delta_v = vec3_div_scal(&cam->viewport_v, cvs.image_height);
	upper_left = vec3_init(\
		cam->center.x - (cam->viewport_u.x + cam->viewport_v.x) / 2 \
										- cam->cam_dir.x * cvs.focal_length, \
		cam->center.y - (cam->viewport_u.y + cam->viewport_v.y) / 2 \
										- cam->cam_dir.y * cvs.focal_length, \
		cam->center.z - (cam->viewport_u.z + cam->viewport_v.z) / 2 \
										- cam->cam_dir.z * cvs.focal_length);
	cam->pixel00 = vec3_init(\
		upper_left.x + 0.5 * (cam->delta_u.x + cam->delta_v.x), \
		upper_left.y + 0.5 * (cam->delta_u.y + cam->delta_v.y), \
		upper_left.z + 0.5 * (cam->delta_u.z + cam->delta_v.z));
}

void	render(t_render *inf, t_canvas *cvs, t_camera *cam, t_data *img)
{
	t_vec3		ray_dir;
	int			i;
	int			j;

	i = 0;
	while (i < cvs->image_height)
	{
		j = 0;
		while (j < cvs->image_width)
		{
			inf->pixel_center = vec3_init(\
				cam->pixel00.x + j * cam->delta_u.x + i * cam->delta_v.x, \
				cam->pixel00.y + j * cam->delta_u.y + i * cam->delta_v.y, \
				cam->pixel00.z + j * cam->delta_u.z + i * cam->delta_v.z);
			ray_dir = vec3_sub(&inf->pixel_center, &cam->center);
			ray_init(&inf->ray, &cam->center, &ray_dir);
			inf->color = ray_color(inf);
			my_mlx_pixel_put(img, j, i, rgb_to_int(0, &inf->color));
			++j;
		}
		++i;
	}
}

double	degrees_to_radians(double degrees)
{
	return (degrees * M_PI / 180.0);
}

// t_render	render_init(void)
// {
// 	t_render	render;
// 	t_color		color;
// 	double		ka;

// 	obj_init(&render.world);
// 	obj_add(&render.world, sphere_gen(point3_init(-2, 0, -5), 
// 				color_init(1, 1, 1), 2, color_init(0.5, 0, 0)));
// 	obj_add(&render.world, sphere_gen(point3_init(2, 0, -5), 
// 				color_init(1, 1, 1), 2, color_init(0, 0.5, 0)));
// 	obj_add(&render.world, sphere_gen(point3_init(0, 23, 0),
// 				color_init(1, 1, 1), 2, color_init(0, 0.5, 0)));
// 	obj_add(&render.world, sphere_gen(point3_init(0, -1000, 1), 
// 				color_init(0, 1, 1), 995, color_init(1, 1, 1)));
// 	obj_add(&render.world, cylinder_gen(point3_init(0, 2, -20), 
// 				vec3_init(0, 0, -1), color_init(0.5, 0.5, 0.5), 
// 										color_init(1, 1, 1), 3, 10));
// 	obj_add(&render.world, plane_gen(point3_init(5, 1, 20), 
// 				color_init(1, 0.7, 0.8), vec3_init(-1, 0, 0), 
// 					color_init(0, 0, 0.5)));
// 	obj_init(&render.light);
// 	obj_add(&render.light, light_gen(point3_init(0, 20, 0), 
// 				color_init(1, 1, 1), 0.3));
// 	ka = 0.1;
// 	color = color_init(1, 1, 1);
// 	render.ambient = vec3_mul_scal(&color, ka);
// 	return (render);
// }