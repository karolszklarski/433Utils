/*
  RFSniffer

  Usage: ./RFSniffer [<pulseLength>]
  [] = optional

  Hacked from http://code.google.com/p/rc-switch/
  by @justy to provide a handy RF code sniffer
*/

#include "../rc-switch/RCSwitch.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>


RCSwitch mySwitch;


double getMicrotime(){
    struct timeval currentTime;
    gettimeofday(&currentTime, NULL);
    return currentTime.tv_sec + ((double)currentTime.tv_usec) / 1000000L;
}


int main(int argc, char *argv[]) {

     // This pin is not the first pin on the RPi GPIO header!
     // Consult https://projects.drogon.net/raspberry-pi/wiringpi/pins/
     // for more information.
     int PIN = 2;

     if (wiringPiSetup() == -1) {
       printf("wiringPiSetup failed, exiting...");
       exit(1);
     }

     mySwitch = RCSwitch();
     mySwitch.enableReceive(PIN);  // Receiver on interrupt 0 => that is pin #2

     while(1) {
      if (mySwitch.available()) {
        printf("%f %i\n", getMicrotime(), mySwitch.getReceivedValue());
        fflush(stdout);
        mySwitch.resetAvailable();
      }
      usleep(10);
    }
}
