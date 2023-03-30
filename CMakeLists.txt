cmake_minimum_required(VERSION 3.16)
project(petripat)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wpedantic -Wextra -g -fsanitize=address")
set(CMAKE_BUILD_TYPE Debug)

include_directories(src/AbstractPiece)
include_directories(src/AbstractPiece/Bishop)
include_directories(src/AbstractPiece/King)
include_directories(src/AbstractPiece/Knight)
include_directories(src/AbstractPiece/Pawn)
include_directories(src/AbstractPiece/Queen)
include_directories(src/AbstractPiece/Rook)
include_directories(src/AI)
include_directories(src/AI/Easy)
include_directories(src/AI/Hard)
include_directories(src/AI/Medium)
include_directories(src/Board)
include_directories(src/Configuration)
include_directories(src/AbstractPlayer)
include_directories(src/Visualization)

add_executable(petripat
        src/AbstractPiece/Bishop/CBishop.cpp
        src/AbstractPiece/Bishop/CBishop.h
        src/AbstractPiece/King/CKing.cpp
        src/AbstractPiece/King/CKing.h
        src/AbstractPiece/Knight/CKnight.cpp
        src/AbstractPiece/Knight/CKnight.h
        src/AbstractPiece/Pawn/CPawn.cpp
        src/AbstractPiece/Pawn/CPawn.h
        src/AbstractPiece/Queen/CQueen.cpp
        src/AbstractPiece/Queen/CQueen.h
        src/AbstractPiece/Rook/CRook.cpp
        src/AbstractPiece/Rook/CRook.h
        src/AbstractPiece/CAbstractPiece.cpp
        src/AbstractPiece/CAbstractPiece.h
        src/AI/Easy/CEasy.cpp
        src/AI/Easy/CEasy.h
        src/AI/Hard/CHard.cpp
        src/AI/Hard/CHard.h
        src/AI/Medium/CMedium.cpp
        src/AI/Medium/CMedium.h
        src/AI/CAI.cpp
        src/AI/CAI.h
        src/Board/CBoard.cpp
        src/Board/CBoard.h
        src/CChessBoard/CChessBoard.h
        src/Configuration/CConfiguration.cpp
        src/Configuration/CConfiguration.h
        src/AbstractPlayer/CAbstractPlayer.cpp
        src/AbstractPlayer/CAbstractPlayer.h
        src/Visualization/CVisualization.cpp
        src/Visualization/CVisualization.h
        src/main.cpp
        src/Chess/CChess.cpp
        src/Chess/CChess.h
        src/AbstractPlayer/Computer/CComputer.cpp
        src/AbstractPlayer/Computer/CComputer.h
        src/AbstractPlayer/Player/CPlayer.cpp
        src/PieceMove/SPieceMove.h
        src/AbstractPlayer/Player/CPlayer.h src/Chess/ECColor.h src/AbstractPiece/ECPiece.h src/Coordinates/CCoordinates.cpp src/Coordinates/CCoordinates.h src/CChessBoard/CChessBoard.cpp src/Board/ECGameState.h src/Game/CGame.cpp src/Game/CGame.h)
