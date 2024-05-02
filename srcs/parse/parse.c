/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljh <ljh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:33:31 by ljh               #+#    #+#             */
/*   Updated: 2024/05/02 21:54:14 by ljh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	error_exit(char *str)
{
	if (errno && str == NULL)
	{
		ft_putstr_fd("Error\n", STDERR_FILENO);
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		exit(errno);
	}
	ft_putstr_fd(str, STDERR_FILENO);
	exit(1);
}

t_bool	check_double(char *str)
{
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str) && !(*str == '.'))
			return (FALSE);
		str++;
	}
	if (*(str - 1) == '.')
		return (FALSE);
	return (TRUE);
}

int	get_arraysize(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	end_line(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		str[i] = '\0';
}

t_bool	is_int(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (TRUE);
		i++;
	}
	return (FALSE);
}

double	atod(char *str)
{
	double	result;
	double	sign;
	double	factor;

	result = 0.0;
	sign = 1.0;
	factor = 1.0;
	if (*(str) == '-' || *(str) == '+')
		if (*(str++) == '-')
			sign *= -1;
	while (*(str) >= '0' && *(str) <= '9')
	{
		result = result * 10 + (*(str) - '0');
		str++;
	}
	if (*str++ != '.')
		return (result * sign);
	while (*(str) >= '0' && *(str) <= '9')
	{
		factor *= 0.1;
		result = result + (*(str) - '0') * factor;
		str++;
	}
	return (result * sign);
}

void	free_array(char **str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

t_color	atorgb(char *str)
{
	t_color	rgb;
	char	**rgb_str;

	rgb_str = ft_split(str, ',');
	if (!rgb_str)
		error_exit("Error\nfail malloc\n");
	if (get_arraysize(rgb_str) != 3 || is_int(rgb_str[0]) \
		|| is_int(rgb_str[1]) || is_int(rgb_str[2]))
		error_exit("Error\ninvalid rgb value\n");
	rgb.x = atod(rgb_str[0]) / 255.0;
	rgb.y = atod(rgb_str[1]) / 255.0;
	rgb.z = atod(rgb_str[2]) / 255.0;
	free_array(rgb_str);
	return (rgb);
}	

t_bool	is_valid_rgb(t_color rgb)
{
	if (rgb.x < 0 || rgb.x > 1\
		|| rgb.y < 0 || rgb.y > 1\
		|| rgb.z < 0 || rgb.z > 1)
		return (TRUE);
	return (FALSE);
}

t_vec3	atoxyz(char *str)
{
	t_vec3	coordinate;
	char	**xyz_str;

	errno = 0;
	xyz_str = ft_split(str, ',');
	if (xyz_str == NULL && errno)
		error_exit(NULL);
	if (get_arraysize(xyz_str) != 3 \
		|| !check_double(xyz_str[0]) \
		|| !check_double(xyz_str[1]) \
		|| !check_double(xyz_str[2]))
		error_exit("Error\ninvalid xyz value\n");
	coordinate.x = atod(xyz_str[0]);
	coordinate.y = atod(xyz_str[1]);
	coordinate.z = atod(xyz_str[2]);
	free_array(xyz_str);
	return (coordinate);
}

void	parse_ambient(char **id_line, t_minirt *mi)
{
	double		ambient_ratio;
	t_color		rgb;

	if (mi->render.has_amb == TRUE)
		error_exit("Error\nMore than one ambient light.\n");
	if (get_arraysize(id_line) != 3)
		error_exit("Error\nInvalid ambient elem count.\n");
	errno = 0;
	if (!check_double(id_line[1]))
		error_exit("Error\ninvalid ambient lighting ratio value.\n");
	ambient_ratio = atod(id_line[1]);
	if (ambient_ratio < 0.0 || ambient_ratio > 1.0)
		error_exit("Error\ninvalid ambient lighting ratio value.\n");
	rgb = atorgb(id_line[2]);
	if (is_valid_rgb(rgb))
		error_exit("Error\ninvalid ambient rgb value.\n");
	mi->render.ambient = vec3_mul_scal(&rgb, ambient_ratio);
	mi->render.has_amb = TRUE;
}

t_bool	is_normalized(t_vec3 coordinate)
{
	if (vec3_length(&coordinate) != 1.0)
		return (TRUE);
	return (FALSE);
}

void	parse_camera(char **id_line, t_minirt *mi)
{
	t_camera	*cam;

	if (mi->camera != NULL)
		error_exit("Error\nMore than one camera.\n");
	if (get_arraysize(id_line) != 4)
		error_exit("Error\nInvalid camera elem count.\n");
	errno = 0;
	cam = malloc(sizeof(t_camera));
	if (cam == NULL && errno)
		error_exit(NULL);
	cam->center = atoxyz(id_line[1]);
	cam->cam_dir = atoxyz(id_line[2]);
	if (is_normalized(cam->cam_dir))
		error_exit("Error\ninvalid camera normed direction.\n");
	if (is_int(id_line[3]))
		error_exit("Error\ninvalid camera fov value.\n");
	cam->fov = atod(id_line[3]);
	if (cam->fov < 0 || cam->fov > 180)
		error_exit("Error\ninvalid camera fov value.\n");
	mi->camera = cam;
}

void	parse_light(char **id_line, t_minirt *mi)
{
	t_light	light;

	if (dlst_count(&mi->render.light) != 0)
		error_exit("Error\nMore than one light.\n");
	if (get_arraysize(id_line) != 3)
		error_exit("Error\nInvalid light elem count.\n");
	light.origin = atoxyz(id_line[1]);
	if (!check_double(id_line[2]))
		error_exit("Error\ninvalid light brightness ratio\n");
	light.bright_ratio = atod(id_line[2]);
	if (light.bright_ratio < 0.0 || light.bright_ratio > 1.0)
		error_exit("Error\ninvalid light brightness ratio\n");
	if (id_line[3])
	{
		light.light_color = atorgb(id_line[3]);
		if (is_valid_rgb(light.light_color))
			error_exit("Error\ninvalid light rgb value.\n");
	}
	else
		light.light_color = color_init(1, 1, 1);
	obj_add(&mi->render.light, light_gen(light.origin, light.light_color, \
											light.bright_ratio));
}

void	parse_sphere(char **id_line, t_minirt *mi)
{
	t_sphere	sph;

	if (get_arraysize(id_line) != 4)
		error_exit("Error\nInvalid sphere elem count.\n");
	sph.center = atoxyz(id_line[1]);
	if (!check_double(id_line[2]))
		error_exit("Error\ninvalid sphere diameter value\n");
	sph.radius = atod(id_line[2]) / 2.0;
	if (sph.radius <= 0) //확인하기
		error_exit("Error\ninvalid sphere diameter value\n");
	sph.albedo = atorgb(id_line[3]);
	if (is_valid_rgb(sph.albedo))
		error_exit("Error\ninvalid sphere rgb value.\n");
	obj_add(&mi->render.world, sphere_gen(sph.center, sph.radius, \
									sph.albedo));
}

void	parse_plane(char **id_line, t_minirt *mi)
{
	t_plane	pl;

	if (get_arraysize(id_line) != 4)
		error_exit("Error\nInvalid plane elem count.\n");
	pl.center = atoxyz(id_line[1]);
	pl.plane_norm = atoxyz(id_line[2]);
	if (is_normalized(pl.plane_norm))
		error_exit("Error\ninvalid plane normalized cooridates\n");
	pl.albedo = atorgb(id_line[3]);
	if (is_valid_rgb(pl.albedo))
		error_exit("Error\ninvalid plane rgb value\n");
	obj_add(&mi->render.world, plane_gen(pl.center, pl.plane_norm, \
										pl.albedo));
}

void	parse_cylinder(char **id_line, t_minirt *mi)
{
	t_cylinder	cy;
	
	if (get_arraysize(id_line) != 6)
		error_exit("Error\nInvalid plane elem count.\n");
	cy.center = atoxyz(id_line[1]);
	cy.axis = atoxyz(id_line[2]);
	if (is_normalized(cy.axis))
		error_exit("Error\ninvalid cylinder normalized cooridates\n");
	if (!check_double(id_line[3]))
		error_exit("Error\ninvalid cylinder diameter value\n");
	cy.radius = atod(id_line[3]) / 2.0;
	if (cy.radius < 0.0)
		error_exit("Error\ninvalid cylinder diameter value\n");
	if (!check_double(id_line[4]))
		error_exit("Error\ninvalid cylinder height value\n");
	cy.height = atod(id_line[4]);
	if (cy.height < 0.0)
		error_exit("Error\ninvalid cylinder height value\n");
	cy.albedo = atorgb(id_line[5]);
	if (is_valid_rgb(cy.albedo))
		error_exit("Error\ninvalid plane rgb value\n");
	obj_add(&mi->render.world, cylinder_gen(cy.center, cy.axis, cy.albedo, \
								cy.radius, cy.height));
}

/* t_minirt *mini에서 모든 요소들이 초기화되어 있어야함. */
void	parse_elem(char **id, t_minirt *mini)
{
	if (!ft_strncmp(id[0], "A", 2))
		parse_ambient(id, mini);
	else if (!ft_strncmp(id[0], "C", 2))
		parse_camera(id, mini);
	else if (!ft_strncmp(id[0], "L", 2))
		parse_light(id, mini);
	else if (!ft_strncmp(id[0], "pl", 3)) 
		parse_plane(id, mini);
	else if (!ft_strncmp(id[0], "sp", 3))
		parse_sphere(id, mini);
	else if (!ft_strncmp(id[0], "cy", 3)) 
		parse_cylinder(id, mini);
	else
		error_exit("Error\nInvalid rt file format.\n");
}

void	check_identifier(char *line, t_minirt *mini)
{
	char	**id;

	if (!ft_strncmp(line, "\n", 2))
		return ;
	end_line(line);
	errno = 0;
	id = ft_split(line, ' ');
	if (errno)
		error_exit("Error\nfail malloc.\n");
	parse_elem(id, mini);
	free_array(id);
}

void	file_parse(char *argv[], t_minirt *mini)
{
	int			len;
	int			fd;
	char		*line;

	len = ft_strlen(argv[1]);
	if (ft_strncmp(&argv[1][len - 3], ".rt", 3))
		error_exit("Error\nUsage: ./miniRT filename.rt\n");
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		error_exit("Error\nCannot open the file.\n");
	errno = 0;
	line = get_next_line(fd);
	if (line == NULL)
		error_exit("Error\nEmpty file.\n");
	while (line)
	{
		check_identifier(line, mini);
		free(line);
		line = get_next_line(fd);
	}
	if (errno)
		error_exit(NULL);
	close(fd);
}