#include <string>
#include <iostream>
#ifndef ERR_MSG_H
#define ERR_MSG_H
extern bool DEBUG;

void red();
void yellow();
void green();
void reset();
void resetOut();

void error_msg(std::string s, unsigned line);
void warning_msg(std::string s, unsigned line);
#endif
