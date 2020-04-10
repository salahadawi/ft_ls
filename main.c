/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 13:11:14 by sadawi            #+#    #+#             */
/*   Updated: 2020/04/10 22:03:51 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

void	handle_error(char *message)
{
	ft_printf("Error: %s.\n", message);
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

char	*format_time(char *time)
{
	char *formatted;

	formatted = ft_strsub(time, char_index(time, ' ') + 1,
	char_index(ft_strchr(time, ' ') + 1, ':') + 3);
	return (formatted);
}

void	open_files(t_file *files)
{
	t_file *current;

	current = files;
	while (current)
	{
		#include <stdio.h>
		if (stat(current->name, &current->stats) < 0)
		{
			ft_fprintf(2,
			"ft_ls: cannot access '%s': No such file or directory\n",
			current->name);
			
		}
		current = current->next;
	}
}

void	add_dir(t_file **files, char *dir)
{
	struct dirent	*p_dirent;
	DIR				*p_dir;

	if (!(p_dir = opendir(dir)))
		handle_error("Directory could not be opened");
	while ((p_dirent = readdir(p_dir)))
		new_file(files, ft_strdup(p_dirent->d_name));
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
		if ((unsigned char)low(s1[i]) != (unsigned char)low(s2[i]))
			return ((unsigned char)low(s1[i]) - (unsigned char)low(s2[i]));
		i++;
	}
	return (0);
}


t_file	*sorted_merge_alpha(t_file *first_half, t_file *second_half)
{
	t_file *sorted;

	if (!first_half)
		return (second_half);
	if (!second_half)
		return (first_half);
	if (ft_strcmp_case(first_half->name, second_half->name) < 0)
	{
		sorted = first_half;
		sorted->next = sorted_merge_alpha(first_half->next, second_half);
	}
	else
	{
		sorted = second_half;
		sorted->next = sorted_merge_alpha(first_half, second_half->next);
	}
	return (sorted);
}

t_file	*sorted_merge_alpha_rev(t_file *first_half, t_file *second_half)
{
	t_file *sorted;

	if (!first_half)
		return (second_half);
	if (!second_half)
		return (first_half);
	if (ft_strcmp_case(first_half->name, second_half->name) > 0)
	{
		sorted = first_half;
		sorted->next = sorted_merge_alpha_rev(first_half->next, second_half);
	}
	else
	{
		sorted = second_half;
		sorted->next = sorted_merge_alpha_rev(first_half, second_half->next);
	}
	return (sorted);
}

t_file	*sorted_merge(t_file *first_half, t_file *second_half, int sorting_mode)
{
	if (sorting_mode == SORT_ALPHA)
		return (sorted_merge_alpha(first_half, second_half));
	if (sorting_mode == SORT_ALPHA)
		return (sorted_merge_alpha_rev(first_half, second_half));
	else
		handle_error("Invalid sort mode");
	return NULL;
}

void	split_list(t_file *head, t_file **first_half, t_file **second_half)
{
	t_file *fast;
	t_file *slow;

	slow = head;
	fast = head->next;
	while (fast)
	{
		fast = fast->next;
		if (fast)
		{
			slow = slow->next;
			fast = fast->next;
		}
	}
	*first_half = head;
	*second_half = slow->next;
	slow->next = NULL;
}

void	mergesort(t_file **files, int sorting_mode)
{
	t_file *head;
	t_file *first_half;
	t_file*second_half;

	head = (*files);
	if (!head || !head->next)
		return ;
	split_list(head, &first_half, &second_half);
	mergesort(&first_half, sorting_mode);
	mergesort(&second_half, sorting_mode);
	*files = sorted_merge(first_half, second_half, sorting_mode);
}

int		main(int argc, char **argv)
{
	t_file	*files;

	files = NULL;
	if (argc == 1)
		add_dir(&files, "./");
	while (argc-- > 1)
		new_file(&files, *(++argv));
	open_files(files);
	mergesort(&files, SORT_ALPHA);
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
			ft_printf(" %5d", files->stats.st_size);
			ft_printf(" %s", format_time(ctime(&files->stats.st_ctime)));
			ft_printf(" %s\n", files->name);
		}
		files = files->next;
	}
	return (0);
}