#pragma once

char menu(int integer);
void push();
void pop();
void find_student();
void printlast();
void printAll();
void my_exit();
void clear();
void saveStosToFile();
void readStosFromFile();
void my_menu();

enum INTERFACE {

	PUSH = 1,
	POP,
	TAKE_LAST,
	TAKE_ALL,
	FIND,
	SAVE_ALL_TO_FILE,
	READ_ALL_FROM_FILE,
	CLEAR,
	EXIT
};