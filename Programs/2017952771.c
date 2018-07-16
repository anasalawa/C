#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define SERVER_PORT 47500

int main() {
   FILE *fp;
   struct hostent *hp;
   struct sockaddr_in sin;
   char *host;
   char *buf;
   int t;
   int len;

   host = "localhost";
   
   /* Peer's IP address is translated into the host name */
  
   hp = gethostbyname(host);
   if (!hp) {
      fprintf(stderr, "simplex-talk: unknown host: %s\n", host);
      exit(1);
   }

   /* Address data structure is built */
  
   bzero((char *)&sin, sizeof(sin));
   sin.sin_family = AF_INET;
   bcopy(hp->h_addr, (char *)&sin.sin_addr, hp->h_length);
   sin.sin_port = htons(SERVER_PORT);

   /* Active open */
   
   if ((t = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
      perror("simplex-talk: socket");
      exit(1);
   }
   if (connect(t, (struct sockaddr *)&sin, sizeof(sin)) < 0){
      perror("simplex-talk: connect");
      close(t);
      exit(1);
   }

   /* Sending lines of text */
   
   buf = "2017952771\0";
   send(t, buf, 11, 0);

   /* Closing the connection */
  
   shutdown (t, 2);
}