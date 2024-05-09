/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljh <ljh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 00:40:31 by jeholee           #+#    #+#             */
/*   Updated: 2024/05/06 16:36:01 by ljh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*uc_dst;
	unsigned char	*uc_src;
	int				sign;

	sign = 1;
	uc_dst = (unsigned char *)dst;
	uc_src = (unsigned char *)src;
	if (dst == NULL && src == NULL)
		return (NULL);
	if (src < dst)
	{
		uc_dst += len - 1;
		uc_src += len - 1;
		sign = -1;
	}
	while ((len--) > 0)
	{
		*(uc_dst) = *(uc_src);
		uc_dst += sign;
		uc_src += sign;
	}
	return (dst);
}
