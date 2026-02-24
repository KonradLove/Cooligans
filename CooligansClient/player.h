#pragma once

#include "entity.h"
#include "world_map.h"

class Player : public Entity {
public:
	Player(glm::vec3 position, WorldMap* map, Camera* cam);
	~Player();
	void update(float delta_time) override;
	
private:
	float vel_y;
	WorldMap* map;
	Camera* camera;
};