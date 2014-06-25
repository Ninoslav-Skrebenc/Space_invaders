#pragma once
#include <vector>
#include "Alien.h"

typedef std::vector<Alien> cont;
typedef cont::const_iterator iter;


class space
{
public:
	space(void);
	~space(void);
	//atributes
	bool game;
	CRect border;

	CPoint p;
	CRect player;

    CRect pRocket;
	bool pRock;

	CRect aRocket;
	bool aRock;

	CSize sz;
	bool MoveR;

	bool pMoveR;
	bool pMoveL;
	bool collide;
	bool collidep;
	bool exploa;
	bool explop;

	int lives;
	int level;
    int aLeftBorder;
    int aTopBorder;

	int hStep;
	int vStep;
	int pStep;
	int rStep;
	int arStep;

	int score;
	CString str;
	CString scr;
	CString llvl;
	CString lvl;
	CString liv;
	CString lliv;

	cont aliens;
	Alien a;

	bool gameOver;
	bool reset;
	
	//operations
	void SetBoard();
	void SetPlayer();
	void SetAliens();

    void MoveLeft();
	void MoveRight();

	void AMove();
	void ADescend();


	void PShoot();
	void PRocketMove();

	void AShoot();
	void ARocketMove();

	void CollisionA();
	void CollisionP();
			 
	void Score(int i);

	void Pause();
	void NextLevel();
	void Reset();
	void GameOver();
};

