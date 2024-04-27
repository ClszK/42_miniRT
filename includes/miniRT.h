/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeholee <jeholee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 07:49:09 by jeholee           #+#    #+#             */
/*   Updated: 2024/04/27 18:39:27 by jeholee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <unistd.h>
# include "vec3.h"
# include "my_mlx.h"
# include "mlx.h"
# include "ray.h"
# include "camera.h"

# define UP 126
# define DOWN 125
# define LEFT 123
# define RIGHT 124

# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2


typedef int t_bool;

typedef struct s_minirt
{
	t_vars		vars;
	t_data		image;
	t_canvas	canvas;
	t_camera	camera;
	t_bool		rendering;
	double		yaw;
	double		pitch;
	t_vec3		start_dir;
	t_point3	start_center;
}	t_minirt;

t_minirt	mini_init(void);

#endif