/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_algorithms_dir.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/11 15:37:31 by sadawi            #+#    #+#             */
/*   Updated: 2020/04/11 21:05:16 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

t_dir	*sorted_merge_alpha_dir(t_dir *first_half, t_dir *second_half)
{
	t_dir *sorted;

	if (!first_half)
		return (second_half);
	if (!second_half)
		return (first_half);
	if (ft_strcmp_case(first_half->path, second_half->path) < 0)
	{
		sorted = first_half;
		sorted->next = sorted_merge_alpha_dir(first_half->next, second_half);
	}
	else
	{
		sorted = second_half;
		sorted->next = sorted_merge_alpha_dir(first_half, second_half->next);
	}
	return (sorted);
}

t_dir	*sorted_merge_alpha_rev_dir(t_dir *first_half, t_dir *second_half)
{
	t_dir *sorted;

	if (!first_half)
		return (second_half);
	if (!second_half)
		return (first_half);
	if (ft_strcmp_case(first_half->path, second_half->path) > 0)
	{
		sorted = first_half;
		sorted->next = sorted_merge_alpha_rev_dir(first_half->next,
		second_half);
	}
	else
	{
		sorted = second_half;
		sorted->next = sorted_merge_alpha_rev_dir(first_half,
		second_half->next);
	}
	return (sorted);
}

t_dir	*sorted_merge_mod_time_dir(t_dir *first_half, t_dir *second_half)
{
	t_dir *sorted;

	if (!first_half)
		return (second_half);
	if (!second_half)
		return (first_half);
	if (first_half->stats.st_mtime > second_half->stats.st_mtime)
	{
		sorted = first_half;
		sorted->next = sorted_merge_mod_time_dir(first_half->next, second_half);
	}
	else
	{
		sorted = second_half;
		sorted->next = sorted_merge_mod_time_dir(first_half, second_half->next);
	}
	return (sorted);
}

t_dir	*sorted_merge_mod_time_rev_dir(t_dir *first_half, t_dir *second_half)
{
	t_dir *sorted;

	if (!first_half)
		return (second_half);
	if (!second_half)
		return (first_half);
	if (first_half->stats.st_mtime <= second_half->stats.st_mtime)
	{
		sorted = first_half;
		sorted->next = sorted_merge_mod_time_rev_dir(first_half->next,
		second_half);
	}
	else
	{
		sorted = second_half;
		sorted->next = sorted_merge_mod_time_rev_dir(first_half,
		second_half->next);
	}
	return (sorted);
}