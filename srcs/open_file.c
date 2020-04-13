/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 14:39:19 by sadawi            #+#    #+#             */
/*   Updated: 2020/04/13 14:40:05 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	open_files(t_ls *ls)
{
	t_file	*file;
	t_dir	*dir;

	file = ls->files;
	while (file)
	{
		if (!((file->name[0] == '.' && !ft_strchr(ls->flags, 'a'))))
			save_stats(ls, file, NULL);
		file = file->next;
	}
	dir = ls->dirs;
	while (dir)
	{
		file = dir->files;
		while (file)
		{
			if (!((file->name[0] == '.' && !ft_strchr(ls->flags, 'a'))))
				save_stats(ls, file, dir->path);
			file = file->next;
		}
		if (!((dir->path[0] == '.' && !ft_strchr(ls->flags, 'a'))))
			save_stats_dir(ls, dir);
		dir = dir->next;
	}
}

void	save_files(t_ls *ls, int argc, char **argv)
{
	if (!argc)
	{
		add_dir(ls, &ls->dirs, ft_strdup("."));
		ls->dirs_amount++;
	}
	while (argc--)
	{
		if (check_if_dir(*argv))
		{
			add_dir(ls, &ls->dirs, ft_strdup(*argv++));
			ls->dirs_amount++;
		}
		else
		{
			new_file(&ls->files, *argv++);
			ls->files_amount++;
		}
		ls->files_dirs_amount++;
	}
}
