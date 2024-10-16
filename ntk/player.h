#pragma once

class Player : public GameObject
{
public:
	Player(const char* fileName, const char* id, int nf)
		: GameObject(fileName, id, nf)
	{ }

	void Init() override;
	void Update(float deltaTime) override;
	void Draw(Surface* screen) override;

private:
	// extra components for player
	Input input;
};