/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dferjul <dferjul@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 19:39:47 by dferjul           #+#    #+#             */
/*   Updated: 2024/01/17 19:42:22 by dferjul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

/*	ft_signal.c	*/
void	signal_manager(int signum);
void	handle_ctrld(t_data *data);
