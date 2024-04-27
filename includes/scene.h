/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeholee <jeholee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 04:18:28 by jeholee           #+#    #+#             */
/*   Updated: 2024/04/27 21:10:44 by jeholee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "vec3.h"
# include "object.h"
# include "light.h"

typedef struct s_camera
{
	t_point3	center;
	t_point3	pixel00;
	t_vec3		delta_u;
	t_vec3		delta_v;
	t_vec3		cam_dir;
	t_color		ambient;
	t_vec3		viewport_u;
	t_vec3		viewport_v;
	t_vec3		right;
}	t_camera;

typedef struct s_canvas
{
	double		aspect_ratio;
	int			image_width;
	int			image_height;
	int			fov;
	double		focal_length;
	double		viewport_width;
	double		viewport_height;
	t_vec3		world_up;
}	t_canvas;

typedef struct s_render
{
	t_vec3			pixel_center;
	t_color			color;
	t_object		world;
	t_object		light;
	t_ambient		ambient_after;
	t_color			ambient;
	t_hit_record	rec;
	t_ray			ray;
}	t_render;

t_canvas	canvas_init(int width, int height, int fov); 
t_camera	camera_init(t_canvas cvs, t_point3 center, t_vec3 cam_dir);
void		render(t_canvas cvs, t_camera cm, t_data *img);
t_render	render_init(void);
double		degrees_to_radians(double degrees);

#endif