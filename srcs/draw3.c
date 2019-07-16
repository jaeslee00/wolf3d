/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viccarau <viccarau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 17:06:49 by viccarau          #+#    #+#             */
/*   Updated: 2019/05/09 12:12:23 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "draw.h"

t_3d	find_center(t_fdf fdf)
{
	int		center;
	t_3d	offset;

	if (fdf.obj.size % 2 == 0)
		center = round(fdf.obj.size / 2) + round((fdf.obj.len) / 2);
	else
		center = round(fdf.obj.size / 2);
	offset.xyz.x = ((W / 2) - transform(fdf.proj_matrix, fdf.p[center]).xy.xy.x)
		+ fdf.offset.xyz.x;
	offset.xyz.y = ((H / 2) - transform(fdf.proj_matrix, fdf.p[center]).xy.xy.y)
		+ fdf.offset.xyz.y;
	offset.xyz.z = 0 + fdf.offset.xyz.z;
	return (offset);
}
