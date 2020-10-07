# Usage 

## Build

Build with: 
```
make
```

And run `./build/task[N]` where `N` is the task number.

## Usage withought OpenMP

If you do not whant to install OpenMP on your machine (totally get it), you might use the docker container.
Working directory would be mounted as a volume.

To run the container:
```
docker-compose up -d
```


To open interactive shell inside the container:
```
docker-compose exec openmp_dev_environment /bin/bash
```
