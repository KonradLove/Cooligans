#include "player.h"

Player::Player(glm::vec3 position, WorldMap* map, Camera* cam) : Entity(position) {
	Player::map = map;
	Player::camera = cam;
}
Player::~Player() {

}

void Player::update(float delta_time)
{
	camera->position = glm::vec3(position.x, position.y + 1, position.z);
	
}
