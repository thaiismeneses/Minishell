/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfranco <thfranco@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 11:30:36 by thfranco          #+#    #+#             */
/*   Updated: 2024/08/08 20:17:39 by thfranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	int		i;
	int		len;
	char	*dest;

	if (!src)
		return (NULL);
	len = ft_strlen(src);
	dest = (char *)malloc(len + 1);
	if (dest != NULL)
	{
		i = 0;
		while (src[i] != '\0')
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (dest);
}

/*int	main(void)
{
	printf("%s\n", ft_strdup("Hello world!"));
	return (0);
}*/
