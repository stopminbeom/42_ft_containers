NAME		=	test
CXX			=	clang++
CXXFLAGS	=	-Wall -Wextra -Werror -std=c++98

SRC			=	main.cpp
				
RM			=	rm -rf

OBJ			=	$(SRC:.cpp=.o)

%.o			:	%.cpp
				$(CXX) $(CXXFLAGS) -c $< -o $@

$(NAME)		:	$(OBJ)
				$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME)

all			:	$(NAME)

clean		:
				$(RM) $(OBJ)

fclean		:	clean
				$(RM) $(NAME)

re			:	fclean all

.PHONY		:	all clean fclean re