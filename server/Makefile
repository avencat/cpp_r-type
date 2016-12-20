##
## Makefile for Makefile in /home/van-de_j/Tek3/rendu/RType/rtype/server/src
## 
## Made by Jessica VAN-DEN-ZANDE
## Login   <van-de_j@epitech.net>
## 
## Started on  Mon Dec 19 18:28:51 2016 Jessica VAN-DEN-ZANDE
## Last update Tue Dec 20 13:15:17 2016 Jessica VAN-DEN-ZANDE
##

CXX		= g++

NAME		= server

DIR_PROTO	= ../common/src/

DIR		= src/

SRC		= $(DIR_PROTO)RtypeProtocol.cpp	\
		  $(DIR)main.cpp		\
		  $(DIR)ASocket.cpp		\
		  $(DIR)LinuxConnection.cpp	\
		  $(DIR)Socket.cpp

OBJ		= $(SRC:.cpp=.o)

CXXFLAGS	= -std=c++11 -W -Wall -Werror -Wextra -I ../common/inc/ -I ./inc/

RM		= rm -rf

all:		$(NAME)

$(NAME):	$(OBJ)
		$(CXX) $(OBJ) -o $(NAME) $(DLFLAGS)

clean:
		$(RM) $(OBJ)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:		all clean fclean re
