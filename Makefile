##
## EPITECH PROJECT, 2019
## NWP_myftp_2019
## File description:
## Makefile
##

NAME				=		myftp
CLIENT_NAME			=		myftp_client
SERVER_NAME			=		myftp_server

CLIENT_DIR			=		client
SERVER_DIR			=		server

CP					=		cp
RM					=		rm -rf

MAKEFLAGS			+=		--silent

all:				server
					$(CP) $(SERVER_DIR)/$(SERVER_NAME) $(NAME)

clean:				server_clean

fclean:				server_fclean
					$(RM) $(NAME)

re:					fclean all

tests_run:			server_tests_run

tests_sh:			server_tests_sh

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

client_tests_run:
					cd $(CLIENT_DIR) && $(MAKE) tests_run

client_tests_sh:
					cd $(CLIENT_DIR) && $(MAKE) tests_sh

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

server_tests_run:
					cd $(SERVER_DIR) && $(MAKE) tests_run

server_tests_sh:
					cd $(SERVER_DIR) && $(MAKE) tests_sh

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
