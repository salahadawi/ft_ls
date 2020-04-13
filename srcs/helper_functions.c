/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 14:34:32 by sadawi            #+#    #+#             */
/*   Updated: 2020/04/13 14:53:49 by sadawi           ###   ########.fr       */
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
