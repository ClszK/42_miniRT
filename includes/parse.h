/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljh <ljh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 18:59:50 by ljh               #+#    #+#             */
/*   Updated: 2024/05/02 19:56:48 by ljh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

typedef struct s_minirt	t_minirt;
typedef int				t_bool;
typedef struct s_vec3	t_vec3;
typedef	struct s_vec3	t_color;

void	error_exit(char *str);
t_bool	check_double(char *str);
int		get_arraysize(char **str);
void	end_line(char *str);
t_bool	is_int(char *str);

double	atod(char *str);
void	free_array(char **str);
t_color	atorgb(char *str);
t_bool	is_valid_rgb(t_color rgb);
t_vec3	atoxyz(char *str);

t_bool	is_normalized(t_vec3 coordinate);
void	parse_ambient(char **id_line, t_minirt *mi);
void	parse_camera(char **id_line, t_minirt *mi);
void	parse_light(char **id_line, t_minirt *mi);
void	parse_sphere(char **id_line, t_minirt *mi);

void	parse_plane(char **id_line, t_minirt *mi);
void	parse_cylinder(char **id_line, t_minirt *mi);
void	parse_elem(char **id, t_minirt *mini);
void	check_identifier(char *line, t_minirt *mini);
void	file_parse(char *argv[], t_minirt *mini);

#endif