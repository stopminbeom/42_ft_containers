CXX			=	c++
CXXFLAGS	=	-Wall -Wextra -Werror -std=c++98
STLTYPE		=	-DTYPE=1
TESTTYPE	=	-DTYPE=2
STLNAME		=	STL_containers
TESTNAME	=	MY_containers
STLOUT		=	./STL
TESTOUT		=	./TEST
DIFF		=	./diff

SRC			=	test_main.cpp \
				./testfiles/vector_test.cpp \
				./testfiles/stack_test.cpp \
				./testfiles/map_test.cpp \
				./testfiles/set_test.cpp
				
RM			=	rm -rf

OBJ			=	$(SRC:.cpp=.o)

all			:	run

run			:	$(SRC)
				@$(CXX) $(CXXFLAGS) $(TESTTYPE) $(SRC) -o $(TESTNAME)
				@./$(TESTNAME) > $(TESTOUT)
				@$(CXX) $(CXXFLAGS) $(STLTYPE) $(SRC) -o $(STLNAME)
				@./$(STLNAME) > $(STLOUT)
				@diff $(STLOUT) $(TESTOUT) > $(DIFF); [ $$? -eq 1 ]

clean		:
				@$(RM) $(TESTOUT) $(STLOUT) $(DIFF)

fclean		:	clean
				@$(RM) $(TESTNAME) $(STLNAME)

re			:	fclean all

.PHONY		:	all clean fclean re run