/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljh <ljh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 16:32:47 by jeholee           #+#    #+#             */
/*   Updated: 2024/05/02 21:46:09 by ljh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"

t_cylinder	*cylinder_gen(t_point3 center, t_vec3 axis, t_color albedo, \
													double r, double h)
{
	t_cylinder	*cylinder;

	cylinder = malloc(sizeof(t_cylinder));
	if (cylinder == NULL)
		exit(errno);
	cylinder->hit = &hit_cylinder;
	cylinder->center = center;
	cylinder->axis = axis;
	cylinder->albedo = albedo;
	cylinder->radius = r;
	cylinder->height = h;
	return (cylinder);
}

t_bool	hit_cylinder(const t_ray *r, const t_cylinder *cy, \
											t_hit_record *rec)
{
	t_bool	result;
	t_plane	pl;

	result = FALSE;
	pl.albedo = cy->albedo;
	pl.plane_norm = cy->axis;
	pl.center = vec3_init(cy->center.x + cy->axis.x * cy->height / 2, \
							cy->center.y + cy->axis.y * cy->height / 2, \
							cy->center.z + cy->axis.z * cy->height / 2);
	pl.d = vec3_dot(&pl.plane_norm, &pl.center) * -1;
	result += hit_cylinder_caps(r, cy, &pl, rec);
	pl.center = vec3_init(cy->center.x - cy->axis.x * cy->height / 2, \
							cy->center.y - cy->axis.y * cy->height / 2, \
							cy->center.z - cy->axis.z * cy->height / 2);
	pl.d = vec3_dot(&pl.plane_norm, &pl.center) * -1;
	result += hit_cylinder_caps(r, cy, &pl, rec);
	if (fabs(vec3_dot(&r->dir, &cy->axis)) < EPSILON)
		return (result);
	result += hit_cylinder_side(r, cy, rec);
	return (result);
}

t_bool	hit_cylinder_side(const t_ray *r, const t_cylinder *cy, \
													t_hit_record *rec)
{
	t_cy_info	inf;
	t_point3	tmp_p;
	double		pc_dot;

	if (!cy_determine(&inf, cy, r, rec))
		return (FALSE);
	tmp_p = at(inf.root, r);
	inf.pc = vec3_sub(&tmp_p, &cy->center);
	if (fabs(vec3_dot(&cy->axis, &inf.pc)) > cy->height / 2)
		return (FALSE);
	pc_dot = vec3_dot(&inf.pc, &cy->axis);
	rec->t = inf.root;
	rec->p = tmp_p;
	rec->norm = vec3_init((inf.pc.x - cy->axis.x * pc_dot) / cy->radius, \
							(inf.pc.y - cy->axis.y * pc_dot) / cy->radius, \
							(inf.pc.z - cy->axis.z * pc_dot) / cy->radius);
	set_face_norm(r, rec, &rec->norm);
	rec->albedo = cy->albedo;
	return (TRUE);
}

t_bool	hit_cylinder_caps(const t_ray *r, const t_cylinder *cy, \
										const t_plane *pl, t_hit_record *rec)
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

t_bool	cy_determine(t_cy_info *inf, const t_cylinder *cy, \
										const t_ray *r, const t_hit_record *rec)
{
	inf->oc = vec3_sub(&r->orig, &cy->center);
	inf->projection = vec3_dot(&inf->oc, &cy->axis);
	inf->u = vec3_init(inf->oc.x - cy->axis.x * inf->projection, \
						inf->oc.y - cy->axis.y * inf->projection, \
						inf->oc.z - cy->axis.z * inf->projection);
	inf->projection = vec3_dot(&r->dir, &cy->axis);
	inf->v = vec3_init(r->dir.x - cy->axis.x * inf->projection, \
						r->dir.y - cy->axis.y * inf->projection, \
						r->dir.z - cy->axis.z * inf->projection);
	inf->a = vec3_dot(&inf->v, &inf->v);
	inf->h = vec3_dot(&inf->u, &inf->v);
	inf->discriminant = inf->h * inf->h - inf->a * \
					(vec3_dot(&inf->u, &inf->u) - cy->radius * cy->radius);
	if (inf->discriminant < 0)
		return (FALSE);
	inf->sqrtd = sqrt(inf->discriminant);
	inf->root = (-1 * inf->h - inf->sqrtd) / inf->a;
	if (inf->root < rec->tmin || rec->tmax < inf->root)
	{
		inf->root = (-1 * inf->h + inf->sqrtd) / inf->a;
		if (inf->root < rec->tmin || rec->tmax < inf->root)
			return (FALSE);
	}
	return (TRUE);
}
