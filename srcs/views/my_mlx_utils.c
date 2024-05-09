/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_mlx_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljh <ljh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 20:08:48 by jeholee           #+#    #+#             */
/*   Updated: 2024/05/06 15:06:18 by ljh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	key_hook(int keycode, t_minirt *mini)
{
	if (keycode == 53)
	{
		mlx_destroy_window(mini->vars.mlx, mini->vars.win);
		exit(0);
	}
	else if (keycode == LEFT || keycode == RIGHT \
			|| keycode == UP || keycode == DOWN)
		camera_rotate(keycode, mini);
	else if (keycode == KEY_A || keycode == KEY_D \
			|| keycode == KEY_S || keycode == KEY_W)
		camera_move(keycode, mini);
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
