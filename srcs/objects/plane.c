/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeholee <jeholee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:35:01 by jeholee           #+#    #+#             */
/*   Updated: 2024/04/24 13:22:52 by jeholee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "plane.h"

t_plane	*plane_gen(t_point3 center, t_color col, t_vec3 norm, t_color albedo)
{
	t_plane	*plane;

	plane = malloc(sizeof(t_plane));
	if (plane == NULL)
		exit(1);
	plane->hit = &hit_plane;
	plane->albedo = albedo;
	plane->center = center;
	plane->color = col;
	plane->plane_norm = norm;
	plane->d = vec3_dot(&norm, &center) * -1;
	return (plane);
}

t_bool	hit_plane(const t_ray *r, const t_plane *plane, t_hit_record *rec)
{
	double	denominator;
	double	t;

	denominator = vec3_dot(&plane->plane_norm, &r->dir);
	if (fabs(denominator) < EPSILON)
		return (FALSE);
	t = -1 * (vec3_dot(&plane->plane_norm, &r->orig) + plane->d) / denominator;
	if (t < rec->tmin || rec->tmax < t)
		return (FALSE);
	rec->t = t;
	rec->p = at(rec->t, r);
	rec->norm = plane->plane_norm;
	set_face_norm(r, rec, &rec->norm);
	rec->albedo = plane->albedo;
	return (TRUE);
}