/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_mlx_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljh <ljh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 21:03:16 by jeholee           #+#    #+#             */
/*   Updated: 2024/05/10 05:41:13 by ljh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	rotate_y(t_vec3 v, double *angle)
{
	double	rad;
	t_vec3	result;

	if (*angle > 360 || *angle < -360)
		*angle = 0;
	rad = (*angle) * M_PI / 180.0;
	result.x = cos(rad) * v.x + sin(rad) * v.z;
	result.y = v.y;
	result.z = -sin(rad) * v.x + cos(rad) * v.z;
	return (result);
}

t_vec3	rotate_x(t_vec3 v, double *angle)
{
	double	rad;
	t_vec3	result;

	if (*angle > 360 || *angle < -360)
		*angle = 0;
	rad = (*angle) * M_PI / 180.0;
	result.x = v.x;
	result.y = cos(rad) * v.y - sin(rad) * v.z;
	result.z = sin(rad) * v.y + cos(rad) * v.z;
	return (result);
}

void	camera_rotate(int keycode, t_minirt *mini)
{
	t_vec3	rotate_vec;

	if (keycode == LEFT)
		mini->yaw -= 10.0;
	else if (keycode == RIGHT)
		mini->yaw += 10.0;
	else if (keycode == UP && mini->pitch > -80)
		mini->pitch -= 10.0;
	else if (keycode == DOWN && mini->pitch < 80)
		mini->pitch += 10.0;
	rotate_vec = rotate_x(mini->start_dir, &mini->pitch);
	rotate_vec = rotate_y(rotate_vec, &mini->yaw);
	mini->camera->cam_dir = rotate_vec;
	camera_init(mini->canvas, mini->camera);
	mini->rendering = TRUE;
}

void	camera_move(int keycode, t_minirt *mini)
{
	if (keycode == KEY_W)
		mini->start_center = vec3_sub(&mini->start_center, \
										&mini->camera->cam_dir);
	else if (keycode == KEY_S)
		mini->start_center = vec3_add(&mini->start_center, \
										&mini->camera->cam_dir);
	else if (keycode == KEY_A)
		mini->start_center = vec3_sub(&mini->start_center, \
										&mini->camera->right);
	else if (keycode == KEY_D)
		mini->start_center = vec3_add(&mini->start_center, \
										&mini->camera->right);
	mini->camera->center = mini->start_center;
	camera_init(mini->canvas, mini->camera);
	mini->rendering = TRUE;
}
