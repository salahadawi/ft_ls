/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_algorithms_rev.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 14:55:03 by sadawi            #+#    #+#             */
/*   Updated: 2020/06/14 17:28:02 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

t_file	*sorted_merge_alpha_rev(t_file *first_half, t_file *second_half)
{
	t_file *sorted;

	if (!first_half)
		return (second_half);
	if (!second_half)
		return (first_half);
	if (ft_strcmp_case(first_half->name, second_half->name) > 0)
	{
		sorted = first_half;
		sorted->next = sorted_merge_alpha_rev(first_half->next, second_half);
	}
	else
	{
		sorted = second_half;
		sorted->next = sorted_merge_alpha_rev(first_half, second_half->next);
	}
	return (sorted);
}

t_file	*sorted_merge_mod_time_rev(t_file *first_half, t_file *second_half)
{
	t_file *sorted;

	if (!first_half)
		return (second_half);
	if (!second_half)
		return (first_half);
	if (first_half->stats.st_mtime < second_half->stats.st_mtime ||
		(first_half->stats.st_mtime == second_half->stats.st_mtime &&
		first_half->stats.st_mtim.tv_nsec < second_half->stats.st_mtim.tv_nsec)
		|| (first_half->stats.st_mtime == second_half->stats.st_mtime &&
		first_half->stats.st_mtim.tv_nsec == second_half->stats.st_mtim.tv_nsec
		&& ft_strcmp_case(first_half->name, second_half->name) > 0))
	{
		sorted = first_half;
		sorted->next = sorted_merge_mod_time_rev(first_half->next, second_half);
	}
	else
	{
		sorted = second_half;
		sorted->next = sorted_merge_mod_time_rev(first_half, second_half->next);
	}
	return (sorted);
}

t_file	*sorted_merge_size_rev(t_file *first_half, t_file *second_half)
{
	t_file *sorted;

	if (!first_half)
		return (second_half);
	if (!second_half)
		return (first_half);
	if (first_half->stats.st_size < second_half->stats.st_size ||
		(first_half->stats.st_size == second_half->stats.st_size &&
		ft_strcmp_case_basename(first_half->name, second_half->name, 0) > 0))
	{
		sorted = first_half;
		sorted->next = sorted_merge_size_rev(first_half->next, second_half);
	}
	else
	{
		sorted = second_half;
		sorted->next = sorted_merge_size_rev(first_half, second_half->next);
	}
	return (sorted);
}
