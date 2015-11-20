#include "GameObject.h"

/*Game object global states
	-It is possible to improve performance of game objects by avoiding certain actions
	-For example, in the naming constructor we can use the GINES_GO_USE_INDEX_NAME bit to avoid the string= operation
*/
#define GINES_GO_USE_INDEX_NAMING 1//Should the default constructor use index naming
#define GINES_GO_NOTIFY_PARENT 2//Should the destructor call parent -> remove child
#define GINES_GO_STATE_DATA_TYPE int8_t//Update this type when number of state bits exceeds type's bit count
static GINES_GO_STATE_DATA_TYPE GAME_OBJECT_STATE = GINES_GO_USE_INDEX_NAMING | GINES_GO_NOTIFY_PARENT;//Sets these bits to 1's
static std::vector<gines::GameObject*> gameObjects;//All the game objects. TODO: better performance (getGameObject(stringName) goes through the entire vector)
Transform nulltransform;
namespace state
{
	void enable(GINES_GO_STATE_DATA_TYPE bit)
	{//Sets this bit to 1
		GAME_OBJECT_STATE |= bit;
	}
	void disable(GINES_GO_STATE_DATA_TYPE bit)
	{//Sets this bit to 0
		GAME_OBJECT_STATE &= ~bit;
	}
	void toggle(GINES_GO_STATE_DATA_TYPE bit)
	{//If this bit is 1, it is set to 0. If it is 0 it is set to 1 instead
		GAME_OBJECT_STATE ^= bit;
	}
	bool isEnabled(GINES_GO_STATE_DATA_TYPE bit)
	{//Returns true if this bit is 1
		if (GAME_OBJECT_STATE & bit)
			return true;
		return false;
	}
}
gines::GameObject* gines::GameObject::getGameObject(std::string gameObjectName) {
	for (unsigned i = 0; i < gameObjects.size(); i++) {
		if (gameObjects[i]->getNameReference() == gameObjectName) {
			return gameObjects[i];
		}
	}
	return nullptr;
}


namespace gines
{
	GameObject::GameObject()
	{//Default constructor
		

		//Called for every game object
		static unsigned gameObjectIndex = 0;
		gameObjectIndex++;

		//Name each game object with index so that each object has a different name by default
		if (state::isEnabled(GINES_GO_USE_INDEX_NAMING))//Check whether to avoid index naming this time
		{//Use index naming
			name = "GameObject" + gameObjectIndex;
		}
		else
		{//Do not name the object here
			state::enable(GINES_GO_USE_INDEX_NAMING);//Sets the state to use index naming next time
		}
		gameObjects.push_back(this);
	}
	GameObject::GameObject(std::string gameObjectName)
	{//Naming constructor
		state::disable(GINES_GO_USE_INDEX_NAMING);//Clear this bit so that index naming is not used
		GameObject();
		name = gameObjectName;
	}

	GameObject::~GameObject() {

		//Notify parent object
		if (state::isEnabled(GINES_GO_NOTIFY_PARENT))
		{
			if (parent != nullptr) {
				parent->removeChild(this);
			}
		}
		else
		{
			state::enable(GINES_GO_NOTIFY_PARENT);//Notify by default next time
		}

		//Free component memory
		while (!components.empty()) {
			delete components.back();
			components.pop_back();
		}

		//Free children memory
		while (!children.empty()) {
			state::disable(GINES_GO_NOTIFY_PARENT);//Clear this bit so that this is  not notified
			delete children[0];
			children.erase(children.begin());
		}

		//Remove self from game objects vector
		for (unsigned i = 0; i < gameObjects.size(); i++) {
			if (gameObjects[i] == this) {
				gameObjects.erase(gameObjects.begin() + i);
			}
		}
	}
	void GameObject::update() {
		for (unsigned i = 0; i < components.size(); i++) {
			components[i]->update();
		}
		for (auto it : children) {
			it->update();
		}
	}
	void GameObject::render() {
		for (unsigned i = 0; i < components.size(); i++) {
			components[i]->render();
		}
		for (auto it : children) {
			it->render();
		}
	}
	Transform& GameObject::transform() {
		if (transformComponent == nullptr)
		{
			//TODO: warning: trying to access transform component which does not exist
			//logError("\nWarning: trying to access transform shortcut which does not exist!");
			return nulltransform;
		}
		return *transformComponent;
	}

	//-----------------//
	// RELATED OBJECTS //
	//-----------------//
	//Parent
	GameObject* GameObject::getParent() {
		return parent;
	}
	GameObject* GameObject::createParent() {
		unparent();
		parent = new GameObject();
		return parent;
	}
	GameObject* GameObject::createParent(std::string parentName) {
		unparent();
		parent = new GameObject(parentName);
		return parent;
	}
	void GameObject::setParent(std::string parentName) {
		unparent();
		parent = getGameObject(parentName);
	}
	void GameObject::setParent(GameObject* parentObject) {
		unparent();
		parent = parentObject;
	}
	void GameObject::unparent() {
		parent = nullptr;
	}
	void GameObject::destroyParent() {
		delete parent;
		unparent();
	}
	//Children
	std::vector<GameObject*> GameObject::getChildren() {
		return children;
	}
	GameObject* GameObject::getChild(std::string childName) {
		for (unsigned i = 0; i < children.size(); i++) {
			if (children[i]->getNameReference() == childName) {
				return children[i];
			}
		}
		return nullptr;
	}
	GameObject* GameObject::createChild() {
		children.push_back(new GameObject());
		return children.back();
	}
	GameObject* GameObject::createChild(std::string childName) {
		children.push_back(new GameObject(childName));
		return children.back();
	}
	void GameObject::addChild(std::string childName) {
		children.push_back(getGameObject(childName));
	}
	void GameObject::addChild(GameObject* childObject) {
		children.push_back(childObject);
	}
	void GameObject::removeChild(std::string childName) {
		for (unsigned i = 0; i < children.size(); i++) {
			if (children[i]->getNameReference() == childName) {
				children.erase(children.begin() + i);
				return;
			}
		}
	}
	void GameObject::removeChild(GameObject* childObject) {
		for (unsigned i = 0; i < children.size(); i++) {
			if (children[i] == childObject) {
				children.erase(children.begin() + i);
				return;
			}
		}
	}
	void GameObject::destroyChild(std::string childName) {
		for (unsigned i = 0; i < children.size(); i++) {
			if (children[i]->getNameReference() == childName) {
				delete children[i];
				children.erase(children.begin() + i);
				return;
			}
		}
	}
	void GameObject::destroyChild(GameObject* childObject) {
		for (unsigned i = 0; i < children.size(); i++) {
			if (children[i] == childObject) {
				delete children[i];
				children.erase(children.begin() + i);
				return;
			}
		}
	}
}