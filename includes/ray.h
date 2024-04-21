/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeholee <jeholee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 21:07:04 by jeholee           #+#    #+#             */
/*   Updated: 2024/04/21 08:44:28 by jeholee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "vec3.h"

typedef struct s_ray
{
	t_point3	orig;
	t_vec3		dir;
}	t_ray;

void		ray_init(t_ray *r, const t_point3 *p, const t_vec3 *d);
t_point3	at(double t, const t_ray *ray); // P(t) = A + t * b

#endif