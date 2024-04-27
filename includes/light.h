/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeholee <jeholee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 10:25:45 by jeholee           #+#    #+#             */
/*   Updated: 2024/04/27 18:56:54 by jeholee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
# define LIGHT_H

# define LUMEN 3

# include "vec3.h"
# include <stdlib.h>
# include <errno.h>

typedef t_vec3			t_color;
typedef struct s_render	t_render;
typedef struct s_lst	t_object;
typedef struct s_ray	t_ray;

typedef struct s_light
{
	t_point3		origin;
	t_color			light_color;
	double			bright_ratio;
}	t_light;

typedef struct s_ambient
{
	double	ambient_ratio;
	t_color	color;
}	t_ambient;

typedef struct s_light_info
{
	t_color		diffuse;	// diffuse의 강도와 빛의 양을 곱함
	t_color		specular;
	t_vec3		light_dir;
}	t_light_info;

t_light	*light_gen(t_point3 origin, t_color light_color, double bright_radio);
t_color	phong_lighting(t_render *render);
t_color	point_light_get(t_render *render, t_light *light);
t_bool	hard_shadow(t_light_info *info, t_render *render, t_light *light);

void	diffuse_cal(t_light_info *info, t_render *render, t_light *light);
void	specular_cal(t_light_info *info, t_render *render, t_light *light);
void	reflect(t_vec3 *v, const t_vec3 *n);
t_bool	in_shadow(t_object *objs, t_ray *light_ray, double light_len);
void	color_surround(t_color *light_color);

#endif