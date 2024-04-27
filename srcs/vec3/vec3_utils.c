/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeholee <jeholee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 16:23:53 by jeholee           #+#    #+#             */
/*   Updated: 2024/04/27 21:15:27 by jeholee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	vec3_init(double x, double y, double z)
{
	t_vec3	tmp;

	tmp.x = x;
	tmp.y = y;
	tmp.z = z;
	return (tmp);
}

t_point3	point3_init(double x, double y, double z)
{
	t_point3	tmp;

	tmp.x = x;
	tmp.y = y;
	tmp.z = z;
	return (tmp);
}

double	vec3_length(const t_vec3 *vec)
{
	return (sqrt(vec->x * vec->x + \
				vec->y * vec->y + \
				vec->z * vec->z));
}

t_vec3	vec3_unit(const t_vec3 v)
{
	return (vec3_div_scal(&v, vec3_length(&v)));
}
