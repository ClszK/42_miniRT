/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_mlx.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljh <ljh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 17:48:43 by jeholee           #+#    #+#             */
/*   Updated: 2024/04/28 19:56:00 by ljh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_MLX_H
# define MY_MLX_H

# include "vec3.h"

typedef struct s_minirt	t_minirt;
typedef t_vec3			t_color;

typedef struct s_vars {
	void		*mlx;
	void		*win;
}				t_vars;
//	이미지의 정보를 나타내는 변수를 저장한 구조체
typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}		t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		key_hook(int keycode, t_minirt *mini);
t_color	color_init(double x, double y, double z);
int		rgb_to_int(const int t, const t_color *color);

void	camera_rotate(int keycode, t_minirt *mini);
void	camera_move(int keycode, t_minirt *mini);
t_vec3	rotate_x(t_vec3 v, double *angle);
t_vec3	rotate_y(t_vec3 v, double *angle);

#endif