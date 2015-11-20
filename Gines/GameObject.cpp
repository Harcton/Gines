#include "GameObject.h"

GameObject::GameObject() {

}

GameObject::~GameObject() {
	//Free component memory
	while (!components.empty()) {
		delete components.back();
		components.pop_back();
	}

	//Delete children from memory
	while (!children.empty()) {
		children.erase(children.begin());
	}
}
void GameObject::update() {
	for (unsigned i = 0; i < components.size(); i++) {
		components[i]->update();
	}
	for (auto it : children) {
		it.second->update();
	}
}
void GameObject::render() {
	for (unsigned i = 0; i < components.size(); i++) {
		components[i]->render();
	}
	for (auto it : children) {
		it.second->render();
	}
}

void GameObject::addChild(std::string key, GameObject* child) {
	children.insert(std::make_pair(key, child));
}

void GameObject::removeChild(std::string key) {
	children.erase(children.find(key));
}

GameObject* GameObject::getChild(std::string key) {
	auto it = children.find(key);
	if (it != children.end()) {
		return it->second;
	}
	return nullptr;
}