/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeholee <jeholee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 23:57:30 by ljh               #+#    #+#             */
/*   Updated: 2024/04/17 11:43:03 by jeholee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "double_lst.h"

t_node	*dlst_node_generate(void *element)
{
	t_node	*node;

	errno = 0;
	node = (t_node *)malloc(sizeof(t_node));
	if (node == NULL)
		exit(errno);
	node->elem = element;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

int	dlst_init(struct s_lst *lst)
{
	if (lst == NULL)
		return (1);
	lst->head = dlst_node_generate(NULL);
	lst->tail = dlst_node_generate(NULL);
	lst->head->next = lst->tail;
	lst->tail->prev = lst->head;
	return (0);
}

int	dlst_add_last(struct s_lst *lst, void *element)
{
	t_node	*node;

	node = dlst_node_generate(element);
	lst->tail->prev->next = node;
	node->prev = lst->tail->prev;
	node->next = lst->tail;
	lst->tail->prev = node;
	return (0);
}

void	dlst_del_last(struct s_lst *lst, void (*del)(void*))
{
	t_node	*del_node_prev;

	del_node_prev = lst->tail->prev->prev;
	del(del_node_prev->next->elem);
	free(del_node_prev->next);
	del_node_prev->next = lst->tail;
	lst->tail->prev = del_node_prev;
}

void	dlst_del_all(struct s_lst *lst, void (*del)(void*))
{
	t_node	*node;
	t_node	*next;

	node = lst->head;
	while (node)
	{
		if (node->elem && del)
			del(node->elem);
		next = node->next;
		free(node);
		node = next;
	}
}
