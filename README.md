# minishell-before-school-repo


Start le server
```./ircserv 6667 go``` Start le server
 ```./aug.sh``` ```./alex.sh``` ```./bidiche.sh``` Log des clients dans des terminaux différents.

Commandes de base :
 ```CREATE <nom du channel>``` Créer un channel. (Te met admin du channel)
 ```INVITE <nickname>``` Inviter un user.  (admin)
```JOIN <nom du channel>``` Rejoindre un channel en particulier.

Commandes channel :
```KICK <nickname>``` Kick un user. (admin)
```INVITE <nickname>``` Inviter un user. (admin)
```TOPIC``` 
        ```-p``` Print le topic.
        ```-s <nouvelle> <description> <sur> <autant> <d'arg> <que> <tu> <veux>``` Set le nouveau topic. (admin ou pas selon les paramètres du channel)
```QUIT``` Quitte le channel
```MODE <opt>``` Gérer le channel avec les options suivante:
        ```MODE -i``` Activer ou désactiver le mode "invite only".
        ```MODE -t``` Activer ou désactiver le fait de devoir être admin pour set le topic.
        ```MODE -k -d``` Delete le mot de passe.
        ```MODE -k -s <nouveau mot de passe>``` Set le nouveau mot de passe.
        ```MODE -o <nickname>``` Up ou down les droits d'un user.
        ```MODE -l -d``` Delete la limite max d'users.
        ```MODE -l -s <un int>``` Set la limite max d'users.
