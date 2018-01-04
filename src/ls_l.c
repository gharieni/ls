/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inspect_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelek <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 13:37:21 by gmelek            #+#    #+#             */
/*   Updated: 2018/01/04 18:18:22 by gmelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_ls.h"
#include <errno.h>
#include <string.h>

char*	ft_basename(char** str)
{
	char* buff;
	char* old;
	char* s;

	buff = *str;
	s = NULL;
	old = NULL;
	while(strchr(buff,'/') && (buff = strchr(buff,'/')) )
		old = ++buff;
	if (old)
	{
		s = ft_strdup(old);
		*old = '\0';
		ft_strclr(old);
	}
	else
	{
		s = ft_strdup(*str);
		*str = ".";
		ft_strclr(*str + 1);
	}
	return(s);
}


char*	file_str(char *s1, const char *s2)
{

	int i;

	i = 0;
	while (s1[i++]);
	if (!ft_strncmp(&s1[i - 2],".",1) && !ft_strncmp(&s1[i - 3],"/",1))
		s1[i - 2] = '\0';
	else if (ft_strncmp(&s1[i - 2],"/",1))
		s1 = ft_strjoin(s1,"/");
	return(ft_strjoin(s1,s2));
}

int			lsl(int ac ,char *av,t_flags flag)

{
	int m;
	struct	stat	st;
	struct	dirent	*dir;
	DIR				*pdir;
	char			*buff;
	char			*str;
	char			*s;
	int				i = 2;
	d_list			*l_dir;
	d_list			*tmp;
	node *tree;
	//t_flags *flags;

	//flags = (t_flags*)malloc(sizeof(t_flags));
	tree = NULL;
	l_dir = tmp;
	buff = ft_strnew(sizeof(av[2]));
	ft_strcpy(buff,av);
	while (!(pdir = opendir(buff)) && i--)
		s = ft_basename(&buff);
	i = 0;
	//ft_arg_parse_flags(flags,av);
	while ((dir = readdir(pdir)) != NULL)
	{
		if(!s || (!ft_strcmp( s, dir->d_name)))
		{
			str = file_str(buff,dir->d_name);
			stat(str,&st);
	
			node *elem = malloc(sizeof(node));
		printf("hooooooooooooooooooooooola");
			elem->val = lst_add(str,&tmp,&st,&m,&i);
			
			elem->left = NULL;
			elem->right = NULL;
	//tmp = lst_add(dir->d_name,&tmp,&st,&m,&i);
			tree = addnode(&tree,dir->d_name,tmp,elem);//,&st,&m,&i);
		}
	}
		l_dir = tmp;
		ft_putstr("total ");
		ft_putnbr(i);
		ft_putstr("\n");
//	while(l_dir)
//	{
		//print(l_dir,m);
		printTree(tree,m,&flag);
//		l_dir = l_dir->next;
		printf("\n");
//	}
	return (0);
}
