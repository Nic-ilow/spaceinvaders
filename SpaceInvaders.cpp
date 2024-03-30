#include "SpaceInvaders.h"

using namespace std;

Player player;
std::list<Enemy> enemies;
std::list<Enemy>::iterator enemiesIterator;
std::list<Bullet> bullets;
std::list<Bullet>::iterator bulletsIterator;


int i, j, score = 0;
enum eDirection { STOP = 0, LEFT, RIGHT };
eDirection dir;
bool shoot;
bool gameOver;
bool printPlayer, printEnemy, printBullet;


void spawnEnemies() {
	for (i = 0; i < width / 3; i++) {
		Enemy enemy;
		enemy.setXPos(rand() % (width-1));
		enemy.setYPos(1);
		enemies.push_back(enemy);
	}
}

void moveEnemies() {
	for (enemiesIterator = enemies.begin(); enemiesIterator != enemies.end(); enemiesIterator++) {
		enemiesIterator->setYPos(enemiesIterator->getYPos() + 1);
	}
}

void logic() {
	if (dir == LEFT) {
		if (player.getXPos() > 0) {
			player.setXPos(player.getXPos() - 1);
		}
		else {
			player.setXPos(width - 1);
		}
}
	else if (dir == RIGHT) {
		if (player.getXPos() == width - 1) {
			player.setXPos(0);
		}
		else {
			player.setXPos(player.getXPos() + 1);
		}

	}
	dir = STOP;
	
	if (shoot) {
		Bullet bullet;
		bullet.create(player.getXPos(), player.getYPos() - 1);
		bullets.push_back(bullet);
		shoot = false;
	}

	for (bulletsIterator = bullets.begin(); bulletsIterator != bullets.end(); bulletsIterator++) {
		for (enemiesIterator = enemies.begin(); enemiesIterator != enemies.end(); enemiesIterator++) {
			if (bulletsIterator->getXPos() == enemiesIterator->getXPos() && bulletsIterator->getYPos() == enemiesIterator->getYPos()) {
				score++;
				if (bullets.size() == 1) {
					bullets.clear();
					break;
				}
				else {
					bulletsIterator = bullets.erase(bulletsIterator);
				}
				if (enemies.size() == 1) {
					enemies.clear();
				}
				else {
					enemiesIterator = enemies.erase(enemiesIterator);
				}
				break;
			}
		}
		if (bullets.empty()) {
			break;
		}
		if (bulletsIterator->getYPos() == 0) {
			if (bullets.size() == 1) {
				bullets.clear();
				break;
			}
			else {
				bulletsIterator = bullets.erase(bulletsIterator);
			}
		}
		else {
			bulletsIterator->setYPos(bulletsIterator->getYPos() - 1);
		}
	}
}


void Input() {
	if (_kbhit()) {
		switch (_getch()) {
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case ' ':
			shoot = true;
			break;
		case 'x':
			gameOver = true;
			break;
		}
	}
}

void draw() {
	system("cls");
	for (i = 0; i < width; i++) {
		cout << "#";
	}
	cout << endl;

	for (i = 0; i < height; i++) {

		for (j = 0; j < width; j++) {
			printEnemy = false;
			printPlayer = false;
			printBullet = false;
			if (j == 0 || j == width - 1) {
				cout << "#";
			}
			else if (j == player.getXPos() && i == player.getYPos()) {
				cout << "-";
				printPlayer = true;
			}
			for (enemiesIterator = enemies.begin(); enemiesIterator != enemies.end(); enemiesIterator++) {
				if (j == enemiesIterator->getXPos() && i == enemiesIterator->getYPos()) {
					cout << "X";
					printEnemy = true;
				}
			}
			for (bulletsIterator = bullets.begin(); bulletsIterator != bullets.end(); bulletsIterator++) {
				if (j == bulletsIterator->getXPos() && i == bulletsIterator->getYPos()) {
					cout << "*";
					printBullet = true;
				}
			}
			if (!printEnemy && !printPlayer && !printBullet) {
				cout << " ";
			}
		}
		cout << endl;
	}

	for (i = 0; i < width; i++) {
		cout << "#";
	}
	cout << endl;
	cout << "Score: " << score << endl;
}


int main() {	
	shoot = false;
	dir = STOP;
	gameOver = false;
	int turn = 0;
	while (!gameOver) {
		if (!(turn % 25)) {
			moveEnemies();
			spawnEnemies();
		}
		Input();
		logic();
		draw();
		turn++;
		Sleep(100);
	}
}