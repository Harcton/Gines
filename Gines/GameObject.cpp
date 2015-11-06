#include "GameObject.h"

GameObject::GameObject() {

}

GameObject::~GameObject() {

}

void GameObject::draw() {

}

void GameObject::update() {

}

void GameObject::addComponent(Component* component) {
	components.push_back(component);
}