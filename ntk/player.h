#pragma once

class Player : public GameObject
{
public:
	/* Construct the player (player ID automatically defined) */
	Player(const char* fileName, int nf);

	void Init() override;
	void Update(float deltaTime) override;
	void Draw(Surface* screen) override;

private:
	// extra components for player
	Input input;
};