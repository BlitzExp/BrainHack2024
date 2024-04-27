# Base Image
FROM ubuntu:latest

# The necessary installations
RUN apt-get update && \
    apt-get install -y g++ libsfml-dev x11-apps xvfb

# Set working directory
WORKDIR /app

# Copy the contents of the directory onto the container
COPY . .

# Compile main.cpp et al.
RUN g++ -c main.cpp -o main.o

# Linking the main executable with the SFML libraries
RUN g++ main.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system

# Set DISPLAY environment variable
ENV DISPLAY=:99

# Running Xvfb and the app
CMD Xvfb :99 -screen 0 1024x768x16 & ./sfml-app
