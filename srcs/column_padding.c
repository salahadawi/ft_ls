/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   column_padding.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 14:32:14 by sadawi            #+#    #+#             */
/*   Updated: 2020/07/09 21:57:02 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int		*calculate_padding(t_ls *ls, t_file *files, int row_amount)
{
	int file_amount;
	int	col_amount;
	int	*col_padding;
	int col;

	file_amount = count_files(ls, files);
	col_amount = count_cols(file_amount, row_amount);
	col_padding = (int*)ft_memalloc(sizeof(int) * (col_amount + 1));
	col = 0;
	while (col < col_amount)
	{
		col_padding[col] = get_col_padding(ls, files, col, row_amount);
		col++;
	}
	col_padding[col] = -1;
	return (col_padding);
}

int		count_cols(int file_amount, int row_amount)
{
	int cols;

	cols = 0;
	if (row_amount == 1)
		return (file_amount);
	while (file_amount > 0)
	{
		file_amount -= row_amount;
		cols++;
	}
	return (cols);
}

void	skip_cols(t_ls *ls, t_file **files, int cols, int row_amount)
{
	int i;

	while (cols-- > 0)
	{
		i = 0;
		while (i++ < row_amount && files)
		{
			if ((*files)->name[0] == '.' && !ft_strchr(ls->flags, 'a'))
				i--;
			*files = (*files)->next;
		}
	}
}

int		get_col_padding(t_ls *ls, t_file *files, int cols, int row_amount)
{
	int i;
	int	padding;
	int len;

	padding = 0;
	skip_cols(ls, &files, cols, row_amount);
	i = row_amount;
	while (i-- > 0 && files)
	{
		if (!((files->name[0] == '.' && !ft_strchr(ls->flags, 'a'))))
		{
			len = ft_strlen(files->name);
			if (len > padding)
				padding = len;
			files = files->next;
		}
		else
		{
			i++;
			files = files->next;
		}
	}
	return (padding);
}

int		padding_total(t_ls *ls, t_file *files, int row_amount)
{
	int total;
	int col;
	int *padding;

	padding = calculate_padding(ls, files, row_amount);
	col = 0;
	total = 0;
	while (padding[col] > 0)
		total += padding[col++];
	free(padding);
	return (total);
}
