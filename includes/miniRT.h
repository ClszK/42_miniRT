/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeholee <jeholee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 07:49:09 by jeholee           #+#    #+#             */
/*   Updated: 2024/04/23 04:16:23 by jeholee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <unistd.h>
# include "vec3.h"
# include "my_mlx.h"
# include "mlx.h"
# include "ray.h"
# include "sphere.h"
# include "camera.h"

#define	UP          126
#define	DOWN        125
#define	LEFT        123
#define	RIGHT       124

typedef int t_bool;

typedef struct s_minirt
{
	t_vars		vars;
	t_data		image;
	t_canvas	canvas;
	t_camera	camera;
	t_bool		rendering;
}	t_minirt;

t_minirt	mini_init(void);

#endif