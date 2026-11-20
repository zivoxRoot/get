#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>

struct dirent	**get_subdirs(DIR *path)
{
	struct dirent	*current_dir;
	int				count;
	struct dirent	**res;

	if (!path)
	{
		printf("Could not open current dir\n");
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
	res = (struct dirent **)malloc((count + 1) * sizeof(struct dirent *));
	// Copy each dir
	current_dir = readdir(path);
	int i = 0;
	while (i < count)
	{
		res[i] = current_dir;
		current_dir = readdir(path);
		i++;
	}
	res[i] = NULL;
	return (res);
}

int	main(void)
{
	DIR 			*dir;
	struct dirent	**dir_list;

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

	printf("It worked!\n");

	// Print 'em
	int i = 0;
	while (dir_list[i] != NULL)
	{
		printf("siuu\n");
		printf("%s\n", dir_list[i]->d_name);
		i++;
	}

	closedir(dir);
	return (0);
}
