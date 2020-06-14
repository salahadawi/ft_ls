/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_digits.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 14:44:42 by sadawi            #+#    #+#             */
/*   Updated: 2020/06/14 15:38:12 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	print_file_links(t_ls *ls, t_file *file)
{
	char *format;

	format = ft_sprintf(" %%%dd", ls->links_width);
	ft_printf(format, file->stats.st_nlink);
	free(format);
}

void	print_file_size(t_ls *ls, t_file *file)
{
	char *format;

	format = ft_sprintf(" %%%dd", ls->size_width);
	ft_printf(format, file->stats.st_size);
	free(format);
}

void	print_file_date(t_file *file)
{
	char *format;

	format = format_time(ctime(&file->stats.st_mtime));
	ft_printf(" %s", format);
	free(format);
}

char	*format_time(char *time)
{
	char *formatted;

	formatted = ft_strsub(time, char_index(time, ' ') + 1,
	char_index(ft_strchr(time, ' ') + 1, ':') + 3);
	return (formatted);
}
