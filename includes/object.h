/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeholee <jeholee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 20:54:15 by jeholee           #+#    #+#             */
/*   Updated: 2024/04/27 14:24:12 by jeholee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H 
# define OBJECT_H

# define EPSILON 1e-6

# include "ray.h"
# include "my_mlx.h"
# include "double_lst.h"

typedef struct s_render t_render;
typedef struct s_cylinder t_cylinder;
typedef struct s_plane t_plane;

typedef struct s_hit_record
{
	t_point3	p;
	t_vec3		norm;
	double		t;
	double		tmin;
	double		tmax;
	t_bool		front_face;
	t_color		albedo;	// �ݻ���
}	t_hit_record;

typedef struct s_oc_ahc
{
	t_vec3	oc;
	double	a;
	double	h;
	double	c;
	double	discriminant;
	double	sqrtd;
	double	root;
}	t_oc_ahc;

typedef struct s_cy_info
{
	t_vec3	oc;
	t_vec3	pc;
	t_vec3	u;
	t_vec3	v;
	t_vec3	perpendicular;
	double	a;
	double	h;
	double	c;
	double	discriminant;
	double	sqrtd;
	double	root;
	double	p_height;
}	t_cy_info;

typedef struct s_cylinder
{
	t_bool		(*hit)(const t_ray*, const t_cylinder*, t_hit_record*);
	t_point3	center;
	t_vec3		axis;
	t_color		color;
	t_color		albedo;	//반사율
	double		radius;
	double		height;
}	t_cylinder;


typedef int t_type;
typedef struct s_lst t_object;

void		set_face_norm(const t_ray *r, t_hit_record *rec, t_vec3 *out_norm);
t_color		ray_color(t_render *render);
void		obj_init(t_object *obj);
void		obj_add(t_object *obj, void *elem);
t_bool		hit(t_object *world, const t_ray *r, t_hit_record *rec);

t_cylinder	*cylinder_gen(t_point3 center, t_vec3 axis, t_color col, \
							t_color albedo, double r, double h);
t_bool		hit_cylinder(const t_ray *r, const t_cylinder *cy, t_hit_record *rec);
t_bool		hit_cylinder_side(const t_ray *r, const t_cylinder *cy, t_hit_record *rec);
t_bool		hit_cylinder_caps(const t_ray *r, const t_cylinder *cy, const t_plane *pl, t_hit_record *rec);

#endif