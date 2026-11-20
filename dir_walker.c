#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

char    *ft_strjoin(char const *s1, char const *s2)
{
	int             size_s1;
	int             size_s2;
	char    *res;

	size_s1 = strlen(s1);
	size_s2 = strlen(s2);
	res = (char *)malloc((size_s1 + size_s2 + 1) * sizeof(char));
	if (!res)
		return (NULL);
	memcpy(res, s1, size_s1);
	memcpy(res + size_s1, s2, size_s2);
	res[size_s1 + size_s2] = '\0';
	return (res);
}

typedef struct {
	char			*name;
	unsigned char	type;
}	directory;

// Takes a path and returns all children from that path (including . and ..)
directory	**get_subdirs(DIR *path)
{
	struct dirent	*current_dir;
	struct dirent	*tmp;
	int				count;
	directory		**res;

	if (!path)
	{
		printf("Could not open current directory\n");
		return (NULL);
	}
	// Get number of children
	count = 0;
	current_dir = readdir(path);
	while (current_dir)
	{
		count++;
		current_dir = readdir(path);
	}
	// Malloc size
	res = (directory **)malloc((count + 1) * sizeof(struct directory *));
	if (!res)
		return (NULL);
	// Copy each directory
	rewinddir(path);
	int i = 0;
	while (i < count)
	{
		res[i] = (directory *)malloc(sizeof(directory));
		tmp = readdir(path);
		res[i]->name = strdup(tmp->d_name);
		res[i]->type = tmp->d_type;
		i++;
	}
	res[i] = NULL;
	return (res);
}

void	free_subdirs(directory **dirs)
{
	int	count;

	count = 0;
	while (dirs[count])
	{
		free(dirs[count]);
		count++;
	}
	free(dirs);
}

int substr(char *str, char *pattern)
{
  int i;
  int y;

  i = 0;
  y = 0;
  while (str[i])
  {
    while (str[i] == pattern[y])
    {
      if (pattern[y + 1])
      {
        return (i);
      }
      y++;
    }
    y = 0;
    i++;
  }
  return (-1);
}

// Print a string with the pattern highlighted
void  print_pattern(char *str, int index, int size)
{
  int i;

  i = 0;
  while (str[i])
  {
    if (i == index)
      write(1, "\033[34m", 5);
    write(1, &str[i], 1);
    if (i == index + size - 1)
      write(1, "\033[39m", 5);
    i++;
  }
}

void  ft_printf(char *str)
{
  int i;

  i = 0;
  while (str[i])
  {
    write(1, &str[i], 1);
    i++;
  }
}

// Show each mathing result (either filename or content)
void	show_matching_results(directory **dir_list, char *pattern, char *path)
{
	int i;

	i = 0;
	while (dir_list[i] != NULL)
	{
    int index = substr(dir_list[i]->name, pattern);
    // Handle directories
    if (dir_list[i]->type == DT_DIR)
    {
      if (index > 0)
      {
        ft_printf(path);
        ft_printf("/");
        print_pattern(dir_list[i]->name, index, strlen(pattern));
        ft_printf("/\n");
      }
    }
    // Handle files
    else
    {
      if (index > 0)
      {
        ft_printf(path);
        ft_printf("/");
        print_pattern(dir_list[i]->name, index, strlen(pattern));
        ft_printf("\n");
      }
    }
		i++;
	}
}

// Recursively explore subdirectories
void	rec_explore(char *path, char *pattern)
{
	char			*dir;
	DIR			*current_dir;
	directory	**dir_list;

	// Open path
	current_dir = opendir(path);
	if (!current_dir)
	{
		printf("Could not open current dir\n");
		return ;
	}

	// Get subdirs
	dir_list = get_subdirs(current_dir);
	if (!dir_list)
	{
		printf("Error getting list of subdirs...\n");
		return ;
	}

	show_matching_results(dir_list, pattern, path);

	// Operate on 'em
	int i = 0;
	while (dir_list[i] != NULL)
	{
		// Ignore .git (to check with config later)
		if (strcmp(".git", dir_list[i]->name) == 0)
		{
			i++;
			continue ;
		}
		// Ignore standard files
		if (dir_list[i]->type != DT_DIR)
		{
			i++;
			continue ;
		}
		// Ignore '.' and '..'
		if (strcmp(".", dir_list[i]->name) == 0 || strcmp("..", dir_list[i]->name) == 0)
		{
			i++;
			continue ;
		}
		dir = ft_strjoin(ft_strjoin(path, "/"), dir_list[i]->name);
		rec_explore(dir, pattern);
		free(dir);
		i++;
	}

	free_subdirs(dir_list);
	closedir(current_dir);
}

int	main(void)
{
	rec_explore(".", "st");
	return (0);
}
