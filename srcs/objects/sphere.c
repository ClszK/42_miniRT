/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeholee <jeholee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 03:01:10 by jeholee           #+#    #+#             */
/*   Updated: 2024/04/20 03:21:57 by jeholee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sphere.h"

t_sphere	*sphere_gen(const t_point3 center, const t_color col, double r, \
														const t_color albedo)
{
	t_sphere *sph;

	sph = malloc(sizeof(t_sphere));
	if (sph == NULL)
		exit(1);
	sph->hit = &hit_sphere;
	sph->center = center;
	sph->radius = r;
	sph->color = col;
	sph->albedo = albedo;
	return (sph);
}

t_bool	hit_sphere(const t_ray *r, const t_sphere *sphere, t_hit_record *rec)
{
	t_oc_ahc	coef;

	coef.oc = vec3_sub(&sphere->center, &r->orig);
	coef.a = vec3_dot(&r->dir, &r->dir);
	coef.h = vec3_dot(&r->dir, &coef.oc);
	coef.c = vec3_dot(&coef.oc, &coef.oc) - sphere->radius * sphere->radius;
	coef.discriminant = coef.h * coef.h - coef.a * coef.c;
	if (coef.discriminant < 0)
		return (FALSE);
	coef.sqrtd = sqrt(coef.discriminant);
	coef.root = (coef.h - coef.sqrtd) / coef.a;
	if (coef.root < rec->tmin || rec->tmax < coef.root)
	{
		coef.root = (coef.h + coef.sqrtd) / coef.a;
		if (coef.root < rec->tmin || rec->tmax < coef.root)
			return (FALSE);
	}
	rec->t = coef.root;
	rec->p = at(coef.root, r);
	rec->norm = vec3_init((rec->p.x - sphere->center.x) / sphere->radius, \
						(rec->p.y - sphere->center.y) / sphere->radius, \
						(rec->p.z - sphere->center.z) / sphere->radius);
	set_face_norm(r, rec, &rec->norm);
	rec->albedo = sphere->albedo;
	return (TRUE);
}
