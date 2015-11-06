#include "GameObject.h"

GameObject::GameObject() {
	
}

GameObject::~GameObject() {

}

void GameObject::draw() {

}

void GameObject::update() {

}

void GameObject::addComponent(std::string componentName, Component* component) {
	component->setParent(this);
	components.push_back(component);
	componentPosition.insert(std::make_pair(componentName, components.size()-1));
}

void GameObject::removeComponent(std::string componentName) {
	auto it = componentPosition.find(componentName);
	if (it != componentPosition.end()) {
		delete components[it->second];
		components[it->second] = nullptr;
		componentPosition.erase(it);
	}
}

void GameObject::rotate(float rotate) {
	objectRotation += rotate;
}

void GameObject::rotation(float rotation) {
	objectRotation = rotation;
}

void GameObject::move(vector2 move) {
	objectPosition.x += move.x;
	objectPosition.y += move.y;
}

void GameObject::setPosition(vector2 position) {
	objectPosition = position;
}

void GameObject::scale(size_t scale) {
	objectScale.x = scale;
	objectScale.y = scale;
}

void GameObject::scale(vector2 scale) {
	objectScale = scale;
}