/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mergesort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/11 15:38:13 by sadawi            #+#    #+#             */
/*   Updated: 2020/04/11 19:55:37 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

t_file	*sorted_merge(t_ls *ls, t_file *first_half, t_file *second_half)
{
	if (ls->sort_mode == SORT_ALPHA)
		return (sorted_merge_alpha(first_half, second_half));
	else if (ls->sort_mode == SORT_ALPHA_REV)
		return (sorted_merge_alpha_rev(first_half, second_half));
	else if (ls->sort_mode == SORT_MOD_TIME)
		return (sorted_merge_mod_time(first_half, second_half));
	else if (ls->sort_mode == SORT_MOD_TIME_REV)
		return (sorted_merge_mod_time_rev(first_half, second_half));
	else
		handle_error("Invalid sort mode");
	return NULL;
}

void	split_list(t_file *head, t_file **first_half, t_file **second_half)
{
	t_file *fast;
	t_file *slow;

	slow = head;
	fast = head->next;
	while (fast)
	{
		fast = fast->next;
		if (fast)
		{
			slow = slow->next;
			fast = fast->next;
		}
	}
	*first_half = head;
	*second_half = slow->next;
	slow->next = NULL;
}

void	mergesort(t_ls *ls, t_file **files)
{
	t_file *head;
	t_file *first_half;
	t_file*second_half;

	head = (*files);
	if (!head || !head->next)
		return ;
	split_list(head, &first_half, &second_half);
	mergesort(ls, &first_half);
	mergesort(ls, &second_half);
	*files = sorted_merge(ls, first_half, second_half);
}
