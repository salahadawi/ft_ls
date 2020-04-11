/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 13:11:14 by sadawi            #+#    #+#             */
/*   Updated: 2020/04/11 17:55:27 by sadawi           ###   ########.fr       */
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
		(*files)->name = name;
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

void	save_stats(t_file *current)
{
	if (stat(current->name, &current->stats) < 0)
	{
		ft_fprintf(2,
		"ft_ls: cannot access '%s': No such file or directory\n",
		current->name);		
	}
}

void	open_files(t_ls *ls, t_file *files)
{
	t_file *current;

	current = files;
	while (current)
	{
		if (!((current->name[0] == '.' && !ft_strchr(ls->flags, 'a'))))
			save_stats(current);
		current = current->next;
	}
}

void	add_dir(t_dir **dir, char *path)
{
	struct dirent	*p_dirent;
	DIR				*p_dir;

	if (!(p_dir = opendir(path)))
		handle_error("Directory could not be opened");
	new_dir(dir, path);
	while ((p_dirent = readdir(p_dir)))
		new_file(&(*dir)->files, ft_strdup(p_dirent->d_name));
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
	while (s1[i] || s2[i])
	{
		if (s1[i] == '.')
			s1++;
		if (s2[i] == '.')
			s2++;
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

	stat(path, &stats);
	if (S_ISDIR(stats.st_mode))
		return (1);
	return (0);
}

void	save_files(t_ls *ls, int argc, char **argv)
{
	if (!argc)
		add_dir(&ls->dirs, "./");
	while (argc--)
	{
		if (check_if_dir(*argv))
			add_dir(&ls->dirs, *argv++);
		else
			new_file(&ls->files, *argv++);
	}
}

void	init_ls(t_ls **ls, int *argc, char **argv)
{
	*ls = (t_ls*)malloc(sizeof(t_ls));
	(*ls)->flags = ft_strdup("-");
	(*ls)->files = NULL;
	(*ls)->sort_mode = SORT_ALPHA;
	argv++;
	save_options(*ls, argc, &argv);
	save_files(*ls, *argc, argv);
	sort_mode(*ls);
}

void	print_l(t_ls *ls, t_file *files)
{
	(void)ls;
	while (files)
	{
		if (files->stats.st_mode) //seems to work?
		{
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
			ft_printf(" %2d", files->stats.st_nlink);
			ft_printf(" %s", getpwuid(files->stats.st_uid)->pw_name);
			ft_printf(" %s", getgrgid(files->stats.st_gid)->gr_name);
			ft_printf(" %5d", files->stats.st_size); //width should be determined by widest file
			ft_printf(" %s", format_time(ctime(&files->stats.st_ctime)));
			ft_printf(" %s\n", files->name);
		}
		files = files->next;
	}
}

void	print_basic(t_ls *ls, t_file *files)
{
	(void)ls;
	while (files)
	{
		if (files->stats.st_mode) //seems to work?
			ft_printf("%s  ", files->name);
		files = files->next;
	}
	ft_printf("\n");
}

void	print_files(t_ls *ls, t_file *files)
{
	if (ft_strchr(ls->flags, 'l'))
		print_l(ls, files);
	else
		print_basic(ls, files);
}

void	print_ls(t_ls *ls)
{
	print_files(ls, ls->files);
	while (ls->dirs)
	{
		ft_printf("test");
		print_files(ls, ls->dirs->files);
		ls->dirs = ls->dirs->next;
	}	
}

int		main(int argc, char **argv)
{
	t_ls	*ls;

	init_ls(&ls, &argc, argv);
	open_files(ls, ls->files);
	mergesort(ls, &ls->files);
	print_ls(ls);
	return (0);
}