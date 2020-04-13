/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 13:24:25 by sadawi            #+#    #+#             */
/*   Updated: 2020/04/13 14:12:29 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	new_file(t_file **files, char *name)
{
	if (!*files)
	{
		*files = (t_file*)ft_memalloc(sizeof(t_file));
		(*files)->name = ft_strdup(name);
		(*files)->next = NULL;
		return ;
	}
	new_file(&(*files)->next, name);
}

void	new_dir(t_dir **dir, char *path)
{
	if (!*dir)
	{
		*dir = (t_dir*)ft_memalloc(sizeof(t_dir));
		(*dir)->path = ft_strdup(path);
		(*dir)->files = NULL;
		(*dir)->next = NULL;
		return ;
	}
	new_dir(&(*dir)->next, path);
}

void	init_ls(t_ls **ls, int *argc, char **argv)
{
	*ls = (t_ls*)ft_memalloc(sizeof(t_ls));
	(*ls)->flags = ft_strdup("-");
	(*ls)->files = NULL;
	(*ls)->sort_mode = SORT_ALPHA;
	(*ls)->links_width = 0;
	(*ls)->size_width = 0;
	(*ls)->files_amount = 0;
	(*ls)->dirs_amount = 0;
	(*ls)->files_dirs_amount = 0;
	argv++;
	get_terminal_size(*ls);
	save_options(*ls, argc, &argv);
	save_files(*ls, *argc, argv);
	sort_mode(*ls);
}
