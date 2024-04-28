/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_operator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljh <ljh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 16:21:06 by jeholee           #+#    #+#             */
/*   Updated: 2024/04/28 19:48:12 by ljh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	vec3_add(const t_vec3 *a, const t_vec3 *b)
{
	t_vec3	tmp;

	tmp.x = a->x + b->x;
	tmp.y = a->y + b->y;
	tmp.z = a->z + b->z;
	return (tmp);
}

t_vec3	vec3_sub(const t_vec3 *a, const t_vec3 *b)
{
	t_vec3	tmp;

	tmp.x = a->x - b->x;
	tmp.y = a->y - b->y;
	tmp.z = a->z - b->z;
	return (tmp);
}

t_vec3	vec3_mul(const t_vec3 *a, const t_vec3 *b)
{
	t_vec3	tmp;

	tmp.x = a->x * b->x;
	tmp.y = a->y * b->y;
	tmp.z = a->z * b->z;
	return (tmp);
}

t_vec3	vec3_div(const t_vec3 *a, const t_vec3 *b)
{
	t_vec3	tmp;

	tmp.x = a->x / b->x;
	tmp.y = a->y / b->y;
	tmp.z = a->z / b->z;
	return (tmp);
}
