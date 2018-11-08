# What is '**ls**'

**ls** is a command used for listing directories in a file system. And can also print details about files and/or directories. The behavior of the command depends on the options it receives from the arguments.

`usage: ft_ls [-lRartG1TDSUuYAnf] [file ...]`

The goal of this project was to reimplement the behavior of this command with a minimum of options.

Without arguments nor options, it lists the files and directories of the current directory, alphabetically:

* ![ft_ls0](/screenshots/ft_ls0.png)

It can list specific directories that are specified in arguments:

* ![ft_ls1](/screenshots/ft_ls1.png)

And with some option combinations, we can change its behavior:

* ![ft_ls2](/screenshots/ft_ls2.png)

Here we gave 3 different options, `Y`, `l` and `t`. The `Y` option colors the output, the `l` option prints more details, and the `t` option sort the files by modification time.

Here is a table of all the available option

| Option | Description |
| --- | --- |
| `-l` | Long listing format |
| `-R` | List subdirectories recursively |
| `-a` | List files and directories that start with a *.* (dot) |
| `-A` | Same as above (`-a`) but do not list the current directory alias *.* and parent directory alias *..*
| `-r` | Print the sorted list in a reverse order |
| `-t` | Sort by modification time |
| `-G` | Colorize the output following the LSCOLORS environnement variable |
| `-1` | List one file per line |
| `-T` | With the `-l` option, also prints the second and the year |
| `-D` | Prints the full path of each files |
| `-S` | Sort by file size |
| `-U` | Do not sort |
| `-u` | Sort by access time |
| `-Y` | Colorize the output but with the a default LSCOLORS |
| `-n` | List numeric user and group IDs |
| `-f` | Do not sort and print by the system order |
