# Pipex
An introduction on command execution

## Introduction
Pipex is a first approach on the command execution and an first approach to
[minishell](https://github.com/GermainToubol/minishell), introducing the
`forks`, `pipe` and `execve` commands.

## Objective
The aim of this project is to mimic the shell behaviour with the following
input:

```bash
cmd1 < infile | cmd2 > outfile
```

The main difficulty on this project is to understand how the different elements
can work together to archive it. The program is used as follows:

```bash
./pipex infile cmd1 cmd2 outfile
```

## Bonus
To go further on the way to mimic an input, the bonus aim is to reproduce the
following behaviours:

```bash
< in cmd1 | cmd2 | cmd3 | ... | cmdn > out
<< TAG cmd1 | cmd2 >> out
```
