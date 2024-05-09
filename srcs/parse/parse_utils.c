/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljh <ljh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 15:56:37 by ljh               #+#    #+#             */
/*   Updated: 2024/05/07 03:12 by ljh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_bool	is_double(char *str)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (str[i] == '.')
		return (FALSE);
	while (str[i])
	{
		if (str[i] == '.')
		{
			++cnt;
			++i;
		}
		if (!ft_isdigit(str[i]))
			return (FALSE);
		++i;
	}
	if (str[i] == '.' || cnt > 1)
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

double	atod(char *str, double result, double sign, double factor)
{
	int	digit_cnt;

	digit_cnt = 0;
	if (*(str) == '-' || *(str) == '+')
		if (*(str++) == '-')
			sign *= -1;
	while (*(str) >= '0' && *(str) <= '9')
	{
		result = result * 10 + (*(str++) - '0');
		digit_cnt++;
		if (digit_cnt > 10)
			error_exit("Error\nExceeded acceptable range.\n");
	}
	if (*str++ != '.')
		return (result * sign);
	while (*(str) >= '0' && *(str) <= '9')
	{
		factor *= 0.1;
		result = result + (*(str++) - '0') * factor;
		digit_cnt++;
		if (digit_cnt > 10)
			error_exit("Error\nExceeded acceptable range.\n");
	}
	return (result * sign);
}
