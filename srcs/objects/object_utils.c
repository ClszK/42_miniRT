/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeholee <jeholee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 10:57:00 by jeholee           #+#    #+#             */
/*   Updated: 2024/04/21 08:40:00 by jeholee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"
#include "sphere.h"
#include "camera.h"

void	set_face_norm(const t_ray *r, t_hit_record *rec, t_vec3 *out_norm)
{
	rec->front_face = vec3_dot(&r->dir, out_norm) < 0;
	rec->norm = *out_norm;
	if (!rec->front_face)
		rec->norm = vec3_mul_scal(out_norm, -1.0);
}

t_color		ray_color(t_render *render)
{
	double			t;
	double			inverse_t;
	t_hit_record	*rec;
	t_ray			*r;

	rec = &render->rec;
	rec->tmin = EPSILON;
	rec->tmax = INFINITY;
	r = &render->ray;
	if (hit(&render->world, r, rec))
		return (phong_lighting(render));
	t = 0.5 * (vec3_unit(r->dir).y + 1.0);
	inverse_t = 1.0 - t;
	return (color_init(1.0 * inverse_t + 0.5 * t, \
						1.0 * inverse_t + 0.7 * t, \
						1.0 * inverse_t + 1.0 * t));
}

void		obj_init(t_object *obj)
{
	dlst_init(obj);
}

void	obj_add(t_object *obj, void *elem)
{
	dlst_add_last(obj, elem);
}

t_bool		hit(t_object *world, const t_ray *r, t_hit_record *rec)
{
	t_hit_record	tmp_rec;
	t_node			*node;
	t_bool			hit_anything;

	hit_anything = FALSE;
	tmp_rec = *rec;
	node = world->head->next;
	while (node->next)
	{
		if (((t_sphere*)(node->elem))->hit(r, node->elem, &tmp_rec))
		{
			hit_anything = TRUE;
			tmp_rec.tmax = tmp_rec.t;
			*rec = tmp_rec;
		}
		node = node->next;
	}
	return (hit_anything);
}