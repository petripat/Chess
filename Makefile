# compile into object files
CXX = g++
CXXFLAGS = -Wall -pedantic -Wextra -Wno-long-long -g -std=c++14 -fsanitize=address
# link object files into final executable file
LD = g++
LDFLAGS = -Wall -pedantic -fsanitize=address -o3

PROGRAM=./petripat
# all .o modules to make
#         ls *.cpp | sed 's/.cpp/.o/g' | tr '\n' ' ' // */*/*.cpp */*.cpp
OBJECTS=src/main.o src/AI/CAI.o src/AI/Easy/CEasy.o src/AI/Hard/CHard.o src/AI/Medium/CMedium.o src/AbstractPiece/Bishop/CBishop.o src/AbstractPiece/CAbstractPiece.o src/AbstractPiece/King/CKing.o \
		src/AbstractPiece/Knight/CKnight.o src/AbstractPiece/Pawn/CPawn.o src/AbstractPiece/Queen/CQueen.o src/AbstractPiece/Rook/CRook.o src/AbstractPlayer/CAbstractPlayer.o \
		src/AbstractPlayer/Computer/CComputer.o src/AbstractPlayer/Player/CPlayer.o src/Board/CBoard.o src/CChessBoard/CChessBoard.o src/Chess/CChess.o src/Configuration/CConfiguration.o \
		src/Coordinates/CCoordinates.o src/Game/CGame.o src/Visualization/CVisualization.o

DOXYFILE=Doxyfile
RM=rm -rf

#---------------------------------------------------

all: $(PROGRAM)
	make compile
	make doc

compile: $(PROGRAM)

run: $(PROGRAM)
	$(PROGRAM)

debug: $(BPROGRAM)
	valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all $(PROGRAM)

doc: $(DOXYFILE)
	mkdir -p doc
	(doxygen $(DOXYFILE) 1>/dev/null 2>&1)

$(PROGRAM): $(OBJECTS)
	$(LD) $(LDFLAGS) $(OBJECTS) -o $(PROGRAM)

obj/%.o: src/%.cpp
	mkdir -p obj
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) $(PROGRAM) $(OBJECTS) doc

#
# here add output of "g++ -MM src/*/*.cpp src/*/*/*.cpp >> Makefile"
CAbstractPiece.o: src/AbstractPiece/CAbstractPiece.cpp \
 src/AbstractPiece/CAbstractPiece.h \
 src/AbstractPiece/../CChessBoard/CChessBoard.h \
 src/AbstractPiece/../CChessBoard/../Chess/ECColor.h \
 src/AbstractPiece/../CChessBoard/../Coordinates/CCoordinates.h \
 src/AbstractPiece/../CChessBoard/../PieceMove/SPieceMove.h \
 src/AbstractPiece/../CChessBoard/../PieceMove/../AbstractPiece/ECPiece.h \
 src/AbstractPiece/Pawn/CPawn.h \
 src/AbstractPiece/Pawn/../CAbstractPiece.h \
 src/AbstractPiece/Pawn/../Bishop/CBishop.h \
 src/AbstractPiece/Pawn/../Bishop/../CAbstractPiece.h \
 src/AbstractPiece/Pawn/../Knight/CKnight.h \
 src/AbstractPiece/Pawn/../Knight/../CAbstractPiece.h \
 src/AbstractPiece/Pawn/../Queen/CQueen.h \
 src/AbstractPiece/Pawn/../Queen/../CAbstractPiece.h \
 src/AbstractPiece/Pawn/../Rook/CRook.h \
 src/AbstractPiece/Pawn/../Rook/../CAbstractPiece.h \
 src/AbstractPiece/King/CKing.h \
 src/AbstractPiece/King/../CAbstractPiece.h
CAbstractPlayer.o: src/AbstractPlayer/CAbstractPlayer.cpp \
 src/AbstractPlayer/CAbstractPlayer.h src/AbstractPlayer/../AI/CAI.h \
 src/AbstractPlayer/../AI/../Board/CBoard.h \
 src/AbstractPlayer/../AI/../Board/../AbstractPiece/King/CKing.h \
 src/AbstractPlayer/../AI/../Board/../AbstractPiece/King/../CAbstractPiece.h \
 src/AbstractPlayer/../AI/../Board/../AbstractPiece/King/../../CChessBoard/CChessBoard.h \
 src/AbstractPlayer/../AI/../Board/../AbstractPiece/King/../../CChessBoard/../Chess/ECColor.h \
 src/AbstractPlayer/../AI/../Board/../AbstractPiece/King/../../CChessBoard/../Coordinates/CCoordinates.h \
 src/AbstractPlayer/../AI/../Board/../AbstractPiece/King/../../CChessBoard/../PieceMove/SPieceMove.h \
 src/AbstractPlayer/../AI/../Board/../AbstractPiece/King/../../CChessBoard/../PieceMove/../AbstractPiece/ECPiece.h \
 src/AbstractPlayer/../AI/../Board/../AbstractPiece/Pawn/CPawn.h \
 src/AbstractPlayer/../AI/../Board/../AbstractPiece/Pawn/../CAbstractPiece.h \
 src/AbstractPlayer/../AI/../Board/../AbstractPiece/Pawn/../Bishop/CBishop.h \
 src/AbstractPlayer/../AI/../Board/../AbstractPiece/Pawn/../Bishop/../CAbstractPiece.h \
 src/AbstractPlayer/../AI/../Board/../AbstractPiece/Pawn/../Knight/CKnight.h \
 src/AbstractPlayer/../AI/../Board/../AbstractPiece/Pawn/../Knight/../CAbstractPiece.h \
 src/AbstractPlayer/../AI/../Board/../AbstractPiece/Pawn/../Queen/CQueen.h \
 src/AbstractPlayer/../AI/../Board/../AbstractPiece/Pawn/../Queen/../CAbstractPiece.h \
 src/AbstractPlayer/../AI/../Board/../AbstractPiece/Pawn/../Rook/CRook.h \
 src/AbstractPlayer/../AI/../Board/../AbstractPiece/Pawn/../Rook/../CAbstractPiece.h \
 src/AbstractPlayer/../AI/../Board/../Visualization/CVisualization.h \
 src/AbstractPlayer/../AI/../Board/../Visualization/../CChessBoard/CChessBoard.h \
 src/AbstractPlayer/../AI/../Board/../Visualization/../AbstractPiece/CAbstractPiece.h \
 src/AbstractPlayer/../AI/../Board/ECGameState.h
CAI.o: src/AI/CAI.cpp src/AI/CAI.h src/AI/../Board/CBoard.h \
 src/AI/../Board/../AbstractPiece/King/CKing.h \
 src/AI/../Board/../AbstractPiece/King/../CAbstractPiece.h \
 src/AI/../Board/../AbstractPiece/King/../../CChessBoard/CChessBoard.h \
 src/AI/../Board/../AbstractPiece/King/../../CChessBoard/../Chess/ECColor.h \
 src/AI/../Board/../AbstractPiece/King/../../CChessBoard/../Coordinates/CCoordinates.h \
 src/AI/../Board/../AbstractPiece/King/../../CChessBoard/../PieceMove/SPieceMove.h \
 src/AI/../Board/../AbstractPiece/King/../../CChessBoard/../PieceMove/../AbstractPiece/ECPiece.h \
 src/AI/../Board/../AbstractPiece/Pawn/CPawn.h \
 src/AI/../Board/../AbstractPiece/Pawn/../CAbstractPiece.h \
 src/AI/../Board/../AbstractPiece/Pawn/../Bishop/CBishop.h \
 src/AI/../Board/../AbstractPiece/Pawn/../Bishop/../CAbstractPiece.h \
 src/AI/../Board/../AbstractPiece/Pawn/../Knight/CKnight.h \
 src/AI/../Board/../AbstractPiece/Pawn/../Knight/../CAbstractPiece.h \
 src/AI/../Board/../AbstractPiece/Pawn/../Queen/CQueen.h \
 src/AI/../Board/../AbstractPiece/Pawn/../Queen/../CAbstractPiece.h \
 src/AI/../Board/../AbstractPiece/Pawn/../Rook/CRook.h \
 src/AI/../Board/../AbstractPiece/Pawn/../Rook/../CAbstractPiece.h \
 src/AI/../Board/../Visualization/CVisualization.h \
 src/AI/../Board/../Visualization/../CChessBoard/CChessBoard.h \
 src/AI/../Board/../Visualization/../AbstractPiece/CAbstractPiece.h \
 src/AI/../Board/ECGameState.h
CBoard.o: src/Board/CBoard.cpp src/Board/CBoard.h \
 src/Board/../AbstractPiece/King/CKing.h \
 src/Board/../AbstractPiece/King/../CAbstractPiece.h \
 src/Board/../AbstractPiece/King/../../CChessBoard/CChessBoard.h \
 src/Board/../AbstractPiece/King/../../CChessBoard/../Chess/ECColor.h \
 src/Board/../AbstractPiece/King/../../CChessBoard/../Coordinates/CCoordinates.h \
 src/Board/../AbstractPiece/King/../../CChessBoard/../PieceMove/SPieceMove.h \
 src/Board/../AbstractPiece/King/../../CChessBoard/../PieceMove/../AbstractPiece/ECPiece.h \
 src/Board/../AbstractPiece/Pawn/CPawn.h \
 src/Board/../AbstractPiece/Pawn/../CAbstractPiece.h \
 src/Board/../AbstractPiece/Pawn/../Bishop/CBishop.h \
 src/Board/../AbstractPiece/Pawn/../Bishop/../CAbstractPiece.h \
 src/Board/../AbstractPiece/Pawn/../Knight/CKnight.h \
 src/Board/../AbstractPiece/Pawn/../Knight/../CAbstractPiece.h \
 src/Board/../AbstractPiece/Pawn/../Queen/CQueen.h \
 src/Board/../AbstractPiece/Pawn/../Queen/../CAbstractPiece.h \
 src/Board/../AbstractPiece/Pawn/../Rook/CRook.h \
 src/Board/../AbstractPiece/Pawn/../Rook/../CAbstractPiece.h \
 src/Board/../Visualization/CVisualization.h \
 src/Board/../Visualization/../CChessBoard/CChessBoard.h \
 src/Board/../Visualization/../AbstractPiece/CAbstractPiece.h \
 src/Board/ECGameState.h
CChessBoard.o: src/CChessBoard/CChessBoard.cpp \
 src/CChessBoard/CChessBoard.h src/CChessBoard/../Chess/ECColor.h \
 src/CChessBoard/../Coordinates/CCoordinates.h \
 src/CChessBoard/../PieceMove/SPieceMove.h \
 src/CChessBoard/../PieceMove/../AbstractPiece/ECPiece.h
CChess.o: src/Chess/CChess.cpp src/Chess/CChess.h \
 src/Chess/../Configuration/CConfiguration.h \
 src/Chess/../Configuration/../Visualization/CVisualization.h \
 src/Chess/../Configuration/../Visualization/../CChessBoard/CChessBoard.h \
 src/Chess/../Configuration/../Visualization/../CChessBoard/../Chess/ECColor.h \
 src/Chess/../Configuration/../Visualization/../CChessBoard/../Coordinates/CCoordinates.h \
 src/Chess/../Configuration/../Visualization/../CChessBoard/../PieceMove/SPieceMove.h \
 src/Chess/../Configuration/../Visualization/../CChessBoard/../PieceMove/../AbstractPiece/ECPiece.h \
 src/Chess/../Configuration/../Visualization/../AbstractPiece/CAbstractPiece.h \
 src/Chess/../Configuration/../Visualization/../AbstractPiece/../CChessBoard/CChessBoard.h \
 src/Chess/../Configuration/../AbstractPlayer/Computer/CComputer.h \
 src/Chess/../Configuration/../AbstractPlayer/Computer/../CAbstractPlayer.h \
 src/Chess/../Configuration/../AbstractPlayer/Computer/../../AI/CAI.h \
 src/Chess/../Configuration/../AbstractPlayer/Computer/../../AI/../Board/CBoard.h \
 src/Chess/../Configuration/../AbstractPlayer/Computer/../../AI/../Board/../AbstractPiece/King/CKing.h \
 src/Chess/../Configuration/../AbstractPlayer/Computer/../../AI/../Board/../AbstractPiece/King/../CAbstractPiece.h \
 src/Chess/../Configuration/../AbstractPlayer/Computer/../../AI/../Board/../AbstractPiece/Pawn/CPawn.h \
 src/Chess/../Configuration/../AbstractPlayer/Computer/../../AI/../Board/../AbstractPiece/Pawn/../CAbstractPiece.h \
 src/Chess/../Configuration/../AbstractPlayer/Computer/../../AI/../Board/../AbstractPiece/Pawn/../Bishop/CBishop.h \
 src/Chess/../Configuration/../AbstractPlayer/Computer/../../AI/../Board/../AbstractPiece/Pawn/../Bishop/../CAbstractPiece.h \
 src/Chess/../Configuration/../AbstractPlayer/Computer/../../AI/../Board/../AbstractPiece/Pawn/../Knight/CKnight.h \
 src/Chess/../Configuration/../AbstractPlayer/Computer/../../AI/../Board/../AbstractPiece/Pawn/../Knight/../CAbstractPiece.h \
 src/Chess/../Configuration/../AbstractPlayer/Computer/../../AI/../Board/../AbstractPiece/Pawn/../Queen/CQueen.h \
 src/Chess/../Configuration/../AbstractPlayer/Computer/../../AI/../Board/../AbstractPiece/Pawn/../Queen/../CAbstractPiece.h \
 src/Chess/../Configuration/../AbstractPlayer/Computer/../../AI/../Board/../AbstractPiece/Pawn/../Rook/CRook.h \
 src/Chess/../Configuration/../AbstractPlayer/Computer/../../AI/../Board/../AbstractPiece/Pawn/../Rook/../CAbstractPiece.h \
 src/Chess/../Configuration/../AbstractPlayer/Computer/../../AI/../Board/../Visualization/CVisualization.h \
 src/Chess/../Configuration/../AbstractPlayer/Computer/../../AI/../Board/ECGameState.h \
 src/Chess/../Configuration/../AbstractPlayer/Computer/../../AI/Easy/CEasy.h \
 src/Chess/../Configuration/../AbstractPlayer/Computer/../../AI/Easy/../CAI.h \
 src/Chess/../Configuration/../AbstractPlayer/Computer/../../AI/Medium/CMedium.h \
 src/Chess/../Configuration/../AbstractPlayer/Computer/../../AI/Medium/../CAI.h \
 src/Chess/../Configuration/../AbstractPlayer/Computer/../../AI/Hard/CHard.h \
 src/Chess/../Configuration/../AbstractPlayer/Computer/../../AI/Hard/../CAI.h \
 src/Chess/../Configuration/../AbstractPlayer/Player/CPlayer.h \
 src/Chess/../Configuration/../AbstractPlayer/Player/../CAbstractPlayer.h
CConfiguration.o: src/Configuration/CConfiguration.cpp \
 src/Configuration/CConfiguration.h \
 src/Configuration/../Visualization/CVisualization.h \
 src/Configuration/../Visualization/../CChessBoard/CChessBoard.h \
 src/Configuration/../Visualization/../CChessBoard/../Chess/ECColor.h \
 src/Configuration/../Visualization/../CChessBoard/../Coordinates/CCoordinates.h \
 src/Configuration/../Visualization/../CChessBoard/../PieceMove/SPieceMove.h \
 src/Configuration/../Visualization/../CChessBoard/../PieceMove/../AbstractPiece/ECPiece.h \
 src/Configuration/../Visualization/../AbstractPiece/CAbstractPiece.h \
 src/Configuration/../Visualization/../AbstractPiece/../CChessBoard/CChessBoard.h \
 src/Configuration/../AbstractPlayer/Computer/CComputer.h \
 src/Configuration/../AbstractPlayer/Computer/../CAbstractPlayer.h \
 src/Configuration/../AbstractPlayer/Computer/../../AI/CAI.h \
 src/Configuration/../AbstractPlayer/Computer/../../AI/../Board/CBoard.h \
 src/Configuration/../AbstractPlayer/Computer/../../AI/../Board/../AbstractPiece/King/CKing.h \
 src/Configuration/../AbstractPlayer/Computer/../../AI/../Board/../AbstractPiece/King/../CAbstractPiece.h \
 src/Configuration/../AbstractPlayer/Computer/../../AI/../Board/../AbstractPiece/Pawn/CPawn.h \
 src/Configuration/../AbstractPlayer/Computer/../../AI/../Board/../AbstractPiece/Pawn/../CAbstractPiece.h \
 src/Configuration/../AbstractPlayer/Computer/../../AI/../Board/../AbstractPiece/Pawn/../Bishop/CBishop.h \
 src/Configuration/../AbstractPlayer/Computer/../../AI/../Board/../AbstractPiece/Pawn/../Bishop/../CAbstractPiece.h \
 src/Configuration/../AbstractPlayer/Computer/../../AI/../Board/../AbstractPiece/Pawn/../Knight/CKnight.h \
 src/Configuration/../AbstractPlayer/Computer/../../AI/../Board/../AbstractPiece/Pawn/../Knight/../CAbstractPiece.h \
 src/Configuration/../AbstractPlayer/Computer/../../AI/../Board/../AbstractPiece/Pawn/../Queen/CQueen.h \
 src/Configuration/../AbstractPlayer/Computer/../../AI/../Board/../AbstractPiece/Pawn/../Queen/../CAbstractPiece.h \
 src/Configuration/../AbstractPlayer/Computer/../../AI/../Board/../AbstractPiece/Pawn/../Rook/CRook.h \
 src/Configuration/../AbstractPlayer/Computer/../../AI/../Board/../AbstractPiece/Pawn/../Rook/../CAbstractPiece.h \
 src/Configuration/../AbstractPlayer/Computer/../../AI/../Board/../Visualization/CVisualization.h \
 src/Configuration/../AbstractPlayer/Computer/../../AI/../Board/ECGameState.h \
 src/Configuration/../AbstractPlayer/Computer/../../AI/Easy/CEasy.h \
 src/Configuration/../AbstractPlayer/Computer/../../AI/Easy/../CAI.h \
 src/Configuration/../AbstractPlayer/Computer/../../AI/Medium/CMedium.h \
 src/Configuration/../AbstractPlayer/Computer/../../AI/Medium/../CAI.h \
 src/Configuration/../AbstractPlayer/Computer/../../AI/Hard/CHard.h \
 src/Configuration/../AbstractPlayer/Computer/../../AI/Hard/../CAI.h \
 src/Configuration/../AbstractPlayer/Player/CPlayer.h \
 src/Configuration/../AbstractPlayer/Player/../CAbstractPlayer.h
CCoordinates.o: src/Coordinates/CCoordinates.cpp \
 src/Coordinates/CCoordinates.h
CGame.o: src/Game/CGame.cpp src/Game/CGame.h src/Game/../Chess/CChess.h \
 src/Game/../Chess/../Configuration/CConfiguration.h \
 src/Game/../Chess/../Configuration/../Visualization/CVisualization.h \
 src/Game/../Chess/../Configuration/../Visualization/../CChessBoard/CChessBoard.h \
 src/Game/../Chess/../Configuration/../Visualization/../CChessBoard/../Chess/ECColor.h \
 src/Game/../Chess/../Configuration/../Visualization/../CChessBoard/../Coordinates/CCoordinates.h \
 src/Game/../Chess/../Configuration/../Visualization/../CChessBoard/../PieceMove/SPieceMove.h \
 src/Game/../Chess/../Configuration/../Visualization/../CChessBoard/../PieceMove/../AbstractPiece/ECPiece.h \
 src/Game/../Chess/../Configuration/../Visualization/../AbstractPiece/CAbstractPiece.h \
 src/Game/../Chess/../Configuration/../Visualization/../AbstractPiece/../CChessBoard/CChessBoard.h \
 src/Game/../Chess/../Configuration/../AbstractPlayer/Computer/CComputer.h \
 src/Game/../Chess/../Configuration/../AbstractPlayer/Computer/../CAbstractPlayer.h \
 src/Game/../Chess/../Configuration/../AbstractPlayer/Computer/../../AI/CAI.h \
 src/Game/../Chess/../Configuration/../AbstractPlayer/Computer/../../AI/../Board/CBoard.h \
 src/Game/../Chess/../Configuration/../AbstractPlayer/Computer/../../AI/../Board/../AbstractPiece/King/CKing.h \
 src/Game/../Chess/../Configuration/../AbstractPlayer/Computer/../../AI/../Board/../AbstractPiece/King/../CAbstractPiece.h \
 src/Game/../Chess/../Configuration/../AbstractPlayer/Computer/../../AI/../Board/../AbstractPiece/Pawn/CPawn.h \
 src/Game/../Chess/../Configuration/../AbstractPlayer/Computer/../../AI/../Board/../AbstractPiece/Pawn/../CAbstractPiece.h \
 src/Game/../Chess/../Configuration/../AbstractPlayer/Computer/../../AI/../Board/../AbstractPiece/Pawn/../Bishop/CBishop.h \
 src/Game/../Chess/../Configuration/../AbstractPlayer/Computer/../../AI/../Board/../AbstractPiece/Pawn/../Bishop/../CAbstractPiece.h \
 src/Game/../Chess/../Configuration/../AbstractPlayer/Computer/../../AI/../Board/../AbstractPiece/Pawn/../Knight/CKnight.h \
 src/Game/../Chess/../Configuration/../AbstractPlayer/Computer/../../AI/../Board/../AbstractPiece/Pawn/../Knight/../CAbstractPiece.h \
 src/Game/../Chess/../Configuration/../AbstractPlayer/Computer/../../AI/../Board/../AbstractPiece/Pawn/../Queen/CQueen.h \
 src/Game/../Chess/../Configuration/../AbstractPlayer/Computer/../../AI/../Board/../AbstractPiece/Pawn/../Queen/../CAbstractPiece.h \
 src/Game/../Chess/../Configuration/../AbstractPlayer/Computer/../../AI/../Board/../AbstractPiece/Pawn/../Rook/CRook.h \
 src/Game/../Chess/../Configuration/../AbstractPlayer/Computer/../../AI/../Board/../AbstractPiece/Pawn/../Rook/../CAbstractPiece.h \
 src/Game/../Chess/../Configuration/../AbstractPlayer/Computer/../../AI/../Board/../Visualization/CVisualization.h \
 src/Game/../Chess/../Configuration/../AbstractPlayer/Computer/../../AI/../Board/ECGameState.h \
 src/Game/../Chess/../Configuration/../AbstractPlayer/Computer/../../AI/Easy/CEasy.h \
 src/Game/../Chess/../Configuration/../AbstractPlayer/Computer/../../AI/Easy/../CAI.h \
 src/Game/../Chess/../Configuration/../AbstractPlayer/Computer/../../AI/Medium/CMedium.h \
 src/Game/../Chess/../Configuration/../AbstractPlayer/Computer/../../AI/Medium/../CAI.h \
 src/Game/../Chess/../Configuration/../AbstractPlayer/Computer/../../AI/Hard/CHard.h \
 src/Game/../Chess/../Configuration/../AbstractPlayer/Computer/../../AI/Hard/../CAI.h \
 src/Game/../Chess/../Configuration/../AbstractPlayer/Player/CPlayer.h \
 src/Game/../Chess/../Configuration/../AbstractPlayer/Player/../CAbstractPlayer.h
CVisualization.o: src/Visualization/CVisualization.cpp \
 src/Visualization/CVisualization.h \
 src/Visualization/../CChessBoard/CChessBoard.h \
 src/Visualization/../CChessBoard/../Chess/ECColor.h \
 src/Visualization/../CChessBoard/../Coordinates/CCoordinates.h \
 src/Visualization/../CChessBoard/../PieceMove/SPieceMove.h \
 src/Visualization/../CChessBoard/../PieceMove/../AbstractPiece/ECPiece.h \
 src/Visualization/../AbstractPiece/CAbstractPiece.h \
 src/Visualization/../AbstractPiece/../CChessBoard/CChessBoard.h
CBishop.o: src/AbstractPiece/Bishop/CBishop.cpp \
 src/AbstractPiece/Bishop/CBishop.h \
 src/AbstractPiece/Bishop/../CAbstractPiece.h \
 src/AbstractPiece/Bishop/../../CChessBoard/CChessBoard.h \
 src/AbstractPiece/Bishop/../../CChessBoard/../Chess/ECColor.h \
 src/AbstractPiece/Bishop/../../CChessBoard/../Coordinates/CCoordinates.h \
 src/AbstractPiece/Bishop/../../CChessBoard/../PieceMove/SPieceMove.h \
 src/AbstractPiece/Bishop/../../CChessBoard/../PieceMove/../AbstractPiece/ECPiece.h
CKing.o: src/AbstractPiece/King/CKing.cpp src/AbstractPiece/King/CKing.h \
 src/AbstractPiece/King/../CAbstractPiece.h \
 src/AbstractPiece/King/../../CChessBoard/CChessBoard.h \
 src/AbstractPiece/King/../../CChessBoard/../Chess/ECColor.h \
 src/AbstractPiece/King/../../CChessBoard/../Coordinates/CCoordinates.h \
 src/AbstractPiece/King/../../CChessBoard/../PieceMove/SPieceMove.h \
 src/AbstractPiece/King/../../CChessBoard/../PieceMove/../AbstractPiece/ECPiece.h
CKnight.o: src/AbstractPiece/Knight/CKnight.cpp \
 src/AbstractPiece/Knight/CKnight.h \
 src/AbstractPiece/Knight/../CAbstractPiece.h \
 src/AbstractPiece/Knight/../../CChessBoard/CChessBoard.h \
 src/AbstractPiece/Knight/../../CChessBoard/../Chess/ECColor.h \
 src/AbstractPiece/Knight/../../CChessBoard/../Coordinates/CCoordinates.h \
 src/AbstractPiece/Knight/../../CChessBoard/../PieceMove/SPieceMove.h \
 src/AbstractPiece/Knight/../../CChessBoard/../PieceMove/../AbstractPiece/ECPiece.h
CPawn.o: src/AbstractPiece/Pawn/CPawn.cpp src/AbstractPiece/Pawn/CPawn.h \
 src/AbstractPiece/Pawn/../CAbstractPiece.h \
 src/AbstractPiece/Pawn/../../CChessBoard/CChessBoard.h \
 src/AbstractPiece/Pawn/../../CChessBoard/../Chess/ECColor.h \
 src/AbstractPiece/Pawn/../../CChessBoard/../Coordinates/CCoordinates.h \
 src/AbstractPiece/Pawn/../../CChessBoard/../PieceMove/SPieceMove.h \
 src/AbstractPiece/Pawn/../../CChessBoard/../PieceMove/../AbstractPiece/ECPiece.h \
 src/AbstractPiece/Pawn/../Bishop/CBishop.h \
 src/AbstractPiece/Pawn/../Bishop/../CAbstractPiece.h \
 src/AbstractPiece/Pawn/../Knight/CKnight.h \
 src/AbstractPiece/Pawn/../Knight/../CAbstractPiece.h \
 src/AbstractPiece/Pawn/../Queen/CQueen.h \
 src/AbstractPiece/Pawn/../Queen/../CAbstractPiece.h \
 src/AbstractPiece/Pawn/../Rook/CRook.h \
 src/AbstractPiece/Pawn/../Rook/../CAbstractPiece.h
CQueen.o: src/AbstractPiece/Queen/CQueen.cpp \
 src/AbstractPiece/Queen/CQueen.h \
 src/AbstractPiece/Queen/../CAbstractPiece.h \
 src/AbstractPiece/Queen/../../CChessBoard/CChessBoard.h \
 src/AbstractPiece/Queen/../../CChessBoard/../Chess/ECColor.h \
 src/AbstractPiece/Queen/../../CChessBoard/../Coordinates/CCoordinates.h \
 src/AbstractPiece/Queen/../../CChessBoard/../PieceMove/SPieceMove.h \
 src/AbstractPiece/Queen/../../CChessBoard/../PieceMove/../AbstractPiece/ECPiece.h
CRook.o: src/AbstractPiece/Rook/CRook.cpp src/AbstractPiece/Rook/CRook.h \
 src/AbstractPiece/Rook/../CAbstractPiece.h \
 src/AbstractPiece/Rook/../../CChessBoard/CChessBoard.h \
 src/AbstractPiece/Rook/../../CChessBoard/../Chess/ECColor.h \
 src/AbstractPiece/Rook/../../CChessBoard/../Coordinates/CCoordinates.h \
 src/AbstractPiece/Rook/../../CChessBoard/../PieceMove/SPieceMove.h \
 src/AbstractPiece/Rook/../../CChessBoard/../PieceMove/../AbstractPiece/ECPiece.h
CComputer.o: src/AbstractPlayer/Computer/CComputer.cpp \
 src/AbstractPlayer/Computer/CComputer.h \
 src/AbstractPlayer/Computer/../CAbstractPlayer.h \
 src/AbstractPlayer/Computer/../../AI/CAI.h \
 src/AbstractPlayer/Computer/../../AI/../Board/CBoard.h \
 src/AbstractPlayer/Computer/../../AI/../Board/../AbstractPiece/King/CKing.h \
 src/AbstractPlayer/Computer/../../AI/../Board/../AbstractPiece/King/../CAbstractPiece.h \
 src/AbstractPlayer/Computer/../../AI/../Board/../AbstractPiece/King/../../CChessBoard/CChessBoard.h \
 src/AbstractPlayer/Computer/../../AI/../Board/../AbstractPiece/King/../../CChessBoard/../Chess/ECColor.h \
 src/AbstractPlayer/Computer/../../AI/../Board/../AbstractPiece/King/../../CChessBoard/../Coordinates/CCoordinates.h \
 src/AbstractPlayer/Computer/../../AI/../Board/../AbstractPiece/King/../../CChessBoard/../PieceMove/SPieceMove.h \
 src/AbstractPlayer/Computer/../../AI/../Board/../AbstractPiece/King/../../CChessBoard/../PieceMove/../AbstractPiece/ECPiece.h \
 src/AbstractPlayer/Computer/../../AI/../Board/../AbstractPiece/Pawn/CPawn.h \
 src/AbstractPlayer/Computer/../../AI/../Board/../AbstractPiece/Pawn/../CAbstractPiece.h \
 src/AbstractPlayer/Computer/../../AI/../Board/../AbstractPiece/Pawn/../Bishop/CBishop.h \
 src/AbstractPlayer/Computer/../../AI/../Board/../AbstractPiece/Pawn/../Bishop/../CAbstractPiece.h \
 src/AbstractPlayer/Computer/../../AI/../Board/../AbstractPiece/Pawn/../Knight/CKnight.h \
 src/AbstractPlayer/Computer/../../AI/../Board/../AbstractPiece/Pawn/../Knight/../CAbstractPiece.h \
 src/AbstractPlayer/Computer/../../AI/../Board/../AbstractPiece/Pawn/../Queen/CQueen.h \
 src/AbstractPlayer/Computer/../../AI/../Board/../AbstractPiece/Pawn/../Queen/../CAbstractPiece.h \
 src/AbstractPlayer/Computer/../../AI/../Board/../AbstractPiece/Pawn/../Rook/CRook.h \
 src/AbstractPlayer/Computer/../../AI/../Board/../AbstractPiece/Pawn/../Rook/../CAbstractPiece.h \
 src/AbstractPlayer/Computer/../../AI/../Board/../Visualization/CVisualization.h \
 src/AbstractPlayer/Computer/../../AI/../Board/../Visualization/../CChessBoard/CChessBoard.h \
 src/AbstractPlayer/Computer/../../AI/../Board/../Visualization/../AbstractPiece/CAbstractPiece.h \
 src/AbstractPlayer/Computer/../../AI/../Board/ECGameState.h \
 src/AbstractPlayer/Computer/../../AI/Easy/CEasy.h \
 src/AbstractPlayer/Computer/../../AI/Easy/../CAI.h \
 src/AbstractPlayer/Computer/../../AI/Medium/CMedium.h \
 src/AbstractPlayer/Computer/../../AI/Medium/../CAI.h \
 src/AbstractPlayer/Computer/../../AI/Hard/CHard.h \
 src/AbstractPlayer/Computer/../../AI/Hard/../CAI.h
CPlayer.o: src/AbstractPlayer/Player/CPlayer.cpp \
 src/AbstractPlayer/Player/CPlayer.h \
 src/AbstractPlayer/Player/../CAbstractPlayer.h \
 src/AbstractPlayer/Player/../../AI/CAI.h \
 src/AbstractPlayer/Player/../../AI/../Board/CBoard.h \
 src/AbstractPlayer/Player/../../AI/../Board/../AbstractPiece/King/CKing.h \
 src/AbstractPlayer/Player/../../AI/../Board/../AbstractPiece/King/../CAbstractPiece.h \
 src/AbstractPlayer/Player/../../AI/../Board/../AbstractPiece/King/../../CChessBoard/CChessBoard.h \
 src/AbstractPlayer/Player/../../AI/../Board/../AbstractPiece/King/../../CChessBoard/../Chess/ECColor.h \
 src/AbstractPlayer/Player/../../AI/../Board/../AbstractPiece/King/../../CChessBoard/../Coordinates/CCoordinates.h \
 src/AbstractPlayer/Player/../../AI/../Board/../AbstractPiece/King/../../CChessBoard/../PieceMove/SPieceMove.h \
 src/AbstractPlayer/Player/../../AI/../Board/../AbstractPiece/King/../../CChessBoard/../PieceMove/../AbstractPiece/ECPiece.h \
 src/AbstractPlayer/Player/../../AI/../Board/../AbstractPiece/Pawn/CPawn.h \
 src/AbstractPlayer/Player/../../AI/../Board/../AbstractPiece/Pawn/../CAbstractPiece.h \
 src/AbstractPlayer/Player/../../AI/../Board/../AbstractPiece/Pawn/../Bishop/CBishop.h \
 src/AbstractPlayer/Player/../../AI/../Board/../AbstractPiece/Pawn/../Bishop/../CAbstractPiece.h \
 src/AbstractPlayer/Player/../../AI/../Board/../AbstractPiece/Pawn/../Knight/CKnight.h \
 src/AbstractPlayer/Player/../../AI/../Board/../AbstractPiece/Pawn/../Knight/../CAbstractPiece.h \
 src/AbstractPlayer/Player/../../AI/../Board/../AbstractPiece/Pawn/../Queen/CQueen.h \
 src/AbstractPlayer/Player/../../AI/../Board/../AbstractPiece/Pawn/../Queen/../CAbstractPiece.h \
 src/AbstractPlayer/Player/../../AI/../Board/../AbstractPiece/Pawn/../Rook/CRook.h \
 src/AbstractPlayer/Player/../../AI/../Board/../AbstractPiece/Pawn/../Rook/../CAbstractPiece.h \
 src/AbstractPlayer/Player/../../AI/../Board/../Visualization/CVisualization.h \
 src/AbstractPlayer/Player/../../AI/../Board/../Visualization/../CChessBoard/CChessBoard.h \
 src/AbstractPlayer/Player/../../AI/../Board/../Visualization/../AbstractPiece/CAbstractPiece.h \
 src/AbstractPlayer/Player/../../AI/../Board/ECGameState.h
CEasy.o: src/AI/Easy/CEasy.cpp src/AI/Easy/CEasy.h src/AI/Easy/../CAI.h \
 src/AI/Easy/../../Board/CBoard.h \
 src/AI/Easy/../../Board/../AbstractPiece/King/CKing.h \
 src/AI/Easy/../../Board/../AbstractPiece/King/../CAbstractPiece.h \
 src/AI/Easy/../../Board/../AbstractPiece/King/../../CChessBoard/CChessBoard.h \
 src/AI/Easy/../../Board/../AbstractPiece/King/../../CChessBoard/../Chess/ECColor.h \
 src/AI/Easy/../../Board/../AbstractPiece/King/../../CChessBoard/../Coordinates/CCoordinates.h \
 src/AI/Easy/../../Board/../AbstractPiece/King/../../CChessBoard/../PieceMove/SPieceMove.h \
 src/AI/Easy/../../Board/../AbstractPiece/King/../../CChessBoard/../PieceMove/../AbstractPiece/ECPiece.h \
 src/AI/Easy/../../Board/../AbstractPiece/Pawn/CPawn.h \
 src/AI/Easy/../../Board/../AbstractPiece/Pawn/../CAbstractPiece.h \
 src/AI/Easy/../../Board/../AbstractPiece/Pawn/../Bishop/CBishop.h \
 src/AI/Easy/../../Board/../AbstractPiece/Pawn/../Bishop/../CAbstractPiece.h \
 src/AI/Easy/../../Board/../AbstractPiece/Pawn/../Knight/CKnight.h \
 src/AI/Easy/../../Board/../AbstractPiece/Pawn/../Knight/../CAbstractPiece.h \
 src/AI/Easy/../../Board/../AbstractPiece/Pawn/../Queen/CQueen.h \
 src/AI/Easy/../../Board/../AbstractPiece/Pawn/../Queen/../CAbstractPiece.h \
 src/AI/Easy/../../Board/../AbstractPiece/Pawn/../Rook/CRook.h \
 src/AI/Easy/../../Board/../AbstractPiece/Pawn/../Rook/../CAbstractPiece.h \
 src/AI/Easy/../../Board/../Visualization/CVisualization.h \
 src/AI/Easy/../../Board/../Visualization/../CChessBoard/CChessBoard.h \
 src/AI/Easy/../../Board/../Visualization/../AbstractPiece/CAbstractPiece.h \
 src/AI/Easy/../../Board/ECGameState.h
CHard.o: src/AI/Hard/CHard.cpp src/AI/Hard/CHard.h src/AI/Hard/../CAI.h \
 src/AI/Hard/../../Board/CBoard.h \
 src/AI/Hard/../../Board/../AbstractPiece/King/CKing.h \
 src/AI/Hard/../../Board/../AbstractPiece/King/../CAbstractPiece.h \
 src/AI/Hard/../../Board/../AbstractPiece/King/../../CChessBoard/CChessBoard.h \
 src/AI/Hard/../../Board/../AbstractPiece/King/../../CChessBoard/../Chess/ECColor.h \
 src/AI/Hard/../../Board/../AbstractPiece/King/../../CChessBoard/../Coordinates/CCoordinates.h \
 src/AI/Hard/../../Board/../AbstractPiece/King/../../CChessBoard/../PieceMove/SPieceMove.h \
 src/AI/Hard/../../Board/../AbstractPiece/King/../../CChessBoard/../PieceMove/../AbstractPiece/ECPiece.h \
 src/AI/Hard/../../Board/../AbstractPiece/Pawn/CPawn.h \
 src/AI/Hard/../../Board/../AbstractPiece/Pawn/../CAbstractPiece.h \
 src/AI/Hard/../../Board/../AbstractPiece/Pawn/../Bishop/CBishop.h \
 src/AI/Hard/../../Board/../AbstractPiece/Pawn/../Bishop/../CAbstractPiece.h \
 src/AI/Hard/../../Board/../AbstractPiece/Pawn/../Knight/CKnight.h \
 src/AI/Hard/../../Board/../AbstractPiece/Pawn/../Knight/../CAbstractPiece.h \
 src/AI/Hard/../../Board/../AbstractPiece/Pawn/../Queen/CQueen.h \
 src/AI/Hard/../../Board/../AbstractPiece/Pawn/../Queen/../CAbstractPiece.h \
 src/AI/Hard/../../Board/../AbstractPiece/Pawn/../Rook/CRook.h \
 src/AI/Hard/../../Board/../AbstractPiece/Pawn/../Rook/../CAbstractPiece.h \
 src/AI/Hard/../../Board/../Visualization/CVisualization.h \
 src/AI/Hard/../../Board/../Visualization/../CChessBoard/CChessBoard.h \
 src/AI/Hard/../../Board/../Visualization/../AbstractPiece/CAbstractPiece.h \
 src/AI/Hard/../../Board/ECGameState.h
CMedium.o: src/AI/Medium/CMedium.cpp src/AI/Medium/CMedium.h \
 src/AI/Medium/../CAI.h src/AI/Medium/../../Board/CBoard.h \
 src/AI/Medium/../../Board/../AbstractPiece/King/CKing.h \
 src/AI/Medium/../../Board/../AbstractPiece/King/../CAbstractPiece.h \
 src/AI/Medium/../../Board/../AbstractPiece/King/../../CChessBoard/CChessBoard.h \
 src/AI/Medium/../../Board/../AbstractPiece/King/../../CChessBoard/../Chess/ECColor.h \
 src/AI/Medium/../../Board/../AbstractPiece/King/../../CChessBoard/../Coordinates/CCoordinates.h \
 src/AI/Medium/../../Board/../AbstractPiece/King/../../CChessBoard/../PieceMove/SPieceMove.h \
 src/AI/Medium/../../Board/../AbstractPiece/King/../../CChessBoard/../PieceMove/../AbstractPiece/ECPiece.h \
 src/AI/Medium/../../Board/../AbstractPiece/Pawn/CPawn.h \
 src/AI/Medium/../../Board/../AbstractPiece/Pawn/../CAbstractPiece.h \
 src/AI/Medium/../../Board/../AbstractPiece/Pawn/../Bishop/CBishop.h \
 src/AI/Medium/../../Board/../AbstractPiece/Pawn/../Bishop/../CAbstractPiece.h \
 src/AI/Medium/../../Board/../AbstractPiece/Pawn/../Knight/CKnight.h \
 src/AI/Medium/../../Board/../AbstractPiece/Pawn/../Knight/../CAbstractPiece.h \
 src/AI/Medium/../../Board/../AbstractPiece/Pawn/../Queen/CQueen.h \
 src/AI/Medium/../../Board/../AbstractPiece/Pawn/../Queen/../CAbstractPiece.h \
 src/AI/Medium/../../Board/../AbstractPiece/Pawn/../Rook/CRook.h \
 src/AI/Medium/../../Board/../AbstractPiece/Pawn/../Rook/../CAbstractPiece.h \
 src/AI/Medium/../../Board/../Visualization/CVisualization.h \
 src/AI/Medium/../../Board/../Visualization/../CChessBoard/CChessBoard.h \
 src/AI/Medium/../../Board/../Visualization/../AbstractPiece/CAbstractPiece.h \
 src/AI/Medium/../../Board/ECGameState.h
