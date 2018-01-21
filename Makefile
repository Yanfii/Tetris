CXX = g++-5
CXXFLAGS = -std=c++14 -Wall -MMD -Werror=vla
EXEC = quadris -lX11
OBJECTS = board.o cell.o iPiece.o jPiece.o oPiece.o lPiece.o sPiece.o zPiece.o tPiece.o main.o pieces.o textdisplay.o subject.o graphicsdisplay.o interpreter.o window.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
