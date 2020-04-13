/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_options.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 14:35:57 by sadawi            #+#    #+#             */
/*   Updated: 2020/04/13 14:36:07 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	save_flag(t_ls *ls, char *flag)
{
	int i;

	i = 1;
	while (flag[i])
	{
		if (!(ft_strchr(VALID_FLAGS, flag[i])))
			handle_error(ft_sprintf("invalid option -- '%c'", flag[i]));
		ls->flags = join_char_to_str(ls->flags, flag[i++]);
	}
}

void	save_options(t_ls *ls, int *argc, char ***argv)
{
	*argc -= 1;
	while (*argc)
	{
		if (**argv[0] != '-' || ft_strlen(**argv) < 2)
			return ;
		save_flag(ls, *(*argv)++);
		*argc -= 1;
	}
}
