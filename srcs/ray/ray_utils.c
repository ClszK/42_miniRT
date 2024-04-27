/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeholee <jeholee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 21:11:30 by jeholee           #+#    #+#             */
/*   Updated: 2024/04/27 21:30:17 by jeholee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"

void	ray_init(t_ray *r, const t_point3 *p, const t_vec3 *d)
{
	r->orig = *p;
	r->dir = *d;
}

t_point3	at(double t, const t_ray *ray)
{
	t_vec3	tmp;

	tmp.x = t * ray->dir.x + ray->orig.x;
	tmp.y = t * ray->dir.y + ray->orig.y;
	tmp.z = t * ray->dir.z + ray->orig.z;
	return (tmp);
}
