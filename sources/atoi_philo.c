/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez-g <egomez-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 18:16:36 by egomez-g          #+#    #+#             */
/*   Updated: 2024/02/07 17:50:52 by egomez-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	atoi_philo(const char *str)
{
	long int	sol;
	int			neg;

	sol = 0;
	neg = 1;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			neg *= -1;
		str++;
	}
	if (!(*str >= '0' && *str <= '9'))
		return (0);
	while (*str >= '0' && *str <= '9' && *str)
	{
		sol += *str - '0';
		sol *= 10;
		str++;
	}
	sol /= 10;
	sol *= neg;
	return (sol);
}
/*#include <stdlib.h>
int main(void)
{
	const char	str[] = "--123a";
	printf("%d\n", ft_atoi(str));
	printf("%d", atoi(str));
	return (0);
}*/
