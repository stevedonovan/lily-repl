# lily-repl

### Version 0.1

This package provides a simple repl for Lily. The repl is able to print out
single expressions, or parse statements. The repl will change prompts if the
last command sent was not complete.

This version includes a small Lily binding to [linenoise](https://github.com/antirez/linenoise)
much inspired by Rob Hoelz' [lua-linenoise](https://github.com/hoelzro/lua-linenoise)
To build it,

```
cmake .
make
```

The repl file is small because it uses `spawni` to create an interpreter inside
of an interpreter. The sub interpreter does the actual lifting.

### Requirements

Only `FascinatedBox/spawni` is required.

```
$ /path/to/lily/garden/garden.py install github FascinatedBox/spawni.git
```
