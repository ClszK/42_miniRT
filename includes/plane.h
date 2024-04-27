/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeholee <jeholee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:26:42 by jeholee           #+#    #+#             */
/*   Updated: 2024/04/23 12:48:53 by jeholee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLANE_H
# define PLANE_H

# include "vec3.h"
# include "object.h"

typedef struct s_plane t_plane;

struct s_plane
{
	t_bool		(*hit)(const t_ray*, const t_plane*, t_hit_record*);
	t_point3	center;
	t_vec3		plane_norm;
	t_color		color;
	t_color		albedo;
	double		d;
	/* data */
};

t_plane	*plane_gen(t_point3 center, t_color col, t_vec3 norm, t_color albedo);
t_bool	hit_plane(const t_ray *r, const t_plane *plane, t_hit_record *rec);

#endif