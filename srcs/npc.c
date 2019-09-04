/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 05:32:54 by jaelee            #+#    #+#             */
/*   Updated: 2019/09/04 07:03:15 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

//TODO (jae) : need an AI to have interesting npc behaviors (patrol, shooting player and etc)

void move_npc(t_npc *enemy)
{
	if (enemy->pos.x < 11.5f)
		enemy->pos.x += 0.05f;
	else if (enemy->pos.y < 10.5f)
		enemy->pos.y += 0.05f;
}
