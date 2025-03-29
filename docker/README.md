# Docker

ubuntu:22.04

## Build and run image

### Build

Building the base image is required.
```
docker build -t obsidian-ubuntu2204-base ./ubuntu2204/base
```

Build image using git repository
```
docker build -t obsidian-ubuntu2204 ./ubuntu2204/github
```

Build image using copy instruction
```
docker build -f ./ubuntu2204/Dockerfile -t obsidian-ubuntu2204 ..
```

Run image
```
docker run obsidian-ubuntu2204
```