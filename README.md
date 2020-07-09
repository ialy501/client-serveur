# client-serveur

%%%%%%PETIT DESCRPITION%%%%%%%%%

Créer un socket UDP.
Envoyer un message au serveur.
Attendez que la réponse du serveur soit reçue.
Traitez la réponse et revenez à l'étape 2, si nécessaire.
Fermez le descripteur de socket et quittez.
Fonctions nécessaires:

  int socket (int domaine, type int, protocole int)
 Crée un socket non lié dans le domaine spécifié.
 Retourne le descripteur de fichier de socket.
Arguments : 
domain - Spécifie la communication 
domaine (AF_INET pour IPv4 / AF_INET6 pour IPv6) 
type - Type de socket à créer 
(SOCK_STREAM pour TCP / SOCK_DGRAM pour UDP) 
protocol - Protocole à utiliser par socket. 
0 signifie utiliser le protocole par défaut pour la famille d'adresses.

 int bind (int sockfd, struct struct sockaddr * addr, socklen_t addrlen)

  int close (sockfd)
 Fermer un descripteur de fichier


%%%%%%%%%% COMPILATION %%%%%%%%

gcc client.c -o client( peut contenir maximum 5 client)

ou

gcc serveur.c -o serveur

vous choisiriez le concepte de votre choix

%%%%%%%%%%%% lancement %%%%%%%

./client

ou

./serveur

ce lancement depend du choix de votre compilation et doit etre exacte de celui-ci

