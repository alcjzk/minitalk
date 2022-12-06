################################################################################
# DIRECTORIES ##################################################################
################################################################################

# Includes
INC_DIR = inc/ libft/inc/

# Objects and dependencies
OBJ_DIR = obj/

# Sources
SRC_DIR = src/

# Target directory
TARGET_DIR = ./

################################################################################
# BASIC ########################################################################
################################################################################

# Target name
CLIENT_NAME = client
SERVER_NAME = server

# Sources
SRCS_CLIENT = client.c send.c
SRCS_SERVER = server.c recv.c

OBJS_CLIENT = $(SRCS_CLIENT:%.c=$(OBJ_DIR)%.o)
OBJS_SERVER = $(SRCS_SERVER:%.c=$(OBJ_DIR)%.o)

# Compiler
CC = cc

# Optimization flags
OPT = -O3

# Extra flags
EXTRA = -Wall -Werror -Wextra

# Depflags
DEP = -MP -MMD

################################################################################
# CONFIG #######################################################################
################################################################################

vpath %.c src/
.PHONY: all clean fclean re debug d libft
override FLAGS += $(EXTRA) $(foreach DIR,$(INC_DIR),-I$(DIR)) $(OPT) $(DEP)
DEPS = $(SRCS_CLIENT:%.c=$(OBJ_DIR)%.d) $(SRCS_SERVER:%.c=$(OBJ_DIR)%.d) 
EXPORTS =\
	OBJ_DIR="$(OBJ_DIR:%=$(shell pwd)/%)"\
	INC_DIR="$(INC_DIR:%=$(shell pwd)/%)"\
	TARGET_DIR="$(TARGET_DIR:%=$(shell pwd)/%)"\
	OPT="-O3"

################################################################################
# RULES ########################################################################
################################################################################

# Default rule
all: $(CLIENT_NAME) $(SERVER_NAME)

# Objects
$(OBJS_CLIENT): $(OBJ_DIR)%.o: %.c | $(OBJ_DIR)
	$(CC) $(FLAGS) -c -o $@ $<

$(OBJS_SERVER): $(OBJ_DIR)%.o: %.c | $(OBJ_DIR)
	$(CC) $(FLAGS) -c -o $@ $<

# Target
$(CLIENT_NAME): $(OBJS_CLIENT) | $(TARGET_DIR) libft
	$(CC) $(FLAGS) -o $@ $^ -L. -lft

$(SERVER_NAME): $(OBJS_SERVER) | $(TARGET_DIR) libft
	$(CC) $(FLAGS) -o $@ $^ -L. -lft

libft:
	make all -C libft $(EXPORTS)

# Cleanup
clean: clean_local
	make clean -C libft $(EXPORTS)

clean_local:
	rm -rf $(OBJS_SERVER) $(OBJS_CLIENT) $(DEPS)

fclean_local: clean_local
	rm -rf $(CLIENT_NAME) $(SERVER_NAME)

fclean: fclean_local
	make fclean -C libft $(EXPORTS)

# Debug
debug:
	make fclean
	make all FLAGS="-g -fsanitize=address"

# Aliases
re: fclean all
d: debug

# Dir creation
$(OBJ_DIR) $(TARGET_DIR):
	@mkdir -p $@

-include $(DEPS)