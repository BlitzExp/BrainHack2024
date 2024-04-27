#!/bin/bash

docker build -t game .

xhost +
docker run -it --rm --name game -e DISPLAY=$DISPLAY -v /tmp/.X11-unix:/tmp/.X11-unix game
xhost -