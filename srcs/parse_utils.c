/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaryjan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 19:24:46 by mmaryjan          #+#    #+#             */
/*   Updated: 2021/01/16 19:24:49 by mmaryjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		move_by_space(char **stroka)
{
	if (**stroka != ' ' && **stroka != '\t')
		print_errors(-2);
	while (**stroka == ' ' || **stroka == '\t')
		(*stroka)++;
}

void		check_end_of_str(char **stroka)
{
	while (**stroka)
	{
		if (**stroka != ' ' && **stroka != '\t')
			print_errors(-2);
		(*stroka)++;
	}
}

long int	get_int(char **stroka)
{
	long int	res;
	int			minus;

	res = 0;
	minus = (**stroka == '-' && ((*stroka)++)) ? -1 : 1;
	if (**stroka < '0' || **stroka > '9')
		print_errors(-2);
	while (**stroka >= '0' && **stroka <= '9')
	{
		res = res * 10 + (**stroka - 48);
		(*stroka)++;
	}
	return (res * minus);
}

int			check_sign(float *cel_float)
{
	int minus;

	minus = 1;
	if (*cel_float < 0)
	{
		*cel_float = -*cel_float;
		minus = -1;
	}
	return (minus);
}

float		get_mantfloat(char **stroka, float cel_float)
{
	float	dec;
	int		minus;

	minus = check_sign(&cel_float);
	dec = 0.1;
	if (**stroka == ' ' || **stroka == '\t' || **stroka == ',')
		return (cel_float * minus);
	if (**stroka == '.' && ((*stroka)++))
	{
		if (**stroka >= '0' && **stroka <= '9')
		{
			while (**stroka >= '0' && **stroka <= '9')
			{
				cel_float = cel_float + dec * ((float)**stroka - 48);
				dec *= 0.1;
				(*stroka)++;
			}
		}
		else
			print_errors(-2);
	}
	else
		print_errors(-2);
	return (cel_float * minus);
}
