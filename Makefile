# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/16 13:39:56 by taewonki          #+#    #+#              #
#    Updated: 2025/07/30 12:39:51 by taewonki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# --- 프로젝트 이름 ---
NAME = minishell

# --- 소스 파일 디렉토리 ---
SRCS_DIR = srcs

# --- 헤더 파일 디렉토리 ---
INCLUDES_DIR = includes

# --- Libft 디렉토리 ---
LIBFT_DIR = Libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

# --- 소스 파일 목록 ---
# srcs 디렉토리 내의 모든 .c 파일을 포함
SRCS = $(wildcard $(SRCS_DIR)/*.c)

# --- 오브젝트 파일 디렉토리 ---
OBJS_DIR = objs

# --- 오브젝트 파일 목록 ---
# 소스 파일을 objs 디렉토리 내의 .o 파일로 변환
OBJS = $(patsubst $(SRCS_DIR)/%.c, $(OBJS_DIR)/%.o, $(SRCS))

# --- 컴파일러 및 플래그 ---
CC = gcc
# CFLAGS에서 -I와 $(LIBFT_DIR) 사이에 공백 추가
CFLAGS = -Wall -Wextra -Werror -g -I$(LIBFT_DIR) # 디버깅 정보를 포함 (-g)

# --- 링커 플래그 ---
# Linux에서는 일반적으로 -lreadline만으로 충분합니다.
LDFLAGS = -lreadline -L$(LIBFT_DIR) -lft

# --- 색상 코드 (선택 사항) ---
GREEN = \033[0;32m
RED = \033[0;31m
NC = \033[0m

# --- 모든 타겟 ---
.PHONY: all clean fclean re libft

all: libft $(NAME)

# Libft를 먼저 빌드하는 타겟
libft:
	@echo "$(GREEN)Building Libft...$(NC)"
	@make -C $(LIBFT_DIR) bonus
	@echo "$(GREEN)Libft built successfully!$(NC)"

# 메인 실행 파일 빌드
$(NAME): $(OBJS_DIR) $(OBJS) $(LIBFT_LIB)
	@echo "$(GREEN)Linking $(NAME)...$(NC)"
	@$(CC) $(OBJS) $(LIBFT_LIB) $(LDFLAGS) -o $(NAME)
	@echo "$(GREEN)$(NAME) compiled successfully!$(NC)"

# 오브젝트 파일 디렉토리가 없으면 생성
$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

# .c 파일을 .o 파일로 컴파일하는 규칙
# CFLAGS에 이미 -I$(LIBFT_DIR)가 포함되었으므로 여기서는 중복 제거
$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -I$(INCLUDES_DIR) -c $< -o $@

# 모든 오브젝트 파일 및 Libft 오브젝트 파일 제거
clean:
	@echo "$(RED)Cleaning object files...$(NC)"
	@rm -rf $(OBJS_DIR)
	@make -C $(LIBFT_DIR) clean

# 모든 빌드 결과물 (실행 파일 및 라이브러리) 제거
fclean: clean
	@echo "$(RED)Cleaning $(NAME) and Libft library...$(NC)"
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean

# 전부 새로 빌드 (fclean 후 all)
re: fclean all

# make debug: -g 플래그만 추가하여 디버그 빌드를 위한 타겟
debug: CFLAGS += -g
debug: re
