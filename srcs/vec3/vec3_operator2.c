/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_operator2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeholee <jeholee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 16:47:18 by jeholee           #+#    #+#             */
/*   Updated: 2024/04/21 08:41:07 by jeholee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec3	vec3_mul_scal(const t_vec3 *vec, const double t)
{
	t_vec3	tmp;

	tmp.x = vec->x * t;
	tmp.y = vec->y * t;
	tmp.z = vec->z * t;
	return (tmp);
}

t_vec3	vec3_div_scal(const t_vec3 *vec, const double t)
{
	return (vec3_mul_scal(vec, 1 / t));
}

double	vec3_dot(const t_vec3 *u, const t_vec3 *v)
{
	return (u->x * v->x + \
			u->y * v->y + \
			u->z * v->z);
}

t_vec3	vec3_cross(const t_vec3 *u, const t_vec3 *v)
{
	t_vec3	tmp;

	tmp.x = u->y * v->z - u->z * v->y;
	tmp.y = u->z * v->x - u->x * v->z;
	tmp.x = u->x * v->y - u->y * v->x;
	return (tmp);
}
