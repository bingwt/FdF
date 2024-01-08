/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 11:01:57 by btan              #+#    #+#             */
/*   Updated: 2024/01/08 11:04:17 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	is_sep(char const c, char sep)
{
	return (c == || c == '\0')
}

int	count_words(char const *str, char sep)
{
	int	words;

	words = 0;
	while (*(str++))
		if(is_sep(*str, sep) && !is_sep(*(str - 1), sep))
			words++;
	return (words);
}
