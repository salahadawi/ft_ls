/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 13:11:14 by sadawi            #+#    #+#             */
/*   Updated: 2020/04/12 20:16:58 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

void	handle_error(char *message)
{
	ft_printf("ft_ls: %s\n", message);
	exit(1);
}

int		char_index(char *str, char c)
{
	int i;

	i = 0;
	while (str[i] != c && str[i])
		i++;
	if (str[i] == c)
		return (i);
	return (-1);
}

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
		(*dir)->path = path;
		(*dir)->files = NULL;
		(*dir)->next = NULL;
		return ;
	}
	new_dir(&(*dir)->next, path);
}

char	*format_time(char *time)
{
	char *formatted;

	formatted = ft_strsub(time, char_index(time, ' ') + 1,
	char_index(ft_strchr(time, ' ') + 1, ':') + 3);
	return (formatted);
}

char	*ft_strjoindir(char const *s1, char const *s2)
{
	char	*str;
	int		len1;

	len1 = ft_strlen(s1);
	if (!(str = (char*)ft_memalloc(len1 + ft_strlen(s2) + 2)))
		return (NULL);
	ft_strcpy(str, s1);
	if (str[len1 - 1] != '/')
		ft_strcat(str, "/");
	ft_strcat(str, s2);
	return (str);
}

int		nbrlen(int n)
{
	int i;

	i = 0;
	while (n || !i)
	{
		n /= 10;
		i++;
	}
	return (i);
}

void	update_max_width(t_ls *ls, struct stat stats)
{
	int len;

	len = nbrlen(stats.st_nlink);
	if (len > ls->links_width)
		ls->links_width = len;
	len = nbrlen(stats.st_size);
	if (len > ls->size_width)
		ls->size_width = len;
}

void	save_stats(t_ls *ls, t_file *current, char *path)
{
	char *filename;

	if (path)
		filename = ft_strjoindir(path, current->name);
	else
		filename = ft_strdup(current->name);
	if (lstat(filename, &current->stats) < 0)
	{
		ft_fprintf(2,
		"ft_ls: cannot access '%s': No such file or directory\n",
		filename);
		ls->files_amount--;
	}
	update_max_width(ls, current->stats);
	free(filename);
}

void	save_stats_dir(t_ls *ls, t_dir *current)
{
	if (lstat(current->path, &current->stats) < 0)
	{
		ft_fprintf(2,
		"ft_ls: cannot access '%s': No such file or directory\n",
		current->path);
	}
	update_max_width(ls, current->stats);
}

void	open_files(t_ls *ls)
{
	t_file	*file;
	t_dir	*dir;

	file = ls->files;
	while (file)
	{
		if (!((file->name[0] == '.' && !ft_strchr(ls->flags, 'a'))))
			save_stats(ls, file, NULL);
		file = file->next;
	}
	dir = ls->dirs;
	while (dir)
	{
		file = dir->files;
		while (file)
		{
			if (!((file->name[0] == '.' && !ft_strchr(ls->flags, 'a'))))
				save_stats(ls, file, dir->path);
			file = file->next;
		}
		if (!((dir->path[0] == '.' && !ft_strchr(ls->flags, 'a'))))
				save_stats_dir(ls, dir);
		dir = dir->next;
	}
}

void	add_dir(t_ls *ls, t_dir **dir, char *path)
{
	struct dirent	*p_dirent;
	DIR				*p_dir;
	t_dir			*dir_ptr;

	//ft_printf(path);
	if (!(p_dir = opendir(path)))
	{
		ft_printf(path);
		handle_error("Directory could not be opened");
	}
	new_dir(dir, path);
	dir_ptr = *dir;
	while (dir_ptr->next)
		dir_ptr = dir_ptr->next;
	while ((p_dirent = readdir(p_dir)))
	{
		(void)ls;
		//ft_printf("%s\n", p_dirent->d_name);
		new_file(&dir_ptr->files, p_dirent->d_name);
		if (ft_strchr(ls->flags, 'R') && check_if_dir(ft_strjoindir(path, p_dirent->d_name)))
			if (!((p_dirent->d_name[0] == '.' && !ft_strchr(ls->flags, 'a'))))
				if (!ft_strequ(p_dirent->d_name, "..") && !ft_strequ(p_dirent->d_name, "."))
				{
					//ft_printf(p_dirent->d_name);
					add_dir(ls, &dir_ptr, ft_strjoindir(path, p_dirent->d_name));
					ls->dirs_amount++;
					ls->files_dirs_amount++;
				}
	}
	closedir(p_dir);
}

int	ft_strcmp_case(const char *s1, const char *s2)
{
	int	i;
	int	(*low)(int);

	low = ft_tolower;
	i = 0;
	if (!s1 && !s2)
		return (0);
	if ((s1 && !s2) || (!s1 && s2))
		return (1);
	if (s1[0] == '.')
			s1++;
	if (s2[0] == '.')
			s2++;
	while (s1[i] || s2[i])
	{
		if ((unsigned char)low(s1[i]) != (unsigned char)low(s2[i]))
			return ((unsigned char)low(s1[i]) - (unsigned char)low(s2[i]));
		i++;
	}
	return (0);
}

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

void	sort_mode(t_ls *ls)
{
	if (!ls->flags)
		return ;
	if (ft_strchr(ls->flags, 't'))
		ls->sort_mode = SORT_MOD_TIME;
	if (ft_strchr(ls->flags, 'r'))
		ls->sort_mode++;
}

int		check_if_dir(char *path)
{
	struct stat		stats;

	if (lstat(path, &stats) != 0)
		return (0);
	if (S_ISDIR(stats.st_mode))
		return (1);
	return (0);
}

void	save_files(t_ls *ls, int argc, char **argv)
{
	if (!argc)
	{
		add_dir(ls, &ls->dirs, ".");
		ls->dirs_amount++;
	}
	while (argc--)
	{
		if (check_if_dir(*argv))
		{
			add_dir(ls, &ls->dirs, *argv++);
			ls->dirs_amount++;
		}
		else
		{
			new_file(&ls->files, *argv++);
			ls->files_amount++;
		}
		ls->files_dirs_amount++;
	}
}

void	get_terminal_size(t_ls *ls)
{
	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	ls->window_cols = w.ws_col;
	ls->window_rows = w.ws_row;
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

void	print_color(t_file *file, char *format, char *str)
{
	if (S_ISDIR(file->stats.st_mode))
		ft_printf("\033[1;34m");
	if (!S_ISDIR(file->stats.st_mode) &&
		file->stats.st_mode & S_IXUSR)
		ft_printf("\033[1;32m");
	if (S_ISLNK(file->stats.st_mode))
		ft_printf("\033[1;31m");
	ft_printf(format, str);
	ft_printf("\033[0m");
}

void	print_l(t_ls *ls, t_file *files)
{
	char *format;
	(void)ls;
	while (files)
	{
		if (files->stats.st_mode) //seems to work?
		{
			if (S_ISLNK(files->stats.st_mode))
				ft_printf("l");
			else
				ft_printf((S_ISDIR(files->stats.st_mode)) ? "d" : "-");
			ft_printf((files->stats.st_mode & S_IRUSR) ? "r" : "-");
			ft_printf((files->stats.st_mode & S_IWUSR) ? "w" : "-");
			ft_printf((files->stats.st_mode & S_IXUSR) ? "x" : "-");
			ft_printf((files->stats.st_mode & S_IRGRP) ? "r" : "-");
			ft_printf((files->stats.st_mode & S_IWGRP) ? "w" : "-");
			ft_printf((files->stats.st_mode & S_IXGRP) ? "x" : "-");
			ft_printf((files->stats.st_mode & S_IROTH) ? "r" : "-");
			ft_printf((files->stats.st_mode & S_IWOTH) ? "w" : "-");
			ft_printf((files->stats.st_mode & S_IXOTH) ? "x" : "-");
			format = ft_sprintf(" %%%dd", ls->links_width);
			ft_printf(format, files->stats.st_nlink);
			free(format);
			ft_printf(" %s", getpwuid(files->stats.st_uid)->pw_name);
			ft_printf(" %s", getgrgid(files->stats.st_gid)->gr_name);
			format = ft_sprintf(" %%%dd", ls->size_width);
			ft_printf(format, files->stats.st_size);
			free(format);
			format = format_time(ctime(&files->stats.st_ctime));
			ft_printf(" %s", format);
			free(format);
			print_color(files, " %s", files->name);
			if (S_ISLNK(files->stats.st_mode))
			{
				format = (char*)ft_memalloc(1000);
				readlink(files->name, format, 999);
				ft_printf(" -> ");
				print_color(files, "%s", format);
				free(format);
			}
			ft_printf("\n");
		}
		files = files->next;
	}
}

void	print_x(t_ls *ls, t_file *files)
{
	(void)ls;
	while (files)
	{
		if (files->stats.st_mode) //seems to work?
			print_color(files, "%s  ", files->name);
		files = files->next;
	}
	ft_printf("\n");
}

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
			if (files->stats.st_mode) //seems to work?
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

int		check_rows_len(t_ls *ls, t_file *files, int row_amount)
{
	int padding;

	padding = padding_total(ls, files, row_amount);
	padding += count_files(ls, files) / row_amount * 2;
	//ft_printf("%d\n", padding);
	if (padding > ls->window_cols)
		return (0);
	return (1);
	/*
	while (row < row_amount)
		if (!check_row(ls, files, (int[2]){row++, row_amount}))
			return (0);
	return (1);*/
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
	//ft_printf("%d\n", total_len);
	rows = total_len / ls->window_cols + 1;
	while (!check_rows_len(ls, file_ptr, rows))
		rows++;
	return (rows);
}

void	print_files_row(t_file *files, int row, int row_amount, int *col_pad)
{
	int	i;
	int first;
	int	col;
	char *format;

	i = 0;
	col = 0;
	first = 1;
	while (files)
	{
		if (i++ == row)
		{
			if (files->stats.st_mode) //seems to work?
			{
				if (first-- > 0)
					format = ft_sprintf("%%-%ds", col_pad[col]);
				else
					format = ft_sprintf("  %%-%ds", col_pad[col]);
				print_color(files, format, files->name);
				free(format);
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

int		count_files(t_ls *ls, t_file *files)
{
	int files_amount;

	files_amount = 0;
	while (files)
	{
		if (!((files->name[0] == '.' && !ft_strchr(ls->flags, 'a'))))
			files_amount++;
		files = files->next;
	}
	return (files_amount);
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
		//ft_printf("file_amount: %d\n", file_amount);
		//ft_printf("row amount: %d\n", row_amount);
		cols++;
	}
	return (cols);
}

int		get_col_padding(t_ls *ls, t_file *files, int cols, int row_amount)
{
	int i;
	int	padding;
	int len;
	
	padding = 0;
	while (cols-- > 0)
	{
		i = 0;
		while (i++ < row_amount && files)
		{
			if (files->name[0] == '.' && !ft_strchr(ls->flags, 'a'))
				i--;
			files = files->next;
		}
	}
	i = row_amount;
	while (i-- > 0 && files)
	{
		if (!((files->name[0] == '.' && !ft_strchr(ls->flags, 'a'))))
		{
			len = ft_strlen(files->name);
			//ft_printf("%s: %d", files->name, len);
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

int		*calculate_padding(t_ls *ls, t_file *files, int row_amount)
{
	int file_amount;
	int	col_amount;
	int	*col_padding;
	int col;

	file_amount = count_files(ls, files);
	col_amount = count_cols(file_amount, row_amount);
	//ft_printf("col_amount: %d\n", col_amount);
	col_padding = (int*)ft_memalloc(sizeof(int) * col_amount + 1);
	col = 0;
	while (col < col_amount)
	{
		col_padding[col] = get_col_padding(ls, files, col, row_amount);
		//ft_printf("%d\n", col_amount);
		//ft_printf("%d\n", col_padding[col]);
		col++;
	}
	col_padding[col] = -1;
	return (col_padding);
}

void	print_basic(t_ls *ls, t_file *files)
{
	int	row_amount;
	int	row;
	int	*col_padding;

	row_amount = count_rows(ls, files);
	col_padding = calculate_padding(ls, files, row_amount);
	row = 0;
	while (row < row_amount)
	{
		print_files_row(files, row++, row_amount, col_padding);
		ft_printf("\n");
	}
	free(col_padding);
}

void	print_files(t_ls *ls, t_file *files)
{
	if (ft_strchr(ls->flags, 'l'))
		print_l(ls, files);
	else if (ft_strchr(ls->flags, 'x'))
		print_x(ls, files);
	else
		print_basic(ls, files);
}

void	count_total_blocks(t_dir *dir)
{
	t_file			*file;
	unsigned int	total;

	total = 0;
	file = dir->files;
	while (file)
	{
		total += file->stats.st_blocks;
		file = file->next;
	}
	ft_printf("total %u\n", total/2);
}
void	print_ls(t_ls *ls)
{
	t_file	*files_ptr;
	t_dir	*dir_ptr;
	int		i;

	files_ptr = ls->files;
	dir_ptr = ls->dirs;
	i = ls->dirs_amount - 1;
	if (ls->files_amount)
		print_files(ls, files_ptr);
	if (dir_ptr)
	{
		if (ls->files_amount)
			ft_printf("\n");
		while (dir_ptr)
		{
			if (ls->files_dirs_amount > 1)
				ft_printf("%s:\n", dir_ptr->path);
			if (ft_strchr(ls->flags, 'l'))
				count_total_blocks(dir_ptr);
			print_files(ls, dir_ptr->files);
			if (ls->dirs_amount > 1 && i--)
				ft_printf("\n", dir_ptr->path);
			dir_ptr = dir_ptr->next;
		}	
	}
}

void	sort_files(t_ls *ls)
{
	t_dir *dir;

	mergesort(ls, &ls->files);
	mergesort_dir(ls, &ls->dirs);
	dir = ls->dirs;
	while (dir)
	{
		mergesort(ls, &dir->files);
		dir = dir->next;
	}
}

void	free_files(t_file *files)
{
	t_file *tmp;

	while (files)
	{
		tmp = files->next;
		free(files->name);
		free(files);
		files = tmp;
	}
}

void	free_dirs(t_dir *dirs)
{
	t_dir *tmp;

	while (dirs)
	{
		tmp = dirs->next;
		free_files(dirs->files);
		free(dirs);
		dirs = tmp;
	}
}

void	free_ls(t_ls *ls)
{
	free(ls->flags);
	free_files(ls->files);
	free_dirs(ls->dirs);
	free(ls);
}

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