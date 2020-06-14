/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_stats.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 14:45:43 by sadawi            #+#    #+#             */
/*   Updated: 2020/06/14 16:14:34 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	print_file_type(t_file *file)
{
	if (S_ISLNK(file->stats.st_mode))
		ft_printf("l");
	else
		ft_printf((S_ISDIR(file->stats.st_mode)) ? "d" : "-");
}

void	print_file_permissions(t_ls *ls, t_file *file, t_dir *dir)
{
	char *full_filepath;

	ft_printf((file->stats.st_mode & S_IRUSR) ? "r" : "-");
	ft_printf((file->stats.st_mode & S_IWUSR) ? "w" : "-");
	if (file->stats.st_mode & __S_ISUID)
		ft_printf((file->stats.st_mode & S_IXUSR) ? "s" : "S");
	else
		ft_printf((file->stats.st_mode & S_IXUSR) ? "x" : "-");
	ft_printf((file->stats.st_mode & S_IRGRP) ? "r" : "-");
	ft_printf((file->stats.st_mode & S_IWGRP) ? "w" : "-");
	if (file->stats.st_mode & __S_ISGID)
		ft_printf((file->stats.st_mode & S_IXGRP) ? "s" : "S");
	else
		ft_printf((file->stats.st_mode & S_IXGRP) ? "x" : "-");
	ft_printf((file->stats.st_mode & S_IROTH) ? "r" : "-");
	ft_printf((file->stats.st_mode & S_IWOTH) ? "w" : "-");
	if (file->stats.st_mode & __S_ISVTX)
		ft_printf("T");
	else
		ft_printf((file->stats.st_mode & S_IXOTH) ? "x" : "-");
	full_filepath = dir ? ft_strjoindir(dir->path, file->name)
	: ft_strdup(file->name);
	if (ls->acl_found)
		ft_printf((llistxattr(full_filepath, NULL, 0) > 0) ? "+" : " ");
	free(full_filepath);
}

void	print_symbolic_link(t_file *file, t_dir *dir)
{
	char *format;
	char *filepath;

	if (S_ISLNK(file->stats.st_mode))
	{
		format = (char*)ft_memalloc(1000);
		if (dir)
			filepath = ft_strjoindir(dir->path, file->name);
		else
			filepath = file->name;
		if (readlink(filepath, format, 999) != -1)
		{
			ft_printf(" -> ");
			print_color(file, "%s", format);
		}
		free(format);
		free(filepath);
	}
}
