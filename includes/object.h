/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeholee <jeholee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 20:54:15 by jeholee           #+#    #+#             */
/*   Updated: 2024/04/20 10:10:40 by jeholee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H 
# define OBJECT_H

# define EPSILON 1e-6

# include "ray.h"
# include "my_mlx.h"
# include "double_lst.h"

typedef struct s_render t_render;

typedef struct s_hit_record
{
	t_point3	p;
	t_vec3		norm;
	double		t;
	double		tmin;
	double		tmax;
	t_bool		front_face;
	t_color		albedo;	// π›ªÁ¿≤
}	t_hit_record;

typedef int t_type;
typedef struct s_lst t_object;

void		set_face_norm(const t_ray *r, t_hit_record *rec, t_vec3 *out_norm);
t_color		ray_color(t_render *render);
void		obj_init(t_object *obj);
void		obj_add(t_object *obj, void *elem);
t_bool		hit(t_object *world, const t_ray *r, t_hit_record *rec);


#endif