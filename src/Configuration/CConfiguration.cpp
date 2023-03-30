#include "CConfiguration.h"
#include <memory>
#include <map>
#include <functional>

CConfiguration::CConfiguration(std::unique_ptr<CAbstractPlayer> &player1, std::unique_ptr<CAbstractPlayer> &player2,
                               CVisualization &file, std::vector<std::string> &moves) {
    file.paste("Choose game:\n\tFor one player press '1'\n\tFor two players press '2'\n");
    moves.clear();
    player1->resetBoard();
    setUpPlayers(player1, player2, file, moves);
    file.paste("During game move piece please use form: (abbreviation of piece) old_position(letter, number) to new_position\nFor example: k D1 to C1\n");
    file.paste("If you wish to quit, write q/quit. ");
    file.paste("If you wish to save game globally - write !save.\n");
    file.paste("If you wish to play saved game globally - write !load.\n");
    file.paste("Black pieces are red and white pieces are green.\n");
    file.paste("White is starting...\n");
    }

void CConfiguration::setUpPlayers(std::unique_ptr<CAbstractPlayer> &player1, std::unique_ptr<CAbstractPlayer> &player2,
                                  CVisualization &file, std::vector<std::string> &moves) {
    std::string players = getInput(file); //todo
    int playerCount =  players[0] - '0';
    while(playerCount < 0 || playerCount > 2){
        file.paste("Wrong input, please try again.\n");
        players = getInput(file);
        playerCount =  players[0] - '0';
    }
    std::string playersN(std::to_string(playerCount));
    playersN.append("\n");
    moves.emplace_back(playersN);
    playersCountSetUp(playerCount, player1, player2, file, moves);
}

EColor CConfiguration::setUpColor(CVisualization &file, std::vector<std::string> &moves) {
    file.paste("Choose color of pieces: white or black\n");
    while (true){
        std::string line = getInput(file);
        if (line == "black") {
            line.append("\n");
            moves.emplace_back(line);
            moves.emplace_back(line);
            return WHITE;
        } else if (line == "white") {
            line.append("\n");
            moves.emplace_back(line);
            return BLACK;
        }
        else file.paste("Wrong input. Choose white or black color.\n");
    }
}

void CConfiguration::setUpComputerDifficulty(CVisualization &file, std::unique_ptr<CAbstractPlayer> &player,
                                             std::vector<std::string> &moves) {
    file.paste("Choose difficulty of play with computer: easy, medium or hard\n");
    while (true){
        std::string line = getInput(file);
        if(computerDifficulty(line, player)) {
            line.append("\n");
            moves.emplace_back(line);
            return;
        }
        else file.paste("Wrong input. Choose easy, medium or hard difficulty.\n");
    }
}

void CConfiguration::playersCountSetUp(int playerCount, std::unique_ptr<CAbstractPlayer> &player1,
                                       std::unique_ptr<CAbstractPlayer> &player2, CVisualization &file,
                                       std::vector<std::string> &moves) {
    if(playerCount == 1) {
        EColor computer = setUpColor(file, moves);
        if (computer == WHITE) {
            setUpComputerIsWhite(player1, player2);
            setUpComputerDifficulty(file, player1, moves);
        } else {
            setUpComputerIsBlack(player1, player2);
            setUpComputerDifficulty(file, player2, moves);
        }
    }
    else if (playerCount == 2) {
        setPlayers(player1, player2);
    }
    else {
        player1 = std::make_unique<CComputer>(WHITE);
        file.paste(player1->getColorInString(player1->getColorOfPieces()));
        file.paste(" ");
        setUpComputerDifficulty(file, player1, moves);
        player2 = std::make_unique<CComputer>(BLACK);
        file.paste(player2->getColorInString((player2->getColorOfPieces())));
        file.paste(" ");
        setUpComputerDifficulty(file, player2, moves);
    }
}

void CConfiguration::setUpComputerIsWhite(std::unique_ptr<CAbstractPlayer> &player1,
                                          std::unique_ptr<CAbstractPlayer> &player2) {
    player2 = std::make_unique<CPlayer>(BLACK);
    player1 = std::make_unique<CComputer>(WHITE);
}

void CConfiguration::setUpComputerIsBlack(std::unique_ptr<CAbstractPlayer> &player1,
                                          std::unique_ptr<CAbstractPlayer> &player2) {
    player1 = std::make_unique<CPlayer>(WHITE);
    player2 = std::make_unique<CComputer>(BLACK);
}

bool CConfiguration::computerDifficulty(std::string &diff, std::unique_ptr<CAbstractPlayer> &player) {
    CComputer * computerPlayer = dynamic_cast<CComputer*> (&*player);
    std::map<std::string, std::function<void()>> difficultyMap
                    {{ "easy", [computerPlayer]() { computerPlayer->setAIEasy(); }},
                    {"1", [computerPlayer]() { computerPlayer->setAIEasy(); }},
                    {"2", [computerPlayer]() { computerPlayer->setAIMedium(); }},
                    {"3", [computerPlayer]() { computerPlayer->setAIHard(); }},
                    {"medium", [computerPlayer]() { computerPlayer->setAIMedium(); }},
                     {"hard",  [computerPlayer]() { computerPlayer->setAIHard(); }}};
    auto it = difficultyMap.find(diff);
    if (it != difficultyMap.end()) {
        it->second();
        return true;
    }
    else return false;
}

void CConfiguration::setPlayers(std::unique_ptr<CAbstractPlayer> &player1, std::unique_ptr<CAbstractPlayer> &player2) {
    player1 = std::make_unique<CPlayer>(WHITE);
    player2 = std::make_unique<CPlayer>(BLACK);
}



std::string CConfiguration::getInput(CVisualization &file) const {
    std::string tmp;
    if(!file.getLineInLower(tmp) || tmp == "q" || tmp == "quit"){
        throw "quit";
    }
    return tmp;
}

CConfiguration::CConfiguration(std::ifstream &inFile, int &counter, std::unique_ptr<CAbstractPlayer> &player1,
                               std::unique_ptr<CAbstractPlayer> &player2, CVisualization &file,
                               std::vector<std::string> &moves) {
    moves.clear();
    std::string line;
    std::string line1;
    std::string line2;
    std::string line3;
    counter = 1;
    file.getLineForString(inFile, line, counter);
    while(line.empty()){
        file.getLineForString(inFile, line, counter);
        if(counter == 20){
            throw std::invalid_argument("Too many empty lines");
        }
    }
    if(line != "1" && line != "2" && line != "0"){
        throw std::invalid_argument("Incorrect text for players set up");
    }
    line1 = line;
    line1.append("\n");
    moves.emplace_back(line1);
    if(line == "1"){
        line.erase(line.begin(), line.end());
        file.getLineForString(inFile, line, counter);
        if(line == "white"){
            setUpComputerIsBlack(player1, player2);
            line2 = line;
            line2.append("\n");
            moves.emplace_back(line2);
            line.erase(line.begin(), line.end());
            file.getLineForString(inFile, line, counter);
            line3 = line;
            line3.append("\n");
            moves.emplace_back(line3);
            if(!computerDifficulty(line, player2)){
                throw std::invalid_argument("Incorrect text for difficulty set up");
            }

        }
        else if(line == "black"){
            setUpComputerIsWhite(player1, player2);
            line2 = line;
            line2.append("\n");
            moves.emplace_back(line2);
            line.erase(line.begin(), line.end());
            file.getLineForString(inFile, line, counter);
            line3 = line;
            line3.append("\n");
            moves.emplace_back(line3);
            if(!computerDifficulty(line, player1)){
                throw std::invalid_argument("Incorrect text for difficulty set up");
            }
        }
    }
    else setPlayers(player1, player2);
}

