# philosophers

!!! LIBFT NOT AUTHORIZED
if a func from libft is used, it will have to be copied :(
	
MON IDEE POUR PHILO
chaque thread doit manger un certain nombre de fois pour que le programme puisse se terminer. Je vais enregistrer le nombre de fois où un thread a mangé dans un variable (au sein du thread). Le thread doit communiquer avec le processus le nombre de fois où il a mangé.

Une solution pour philo:
- diviser les philosophes en deux groupes: pair et impair.

en effet, le travail que j'ai effectué ce matin ne correspond pas au sujet demandé: les threads ne devraient pas prendre de décisions basée sur les informations issues d'autres threads, mais seulement basé sur les informations directement à sa disposition.

memory:
valgrind --trace-children=yes --leak-check=full --show-leak-kinds=all ./philo 4 800 200 200 4

data race:
valgrind --tool=drd ./philo 4 800 200 200 4

valgrind --tool=helgrind ./philo 4 800 200 200 4

change PHILO NUmbers!!! must start with 0NE

# Changes to be done
- handle double death for test 4 310 200 100