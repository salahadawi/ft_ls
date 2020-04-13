/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 14:37:00 by sadawi            #+#    #+#             */
/*   Updated: 2020/04/13 20:02:55 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

DIR		*open_dir(t_ls *ls, char *path)
{
	DIR *p_dir;

	if (!(p_dir = opendir(path)))
	{
		ft_fprintf(2, "ft_ls: cannot open directory '%s': Permission denied\n",
		path);
		free(path);
		ls->dirs_amount--;
		ls->files_dirs_amount--;
		return (NULL);
	}
	return (p_dir);
}

int		check_dir_recursive(t_ls *ls, char *name, char *filepath)
{
	if (ft_strchr(ls->flags, 'R') && check_if_dir(filepath))
		if (!((name[0] == '.' && !ft_strchr(ls->flags, 'a'))))
			if (!ft_strequ(name, "..") && !ft_strequ(name, "."))
				return (1);
	return (0);
}

void	add_dir(t_ls *ls, t_dir **dir, char *path)
{
	struct dirent	*p_dirent;
	DIR				*p_dir;
	t_dir			*dir_ptr;
	char			*filepath;

	if (!(p_dir = open_dir(ls, path)))
		return ;
	new_dir(dir, path);
	dir_ptr = *dir;
	while (dir_ptr->next)
		dir_ptr = dir_ptr->next;
	while ((p_dirent = readdir(p_dir)))
	{
		new_file(&dir_ptr->files, p_dirent->d_name);
		filepath = ft_strjoindir(path, p_dirent->d_name);
		if (check_dir_recursive(ls, p_dirent->d_name, filepath))
		{
			add_dir(ls, &dir_ptr, ft_strdup(filepath));
			ls->dirs_amount++;
			ls->files_dirs_amount++;
		}
		free(filepath);
	}
	free(path);
	closedir(p_dir);
}

int		check_if_dir(char *path)
{
	struct stat		stats;

	if (lstat(path, &stats) != 0)
		return (0);
	if (S_ISDIR(stats.st_mode))
		return (1);
	return (0);
}
