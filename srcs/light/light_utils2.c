/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljh <ljh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 21:25:19 by jeholee           #+#    #+#             */
/*   Updated: 2024/04/28 19:47:16 by ljh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "light.h"

void	diffuse_cal(t_light_info *info, t_render *render, t_light *light)
{
	double	kd;

	kd = fmax(vec3_dot(&render->rec.norm, &info->light_dir), 0.0);
	info->diffuse = vec3_mul_scal(&light->light_color, kd);
}

void	specular_cal(t_light_info *info, t_render *render, t_light *light)
{
	t_vec3		view_dir;
	t_vec3		reflect_dir;
	double		ksn;
	double		ks;
	double		spec;

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

void	color_surround(t_color *light_color)
{
	if (light_color->x > 1)
		light_color->x = 1;
	if (light_color->y > 1)
		light_color->y = 1;
	if (light_color->z > 1)
		light_color->z = 1;
}
