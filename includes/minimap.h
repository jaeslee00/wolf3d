/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viccarau <viccarau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 19:44:45 by viccarau          #+#    #+#             */
/*   Updated: 2019/10/07 19:56:32 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
# define MINIMAP_H
# include "wolf3d.h"

t_s32		is_valids(t_f32 x, t_f32 y);
t_pts		init_pts(t_2d xy0, t_2d xy1);
void		error_adjust(t_s32 *err, t_s32 *e2, t_ln *ln, t_2d_p *xy);

#endif
