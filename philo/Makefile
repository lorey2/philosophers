# --------------------------------------------
# Variables
# --------------------------------------------

NAME          = philo
NAME_BONUS    = nothing
INCLUDE       = ./
SRC_DIR       = ./
SRC_DIR_BONUS = ./
OBJ_DIR       = obj/
OBJ_DIR_BONUS = obj_bonus/
CC            = gcc
CFLAGS        = -Wall -Werror -Wextra -I$(INCLUDE)
RM            = rm -f
AR            = ar rcs

# --------------------------------------------
# Colors
# --------------------------------------------

DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

# --------------------------------------------
# Source and Object Files
# --------------------------------------------

SRC_FILES        = dinner getter_setter \
				   init mini_libft \
				   monitor philosophers \
				   safe_thread_mutex synchro_utils \
				   utils write

SRC              = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ              = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

# --------------------------------------------
# Targets
# --------------------------------------------

# Default target
all: $(NAME)

# push_swap Compilation
$(NAME): $(OBJ)
	@$(CC) $(OBJ) -o $(NAME)
	@echo "$(GREEN)push_swap compiled!$(DEF_COLOR)"

# Object files compilation (Main)
$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@echo "$(YELLOW)Compiling: $<$(DEF_COLOR)"
	@$(CC) $(CFLAGS) -c $< -o $@

# --------------------------------------------
# Clean and Remove Object Files
# --------------------------------------------

# Clean object files
clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(BLUE)push_swap object files cleaned!$(DEF_COLOR)"

# Full clean (objects and executables)
fclean: clean
	@rm -f $(NAME)
	@echo "$(CYAN)push_swap executables cleaned!$(DEF_COLOR)"

# Rebuild everything
re: fclean all
	@echo "$(GREEN)Cleaned and rebuilt everything for push_swap!$(DEF_COLOR)"

# --------------------------------------------
# Norminette Check
# --------------------------------------------

# Norminette code style check
norm:
	@norminette $(SRC) $(INCLUDE) | grep -v Norme -B1 || true

# --------------------------------------------
# Phony Targets
# --------------------------------------------

.PHONY: all clean fclean re norm
