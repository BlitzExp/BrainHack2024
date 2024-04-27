# Base Image
FROM ubuntu:latest

# The necessary installations
RUN apt-get update && \
    apt-get install -y g++ libsfml-dev &&\
    apt install -y pcmanfm featherpad lxtask xterm

# Set working directory
WORKDIR /app

# Copy the contents of the directory onto the container
COPY . .

# Compile main.cpp et al.
RUN g++ -c main.cpp -o main.o

# Linking the main executable with the SFML libraries
RUN g++ main.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system

# Set DISPLAY environment variable
ENV DISPLAY=host.docker.internal:0.0

# Running Xvfb and the app
CMD ["./sfml-app"]
