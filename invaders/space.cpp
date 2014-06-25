#include "StdAfx.h"
#include "space.h"
#include "resource.h"
#include <MMSystem.h>

space::space(void){

	str.LoadStringW(0,IDC_SCORE,0);
	llvl.LoadStringW(0,IDC_LEVEL,0);
	lliv.LoadStringW(0,IDC_LIVES,0);
	liv.Format(_T("%d"),lives);
	lvl.Format(_T("%d"),level);
	SetBoard();
	SetPlayer();
	SetAliens();
	//aliens	
	}

space::~space(void)
{
}
void space::SetBoard(){
	border.SetRect(0,0,640,480);
	aTopBorder=AfxGetApp()->GetProfileInt(L"Game",L"aTopBorder" ,68);
	aLeftBorder=AfxGetApp()->GetProfileInt(L"Game",L"aLeftBorder" ,88);
	hStep=AfxGetApp()->GetProfileInt(L"Game",L"hStep" ,1);
	vStep=AfxGetApp()->GetProfileInt(L"Game",L"vStep" ,4);
	pStep=AfxGetApp()->GetProfileInt(L"Game",L"pStep" ,8);
	rStep=AfxGetApp()->GetProfileInt(L"Game",L"rStep" ,24);
	arStep=AfxGetApp()->GetProfileInt(L"Game",L"arStep" ,14);
	sz.cx=AfxGetApp()->GetProfileInt(L"Game",L"sz.cx" ,32);
	sz.cy=AfxGetApp()->GetProfileInt(L"Game",L"sz.cy" ,32);
	lives=AfxGetApp()->GetProfileInt(L"Game",L"lives" ,3);
	level=AfxGetApp()->GetProfileInt(L"Game",L"level" ,1);
	score=AfxGetApp()->GetProfileInt(L"Game",L"score" ,0);

	reset=AfxGetApp()->GetProfileInt(L"Game",L"reset" ,0);
	game=AfxGetApp()->GetProfileInt(L"Game",L"game" ,0);
	pMoveR=AfxGetApp()->GetProfileInt(L"Game",L"pMoveR" ,0);
	pMoveL=AfxGetApp()->GetProfileInt(L"Game",L"pMoveL" ,0);
	pRock=AfxGetApp()->GetProfileInt(L"Game",L"pRock" ,0);
	aRock=AfxGetApp()->GetProfileInt(L"Game",L"aRock" ,0);
	collide=AfxGetApp()->GetProfileInt(L"Game",L"collide" ,0);
	collidep=AfxGetApp()->GetProfileInt(L"Game",L"collidep" ,0);
	exploa=AfxGetApp()->GetProfileInt(L"Game",L"exploa" ,0);
	explop=AfxGetApp()->GetProfileInt(L"Game",L"explop" ,0);
	gameOver=AfxGetApp()->GetProfileInt(L"Game",L"gameOver" ,0);
	MoveR=AfxGetApp()->GetProfileInt(L"Game",L"MoveR" ,1);
}
void space::SetPlayer(){
	p.x=(border.right/2)-16;
	p.y=border.bottom-60;
	player=CRect(p,sz);  
}
void space::SetAliens(){
	for(int i=0;i<10;++i){
		for(int j=0;j<4;++j){
		 int left=aLeftBorder+i*sz.cx*3/2;
		 int top=aTopBorder+j*sz.cy*3/2;
		 a.r=CRect(left,top,left+sz.cx,top+sz.cy);
		 a.i=j;
		 aliens.push_back(a);
		}
	}
	
}

//player move
void space::MoveLeft(){
	if(game==true){
	player.left=max(0,player.left-pStep);
	player.right=max(sz.cx,player.right-pStep);
	}	
}
void space::MoveRight(){
	if(game==true){
	player.left=min(border.right-sz.cx,player.left+pStep);
	player.right=min(border.right,player.right+pStep);
	}

}

//alien move

void space::AMove(){
	if(MoveR==false){
		for(int i=0;i<aliens.size();i++){
			if(aliens.at(i).r.left>border.left){
				aliens.at(i).r.left=aliens.at(i).r.left-hStep;
				aliens.at(i).r.right=aliens.at(i).r.right-hStep;	
			}
			else {
				MoveR=true;ADescend();hStep++;break;	
			}
		}
	}
	else {
		int step=hStep;
		for(int i=0;i<aliens.size();i++){
			if(border.right-aliens.at(i).r.right<step){
				step=border.right-aliens.at(i).r.right;
            if(aliens.at(i).r.right>=border.right){
				MoveR=false;ADescend();return;
			}
			}
		}
		for(int i=0;i<aliens.size();i++){
			aliens.at(i).r.OffsetRect(step,0);
			}
		}
	}

void space::ADescend(){
for(int i=0;i<aliens.size();i++){
		aliens.at(i).r.top=aliens.at(i).r.top+vStep;
		aliens.at(i).r.bottom=aliens.at(i).r.bottom+vStep;
		if(aliens.at(i).r.bottom>player.top){
		GameOver();
		}
	}
	
}
void space::PShoot(){
	if(game==true){
		if(!pRock){
			pRocket.left=player.left+4;
			pRocket.right=player.right-24;
			pRocket.top=player.top;
			pRocket.bottom=player.bottom-16;
			pRock=true;
			PlaySound(MAKEINTRESOURCE(IDR_SOUND1),AfxGetResourceHandle(),SND_ASYNC|SND_RESOURCE);
		
		}
	}
}

 void space::PRocketMove(){
	if(pRocket.top>border.top){
		pRocket.left=pRocket.left;
		pRocket.right=pRocket.right;
		pRocket.top=pRocket.top-rStep;
		pRocket.bottom=pRocket.bottom-rStep;
		CollisionA();
	}
	else pRock=false;      
	}

 void space::AShoot(){
	 if(!aRock){
		 int i=rand()%aliens.size();//random number
		 aRocket.left=aliens.at(i).r.left+14;
		aRocket.right=aliens.at(i).r.right-14;
		aRocket.top=aliens.at(i).r.top;
		aRocket.bottom=aliens.at(i).r.bottom-16;
	    aRock=true;
		PlaySound(MAKEINTRESOURCE(IDR_SOUND1),AfxGetResourceHandle(),SND_ASYNC|SND_RESOURCE);
	 }
 }
void space::ARocketMove(){
	if(aRocket.bottom<border.bottom){
	  	aRocket.left=aRocket.left;
		aRocket.right=aRocket.right;
		aRocket.top=aRocket.top+arStep;
		aRocket.bottom=aRocket.bottom+arStep;
		CollisionP();
	}
	else aRock=false;  
}
void space::CollisionA(){
	for(int i=0;i<aliens.size();i++){
	  collide=(aliens.at(i).r.left<pRocket.right&&aliens.at(i).r.right>pRocket.left&&aliens.at(i).r.top<pRocket.bottom&&aliens.at(i).r.bottom>pRocket.top);
	  if(collide){
		  exploa=true;
		  PlaySound(MAKEINTRESOURCE(IDR_SOUND2),AfxGetResourceHandle(),SND_ASYNC|SND_RESOURCE);
		  Score(aliens.at(i).i);
		  aliens.erase(aliens.begin()+i);
		  if(aliens.empty())NextLevel();
		  pRock=false;
		  collide=false;
		  break; 
	  }
	}	
}
void space::CollisionP(){
	collidep=(player.left<aRocket.right&&player.right>aRocket.left&&player.top<aRocket.bottom&&player.bottom>aRocket.top);
	if(collidep){
		explop=true;
		PlaySound(MAKEINTRESOURCE(IDR_SOUND2),AfxGetResourceHandle(),SND_ASYNC|SND_RESOURCE);
		lives--;
		 liv.Format(_T("%d"),lives);
		if(lives<1){GameOver();}
		aRock=false;
		collidep=false;
	}
}
 void space::Score(int i){
	if(i==0)score=score+40;
	if(i==1)score=score+30;
	if(i==2)score=score+20;
	if(i==3)score=score+10;
    scr.Format(_T("%d"),score);
}

void space::NextLevel(){
	game=false;
	explop=false;
	exploa=false;
	pRock=false;
	aRock=false;
	SetPlayer();
	SetAliens();
	hStep=1+level;
	level++;
	lvl.Format(_T("%d"),level);
}

void space::Pause(){
 game=!game;
}
void space::Reset(){
	for(int i=0;i<aliens.size();i++){
		aliens.clear();
	}

	liv.Format(_T("%d"),lives);
	lvl.Format(_T("%d"),level);
	scr.Format(_T("%d"),score);
	SetBoard();
	SetPlayer();
	SetAliens();
}
void space::GameOver(){
     gameOver=true;
}
