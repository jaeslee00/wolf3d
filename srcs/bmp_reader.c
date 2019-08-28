/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viccarau <viccarau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 11:43:55 by viccarau          #+#    #+#             */
/*   Updated: 2019/08/28 14:50:55 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

sint32		read_all(sint32 fd, uint8 *data, sint32 size)
{
	sint32	read_bytes;
	sint32	ret;

	read_bytes = 0;
	while (((ret = read(fd, data + read_bytes, size - read_bytes)) > 0))
		read_bytes = read_bytes + ret;
	if (ret <= 0)
		return (ret);
	return (read_bytes + ret);
}

t_texture	read_bmp(const sint8 *filename, t_wolf *wolf)
{
	uint8		data[3 * 64 * 64];
	sint32		fd;
	uint8		header[54];
	t_texture	tex;
	sint32 i;
	sint32 j;

	i = 0;
	j = 0;
	fd = open(filename, O_RDONLY);
	read(fd, header, 54);

	tex.width = TEX_WIDTH;
	tex.height = TEX_HEIGHT;
	tex.size = 3 * tex.width * tex.height;
	is_alloc(tex.data = (uint32*)ft_mem(&wolf->mem, tex.width * tex.height * sizeof(uint32)), wolf, -1);
	read_all(fd, data, tex.size);
	i = (64 * 64) - 1;
	while (i >= 0)
	{
		tex.data[i] = data[j] | data[j + 1] << 8 | data[j + 2] << 16;
		i--;
		j += 3;
	}
	return (tex);
}
