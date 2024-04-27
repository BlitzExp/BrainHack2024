# Base Image
FROM ubuntu:latest

# The necessary installations
RUN apt-get update 

# Set working directory
WORKDIR /app

# Copy the contents of the directory onto the container
COPY . .
# Running the app
CMD ["/Game/play.bat"]

