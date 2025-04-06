CC = cc 

CFLAGS = -Wall -Wextra -Werror -g3 #-fsanitize=address

NAME = cub3D

NAME_BONUS = cub3D_bonus

LIBFT = ./includes/libft/

LIBFT_NAME = ./includes/libft/libft.a

MLXFLAGS = -Lmlx -lmlx -L/usr/lib -Imlx -lXext -lX11 -lm -lz

SOUFAYNE_FILES  = includes/get_next_line/get_next_line.c includes/get_next_line/get_next_line_utils.c \
$(addprefix ./mandatory/,  main.c \
	parsing/check_color_comma.c parsing/check_color.c parsing/start.c parsing/getMap.c  parsing/texture_validation.c parsing/texture_validation_helper.c parsing/utils.c parsing/my_split.c \
	parsing/map/map_parsing.c parsing/map/map_validation.c parsing/map/adjust_map.c)

AMINE_FILES = $(addprefix ./mandatory/, raycasting/start.c raycasting/init_player.c raycasting/get_position.c \
		raycasting/handle_keys.c raycasting/update.c raycasting/cast_rays.c raycasting/move_player.c raycasting/draw_wall.c \
		raycasting/cast_utils.c raycasting/move_utils.c raycasting/free_resources.c)

SOUFAYNE_FILES_BONUS  = includes/get_next_line/get_next_line.c includes/get_next_line/get_next_line_utils.c \
$(addprefix ./bonus/,  main_bonus.c \
	parsing/check_color_comma_bonus.c parsing/check_color_bonus.c parsing/start_bonus.c parsing/getMap_bonus.c  parsing/texture_validation_bonus.c parsing/texture_validation_helper_bonus.c parsing/utils_bonus.c parsing/my_split_bonus.c \
	parsing/map/map_parsing_bonus.c parsing/map/map_validation_bonus.c parsing/map/adjust_map_bonus.c \
	)

AMINE_FILES_BONUS = $(addprefix ./bonus/, raycasting/start_bonus.c raycasting/color.c raycasting/initialize_resources.c raycasting/door_bonus.c raycasting/init_player_bonus.c raycasting/get_position_bonus.c \
		raycasting/handle_keys_bonus.c raycasting/update_bonus.c raycasting/cast_rays_bonus.c raycasting/move_player_bonus.c raycasting/draw_wall_bonus.c \
		raycasting/cast_utils_bonus.c raycasting/move_utils_bonus.c raycasting/free_resources_bonus.c raycasting/minimap_bonus.c raycasting/animation_bonus.c)

FILES_O = $(SOUFAYNE_FILES:.c=.o) $(AMINE_FILES:.c=.o)

FILES_O_BONUS = $(SOUFAYNE_FILES_BONUS:.c=.o) $(AMINE_FILES_BONUS:.c=.o)

# Override implicit rules to suppress output
%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(FILES_O)
	@echo "\033[0;32mCOMPILING...\033[0m"
	@make -s -C $(LIBFT) > /dev/null 2>&1
	@$(CC) $(CFLAGS) $(FILES_O) $(LIBFT_NAME) $(MLXFLAGS) -o $(NAME) > /dev/null 2>&1
	@echo "\033[0;32mDONE\033[0m"

all : $(NAME) bonus

$(NAME_BONUS) : $(FILES_O_BONUS)
	@echo "\033[0;32mCOMPILING...\033[0m"
	@make -s -C $(LIBFT) > /dev/null 2>&1
	@$(CC) $(CFLAGS) $(FILES_O_BONUS) $(LIBFT_NAME) $(MLXFLAGS) -o $(NAME_BONUS) > /dev/null 2>&1
	@echo "\033[0;32mDONE\033[0m"

bonus: $(NAME_BONUS)

clean : 
	@make clean -s -C $(LIBFT)
	@rm -f $(FILES_O) $(FILES_O_BONUS) $(BONUS_O)

fclean : clean
	@make fclean -s -C $(LIBFT)
	@rm -f $(NAME) $(NAME_BONUS)

re : fclean $(NAME) $(NAME_BONUS)

.PHONY : clean fclean

.SECONDARY : $(FILES_O) $(FILES_O_BONUS)


WELCOME_MESSAGE:
	@echo "\n\033[1;32m"
	@echo "  _____ _    _  ____  ____   _____ "
	@echo " / ____| |  | || __ )|___ \\/  __ \\"
	@echo "| |    | |  | ||  _ \  __) |. |  | |"
	@echo "| |    | |  | || | | | |__ <| |  | |"
	@echo "| |____| |__| || |_|  ___) || |__| |"
	@echo " \_____|\____/ |____/|____/ |_____/"
	@echo "\n\033[1;36m     [ 1337 Project by Awesome Team ]\033[0m\n"
	@echo "\033[1;36m     [ @Amine_Bouramtane and @Soufyane_Marsi ]\033[0m\n"
	@echo "\033[1;33m      Use arrow (WASD) keys to move and (E) to open doors | ESC to quit\033[0m\n"

# Run bonus
run_bonus: WELCOME_MESSAGE
	@./cub3D_bonus maps/bonus.cub

# Run mandatory
run_mandatory: WELCOME_MESSAGE
	@./cub3D maps/mandatory.cub