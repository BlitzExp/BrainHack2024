# Base Image
FROM ubuntu:latest

# The necessary installations
RUN apt-get update && \
    apt-get install -y g++ libsfml-dev x11-apps

# Set working directory
WORKDIR /app

# Copy the contents of the directory onto the container
COPY . .

# Compile main.cpp et al.
RUN g++ -c main.cpp -o main.o

# Linking the main executable with the SFML libraries
RUN g++ main.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system

# Set DISPLAY environment variable for Linux
ENV DISPLAY=:0

# Running the app
CMD ["./sfml-app"]

