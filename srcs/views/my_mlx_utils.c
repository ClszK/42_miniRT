/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_mlx_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeholee <jeholee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 20:08:48 by jeholee           #+#    #+#             */
/*   Updated: 2024/04/25 13:44:26 by jeholee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec3 rotate_y(t_vec3 v, double *angle) {
    double rad; 
    t_vec3 result;

	if (*angle > 360 || *angle < -360)
		*angle = 0;
	rad = (*angle) * M_PI / 180.0;  // 각도를 라디안으로 변환
    result.x = cos(rad) * v.x + sin(rad) * v.z;
    result.y = v.y;
    result.z = -sin(rad) * v.x + cos(rad) * v.z;
    return result;
}

t_vec3 rotate_x(t_vec3 v, double *angle) {
    double rad;
    t_vec3 result;

	if (*angle > 360 || *angle < -360)
		*angle = 0;
	rad = (*angle) * M_PI / 180.0;  // 각도를 라디안으로 변환
    result.x = v.x;
    result.y = cos(rad) * v.y - sin(rad) * v.z;
    result.z = sin(rad) * v.y + cos(rad) * v.z;
    return result;
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	key_hook(int keycode, t_minirt *mini)
{
	t_vec3		rotate_vec;

	if(keycode == 53)
	{
		mlx_destroy_window(mini->vars.mlx, mini->vars.win);
		exit(0);
	} else if (keycode == LEFT || keycode == RIGHT || keycode == UP || keycode == DOWN)
	{
		if (keycode == LEFT)
			mini->yaw -= 10.0;
		else if (keycode == RIGHT)
			mini->yaw += 10.0;
		else if (keycode == UP && mini->pitch < 90)
			mini->pitch += 10.0;
		else if (keycode == DOWN && mini->pitch > -90)
			mini->pitch -= 10.0;
		else
			return (0);
		rotate_vec = rotate_x(mini->start_dir, &mini->pitch);
		rotate_vec = rotate_y(rotate_vec, &mini->yaw);
		mini->camera = camera_init(mini->canvas, mini->camera.center, rotate_vec);
		mini->rendering = TRUE;
	} else if (keycode == KEY_A || keycode == KEY_D || keycode == KEY_S || keycode == KEY_W)
	{
		if (keycode == KEY_W)
			mini->start_center = vec3_sub(&mini->start_center, &mini->camera.cam_dir);
		else if (keycode == KEY_S)
			mini->start_center = vec3_add(&mini->start_center, &mini->camera.cam_dir);
		else if (keycode == KEY_A)
			mini->start_center = vec3_sub(&mini->start_center, &mini->camera.right);
		else if (keycode == KEY_D)
			mini->start_center = vec3_add(&mini->start_center, &mini->camera.right);
		mini->camera = camera_init(mini->canvas, mini->start_center, mini->camera.cam_dir);
		mini->rendering = TRUE;
	}
	return (0);
}

t_color	color_init(double x, double y, double z)
{
	t_color	col;

	col.x = x;
	col.y = y;
	col.z = z;
	return (col);
}

int	rgb_to_int(const int t, const t_color *color)
{
	return (t << 24 | \
			(int)(255.999 * color->x) << 16 | \
			(int)(255.999 * color->y) << 8 | \
			(int)(255.999 * color->z));
}