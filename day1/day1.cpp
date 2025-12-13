#include <iostream>
#include <fstream>
#include <string>

// Part 2 - 6099

int part1(std::string fname) {
    std::ifstream fin(fname, std::ifstream::in);

    std::string line;

    int dial = 50, counter = 0;

    while(std::getline(fin, line)) {
        switch(line[0]) {
            case 'L':
                dial = (((dial - stoi(line.substr(1, line.length() - 1))) % 100) + 100) % 100;
                break;
            case 'R':
                dial = (((dial + stoi(line.substr(1, line.length() - 1))) % 100) + 100) % 100;
                break;
            default:
                break;
        }

        if (dial == 0) {
            counter++;
        }
    }

    return counter;
}

int part2(std::string fname) {
    std::ifstream fin(fname, std::ifstream::in);
    std::string line;

    int dial = 50, counter = 0, num, cycles;
    bool at_zero = false;

    while(std::getline(fin, line)) {
        num = stoi(line.substr(1));

        switch(line[0]) {
            case 'L':
                dial -= num;
                break;

            case 'R':
                dial += num;
                break;
        }

        if (dial < 0) {
            cycles = 1 + (-dial / 100);
            if (at_zero) {
                cycles -= 1;
            }
        } else if (dial >= 100) {
            cycles = dial / 100;
        } else if (dial == 0) {
            cycles = 1;
        } else {
            cycles = 0;
        }
        counter += cycles;
        dial = ((dial % 100) + 100) % 100;
        at_zero = dial == 0;
    }

    return counter;
}


int main() {
    std::string fname = "input.txt";

    std::cout << "Password: " << part2(fname) << std::endl;
}