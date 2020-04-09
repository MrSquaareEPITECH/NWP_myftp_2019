##
## EPITECH PROJECT, 2019
## NWP_myftp_2019
## File description:
## Makefile
##

CLIENT_DIR			=		client
SERVER_DIR			=		server

MAKEFLAGS			+=		--silent

all:				server

clean:				server_clean

fclean:				server_fclean

re:					fclean all

client:
					cd $(CLIENT_DIR) && $(MAKE) all

client_clean:
					cd $(CLIENT_DIR) && $(MAKE) clean

client_fclean:
					cd $(CLIENT_DIR) && $(MAKE) fclean

client_re:			client_fclean client

client_debug:
					cd $(CLIENT_DIR) && $(MAKE) debug

client_debug_re:	client_fclean client_debug

server:
					cd $(SERVER_DIR) && $(MAKE) all

server_clean:
					cd $(SERVER_DIR) && $(MAKE) clean

server_fclean:
					cd $(SERVER_DIR) && $(MAKE) fclean

server_re:			server_fclean server

server_debug:
					cd $(SERVER_DIR) && $(MAKE) debug

server_debug_re:	server_fclean server_debug

full:				client server

full_clean:			client_clean server_clean

full_fclean:		client_fclean server_fclean

full_re:			full_fclean full

full_debug:			client_debug server_debug

full_debug_re:		full_fclean full_debug

.PHONY:				all clean fclean re															\
					client client_clean client_fclean client_re client_debug client_debug_re	\
					server server_clean server_fclean server_re server_debug server_debug_re	\
					full full_clean full_fclean full_re full_debug full_debug_re				\
