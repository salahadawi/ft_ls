/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 12:20:24 by sadawi            #+#    #+#             */
/*   Updated: 2020/06/14 13:59:01 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "../libft/includes/libft.h"
# include <sys/types.h>
# include <sys/ioctl.h>
# include <sys/xattr.h>
# include <sys/stat.h>
# include <dirent.h>
# include <stdio.h>
# include <time.h>
# include <pwd.h>
# include <grp.h>

# define VALID_FLAGS "alrRtx1Sog"

enum				e_sorting_mode
{
	SORT_ALPHA,
	SORT_ALPHA_REV,
	SORT_MOD_TIME,
	SORT_MOD_TIME_REV,
	SORT_SIZE,
	SORT_SIZE_REV
};

typedef struct		s_file
{
	char			*name;
	struct s_file	*next;
	struct stat		stats;
}					t_file;

typedef struct		s_dir
{
	char			*path;
	t_file			*files;
	struct stat		stats;
	struct s_dir	*next;
}					t_dir;

typedef	struct		s_ls
{
	char			*flags;
	t_file			*files;
	t_dir			*dirs;
	int				dirs_amount;
	int				files_amount;
	int				files_dirs_amount;
	int				sort_mode;
	int				links_width;
	int				size_width;
	int				window_cols;
	int				window_rows;
	int				acl_found;
}					t_ls;

void				handle_error(char *message);

int					char_index(char *str, char c);

void				new_file(t_file **files, char *name);

void				new_dir(t_dir **dir, char *path);

char				*format_time(char *time);

char				*ft_strjoindir(char const *s1, char const *s2);

int					nbrlen(int n);

void				update_max_width(t_ls *ls, struct stat stats);

void				save_stats(t_ls *ls, t_file *current, char *path);

void				save_stats_dir(t_ls *ls, t_dir *current);

void				open_files(t_ls *ls);

void				add_dir(t_ls *ls, t_dir **dir, char *path);

int					ft_strcmp_case(const char *s1, const char *s2);

void				save_flag(t_ls *ls, char *flag);

void				save_options(t_ls *ls, int *argc, char ***argv);

void				sort_mode(t_ls *ls);

int					check_if_dir(char *path);

void				save_files(t_ls *ls, int argc, char **argv);

void				get_terminal_size(t_ls *ls);

void				init_ls(t_ls **ls, int *argc, char **argv);

void				print_color(t_file *file, char *format, char *str);

void				print_l(t_ls *ls, t_file *files, t_dir *dir);

void				print_x(t_ls *ls, t_file *files);

void				print_one(t_ls *ls, t_file *files);

int					check_row(t_ls *ls, t_file *files, int row[2]);

int					padding_total(t_ls *ls, t_file *files, int row_amount);

int					check_rows_len(t_ls *ls, t_file *files, int row_amount);

int					count_rows(t_ls *ls, t_file *files);

void				print_files_row(t_file *files, int row, int row_amount,
					int *col_pad);

int					count_files(t_ls *ls, t_file *files);

int					count_cols(int file_amount, int row_amount);

int					get_col_padding(t_ls *ls, t_file *files, int cols,
					int row_amount);

int					*calculate_padding(t_ls *ls, t_file *files, int row_amount);

void				print_basic(t_ls *ls, t_file *files);

void				print_files(t_ls *ls, t_file *files, t_dir *dir);

void				count_total_blocks(t_dir *dir);

void				print_ls(t_ls *ls);

void				sort_files(t_ls *ls);

void				free_files(t_file *files);

void				free_dirs(t_dir *dirs);

void				free_ls(t_ls *ls);

t_file				*sorted_merge(t_ls *ls, t_file *first_half,
					t_file *second_half);

void				split_list(t_file *head, t_file **first_half,
					t_file **second_half);

void				mergesort(t_ls *ls, t_file **files);

t_dir				*sorted_merge_dir(t_ls *ls, t_dir *first_half,
					t_dir *second_half);

void				split_list_dir(t_dir *head, t_dir **first_half,
					t_dir **second_half);

void				mergesort_dir(t_ls *ls, t_dir **dirs);

t_file				*sorted_merge_alpha(t_file *first_half,
					t_file *second_half);

t_file				*sorted_merge_alpha_rev(t_file *first_half,
					t_file *second_half);

t_file				*sorted_merge_mod_time(t_file *first_half,
					t_file *second_half);

t_file				*sorted_merge_mod_time_rev(t_file *first_half,
					t_file *second_half);

t_file				*sorted_merge_size(t_file *first_half, t_file *second_half);

t_file				*sorted_merge_size_rev(t_file *first_half,
					t_file *second_half);

t_dir				*sorted_merge_alpha_dir(t_dir *first_half,
					t_dir *second_half);

t_dir				*sorted_merge_alpha_rev_dir(t_dir *first_half,
					t_dir *second_half);

t_dir				*sorted_merge_mod_time_dir(t_dir *first_half,
					t_dir *second_half);

t_dir				*sorted_merge_mod_time_rev_dir(t_dir *first_half,
					t_dir *second_half);

t_dir				*sorted_merge_size_dir(t_dir *first_half,
					t_dir *second_half);

t_dir				*sorted_merge_size_rev_dir(t_dir *first_half,
					t_dir *second_half);

DIR					*open_dir(t_ls *ls, char *path);

int					check_dir_recursive(t_ls *ls, char *name, char *filepath);

void				print_file_row_format(t_file *files, int *col_pad,
					int *first, int col);

void				print_file_links(t_ls *ls, t_file *file);

void				print_file_size(t_ls *ls, t_file *file);

void				print_file_date(t_file *file);

void				print_file_type(t_file *file);

void				print_file_permissions(t_ls *ls, t_file *file);

void				print_symbolic_link(t_file *file, t_dir *dir);

#endif
