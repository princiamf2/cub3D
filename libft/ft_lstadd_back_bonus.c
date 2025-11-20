/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michel <michel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:18:50 by mm-furi           #+#    #+#             */
/*   Updated: 2024/12/05 19:50:14 by michel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *nouveau)
{
	t_list	*tmp;

	if (!nouveau)
		return ;
	if (!*lst)
	{
		*lst = nouveau;
		return ;
	}
	tmp = ft_lstlast(*lst);
	tmp->next = nouveau;
}
