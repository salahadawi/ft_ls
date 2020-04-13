/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_terminal_stats.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 14:38:23 by sadawi            #+#    #+#             */
/*   Updated: 2020/04/13 14:38:33 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	get_terminal_size(t_ls *ls)
{
	struct winsize w;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	ls->window_cols = w.ws_col;
	ls->window_rows = w.ws_row;
}
