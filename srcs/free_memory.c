/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 13:25:40 by sadawi            #+#    #+#             */
/*   Updated: 2020/04/13 13:26:07 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	free_ls(t_ls *ls)
{
	free(ls->flags);
	free_files(ls->files);
	free_dirs(ls->dirs);
	free(ls);
}

void	free_files(t_file *files)
{
	t_file *tmp;

	while (files)
	{
		tmp = files->next;
		free(files->name);
		free(files);
		files = tmp;
	}
}

void	free_dirs(t_dir *dirs)
{
	t_dir *tmp;

	while (dirs)
	{
		tmp = dirs->next;
		free_files(dirs->files);
		free(dirs->path);
		free(dirs);
		dirs = tmp;
	}
}
