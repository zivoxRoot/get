#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	char			*name;
	unsigned char	type;
}	directory;

// Get a path and returns all children from that path (including . and ..)
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

int	main(void)
{
	DIR	*dir;
	directory	**dir_list;

	dir = opendir(".");
	if (!dir)
	{
		printf("Could not open current dir\n");
		return (1);
	}

	// Get subdirs
	dir_list = get_subdirs(dir);
	if (!dir_list)
	{
		printf("Error getting list of subdirs...\n");
		return (1);
	}

	// Print 'em
	int i = 0;
	while (dir_list[i] != NULL)
	{
		printf("%s\n", dir_list[i]->name);
		i++;
	}

	free_subdirs(dir_list);

	closedir(dir);
	return (0);
}
