/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfranco <thfranco@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 11:14:54 by thfranco          #+#    #+#             */
/*   Updated: 2024/06/04 12:22:01 by thfranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include<tokenization.h>

int print_prompt(void)
{
	char *prompt;
	char *user = getenv("USER");
	char *session = getenv("SESSION_MANAGER");

    if (user != NULL && session != NULL) {
		prompt = ft_strjoin(user, "@");
        printf("%s@\n", prompt);
		printf("O valor da variável PATH é: %s\n", session);

    } else {
        printf("A variável PATH não está definida.\n");
    }
    return 0;

}

int main(void)
{
	//extern char **environ;

	print_prompt();
	/*while (*environ)
	{
   		printf("%s\n", *environ);
		environ++;
    }*/
    return 0;
}


