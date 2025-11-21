#ifndef PROTOCOLE_H
#define PROTOCOLE_H

#define CLE 1234

typedef struct
{
  long  type;
  pid_t expediteur;
  char  texte[80];  
} MESSAGE;

#endif
