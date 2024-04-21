/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeholee <jeholee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 10:30:46 by jeholee           #+#    #+#             */
/*   Updated: 2024/04/20 12:02:42 by jeholee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "light.h"
#include "camera.h"

t_light	*light_gen(t_point3 origin, t_color light_color, double bright_radio, \
					t_light_type type)
{
	t_light	*light;

	light = malloc(sizeof(t_light));
	if (light == NULL)
		exit(errno);
	light->type = type;
	light->origin = origin;
	light->light_color = light_color;
	light->bright_radio = bright_radio;
	return (light);
}

t_color	phong_lighting(t_render *render)
{
	t_color		light_color_sum;
	t_color		light_color;	
	t_node		*node;
	t_light		*light;

	light_color = color_init(0, 0, 0);
	light_color_sum = color_init(0, 0, 0);
	node = render->light.head->next;
	while (node->next)
	{
		light = node->elem;
		if (light->type == LIGHT_POINT)
		{
			light_color = point_light_get(render, light);
			light_color_sum = vec3_add(&light_color_sum, &light_color);
		}
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
	brightness = light->bright_radio * LUMEN;
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
	info->light_dir = vec3_sub(&light->origin, &render->rec.p);
	light_len = vec3_length(&info->light_dir);
	light_ray_orig = point3_init(rec.p.x + EPSILON * rec.norm.x, \
								rec.p.y + EPSILON * rec.norm.y, \
								rec.p.z + EPSILON * rec.norm.z);
	ray_init(&light_ray, &light_ray_orig, &info->light_dir);
	info->light_dir = vec3_div_scal(&info->light_dir, light_len);
	if (in_shadow(&render->world, &light_ray, light_len))
		return (TRUE);
	return (FALSE);
}

void	diffuse_cal(t_light_info *info, t_render *render, t_light *light)
{
	double	kd;	// diffuse의 강도 계수

	kd = fmax(vec3_dot(&render->rec.norm, &info->light_dir), 0.0);
	info->diffuse = vec3_mul_scal(&light->light_color, kd);
}

void	specular_cal(t_light_info *info, t_render *render, t_light *light)
{
	t_vec3		view_dir;
	t_vec3		reflect_dir;
	double		ksn;	// shininess value
	double		ks;		// specular strength
	double		spec;	// cos x ^ ksn

	view_dir = vec3_unit(vec3_mul_scal(&render->ray.dir, -1));
	reflect_dir = vec3_mul_scal(&info->light_dir, -1);
	reflect(&reflect_dir, &render->rec.norm);
	ksn = 64;
	ks = 0.5;
	spec = pow(fmax(vec3_dot(&view_dir, &reflect_dir), 0.0), ksn);
	info->specular = vec3_init(ks * light->light_color.x * spec, \
								ks * light->light_color.y * spec, \
								ks * light->light_color.z * spec);
}

void	reflect(t_vec3 *v, const t_vec3 *n)
{
	double	dot_cal;

	dot_cal = vec3_dot(v, n) * 2;
	v->x = v->x - n->x * dot_cal;
	v->y = v->y - n->y * dot_cal;
	v->z = v->z - n->z * dot_cal;
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

void	color_surround(t_color *light_color)
{	
	if (light_color->x > 1)
		light_color->x = 1;
	if (light_color->y > 1)
		light_color->y = 1;
	if (light_color->z > 1)
		light_color->z = 1;
}
