/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_modes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 14:42:29 by sadawi            #+#    #+#             */
/*   Updated: 2020/06/14 12:46:37 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	print_l(t_ls *ls, t_file *files, t_dir *dir)
{
	while (files)
	{
		if (files->stats.st_mode)
		{
			print_file_type(files);
			print_file_permissions(files);
			print_file_links(ls, files);
			if (!ft_strchr(ls->flags, 'g'))
				ft_printf(" %s", getpwuid(files->stats.st_uid)->pw_name);
			if (!ft_strchr(ls->flags, 'o'))
				ft_printf(" %s", getgrgid(files->stats.st_gid)->gr_name);
			print_file_size(ls, files);
			print_file_date(files);
			print_color(files, " %s", files->name);
			print_symbolic_link(files, dir);
			ft_printf("\n");
		}
		files = files->next;
	}
}

void	print_o(t_ls *ls, t_file *files, t_dir *dir)
{
	while (files)
	{
		if (files->stats.st_mode)
		{
			print_file_type(files);
			print_file_permissions(files);
			print_file_links(ls, files);
			ft_printf(" %s", getpwuid(files->stats.st_uid)->pw_name);
			print_file_size(ls, files);
			print_file_date(files);
			print_color(files, " %s", files->name);
			print_symbolic_link(files, dir);
			ft_printf("\n");
		}
		files = files->next;
	}
}

void	print_g(t_ls *ls, t_file *files, t_dir *dir)
{
	while (files)
	{
		if (files->stats.st_mode)
		{
			print_file_type(files);
			print_file_permissions(files);
			print_file_links(ls, files);
			ft_printf(" %s", getgrgid(files->stats.st_gid)->gr_name);
			print_file_size(ls, files);
			print_file_date(files);
			print_color(files, " %s", files->name);
			print_symbolic_link(files, dir);
			ft_printf("\n");
		}
		files = files->next;
	}
}

void	print_x(t_ls *ls, t_file *files)
{
	(void)ls;
	while (files)
	{
		if (files->stats.st_mode)
			print_color(files, "%s  ", files->name);
		files = files->next;
	}
	ft_printf("\n");
}

void	print_one(t_ls *ls, t_file *files)
{
	(void)ls;
	while (files)
	{
		if (files->stats.st_mode)
			print_color(files, "%s\n", files->name);
		files = files->next;
	}
}
