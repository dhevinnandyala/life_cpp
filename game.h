//
// Created by Dhevin N on 12/14/23.
//

#ifndef LIFE_CPP_GAME_H
#define LIFE_CPP_GAME_H


class Game {
private:
    int SIZE;
    bool** map;
    bool** nextMap;

    /* read and write: */
    bool read(int x, int y);
    void write(int x, int y, bool val);
    void freeMap();

    /* logic */
    int numNeighbors(int x, int y);
    bool nextState(int x, int y);

public:
    /* constructors: */
    Game();
    Game(int size);

    /* interface: */
    int getSize();
    bool** getGeneration();
    void setState(std::map<int[2], bool> input);
    void update();
};


#endif //LIFE_CPP_GAME_H
