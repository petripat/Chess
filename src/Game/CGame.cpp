#include "CGame.h"

bool CGame::canLoadGame() {
    if(savedGames.empty() || (savedGames.size() == 1 && (savedGames.count(currentGame) || savedGames.count(TMP_SAVE_TEXT)))){;
        return false;
    }
    else return true;
}

void CGame::startGame() {
    CChess game(file);
    currentGame = TMP_SAVE_TEXT;
    savedGames.emplace(std::make_pair(currentGame, game));
    return game.run(file);
}

void CGame::loadGame() {
    file.pasteEndOfLine("Choose one game from list - write number.");
    pasteSavedGames();
    currentGame = getNameOfGame();
    //read name and start game using string played game - return and let while cyklus play - možná rovnou začít
    ///set up game??
    //zakazat 1. a tak.. a lze nacist v tomto tvaru
    //vytiknu jmena a nactu jmeno podle cisla nebo vylozene string - co kdyz napise jenom cislo??
    //currentGame = "nejakyString";
}

void CGame::pasteSavedGames() {
    int i = 1;
    for(auto start = savedGames.begin(), end = savedGames.end(); start != end; start++, i++){
        if(start->first != currentGame && start->first != TMP_SAVE_TEXT  ) {
            file.pasteNumber(i);
            file.paste(". ");
            file.pasteEndOfLine(start->first);
        }
        else i--;
    }
}

std::string CGame::getNameOfGame() {
    std::string nameOfGame;
    while(true){
        if(!file.read(nameOfGame) || nameOfGame == "q" || nameOfGame == "quit"){
            throw "quit";
        }
        else if(nameOfGame == "cancel"){
            return currentGame;
        }
        else if(nameOfGame.size() == 1){
            int a = nameOfGame[0] - '0';
            if(a > 0 && (unsigned int) a <= savedGames.size()){
                int i = 0;
                for(auto start = savedGames.begin(), end = savedGames.end(); start != end; start++, i++){
                    if(i == a){
                        nameOfGame = start->first;
                        return nameOfGame;
                    }
                }
            }
        }
        file.paste("Incorrect number. Try again.");
    }
}

std::string CGame::saveGame(std::string &nameOfGame) {
    while(savedGames.count(nameOfGame)){
        file.pasteEndOfLine("This name is already used. Try again.");
        file.pasteEndOfLine("List of saved games:");
        pasteSavedGames();
        nameOfGame = file.getNameOfGame();
    }
    CChess tmp(savedGames[currentGame]);
    savedGames.erase(currentGame);
    savedGames.emplace(std::make_pair(nameOfGame,tmp));
    return nameOfGame;
}

bool CGame::gameDone() {
    savedGames[currentGame].clearMoves();
    savedGames.erase(currentGame);
    currentGame = TMP_SAVE_TEXT;
    return newGame();
}

bool CGame::saveToFile() {
    file.pasteEndOfLine("Write an adress for loading file");
    std::string fileName;
    file.getLineRegular(fileName);
    if(fileName.empty()){
        file.paste("No file.");
        return false;
    }
    return savedGames[currentGame].saveToFile(file, fileName);

}

bool CGame::newGame() {
    if(!canLoadGame()){
        file.paste("I will start new game for you. Pres q/quit to end game.");
        return false;
    }
    else {
    file.paste("Do you wish to load old game? If yes write y/yes. If you write n/no,");
    file.paste("I will start new game for you. Pres q/quit to end game.");
    }

    file.pasteEndOfLine("");
    std::string tmp;
    if(yesMethod(file)){
        loadGame();
        return false;
    }
    else return true;

}
bool CGame::yesMethod(CVisualization &file) {
    std::string tmp;
    while(1) {
        if (!file.getLineInLower(tmp) || tmp == "q" || tmp == "quit") {
            throw "quit";
        } else if (tmp == "y" || tmp == "yes" ){
            return true;
        }
        else if(tmp == "n" || tmp == "no"){
            return false;
        }
        else file.pasteEndOfLine("Invalid input. Try again.");
    }
}

bool CGame::askLoadBeforeStart(CVisualization &file) {
    file.pasteEndOfLine("Do you have old game you want to load?");
    if(yesMethod(file)){
        if(!loadFromFile()) {
            file.pasteEndOfLine("You can try again.");
                if(!loadFromFile()){
                    return true;
                }
                else return false;
            }
        else return false;
        }
        else return true;
    }

bool CGame::afterSave() {
    if (!canLoadGame()) {
        return true;
    } else return newGame();
}

bool CGame::loadGameFile() {
    if(!loadFromFile()){
        file.pasteEndOfLine("Loading was unsuccessful.");
        return false;
    }
    file.pasteEndOfLine("Loading was successful.");
    return true;
}

void CGame::start() {
    bool start;
    bool startLoad;
    while(true){
        try{
            if(savedGames.size() == 0){
                startLoad = true;
                start = true;
            }
            if(startLoad){
                start = askLoadBeforeStart(file);
                startLoad = false;
            }
            if(start){
                startGame();
            }
            else {
                savedGames[currentGame].continueGame(file);
            }
        }
        catch(int exception){
            if(exception == 3){
                //goto SAVE; //tmp.txt for creating test files
                start = gameDone();
            }
            else if(exception == 4) {
                //SAVE:
                savedGames[currentGame].setForSaving();
                if(!saveToFile()){
                    file.pasteEndOfLine("Saving was unsuccessful.");
                    start = false;
                }
                else {
                    file.pasteEndOfLine("Saving in file was successful.");
                    start = afterSave();
                }
            }
            else if(exception == 5){
                loadGameFile();
                start = false;
            }
            else {
                savedGames[currentGame].setForSaving();
                if (exception == 1) {
                    std::string name = file.getNameOfGame();
                    if (name == "cancel") {
                        start = false;
                    }
                    else {
                        currentGame = saveGame(name); //zde todo
                        start = afterSave();
                    }
                } else if (!canLoadGame()) {
                    file.pasteEndOfLine("No games saved locally.");
                    startLoad = true;
                } else {
                    std::string tmp = currentGame;
                    loadGame();
                    if(tmp != currentGame){
                        savedGames.erase(tmp);
                    }
                    start = false;
                }
            }
        }

    }
}

bool CGame::loadFromFile() {
    file.pasteEndOfLine("Write an address of file");
    std::string fileName;
    file.getLineRegular(fileName);
    if(fileName.empty()){
        file.paste("No file.");
        return false;
    }
    std::ifstream inFile(fileName);
    if (!inFile) {
        file.paste("Cannot open file.");
        return false;
    }
    try {
        CChess chess(inFile, file);
        currentGame = TMP_SAVE_TEXT;
        savedGames.clear();
        savedGames.emplace(currentGame, chess);
        savedGames[currentGame].setForSaving();
        return true;
    }
    catch(std::invalid_argument &){
        file.paste("Loading was unsuccessful.");
        return false;
    }
}
