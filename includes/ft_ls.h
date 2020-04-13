/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 12:20:24 by sadawi            #+#    #+#             */
/*   Updated: 2020/04/13 12:04:21 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "../libft/includes/libft.h"
# include <sys/types.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <dirent.h>
# include <stdio.h>
# include <time.h>
# include <pwd.h>
# include <grp.h>

# define VALID_FLAGS "alrRtx1"

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
	int			dirs_amount;
	int			files_amount;
	int			files_dirs_amount;
	int			sort_mode;
	int			links_width;
	int			size_width;
	int			window_cols;
	int			window_rows;
}				t_ls;

void	handle_error(char *message);

int		char_index(char *str, char c);

void	new_file(t_file **files, char *name);

char	*format_time(char *time);

void	open_files(t_ls *ls);

void	add_dir(t_ls *ls, t_dir **dir, char *path);

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

t_file	*sorted_merge_mod_time(t_file *first_half, t_file *second_half);

t_file	*sorted_merge_mod_time_rev(t_file *first_half, t_file *second_half);

t_dir	*sorted_merge_alpha_dir(t_dir *first_half, t_dir *second_half);

t_dir	*sorted_merge_alpha_rev_dir(t_dir *first_half, t_dir *second_half);

t_dir	*sorted_merge_mod_time_dir(t_dir *first_half, t_dir *second_half);

t_dir	*sorted_merge_mod_time_rev_dir(t_dir *first_half, t_dir *second_half);

t_dir	*sorted_merge_dir(t_ls *ls, t_dir *first_half, t_dir *second_half);

void	split_list_dir(t_dir *head, t_dir **first_half, t_dir **second_half);

void	mergesort_dir(t_ls *ls, t_dir **dirs);

void	new_dir(t_dir **dir, char *path);

char	*ft_strjoindir(char const *s1, char const *s2);

int		nbrlen(int n);

void	update_max_width(t_ls *ls, struct stat stats);

void	save_stats(t_ls *ls, t_file *current, char *path);

void	save_stats_dir(t_ls *ls, t_dir *current);

int		check_if_dir(char *path);

void	get_terminal_size(t_ls *ls);

void	print_l(t_ls *ls, t_file *files);

void	print_x(t_ls *ls, t_file *files);

int		padding_total(t_ls *ls, t_file *files, int row_amount);

int		check_rows_len(t_ls *ls, t_file *files, int row_amount);

int		count_rows(t_ls *ls, t_file *files);

void	print_files_row(t_file *files, int row, int row_amount, int *col_pad);

int		count_files(t_ls *ls, t_file *files);

int		count_cols(int file_amount, int row_amount);

int		*calculate_padding(t_ls *ls, t_file *files, int row_amount);

void	print_basic(t_ls *ls, t_file *files);

void	print_files(t_ls *ls, t_file *files);

void	count_total_blocks(t_dir *dir);

void	print_ls(t_ls *ls);

void	sort_files(t_ls *ls);

void	free_files(t_file *files);

void	free_dirs(t_dir *dirs);

void	free_ls(t_ls *ls);

int		check_row(t_ls *ls, t_file *files, int row[2]);

int		get_col_padding(t_ls *ls, t_file *files, int cols, int row_amount);

void	print_color(t_file *file, char *format, char *str);

void	print_one(t_ls *ls, t_file *files);

#endif