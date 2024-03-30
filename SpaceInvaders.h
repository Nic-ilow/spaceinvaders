#include <iostream>
#include <conio.h>
#include<Windows.h>
#include <list>

const int width = 20;
const int height = 20;

class Player {
private:
	int x;
	const int y = height-1;
public:
	Player() : x(width / 2) {}
	~Player() = default;
	
	int getXPos() { return x; }
	int getYPos() { return y; }

	void setXPos(int x) { this->x = x; }

};


class Enemy {
private:
	int x, y;
public:
	Enemy() : x(width / 2), y(0) {}
	~Enemy() = default;

	int getXPos() { return x; }
	int getYPos() { return y; }

	void setXPos(int x) { this->x = x; }
	void setYPos(int y) { this->y = y; }
};


class Bullet {
private:
	int x, y;
public:
	Bullet() : x(width/2), y(height - 1) {}
	~Bullet() = default;
	
	bool create(int x, int y) {
		this->x = x;
		this->y = y;
		return true;
	}

	int getXPos() { return x; }
	int getYPos() { return y; }

	void setXPos(int x) { this->x = x; }
	void setYPos(int y) { this->y = y; }

};