/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljh <ljh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:33:31 by ljh               #+#    #+#             */
/*   Updated: 2024/05/10 03:10:11 by ljh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	parse_cylinder(char **id_line, t_minirt *mi)
{
	t_cylinder	cy;

	if (get_arraysize(id_line) != 6)
		error_exit("Error\nInvalid plane elem count.\n");
	cy.center = atoxyz(id_line[1]);
	cy.axis = atoxyz(id_line[2]);
	if (is_normalized(cy.axis))
		error_exit("Error\nInvalid cylinder normalized cooridates.\n");
	if (!is_double(id_line[3]))
		error_exit("Error\nInvalid cylinder diameter.\n");
	cy.radius = atod(id_line[3], 0, 1, 1) / 2.0;
	if (cy.radius < 0.0)
		error_exit("Error\nInvalid cylinder diameter value.\n");
	if (!is_double(id_line[4]))
		error_exit("Error\nInvalid cylinder height.\n");
	cy.height = atod(id_line[4], 0, 1, 1);
	if (cy.height < 0.0)
		error_exit("Error\nInvalid cylinder height value.\n");
	cy.albedo = atorgb(id_line[5]);
	if (is_valid_rgb(cy.albedo))
		error_exit("Error\nInvalid cylinder rgb value.\n");
	obj_add(&mi->render.world, cylinder_gen(cy));
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
		error_exit(NULL);
	if (id[0] == NULL)
		error_exit("Error\nNot exist element in line.\n");
	parse_elem(id, mini);
	free_array(id);
}

void	file_parse(char *argv[], t_minirt *mini)
{
	int			len;
	int			fd;
	char		*line;

	len = ft_strlen(argv[1]);
	if (len < 4 \
		|| (ft_strncmp(&argv[1][len - 3], ".rt", 3) \
			|| argv[1][len - 4] == '/'))
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
