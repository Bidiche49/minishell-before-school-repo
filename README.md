# minishell-before-school-repo


Start le server\n
```./ircserv 6667 go``` Start le server/n
 ```./aug.sh``` ```./alex.sh``` ```./bidiche.sh``` Log des clients dans des terminaux différents.\n

Commandes de base :\n
 ```CREATE <nom du channel>``` Créer un channel. (Te met admin du channel)\n
 ```INVITE <nickname>``` Inviter un user.  (admin)\n
```JOIN <nom du channel>``` Rejoindre un channel en particulier.\n

Commandes channel :\n
```KICK <nickname>``` Kick un user. (admin)\n
```INVITE <nickname>``` Inviter un user. (admin)\n
```TOPIC``` \n
        ```-p``` Print le topic.\n
        ```-s <nouvelle> <description> <sur> <autant> <d'arg> <que> <tu> <veux>``` Set le nouveau topic. (admin ou pas selon les paramètres du channel)\n
```QUIT``` Quitte le channel\n
```MODE <opt>``` Gérer le channel avec les options suivante:\n
        ```MODE -i``` Activer ou désactiver le mode "invite only".\n
        ```MODE -t``` Activer ou désactiver le fait de devoir être admin pour set le topic.\n
        ```MODE -k -d``` Delete le mot de passe.\n
        ```MODE -k -s <nouveau mot de passe>``` Set le nouveau mot de passe.\n
        ```MODE -o <nickname>``` Up ou down les droits d'un user.\n
        ```MODE -l -d``` Delete la limite max d'users.\n
        ```MODE -l -s <un int>``` Set la limite max d'users.\n
