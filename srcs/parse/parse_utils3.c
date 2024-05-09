/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljh <ljh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 15:59:15 by ljh               #+#    #+#             */
/*   Updated: 2024/05/09 21:13:39 by ljh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	parse_ambient(char **id_line, t_minirt *mi)
{
	double		ambient_ratio;
	t_color		rgb;

	if (mi->render.has_amb == TRUE)
		error_exit("Error\nMore than one ambient light.\n");
	if (get_arraysize(id_line) != 3)
		error_exit("Error\nInvalid ambient elem count.\n");
	errno = 0;
	if (!is_double(id_line[1]))
		error_exit("Error\ninvalid ambient lighting ratio.\n");
	ambient_ratio = atod(id_line[1], 0, 1, 1);
	if (ambient_ratio < 0.0 || ambient_ratio > 1.0)
		error_exit("Error\ninvalid ambient lighting ratio value.\n");
	rgb = atorgb(id_line[2]);
	if (is_valid_rgb(rgb))
		error_exit("Error\ninvalid ambient rgb value.\n");
	mi->render.ambient = vec3_mul_scal(&rgb, ambient_ratio);
	mi->render.has_amb = TRUE;
}

void	parse_camera(char **id_line, t_minirt *mi)
{
	t_camera	*cam;

	if (mi->camera != NULL)
		error_exit("Error\nMore than one camera.\n");
	if (get_arraysize(id_line) != 4)
		error_exit("Error\nInvalid camera elem count.\n");
	errno = 0;
	cam = malloc(sizeof(t_camera));
	if (cam == NULL && errno)
		error_exit(NULL);
	cam->center = atoxyz(id_line[1]);
	cam->cam_dir = atoxyz(id_line[2]);
	if (cam->cam_dir.x == 0 && cam->cam_dir.y == 0 && cam->cam_dir.z == 0)
		cam->cam_dir = vec3_init(0, 0, -1);
	if (is_normalized(cam->cam_dir))
		error_exit("Error\ninvalid camera normed direction.\n");
	if (is_int(id_line[3]))
		error_exit("Error\ninvalid camera fov.\n");
	cam->fov = atod(id_line[3], 0, 1, 1);
	if (cam->fov < 0 || cam->fov > 180)
		error_exit("Error\ninvalid camera fov value.\n");
	mi->camera = cam;
}

void	parse_light(char **id_line, t_minirt *mi)
{
	t_light	light;

	if (dlst_count(&mi->render.light) != 0)
		error_exit("Error\nMore than one light.\n");
	if (!(get_arraysize(id_line) == 3 || get_arraysize(id_line) == 4))
		error_exit("Error\nInvalid light elem count.\n");
	light.origin = atoxyz(id_line[1]);
	if (!is_double(id_line[2]))
		error_exit("Error\nInvalid light brightness ratio\n");
	light.bright_ratio = atod(id_line[2], 0, 1, 1);
	if (light.bright_ratio < 0.0 || light.bright_ratio > 1.0)
		error_exit("Error\ninvalid light brightness ratio value\n");
	if (id_line[3])
	{
		light.light_color = atorgb(id_line[3]);
		if (is_valid_rgb(light.light_color))
			error_exit("Error\ninvalid light rgb value.\n");
	}
	else
		light.light_color = color_init(1, 1, 1);
	obj_add(&mi->render.light, light_gen(light.origin, light.light_color, \
											light.bright_ratio));
}

void	parse_sphere(char **id_line, t_minirt *mi)
{
	t_sphere	sph;

	if (get_arraysize(id_line) != 4)
		error_exit("Error\nInvalid sphere elem count.\n");
	sph.center = atoxyz(id_line[1]);
	if (!is_double(id_line[2]))
		error_exit("Error\nInvalid sphere diameter.\n");
	sph.radius = atod(id_line[2], 0, 1, 1) / 2.0;
	if (sph.radius <= 0)
		error_exit("Error\nInvalid sphere diameter value\n");
	sph.albedo = atorgb(id_line[3]);
	if (is_valid_rgb(sph.albedo))
		error_exit("Error\nInvalid sphere rgb value.\n");
	obj_add(&mi->render.world, sphere_gen(sph.center, sph.radius, \
									sph.albedo));
}

void	parse_plane(char **id_line, t_minirt *mi)
{
	t_plane	pl;

	if (get_arraysize(id_line) != 4)
		error_exit("Error\nInvalid plane elem count.\n");
	pl.center = atoxyz(id_line[1]);
	pl.plane_norm = atoxyz(id_line[2]);
	if (is_normalized(pl.plane_norm))
		error_exit("Error\ninvalid plane normalized cooridates\n");
	pl.albedo = atorgb(id_line[3]);
	if (is_valid_rgb(pl.albedo))
		error_exit("Error\ninvalid plane rgb value\n");
	obj_add(&mi->render.world, plane_gen(pl.center, pl.plane_norm, \
										pl.albedo));
}
