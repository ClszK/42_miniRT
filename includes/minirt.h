/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljh <ljh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 07:49:09 by jeholee           #+#    #+#             */
/*   Updated: 2024/05/09 21:12:49 by ljh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include "vec3.h"
# include "my_mlx.h"
# include "mlx.h"
# include "ray.h"
# include "scene.h"
# include "object.h"
# include "light.h"
# include "parse.h"

# define UP 126
# define DOWN 125
# define LEFT 123
# define RIGHT 124

# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2

typedef struct s_minirt
{
	t_camera	*camera;
	t_canvas	canvas;
	t_render	render;
	t_vars		vars;
	t_data		image;
	t_bool		rendering;
	double		yaw;
	double		pitch;
	t_vec3		start_dir;
	t_point3	start_center;
}	t_minirt;

void		mini_init(t_minirt *mi, char *argv[]);
int			re_render(t_minirt *mini);

#endif