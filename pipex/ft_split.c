/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynafiss <ynafiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 20:24:42 by ynafiss           #+#    #+#             */
/*   Updated: 2022/12/20 14:59:10 by ynafiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	count(const char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i] != '\0')
			count++;
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	return (count);
}

static char	*ft_len_s(const char *s, char c)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	while (s[i] != '\0' && s[i] != c)
	{
		i++;
	}
	str = malloc((i)+ 1);
	if (!str)
		return (NULL);
	while (j < i)
	{
		str[j] = s[j];
		j++;
	}
	str[j] = '\0';
	return (str);
}

static char	**sp_fr(char **str, int j)
{
	while (j >= 0)
	{
		free(str[j]);
		j--;
	}
	free(str);
	return (NULL);
}

static char	**ft_full(char **str, const char *s, char c)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		if (s[i] != c && s[i] != '\0')
		{
			str[j] = ft_len_s(s + i, c);
			if (str[j] == NULL)
				return (sp_fr(str, j));
			j++;
		}
		while (s[i] != c && s[i] != '\0')
		i++;
	}
	str[j] = 0;
	return (str);
}

char	**ft_split(const char *s, char c)
{
	char	**str;

	if (s == NULL)
		return (NULL);
	str = malloc((sizeof (char *)) * (count(s, c) + 1));
	if (!str)
		return (NULL);
	return (ft_full(str, s, c));
}
