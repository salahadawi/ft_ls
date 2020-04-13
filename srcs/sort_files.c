/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 14:40:57 by sadawi            #+#    #+#             */
/*   Updated: 2020/04/13 14:41:18 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	sort_mode(t_ls *ls)
{
	if (!ls->flags)
		return ;
	if (ft_strchr(ls->flags, 't'))
		ls->sort_mode = SORT_MOD_TIME;
	else if (ft_strchr(ls->flags, 'S'))
		ls->sort_mode = SORT_SIZE;
	if (ft_strchr(ls->flags, 'r'))
		ls->sort_mode++;
}

void	sort_files(t_ls *ls)
{
	t_dir *dir;

	mergesort(ls, &ls->files);
	mergesort_dir(ls, &ls->dirs);
	dir = ls->dirs;
	while (dir)
	{
		mergesort(ls, &dir->files);
		dir = dir->next;
	}
}
