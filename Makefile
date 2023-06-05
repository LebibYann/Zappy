##
## EPITECH PROJECT, 2023
## B-OOP-400-PAR-4-1-arcade-yann.lebib
## File description:
## Makefile
##

GUI_SRC = ./gui/
SERVER_SRC = ./server/
AI_SRC = ./ai/

ECHO = echo -e
CAT = /usr/bin/cat
CLS_LINE = echo -ne "\r\033[0K"

LIB_DIRS = ./lib/
LIB_FLAGS =
LIB_INCL_PATH = ./include/

DEFLT	=	"\033[00m"
PINK	=	"\033[0;36m"
GREEN	=	"\033[1;32m"
TEAL	=	"\033[1;36m"
RED 	=	"\033[0;31m"
BLUE	=	"\033[34m"
PURPLE	=	"\033[0;35m"
BLINK 	= 	"\033[1;92m"
SBLINK	= 	"\033[0m"
INVERT  =	"\033[7m"

all:
	@make zappy_gui --no-print-directory; \
	make zappy_server --no-print-directory; \
	make zappy_ai --no-print-directory;

re: fclean all

zappy_gui:
	@make -C $(GUI_SRC) --no-print-directory

zappy_server:
	@make -C $(SERVER_SRC) --no-print-directory

zappy_ai:
	@make -C $(AI_SRC) --no-print-directory

clean:
	@make clean -C $(GUI_SRC) --no-print-directory; \
	make clean -C $(SERVER_SRC) --no-print-directory; \
	make clean -C $(AI_SRC) --no-print-directory;
	@$(ECHO) $(BLINK) "[CLEAN DONE]" $(DEFLT)

fclean:
	@make fclean -C $(GUI_SRC) --no-print-directory; \
	make fclean -C $(SERVER_SRC) --no-print-directory; \
	make fclean -C $(AI_SRC) --no-print-directory;
	@find ./lib/ -maxdepth 1 -name "*.a" -delete
	@$(ECHO) $(BLINK) "[FCLEAN DONE]" $(DEFLT)

lib: FORCE
	@for lib_dir in $(LIB_DIRS); do \
		$(ECHO) $(BLINK)$(PURPLE)"[COMPILING LIBRARIES IN: $$lib_dir]"$(DEFLT);\
		dirs=$$(find $$lib_dir -maxdepth 1 -mindepth 1 -type d 2>/dev/null); \
		for lib_path in $$dirs; do \
			$(ECHO) $(BLINK)$(BLUE)"[COMPILING LIBRARY: $$lib_path]"$(DEFLT);\
			make -C $$lib_path --no-print-directory; \
		done \
	done

lib_clean:
	@find .	-name "*.a" -delete
	@$(ECHO) $(GREEN) "[.a static libraries files deleted.]" $(DEFLT)
	@for lib_dir in $(LIB_DIRS); do \
		$(ECHO) $(BLINK)$(PURPLE)"[CLEANING LIBRARIES IN $$lib_dir]"$(DEFLT); \
		dirs=$$(find $$lib_dir -maxdepth 1 -mindepth 1 -type d 2>/dev/null); \
		for lib_path in $$dirs; do \
			$(ECHO) $(BLINK)$(BLUE)"[CLEANING LIBRARY : $$lib_path]"$(DEFLT); \
			make -C $$lib_path fclean --no-print-directory; \
			lib_name=$$(basename $$lib_path); \
			rm -rf $(LIB_INCL_PATH)$$lib_name; \
		done \
	done

lib_re: lib_clean lib

FORCE:
