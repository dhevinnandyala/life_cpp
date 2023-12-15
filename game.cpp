//
// Created by Dhevin N on 12/14/23.
//

#include "game.h"
#include <iostream>
#include <map>
#include <array>



class Game {
private:
    int SIZE;
    bool** map;
    bool** nextMap;

public:
    /* constructors: */
    Game(){
        Game(100);
    }

    Game(int size){
        map = (bool**)calloc(size, sizeof(bool*));
        for (int i = 0; i < size; i++) {
            map[i] = (bool*)calloc(size, sizeof(bool));
            for (int j = 0; j < size; j++) {
                map[i][j] = false;
            }
        }
        SIZE = size;
    }

private:

    /* read and write: */

    bool read(int x, int y) {
        if (x < 0 || x >= SIZE - 1) throw("READ-- out of bounds exception");

        return map[x][y];
    }

    void write(int x, int y, bool val) {
        if (x < 0 || x >= SIZE - 1) throw("WRITE-- out of bounds exception");

        if (x == 0 || y == SIZE - 1) {
            printf("Can't modify this");
            return;
        }

        nextMap[x][y] = val;
    }

    void freeMap() {
        for (int i = 0; i < SIZE; i++) {
            free(map[i]);
        }
        free(map);
    }

    /* logic */
    int numNeighbors(int x, int y) {
        int sum = 0;
        for (int i = x - 1; i <= x + 1; i++) {
            for (int j = x - 1; j <= x + 1; j++) {
                if (i == x && j == y) continue;
                if (read(x, y)) sum++;
            }
        }

        return sum;
    }

    bool nextState(int x, int y) {
        int num = numNeighbors(x, y);

        if (num < 2) return false;

        if (num > 3) return false;

        if (num == 3) return read(x, y);

        return true;
    }

public:
    /* interface: */

    int getSize() {
        return SIZE;
    }

    bool** getGeneration() { //need to free in main
        bool** output = (bool**)calloc(SIZE, sizeof(bool*));
        for (int i = 0; i < SIZE; i++) {
            output[i] = (bool*)calloc(SIZE, sizeof(bool));
            for (int j = 0; j < SIZE; j++) {
                output[i][j] = read(i, j);
            }
        }
        return output;
    }

    void setState(std::map<int[2], bool> input) {

        //reset:
        freeMap();
        nextMap = (bool**)calloc(SIZE, sizeof(bool*));
        for (int i = 0; i < SIZE; i++) {
            nextMap[i] = (bool*)calloc(SIZE, sizeof(bool));
            for (int j = 0; j < SIZE; j++) {
                nextMap[i][j] = false;
            }
        }


        std::map<int[2], bool>::iterator it = input.begin();
        map = nextMap;

        while (it != input.end()) {
            write(it->first[0], it->first[1], it->second);
        }
    }

    void update() {
        nextMap = (bool**)calloc(SIZE, sizeof(bool*));
        for (int i = 0; i < SIZE; i++) {
            nextMap[i] = (bool*)calloc(SIZE, sizeof(bool));
        }

        for (int x = 0; x < SIZE - 1; x++) {
            for (int y = 0; y < SIZE - 1; y++) {
                if (x == 0 || y == 0) nextMap[x][y] = 0; //lol rip OOP
                write(x, y, nextState(x, y));
            }
        }
        freeMap();
        map = nextMap;
    }
};