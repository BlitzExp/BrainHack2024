#Base Image
FROM ubuntu:latest


#The necessary installations
RUN apt-get update && \ 
    apt-get upgrade -y &&\
    apt install -y g++ - &&\
    apt-get install -y libsfml-dev &&\
    apt-get install -y x11-apps

#1. Update the system
#2. Get upgrades
#3. Install g++ compiler for linux
#4. Install sfml library

#Set workind directory
WORKDIR /app

#Copy the contents of the directory onto the container
COPY . .

#Compile main.cpp et al.
RUN g++ -c main.cpp

#Linking the main executable with the SFML libraries
RUN g++ main.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system

#Giving execution permissions
RUN chmod 777 sfml-app

ENV DISPLAY=:0

#Running the app and Xvfb
CMD [ "./sfml-app" ] 


