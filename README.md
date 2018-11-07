# What is '**ls**'

**ls** is a command used for listing directories in a file system. And can also print details about files and/or directories. The behavior of the command depends on the options it receives from the arguments.

The goal of this project was to reimplement the behavior of this command with a minimum of options.

Without arguments nor options, it lists the files and directories of the current directory, alphabetically:

* ![ft_ls0](/screenshots/ft_ls0.png)

It can list specific directories that are specified in arguments:

* ![ft_ls1](/screenshots/ft_ls1.png)

And with some option combinations, we can change its behavior:

* ![ft_ls2](/screenshots/ft_ls2.png)

Here we gave 3 different options, `Y`, `l` and `t`. The `Y` option colors the output, the `l` option ask for more details and prints them, and the `t` option sort the files by modification time.
