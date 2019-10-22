#ifndef _UI_MANAGER_H
#define _UI_MANAGER_H

#include "GameObject.h"
#include "SDL_ttf.h"

class uiManager : public GameObject
{
private:
	static int hp;
	static int score;
	static int level;
	SDL_Color color = { 255, 255, 255 }; //RGB
	SDL_Surface * surface;
	TTF_Font* font;
	SDL_Texture* texture;
	SDL_Renderer* renderer;
	SDL_Rect* textpos;
	std::string text;
	int xStartingPoint;
	int yStartingPoint;
public:
	bool update(float _frameTime);
	void draw(SDL_Renderer* _renderer);
	static void setScore(int _score);
	static void setLevel(int _level);
	static void setHp(int _hp);
	static void incrementLevel(int _level) { level += _level; }
	static void incrementHp(int _Hp) { hp += _Hp; }
	static void incrementScore(int _Score) { score += _Score; }
	void drawScore();
	void drawHp();
	void drawLvl();
	uiManager(SDL_Renderer* _renderer, int _xStartingPoint, int _yStartingPoint);
	~uiManager();
};
#endif // !_UI_MANAGER_H
