/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_operator2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljh <ljh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 16:47:18 by jeholee           #+#    #+#             */
/*   Updated: 2024/04/28 19:48:01 by ljh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	vec3_mul_scal(const t_vec3 *vec, const double t)
{
	return (vec3_init(vec->x * t, \
					vec->y * t, \
					vec->z * t));
}

t_vec3	vec3_div_scal(const t_vec3 *vec, const double t)
{
	return (vec3_init(vec->x / t, \
					vec->y / t, \
					vec->z / t));
}

double	vec3_dot(const t_vec3 *u, const t_vec3 *v)
{
	return (u->x * v->x + \
			u->y * v->y + \
			u->z * v->z);
}

t_vec3	vec3_cross(const t_vec3 *u, const t_vec3 *v)
{
	return (vec3_init(u->y * v->z - u->z * v->y, \
						u->z * v->x - u->x * v->z, \
						u->x * v->y - u->y * v->x));
}
