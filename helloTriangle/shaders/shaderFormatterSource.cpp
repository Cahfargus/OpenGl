#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>

int main(int argc, char *argv[]) {

    std::fstream shader;
    std::string line;

    shader.open(argv[1]);

    std::getline(shader, line);

    while(!shader.eof()){
        if(line != ""){
        std::cout << "\"" << line << "\\n\"" << std::endl;
        }  
        std::getline(shader, line);
    }

    std::cout << "\"" << line << "\\0\"" << std::endl;

    return 0;
}    