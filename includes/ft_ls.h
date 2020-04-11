/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 12:20:24 by sadawi            #+#    #+#             */
/*   Updated: 2020/04/11 19:33:48 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "../libft/includes/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <time.h>
# include <pwd.h>
# include <grp.h>

# define VALID_FLAGS "alrRt"

enum				e_sorting_mode
{
	SORT_ALPHA,
	SORT_ALPHA_REV,
	SORT_MOD_TIME,
	SORT_MOD_TIME_REV
};

typedef struct	s_file
{
	char			*name;
	struct s_file	*next;
	struct stat		stats;
}				t_file;

typedef struct	s_dir
{
	char			*path;
	t_file			*files;
	struct stat		stats;
	struct s_dir	*next;
}				t_dir;

typedef	struct	s_ls
{
	char		*flags;
	t_file		*files;
	t_dir		*dirs;
	int			files_dirs_amount;
	int			sort_mode;
	int			links_width;
	int			size_width;
}				t_ls;

void	handle_error(char *message);

int		char_index(char *str, char c);

void	new_file(t_file **files, char *name);

char	*format_time(char *time);

void	open_files(t_ls *ls);

void	add_dir(t_dir **dir, char *path);

int		ft_strcmp_case(const char *s1, const char *s2);

void	save_flag(t_ls *ls, char *flag);

void	save_options(t_ls *ls, int *argc, char ***argv);

void	sort_mode(t_ls *ls);

void	save_files(t_ls *ls, int argc, char **argv);

void	init_ls(t_ls **ls, int *argc, char **argv);

t_file	*sorted_merge(t_ls *ls, t_file *first_half, t_file *second_half);

void	split_list(t_file *head, t_file **first_half, t_file **second_half);

void	mergesort(t_ls *ls, t_file **files);

t_file	*sorted_merge_alpha(t_file *first_half, t_file *second_half);

t_file	*sorted_merge_alpha_rev(t_file *first_half, t_file *second_half);

#endif