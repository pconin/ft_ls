/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pconin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 11:33:06 by pconin            #+#    #+#             */
/*   Updated: 2016/05/03 16:18:32 by pconin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"


struct s_fil	*ft_add_file(DIR *rep, struct dirent *fichier)
{
	t_fil		*file;
	struct stat	*buf;
	
	buf = malloc(sizeof(struct stat));
	printf("%s\n", fichier->d_name);
	lstat(fichier->d_name, buf);
	file = (t_fil *)malloc(sizeof(t_fil));
	file->size = buf->st_size;
	file->name = fichier->d_name;
	get_date(file, buf->st_mtime);
	printf("%i\n", buf->st_uid);
//	file->us_name = (getpwuid(buf->st_uid))->pw_name;
//	file->gr_name = (getgrgid(buf->st_gid))->gr_name;
	file->hide = 0;
	if (file->name[0] == '.')
		file->hide = 1;
	file->links = buf->st_nlink;
	file->next = NULL;
	free(buf);
	return (file);
}

int		main(int argc, char **argv)
{
	t_mem *s;
	t_fil	*tail;
	s = (t_mem *)malloc(sizeof(t_mem));
	parse_arg(argv, s);
	DIR* rep = NULL;
	struct dirent	*fichier = NULL;

	fichier = malloc(sizeof(struct dirent));
	rep = malloc(sizeof(DIR));
	s->dat = NULL;
	if ((rep = opendir(s->arg)) == NULL)
	{
		perror("error");
		exit(0);
	}
	while ((fichier = readdir(rep)) != NULL)
	{
		if (s->dat == NULL)
			s->dat = ft_add_file(rep, fichier);
		else
		{
			tail = s->dat;
			while (tail->next)
				tail = tail->next;
			tail->next = ft_add_file(rep, fichier);
		}
	}
	if (closedir(rep) == -1)
		perror("error");
	ft_flags(&s->dat, s);
	print_dir(s->dat, s);
	return (0);
}
