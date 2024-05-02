/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljh <ljh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 10:30:46 by jeholee           #+#    #+#             */
/*   Updated: 2024/05/02 21:23:35 by ljh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "light.h"
#include <stdio.h>

t_light	*light_gen(t_point3 origin, t_color light_color, double bright_ratio)
{
	t_light	*light;

	light = malloc(sizeof(t_light));
	if (light == NULL)
		exit(errno);
	light->origin = origin;
	light->light_color = light_color;
	light->bright_ratio = bright_ratio;
	return (light);
}

t_color	phong_lighting(t_render *render)
{
	t_color		light_color_sum;
	t_color		light_color;	
	t_node		*node;
	t_light		*light;

	light_color_sum = color_init(0, 0, 0);
	node = render->light.head->next;
	while (node->next)
	{
		light = node->elem;
		light_color = point_light_get(render, light);
		light_color_sum = vec3_add(&light_color_sum, &light_color);
		node = node->next;
	}
	light_color = color_init(\
		(light_color_sum.x + render->ambient.x) * render->rec.albedo.x, \
		(light_color_sum.y + render->ambient.y) * render->rec.albedo.y, \
		(light_color_sum.z + render->ambient.z) * render->rec.albedo.z);
	color_surround(&light_color);
	return (light_color);
}

t_color	point_light_get(t_render *render, t_light *light)
{
	t_light_info	info;
	double			brightness;

	if (hard_shadow(&info, render, light))
		return (color_init(0, 0, 0));
	diffuse_cal(&info, render, light);
	specular_cal(&info, render, light);
	brightness = light->bright_ratio * LUMEN;
	return (color_init((info.diffuse.x + info.specular.x) * brightness, \
						(info.diffuse.y + info.specular.y) * brightness, \
						(info.diffuse.z + info.specular.z) * brightness));
}

t_bool	hard_shadow(t_light_info *info, t_render *render, t_light *light)
{
	t_point3		light_ray_orig;
	t_ray			light_ray;
	t_hit_record	rec;
	double			light_len;

	rec = render->rec;
	light_ray_orig = point3_init(rec.p.x + EPSILON * rec.norm.x, \
								rec.p.y + EPSILON * rec.norm.y, \
								rec.p.z + EPSILON * rec.norm.z);
	info->light_dir = vec3_sub(&light->origin, &light_ray_orig);
	light_len = vec3_length(&info->light_dir);
	info->light_dir = vec3_div_scal(&info->light_dir, light_len);
	ray_init(&light_ray, &light_ray_orig, &info->light_dir);
	if (in_shadow(&render->world, &light_ray, light_len))
		return (TRUE);
	return (FALSE);
}

t_bool	in_shadow(t_object *objs, t_ray *light_ray, double light_len)
{
	t_hit_record	rec;

	rec.tmin = 0;
	rec.tmax = light_len;
	if (hit(objs, light_ray, &rec))
		return (TRUE);
	return (FALSE);
}
