/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 14:34:32 by sadawi            #+#    #+#             */
/*   Updated: 2020/06/14 17:17:05 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

char	*ft_strjoindir(char const *s1, char const *s2)
{
	char	*str;
	int		len1;

	len1 = ft_strlen(s1);
	if (!(str = (char*)ft_memalloc(len1 + ft_strlen(s2) + 2)))
		return (NULL);
	ft_strcpy(str, s1);
	if (len1 < 1 || str[len1 - 1] != '/')
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

int		ft_strcmp_case(const char *s1, const char *s2)
{
	int	i;
	int	(*low)(int);

	low = ft_tolower;
	i = 0;
	while (s1[i] && s2[i])
	{
		if (!ft_isalpha(s1[i]))
		{
			if (!ft_isalpha(s2[i]))
				s2++;
			s1++;
			continue;
		}
		if (!ft_isalpha(s2[i]))
		{
			s2++;
			continue;
		}
		if ((unsigned char)low(s1[i]) != (unsigned char)low(s2[i]))
			return ((unsigned char)low(s1[i]) - (unsigned char)low(s2[i]));
		i++;
	}
	return ((unsigned char)low(s1[i]) - (unsigned char)low(s2[i]));
}

int		ft_strcmp_case_basename(const char *s1, const char *s2, int i)
{
	while (s1[i] && s2[i])
	{
		if (!ft_isalpha(s1[i]) && s1[i] != '/')
		{
			if (!ft_isalpha(s2[i]) && s2[i] != '/')
				s2++;
			s1++;
			continue;
		}
		if (!ft_isalpha(s2[i]) && s2[i] != '/')
		{
			s2++;
			continue;
		}
		if ((unsigned char)ft_tolower(s1[i])
		!= (unsigned char)ft_tolower(s2[i]))
		{
			s1 = ft_strrchr(&s1[i], '/') ? ft_strrchr(&s1[i], '/') : &s1[i];
			s2 = ft_strrchr(&s2[i], '/') ? ft_strrchr(&s2[i], '/') : &s2[i];
			return (ft_strcmp_case(s1, s2));
		}
		i++;
	}
	return (ft_strcmp_case(&s1[i], &s2[i]));
}
