##
## Makefile for Makefile in /home/van-de_j/Tek3/rendu/RType/rtype/server/src
##
## Made by Jessica VAN-DEN-ZANDE
## Login   <van-de_j@epitech.net>
##
## Started on  Mon Dec 19 18:28:51 2016 Jessica VAN-DEN-ZANDE
## Last update Sat Dec 31 15:24:00 2016 Axel Vencatareddy
##

CXX		= g++

NAME		= client

DIR_PROTO	= ../common/src/

DIR		= src/

SRC		= $(DIR_PROTO)RtypeProtocol.cpp	\
		  $(DIR)AComponent.cpp		\
		  $(DIR)ASocket.cpp		\
		  $(DIR)Button.cpp		\
		  $(DIR)Core.cpp		\
		  $(DIR)Graphique.cpp		\
		  $(DIR)Main.cpp		\
		  $(DIR)Object.cpp		\
		  $(DIR)Room.cpp		\
		  $(DIR)RoomManager.cpp		\
		  $(DIR)Scene.cpp		\
		  $(DIR)Sprite.cpp		\
		  $(DIR)Animation.cpp		\
		  $(DIR)PlayerLink.cpp		\
		  $(DIR)Socket.cpp

OBJ		= $(SRC:.cpp=.o)

CXXFLAGS	= -std=c++11 -W -Wall -Werror -Wextra -I ../common/inc/ -I ./inc/

LDFLAGS		= -Wl,-rpath,./lib -L./lib/ -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

RM		= rm -rf

all:		$(NAME)

$(NAME):	$(OBJ)
		$(CXX) $(OBJ) -o $(NAME) $(LDFLAGS)

clean:
		$(RM) $(OBJ)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:		all clean fclean re
