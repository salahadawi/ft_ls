/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_row.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 14:33:46 by sadawi            #+#    #+#             */
/*   Updated: 2020/04/13 14:34:00 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int		check_row(t_ls *ls, t_file *files, int row[2])
{
	int	i;
	int	len;
	int padding;

	padding = padding_total(ls, files, row[1]);
	i = 0;
	len = 0;
	while (files)
	{
		if (i++ == row[0])
		{
			if (files->stats.st_mode)
				len += ft_strlen(files->name);
		}
		if (!files->stats.st_mode)
			i--;
		if (i == row[1])
			i = 0;
		files = files->next;
	}
	len += padding;
	len -= 2;
	if (padding > ls->window_cols)
		return (0);
	return (1);
}

int		check_rows_len(t_ls *ls, t_file *files, int row_amount)
{
	int padding;

	padding = padding_total(ls, files, row_amount);
	padding += count_files(ls, files) / row_amount * 2;
	if (padding > ls->window_cols)
		return (0);
	return (1);
}

int		count_rows(t_ls *ls, t_file *files)
{
	int		total_len;
	int		rows;
	t_file	*file_ptr;

	file_ptr = files;
	total_len = 0;
	while (files)
	{
		if (!((files->name[0] == '.' && !ft_strchr(ls->flags, 'a'))))
			total_len += ft_strlen(files->name) + 2;
		files = files->next;
	}
	total_len -= 2;
	rows = total_len / ls->window_cols + 1;
	while (!check_rows_len(ls, file_ptr, rows))
		rows++;
	return (rows);
}

void	print_file_row_format(t_file *files, int *col_pad, int *first, int col)
{
	char *format;

	if ((*first)-- > 0)
		format = ft_sprintf("%%-%ds", col_pad[col]);
	else
		format = ft_sprintf("  %%-%ds", col_pad[col]);
	print_color(files, format, files->name);
	free(format);
}

void	print_files_row(t_file *files, int row, int row_amount, int *col_pad)
{
	int		i;
	int		first;
	int		col;

	i = 0;
	col = 0;
	first = 1;
	while (files)
	{
		if (i++ == row)
		{
			if (files->stats.st_mode)
			{
				print_file_row_format(files, col_pad, &first, col);
				col++;
			}
		}
		if (!files->stats.st_mode)
			i--;
		if (i == row_amount)
			i = 0;
		files = files->next;
	}
}
