/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afont <afont@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 14:50:49 by dferjul           #+#    #+#             */
/*   Updated: 2024/02/08 14:39:02 by afont            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	parser.c	*/
int		count_tokens(t_data *data);
char	*append_char_to_token(char **token, char c);
char	**lexer(char *input);