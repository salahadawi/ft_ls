/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mergesort_dir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/11 15:38:13 by sadawi            #+#    #+#             */
/*   Updated: 2020/04/13 14:53:25 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

t_dir	*sorted_merge_dir(t_ls *ls, t_dir *first_half, t_dir *second_half)
{
	if (ls->sort_mode == SORT_ALPHA)
		return (sorted_merge_alpha_dir(first_half, second_half));
	else if (ls->sort_mode == SORT_ALPHA_REV)
		return (sorted_merge_alpha_rev_dir(first_half, second_half));
	else if (ls->sort_mode == SORT_MOD_TIME)
		return (sorted_merge_mod_time_dir(first_half, second_half));
	else if (ls->sort_mode == SORT_MOD_TIME_REV)
		return (sorted_merge_mod_time_rev_dir(first_half, second_half));
	else if (ls->sort_mode == SORT_SIZE)
		return (sorted_merge_size_dir(first_half, second_half));
	else if (ls->sort_mode == SORT_SIZE_REV)
		return (sorted_merge_size_rev_dir(first_half, second_half));
	else
		handle_error(ft_strdup("Invalid sort mode"));
	return (NULL);
}

void	split_list_dir(t_dir *head, t_dir **first_half, t_dir **second_half)
{
	t_dir	*fast;
	t_dir	*slow;

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

void	mergesort_dir(t_ls *ls, t_dir **dirs)
{
	t_dir	*head;
	t_dir	*first_half;
	t_dir	*second_half;

	head = (*dirs);
	if (!head || !head->next)
		return ;
	split_list_dir(head, &first_half, &second_half);
	mergesort_dir(ls, &first_half);
	mergesort_dir(ls, &second_half);
	*dirs = sorted_merge_dir(ls, first_half, second_half);
}
