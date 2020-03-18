C server that handles commands like FTP or something.

**TODO**: Needs a rewrite.
Crashes on random commands, which worked fine hundred years ago.

# Ubuntu

## Requirements:

```sudo apt install libmxml-dev```


# MakeFile generated using

http://solver.assistedcoding.eu/makefilegen

# Build

```bash
make clean # on second run

make
```

# Usage

```./project # Run server```

In another terminal

telnet localhost 8090 # Run client


## Shorcut:

```bash 
make clean; make; ./project
```
