
EXEC =chessprog  # macro  of the execute file name
Main =_main_chessprog.o
CON_struct =CON_struct__ArrayList.o CON_struct__GameBoard.o CON_struct__HistoryCell.o CON_struct__OrderedPair.o CON_struct__Address_Que.o
CON_func =CON_func__Parser.o CON_func__SaveLoad.o CON_func__game.o CON_func__mainAux.o CON_func__miniMax.o


GUI_OBJ =GUI__Manager.o GUI_ColorWin.o GUI_DifficultyWin.o GUI_GameModeWin.o GUI_GameWin.o GUI_LoadWin.o GUI_MenuWin.o
CONSOL_OBJ =$(CON_struct) $(CON_func)
# list of object files for chessprog.o linking


CC = gcc              										 # macro of the compiler command gcc
CC_FLAG =-std=c99 -Wall -Wextra -Werror -pedantic-errors    # the compiler flags   Wall - 
SDL_flag =$(CC_FLAG) -I/usr/local/lib/sdl_2.0.5/include/SDL2 -D_REENTRANT
LDFLAGS = -L/usr/local/lib/sdl_2.0.5/lib -Wl,-rpath,/usr/local/lib/sdl_2.0.5/lib -Wl,--enable-new-dtags -lSDL2 -lSDL2main

all: $(EXEC)

# linking rule for the executable
# because this target is the first, just 'make' will invoke this with no target.
$(EXEC): $(Main) $(CONSOL_OBJ) $(GUI_OBJ)
	$(CC) $(CC_FLAG) $(Main) $(CONSOL_OBJ) $(GUI_OBJ) $(LDFLAGS) -o $@   #LD are flags for linker
														 # $@ is the name of the target, in our case its $(EXEC) which is ChessProject

#general rule to compile a source file and produce an object file, meaning that 
#every rule   			ch_OrderedPair.o: 
#							$(CC) $(FLAG) -c $*.c
#can be deleted 
#.c.o:
#	$(CC) $(FLAG) –c $<

CON_struct__ArrayList.o: 
	$(CC) $(CC_FLAG) -c $*.c
CON_struct__GameBoard.o: 
	$(CC) $(CC_FLAG) -c $*.c
CON_struct__HistoryCell.o: 
	$(CC) $(CC_FLAG) -c $*.c
CON_struct__OrderedPair.o:
	$(CC) $(CC_FLAG) -c $*.c
CON_func__Parser.o: 
	$(CC) $(CC_FLAG) -c $*.c
CON_func__SaveLoad.o: 
	$(CC) $(CC_FLAG) -c $*.c
CON_struct__Address_Que.o:
	$(CC) $(CC_FLAG) -c $*.c	
CON_func__game.o:
	$(CC) $(CC_FLAG) -c $*.c
CON_func__mainAux.o: 
	$(CC) $(CC_FLAG) -c $*.c
CON_func__miniMax.o:
	$(CC) $(CC_FLAG) -c $*.c
GUI__Manager.o:
	$(CC) $(SDL_flag) -c $*.c
GUI_ColorWin.o:
	$(CC) $(SDL_flag) -c $*.c
GUI_DifficultyWin.o:
	$(CC) $(SDL_flag) -c $*.c
GUI_GameModeWin.o:
	$(CC) $(SDL_flag) -c $*.c
GUI_GameWin.o:
	$(CC) $(SDL_flag) -c $*.c
GUI_LoadWin.o:
	$(CC) $(SDL_flag) -c $*.c
GUI_MenuWin.o:	
	$(CC) $(SDL_flag) -c $*.c
_main_chessprog.o:	
	$(CC) $(SDL_flag) -c $*.c

#make depend
#this command should be first, then make command, this command will auto append every o.file dependencies
#another option is to call first    gcc -MM *.c>>makefile 	  command
#echo -e '\n' >> makefile # add new line before dependencies lines
depend:
	echo -e '\n' >> makefile 
	$(CC) -MM *.c >> makefile


# when  invoke $make clean command  all object files will be deleted
clean:  
	rm -f *.o *~   




CON_func__game.o: CON_func__game.c CON_func__game.h \
 CON_struct__ArrayList.h CON_struct__HistoryCell.h \
 CON_struct__GameBoard.h CON_struct__OrderedPair.h
CON_func__mainAux.o: CON_func__mainAux.c CON_func__mainAux.h \
 CON_func__Parser.h CON_struct__OrderedPair.h CON_func__SaveLoad.h \
 CON_func__game.h CON_struct__ArrayList.h CON_struct__HistoryCell.h \
 CON_struct__GameBoard.h CON_func__miniMax.h
CON_func__miniMax.o: CON_func__miniMax.c CON_func__miniMax.h \
 CON_func__game.h CON_struct__ArrayList.h CON_struct__HistoryCell.h \
 CON_struct__GameBoard.h CON_struct__OrderedPair.h
CON_func__Parser.o: CON_func__Parser.c CON_func__Parser.h \
 CON_struct__OrderedPair.h
CON_func__SaveLoad.o: CON_func__SaveLoad.c CON_func__SaveLoad.h \
 CON_func__game.h CON_struct__ArrayList.h CON_struct__HistoryCell.h \
 CON_struct__GameBoard.h CON_struct__OrderedPair.h
CON__main.o: CON__main.c CON_func__mainAux.h CON_func__Parser.h \
 CON_struct__OrderedPair.h CON_func__SaveLoad.h CON_func__game.h \
 CON_struct__ArrayList.h CON_struct__HistoryCell.h \
 CON_struct__GameBoard.h CON_func__miniMax.h
CON_struct__Address_Que.o: CON_struct__Address_Que.c \
 CON_struct__Address_Que.h CON_func__SaveLoad.h CON_func__game.h \
 CON_struct__ArrayList.h CON_struct__HistoryCell.h \
 CON_struct__GameBoard.h CON_struct__OrderedPair.h
CON_struct__ArrayList.o: CON_struct__ArrayList.c CON_struct__ArrayList.h \
 CON_struct__HistoryCell.h CON_struct__GameBoard.h
CON_struct__GameBoard.o: CON_struct__GameBoard.c CON_struct__GameBoard.h
CON_struct__HistoryCell.o: CON_struct__HistoryCell.c \
 CON_struct__HistoryCell.h CON_struct__GameBoard.h
CON_struct__OrderedPair.o: CON_struct__OrderedPair.c \
 CON_struct__OrderedPair.h
GUI_ColorWin.o: GUI_ColorWin.c GUI_ColorWin.h
GUI_DifficultyWin.o: GUI_DifficultyWin.c GUI_DifficultyWin.h
GUI_GameModeWin.o: GUI_GameModeWin.c GUI_GameModeWin.h
GUI_GameWin.o: GUI_GameWin.c GUI_GameWin.h CON_func__mainAux.h \
 CON_func__Parser.h CON_struct__OrderedPair.h CON_func__SaveLoad.h \
 CON_func__game.h CON_struct__ArrayList.h CON_struct__HistoryCell.h \
 CON_struct__GameBoard.h CON_func__miniMax.h
GUI_LoadWin.o: GUI_LoadWin.c GUI_LoadWin.h CON_struct__Address_Que.h \
 CON_func__SaveLoad.h CON_func__game.h CON_struct__ArrayList.h \
 CON_struct__HistoryCell.h CON_struct__GameBoard.h \
 CON_struct__OrderedPair.h
GUI__main.o: GUI__main.c GUI__Manager.h CON_struct__Address_Que.h \
 CON_func__SaveLoad.h CON_func__game.h CON_struct__ArrayList.h \
 CON_struct__HistoryCell.h CON_struct__GameBoard.h \
 CON_struct__OrderedPair.h GUI_ColorWin.h GUI_DifficultyWin.h \
 GUI_GameModeWin.h GUI_GameWin.h CON_func__mainAux.h CON_func__Parser.h \
 CON_func__miniMax.h GUI_LoadWin.h GUI_MenuWin.h
GUI__Manager.o: GUI__Manager.c GUI__Manager.h CON_struct__Address_Que.h \
 CON_func__SaveLoad.h CON_func__game.h CON_struct__ArrayList.h \
 CON_struct__HistoryCell.h CON_struct__GameBoard.h \
 CON_struct__OrderedPair.h GUI_ColorWin.h GUI_DifficultyWin.h \
 GUI_GameModeWin.h GUI_GameWin.h CON_func__mainAux.h CON_func__Parser.h \
 CON_func__miniMax.h GUI_LoadWin.h GUI_MenuWin.h
GUI_MenuWin.o: GUI_MenuWin.c GUI_MenuWin.h
_main_chessprog.o: _main_chessprog.c
