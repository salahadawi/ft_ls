/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 13:11:14 by sadawi            #+#    #+#             */
/*   Updated: 2020/04/13 14:49:37 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int		main(int argc, char **argv)
{
	t_ls	*ls;

	init_ls(&ls, &argc, argv);
	open_files(ls);
	sort_files(ls);
	print_ls(ls);
	free_ls(ls);
	return (0);
}
