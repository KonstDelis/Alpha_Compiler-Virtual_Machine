#include "ErrMsg.hpp"
#include "VM_dispatcher.hpp"

void red(){
    std::cerr<<"\033[1;31m";
}
void yellow(){
    std::cerr<<"\033[1;33m";
}
void reset(){
    std::cerr<<"\033[1;0m";
}
void green(){
    std::cout<<"\033[1;32m";
}
void resetOut(){
    std::cout<<"\033[1;0m";
}

void error_msg(std::string s, unsigned line){
    red();
    std::cerr<<"Runtime error: line "<<line<<": "<<s<<std::endl;
    reset();
    executionFinished = true;
    exit(1);
}
void warning_msg(std::string s, unsigned line){
    yellow();
    std::cerr<<"Warning: line "<<line<<": "<<s<<std::endl;
    reset();
}