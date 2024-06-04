/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfranco <thfranco@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 11:16:54 by thfranco          #+#    #+#             */
/*   Updated: 2024/06/04 12:20:58 by thfranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft/libft.h"

typedef struct s_token
{
	char			*data;
	char			*token;
	struct s_token	*next;

}					t_token;


void print_prompt(void);
