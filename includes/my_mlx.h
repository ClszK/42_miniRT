/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_mlx.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeholee <jeholee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 17:48:43 by jeholee           #+#    #+#             */
/*   Updated: 2024/04/23 11:58:43 by jeholee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_MLX_H
# define MY_MLX_H

typedef struct s_minirt t_minirt;

typedef struct	s_vars {
	void		*mlx;
	void		*win;
}				t_vars;
//	이미지의 정보를 나타내는 변수를 저장한 구조체
typedef struct s_data
{
	void 	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}		t_data;

typedef t_vec3 t_color;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		key_hook(int keycode, t_minirt *mini);
t_color	color_init(double x, double y, double z);
int		rgb_to_int(const int t, const t_color *color);
t_vec3	rotate_y(t_vec3 v, double *angle);


#endif