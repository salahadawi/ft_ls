/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_stats.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 13:27:26 by sadawi            #+#    #+#             */
/*   Updated: 2020/04/13 14:42:05 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	save_stats(t_ls *ls, t_file *current, char *path)
{
	char *filename;

	if (path)
		filename = ft_strjoindir(path, current->name);
	else
		filename = ft_strdup(current->name);
	if (lstat(filename, &current->stats) < 0)
	{
		ft_fprintf(2,
		"ft_ls: cannot access '%s': No such file or directory\n",
		filename);
		ls->files_amount--;
	}
	update_max_width(ls, current->stats);
	free(filename);
}

void	save_stats_dir(t_ls *ls, t_dir *current)
{
	if (lstat(current->path, &current->stats) < 0)
	{
		ft_fprintf(2,
		"ft_ls: cannot access '%s': No such file or directory\n",
		current->path);
	}
	update_max_width(ls, current->stats);
}

void	update_max_width(t_ls *ls, struct stat stats)
{
	int len;

	len = nbrlen(stats.st_nlink);
	if (len > ls->links_width)
		ls->links_width = len;
	len = nbrlen(stats.st_size);
	if (len > ls->size_width)
		ls->size_width = len;
}

void	count_total_blocks(t_dir *dir)
{
	t_file			*file;
	unsigned int	total;

	total = 0;
	file = dir->files;
	while (file)
	{
		total += file->stats.st_blocks;
		file = file->next;
	}
	ft_printf("total %u\n", total / 2);
}

int		count_files(t_ls *ls, t_file *files)
{
	int files_amount;

	files_amount = 0;
	while (files)
	{
		if (!((files->name[0] == '.' && !ft_strchr(ls->flags, 'a'))))
			files_amount++;
		files = files->next;
	}
	return (files_amount);
}
