/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeholee <jeholee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 02:35:45 by jeholee           #+#    #+#             */
/*   Updated: 2024/04/25 17:10:58 by jeholee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHERE_H
# define SPHERE_H

# include "object.h"

typedef struct s_sphere t_sphere;

struct s_sphere
{
	t_bool		(*hit)(const t_ray*, const t_sphere*, t_hit_record*);
	t_point3	center;
	double		radius;
	t_color		color;
	t_color		albedo;	//반사율
};

t_sphere	*sphere_gen(const t_point3 center, const t_color col, double r, \
													const t_color albedo);
t_bool		hit_sphere(const t_ray *r, const t_sphere *sphere, t_hit_record *rec);

#endif