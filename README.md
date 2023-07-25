* This is a collaborative project made by Tanya Chiramba and Joseph Abang, Students of software engineering at ALX Africa. This repo contains files for the **simple_shell project**. The project requires us to develop our own UNIX command interpreter (shell).

## File structure

These are the files with custom system calls and functions with a brief description.

|  ***file***  | ***Description***     |
|-------------|------------------------|
| ['.shell.c'](./shell.c) | Contains entry point, file and line reader functions |
| ['AUTHORS'](./AUTHORS) | The names of contributors |
| ['README.md'](./README.md) | Readme.md file |
| ['shell_data.c'](./shell_data.c) | Contains initializer, free and other helperr functions |
| ['exec.c'](./exec.c) | File contains execution functions |
| ['exec_help.c'](.exec_help/.c) | Helper functions for the execution of the shell |
| ['tokenizer.c'](./tokenizer.c) | Line tokenizer and helper function |
| ['getline.c'](./getline.c) | Gets line  |
| ['get_path.c'](./execute.c) | Gets and handles path |
| ['cmd.c.c'](./execute_file.c) | Contains some built-in commands |
| ['cd.c'](./cd.c) | Contains cd built-in |
| ['string.c'](./string.c) | Contains (string.h) functions implemented by the team |
| ['more_string.c'](./more_string.c) | File contains more (string.h) fuctions |
| ['setenv.c'](./setenv.c) | Set environment variables |
| ['shell.h'](./shell.h) | Header file containing all prototypes |
| ['hsh'](./hsh) | Executable File (Program name) |

<h2>REQUIREMENTS<h2>
<body>
<ul> 
	<li> Write a UNIX command line interpreter.</li>
	<li>Handle command lines with arguments</li>
	<li>Handle the PATH </li>
	<li>Implement the exit built-in, that exits the shell</li>
	<li>Implement the env built-in, that prints the current environment</li>
	<li>Write your own getline function</li>
	<li>You are not allowed to use strtok</li>
	<li>Implement the setenv and unsetenv builtin commands</li>
	<li>Implement the builtin command `cd`</li>
	<li>Handle the commands separator ;</li>
	<li>Handle the && and || shell logical operators</li>
	<li>Implement the alias builtin command</li>
	<li>Handle variables replacement</li>
	<li>Handle comments (#)</li>
	<li>File as input</li>
</ul>
</body>
