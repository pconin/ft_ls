/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pconin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/03 11:17:13 by pconin            #+#    #+#             */
/*   Updated: 2016/05/11 16:41:56 by pconin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
void	print_l(t_fil *file)
{
	ft_putchar(file->typ);
	ft_putstr(file->rgh);
	ft_putstr("\t");
	ft_putnbr(file->links);
	ft_putstr("\t");
	ft_putstr(file->us_name);
	ft_putstr("\t");
	ft_putstr(file->gr_name);
	ft_putstr("\t");
	ft_putnbr(file->size);
	ft_putstr("\t");
	ft_putstr(file->date_m);
	ft_putstr("\t");
}
void	total_blocks(t_fil *file)
{
	int total;

	total = 0;
	while (file)
	{
		total = total + file->bloc;
		file = file->next;
	}
	ft_putstr("total ");
	ft_putnbr(total);
	ft_putstr("\n");
}

void	ft_print_path(char *path)
{
	ft_putstr("\n");
	if (path[0] != '.')
	{
		ft_putstr(path);
		ft_putstr(":\n");
	}
}

void	print_dir(t_fil *file, t_mem *s, char *path)
{
	int		i;

	if (s->nb_file > 1 || s->R == 1)
		ft_print_path(path);
	if (s->l == 1)
		total_blocks(file);
	while (file)
	{
		if (s->a == 1 || file->hide == 0)
		{
			if (s->l == 1)
				print_l(file);
			ft_putstr(file->name);
			ft_putstr("\n");
		}
		file = file->next;
	}
}
