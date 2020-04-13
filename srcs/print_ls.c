/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 14:43:06 by sadawi            #+#    #+#             */
/*   Updated: 2020/04/13 14:44:10 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	print_ls(t_ls *ls)
{
	t_file	*files_ptr;
	t_dir	*dir_ptr;
	int		i;

	files_ptr = ls->files;
	dir_ptr = ls->dirs;
	i = ls->dirs_amount - 1;
	if (ls->files_amount)
		print_files(ls, files_ptr, NULL);
	if (dir_ptr)
	{
		if (ls->files_amount)
			ft_printf("\n");
		while (dir_ptr)
		{
			if (ls->files_dirs_amount > 1)
				ft_printf("%s:\n", dir_ptr->path);
			if (ft_strchr(ls->flags, 'l'))
				count_total_blocks(dir_ptr);
			print_files(ls, dir_ptr->files, dir_ptr);
			if (ls->dirs_amount > 1 && i--)
				ft_printf("\n", dir_ptr->path);
			dir_ptr = dir_ptr->next;
		}
	}
}

void	print_files(t_ls *ls, t_file *files, t_dir *dir)
{
	if (ft_strchr(ls->flags, 'l'))
		print_l(ls, files, dir);
	else if (ft_strchr(ls->flags, 'x'))
		print_x(ls, files);
	else if (ft_strchr(ls->flags, '1'))
		print_one(ls, files);
	else if (ft_strchr(ls->flags, 'o'))
		print_o(ls, files, dir);
	else if (ft_strchr(ls->flags, 'g'))
		print_g(ls, files, dir);
	else
		print_basic(ls, files);
}

void	print_basic(t_ls *ls, t_file *files)
{
	int	row_amount;
	int	row;
	int	*col_padding;

	row_amount = count_rows(ls, files);
	col_padding = calculate_padding(ls, files, row_amount);
	row = 0;
	while (row < row_amount)
	{
		print_files_row(files, row++, row_amount, col_padding);
		ft_printf("\n");
	}
	free(col_padding);
}

void	print_color(t_file *file, char *format, char *str)
{
	if (S_ISDIR(file->stats.st_mode))
		ft_printf("\033[1;34m");
	if (!S_ISDIR(file->stats.st_mode) &&
		file->stats.st_mode & S_IXUSR)
		ft_printf("\033[1;32m");
	if (S_ISLNK(file->stats.st_mode))
		ft_printf("\033[1;31m");
	if (file->stats.st_mode & __S_ISUID || file->stats.st_mode & __S_ISGID)
		ft_printf("\033[0;31m");
	ft_printf(format, str);
	ft_printf("\033[0m");
}
