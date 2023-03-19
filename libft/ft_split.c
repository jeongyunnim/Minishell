/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 15:56:55 by jeseo             #+#    #+#             */
/*   Updated: 2022/07/31 14:09:36 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	word_count(char *s, char c)
{
	int	count;

	count = 0;
	while (*(s + 1) != '\0')
	{
		if (*s != c && *(s + 1) == c)
			count++;
		s += 1;
	}
	if (*s != c)
		count++;
	return (count);
}

static int	word_len(char *s, char c)
{
	size_t	len;

	len = 0;
	while (s[len] != c && s[len] != '\0')
		len++;
	return (len);
}

static char	*ret_word(char **s, char c)
{
	char	*word;
	size_t	w_len;

	while (**s == c)
		*s += 1;
	w_len = word_len(*s, c);
	word = (char *)malloc(sizeof(char) * w_len + 1);
	if (word == NULL)
		return (NULL);
	ft_strlcpy(word, *s, w_len + 1);
	*s += w_len;
	return (word);
}

static char	**free_all(char **splited, size_t i)
{
	while (i >= 0)
		free(splited[i--]);
	free(splited);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**splited;
	char	*temp;
	int		count;
	int		i;

	i = -1;
	temp = (char *)s;
	if (s == 0 || *s == '\0')
		return ((char **)ft_calloc(1, sizeof(char *)));
	else
		count = word_count(temp, c);
	splited = (char **)ft_calloc(count + 1, sizeof(char *));
	while (++i < count)
	{
		splited[i] = ret_word(&temp, c);
		if (splited[i] == NULL)
			return (free_all(splited, i));
	}
	return (splited);
}
