/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfranco <thfranco@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 11:28:37 by thfranco          #+#    #+#             */
/*   Updated: 2024/06/04 12:39:02 by thfranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"

void	tokenization(char **av_to_parse)
{
	int	i;

	i = 1;
	while (av_to_parse[i])
		check_kind(av_to_parse[i])
}
