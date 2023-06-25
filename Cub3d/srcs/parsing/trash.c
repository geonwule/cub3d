
int		size_arr_2d(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

void	change_arr(char ***arr)
{
	int i;
	int len;

	i = 0;
	while (i < size_arr_2d(*arr))
	{
		len = ft_strlen((*arr)[i]);
		if ((*arr)[i][len - 1] == '\n')
			(*arr)[i][len - 1] = '\0';
		i++;
	}

}

int	check_line(char **arr)
{
	int i;
	int j;
	int len;

	i = 0;
	while (i < size_arr_2d(arr))
	{
		if (arr[i][0] != '1' || arr[i][ft_strlen(arr[i]) - 1] != '1')
			return (1);
		j = 1;
		while (j < ft_strlen(arr[i]) - 1)
		{
			if (arr[i][j] != '0' && arr[i][j] != '1' &&
				arr[i][j] != 'W')
			{
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

void	set_map(char **arr, t_vars *vars, int fd, char *line)
{
	t_list	*head;
	t_list	*tmp;

	change_arr(&arr);
	if (check_line(arr))
	{
		free(line);
		free_arr_2d(&arr);
		print_error("Invalid map1", vars);
	}
	head = ft_lstnew(line);
	free_arr_2d(&arr);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		arr = ft_split(line, ' ');
		change_arr(&arr);
		if (check_line(arr))
		{
			free(line);
			free_arr_2d(&arr);
			print_error("Invalid map2", vars);
		}
		tmp = ft_lstnew(line);
		ft_lstadd_back(&head, tmp);
		free_arr_2d(&arr);
	}
	print_lst(head);
}
