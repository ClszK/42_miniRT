/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljh <ljh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 15:58:03 by ljh               #+#    #+#             */
/*   Updated: 2024/05/10 03:10:20 by ljh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

	if (elem_count(str, ',') != 2)
		error_exit("Error\nInvalid rgb format\n");
	errno = 0;
	rgb_str = ft_split(str, ',');
	if (!rgb_str)
		error_exit("Error\nfail malloc\n");
	if (get_arraysize(rgb_str) != 3 || is_int(rgb_str[0]) \
		|| is_int(rgb_str[1]) || is_int(rgb_str[2]))
		error_exit("Error\nInvalid rgb value\n");
	rgb.x = (double)ft_atoi(rgb_str[0]) / 255.0;
	rgb.y = (double)ft_atoi(rgb_str[1]) / 255.0;
	rgb.z = (double)ft_atoi(rgb_str[2]) / 255.0;
	free_array(rgb_str);
	return (rgb);
}

t_bool	is_valid_rgb(t_color rgb)
{
	if (rgb.x < 0 || rgb.x > 1 \
		|| rgb.y < 0 || rgb.y > 1 \
		|| rgb.z < 0 || rgb.z > 1)
		return (TRUE);
	return (FALSE);
}

t_vec3	atoxyz(char *str)
{
	t_vec3	coordinate;
	char	**xyz_str;

	if (elem_count(str, ',') != 2)
		error_exit("Error\nInvalid xyz format\n");
	errno = 0;
	xyz_str = ft_split(str, ',');
	if (xyz_str == NULL && errno)
		error_exit(NULL);
	if (get_arraysize(xyz_str) != 3 \
		|| !is_double(xyz_str[0]) \
		|| !is_double(xyz_str[1]) \
		|| !is_double(xyz_str[2]))
		error_exit("Error\nInvalid xyz value\n");
	coordinate.x = atod(xyz_str[0], 0, 1, 1);
	coordinate.y = atod(xyz_str[1], 0, 1, 1);
	coordinate.z = atod(xyz_str[2], 0, 1, 1);
	free_array(xyz_str);
	return (coordinate);
}

t_bool	is_normalized(t_vec3 coordinate)
{
	int	length;

	length = vec3_length(&coordinate) * 10000;
	if (length >= 9999 && length <= 10000)
		return (FALSE);
	return (TRUE);
}
