/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeholee <jeholee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 16:32:47 by jeholee           #+#    #+#             */
/*   Updated: 2024/04/27 13:41:09by jeholee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"
#include "plane.h"

t_cylinder	*cylinder_gen(t_point3 center, t_vec3 axis, t_color col, \
							t_color albedo, double r, double h)
{
	t_cylinder	*cylinder;

	cylinder = malloc(sizeof(t_cylinder));
	if (cylinder == NULL)
		exit(errno);
	cylinder->hit = &hit_cylinder;
	cylinder->center = center;
	cylinder->axis = axis;
	cylinder->color = col;
	cylinder->albedo = albedo;
	cylinder->radius = r;
	cylinder->height = h;
	return (cylinder);
}
#include <stdio.h>
// t_bool		hit_cylinder(const t_ray *r, const t_cylinder *cy, t_hit_record *rec)
// {
// 	t_cy_info	inf;
// 	t_plane		pl;

// 	pl.center = vec3_mul_scal(&cy->axis, -1 * cy->height / 2);
// 	pl.center = vec3_add(&pl.center, &cy->center);
// 	pl.color = cy->color;
// 	pl.plane_norm = cy->axis;
// 	pl.d = vec3_dot(&cy->axis, &pl.center) * -1;
// 	pl.albedo = cy->albedo;
// 	if (hit_plane(r, &pl, rec))
// 	{
// 		inf.oc = vec3_sub(&rec->p, &pl.center);
// 		if (vec3_dot(&inf.oc, &inf.oc) <= cy->radius * cy->radius)
// 			rec->tmax = rec->t;
// 	}
// 	pl.center = vec3_mul_scal(&cy->axis, cy->height / 2);
// 	pl.center = vec3_add(&pl.center, &cy->center);
// 	pl.d = vec3_dot(&pl.plane_norm, &pl.center) * -1;
// 	if (hit_plane(r, &pl, rec))
// 	{
// 		inf.oc = vec3_sub(&rec->p, &pl.center);
// 		if (vec3_dot(&inf.oc, &inf.oc) <= cy->radius * cy->radius)
// 			rec->tmax = rec->t;
// 	}
// 	inf.oc = vec3_sub(&r->orig, &cy->center);
// 	inf.u = vec3_mul_scal(&cy->axis ,vec3_dot(&inf.oc, &cy->axis));
// 	inf.u = vec3_sub(&inf.oc, &inf.u);

// 	inf.v = vec3_mul_scal(&cy->axis ,vec3_dot(&r->dir, &cy->axis));
// 	inf.v = vec3_sub(&r->dir, &inf.v);

// 	inf.a = vec3_dot(&inf.v, &inf.v);
// 	inf.h = vec3_dot(&inf.u, &inf.v);
// 	inf.c = vec3_dot(&inf.u, &inf.u) - cy->radius * cy->radius;
// 	inf.discriminant = inf.h * inf.h - inf.a * inf.c;
// 	if (inf.discriminant < 0)
// 		return (FALSE);
// 	inf.sqrtd = sqrt(inf.discriminant);
// 	inf.root = (-1 * inf.h - inf.sqrtd) / inf.a;
// 	if (inf.root < rec->tmin || rec->tmax < inf.root)
// 	{
// 		inf.root = (-1 * inf.h + inf.sqrtd) / inf.a;
// 		if (inf.root < rec->tmin || rec->tmax < inf.root)
// 			return (FALSE);
// 	}
// 	rec->t = inf.root;
// 	rec->p = at(inf.root, r);
// 	inf.pc = vec3_sub(&rec->p, &cy->center);
// 	inf.p_height = vec3_dot(&cy->axis, &inf.pc);
// 	if (fabs(inf.p_height) > cy->height / 2)
// 		return (FALSE);
// 	t_vec3	test2;
	

// 	test2 = vec3_mul_scal(&cy->axis, vec3_dot(&inf.pc, &cy->axis));
// 	rec->norm = vec3_sub(&inf.pc, &test2); 
// 	rec->norm =vec3_unit(rec->norm);
// 	set_face_norm(r, rec, &rec->norm);
// 	rec->albedo = cy->albedo;
// 	return (TRUE);
// }

t_bool		hit_cylinder(const t_ray *r, const t_cylinder *cy, t_hit_record *rec)
{
	t_bool	result;
	t_plane	pl;

	result = FALSE;
	pl.albedo = cy->albedo;
	pl.color = cy->color;
	pl.plane_norm = cy->axis;
	pl.center = vec3_init(cy->center.x + cy->axis.x * cy->height / 2, \
							cy->center.y + cy->axis.y * cy->height / 2, \
							cy->center.z + cy->axis.z * cy->height / 2);
	pl.d = vec3_dot(&pl.plane_norm, &pl.center) * -1;
	result += hit_cylinder_caps(r, cy, &pl ,rec);
	pl.center = vec3_init(cy->center.x - cy->axis.x * cy->height / 2, \
							cy->center.y - cy->axis.y * cy->height / 2, \
							cy->center.z - cy->axis.z * cy->height / 2);
	pl.d = vec3_dot(&pl.plane_norm, &pl.center) * -1;
	result += hit_cylinder_caps(r, cy, &pl ,rec);
	result += hit_cylinder_side(r, cy, rec);
	return (result);
}

t_bool		hit_cylinder_side(const t_ray *r, const t_cylinder *cy, t_hit_record *rec)
{
	t_cy_info	inf;

	inf.oc = vec3_sub(&r->orig, &cy->center);
	inf.u = vec3_mul_scal(&cy->axis ,vec3_dot(&inf.oc, &cy->axis));
	inf.u = vec3_sub(&inf.oc, &inf.u);

	inf.v = vec3_mul_scal(&cy->axis ,vec3_dot(&r->dir, &cy->axis));
	inf.v = vec3_sub(&r->dir, &inf.v);

	inf.a = vec3_dot(&inf.v, &inf.v);
	inf.h = vec3_dot(&inf.u, &inf.v);
	inf.c = vec3_dot(&inf.u, &inf.u) - cy->radius * cy->radius;
	inf.discriminant = inf.h * inf.h - inf.a * inf.c;
	if (inf.discriminant < 0)
		return (FALSE);
	inf.sqrtd = sqrt(inf.discriminant);
	inf.root = (-1 * inf.h - inf.sqrtd) / inf.a;
	if (inf.root < rec->tmin || rec->tmax < inf.root)
	{
		inf.root = (-1 * inf.h + inf.sqrtd) / inf.a;
		if (inf.root < rec->tmin || rec->tmax < inf.root)
			return (FALSE);
	}
	rec->t = inf.root;
	rec->p = at(inf.root, r);
	inf.pc = vec3_sub(&rec->p, &cy->center);
	inf.p_height = vec3_dot(&cy->axis, &inf.pc);
	if (fabs(inf.p_height) > cy->height / 2)
		return (FALSE);
	t_vec3	test2;

	test2 = vec3_mul_scal(&cy->axis, vec3_dot(&inf.pc, &cy->axis));
	rec->norm = vec3_sub(&inf.pc, &test2); 
	rec->norm =vec3_unit(rec->norm);
	set_face_norm(r, rec, &rec->norm);
	rec->albedo = cy->albedo;
	return (TRUE);
}

t_bool	hit_cylinder_caps(const t_ray *r, const t_cylinder *cy, const t_plane *pl, t_hit_record *rec)
{
	t_vec3			pl_radius;
	t_hit_record	pl_rec;

	pl_rec = *rec;
	if (hit_plane(r, pl, &pl_rec))
	{
		pl_radius = vec3_sub(&pl_rec.p, &pl->center);
		if (vec3_dot(&pl_radius, &pl_radius) <= cy->radius * cy->radius)
		{
			*rec = pl_rec;
			rec->tmax = rec->t;
			return (TRUE);
		}
	}
	return (FALSE);
}