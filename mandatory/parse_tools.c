/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 15:41:44 by vtavitia          #+#    #+#             */
/*   Updated: 2023/07/06 18:04:01 by vtavitia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{		
		if (s1[i] != s2[i])
			return (((unsigned char *)s1)[i] - ((unsigned char *) s2)[i]);
		i++;
	}
	return (0);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (2048);
	else
		return (0);
}

static size_t	ft_strlen(const char *str)
{
	int		i;
	char	*str1;

	if (!str)
		return (0);
	str1 = (char *)str;
	i = 0;
	while (str1[i] != '\0')
	{
		i++;
	}
	return (i);
}

static int	parsestr(const char *str)
{
	int	i;

	i = 0;
	while (str[i] <= 32 && str[i] != '\e')
	{
		if (str[i] == '\\')
			i++;
		i++;
	}
	return (i);
}

int	ft_atoi(const char *str)
{
	int	rvalue;
	int	sign;
	int	i;

	if (ft_strlen(str) == 0)
		return (0);
	rvalue = 0;
	sign = 1;
	i = parsestr(str);
	if (str[i] == '-' && str[i + 1] != '+')
	{
		sign *= -1;
		i++;
	}
	if (str[i] == '+')
	{
		i++;
	}
	while (((str[i] >= 48 && str[i] <= 57)))
	{
		rvalue = rvalue * 10 + str[i] - '0';
		i++;
	}
	return (rvalue * sign);
}
