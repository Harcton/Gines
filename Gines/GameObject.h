#ifndef GameObject_h_
#define GameObject_h_

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <memory>
#include "Component.h"

class GameObject
{
public:
	GameObject();
	~GameObject();

	void update();
	void render();

	/*Adds component of type T. If T is mono component and the object already has one instance
	of that component then no component is added.*/
	template <typename T>
	void addComponent()
	{
		//Create component
		T* newComponent = new T();
		//Check if newComponent is a mono component, if it is then check whether there already is one
		MonoComponent* mono = dynamic_cast<MonoComponent*>(newComponent);
		if (mono != nullptr)
		{//Component is mono component. Check for an existing instance of that component
			if (getComponent<T>() != nullptr)
			{//There is already component of this type, return
				delete newComponent;
				return;
			}
		}
		//Convert the new component pointer (T*) into a Component* pointer
		Component* cast = dynamic_cast<Component*>(newComponent);
		components.push_back(cast);
	}

	/*Returns true if the component was removed. False is returned if component is not found
	*/
	template<typename T>
	bool removeComponent()
	{
		T* cast;
		for (unsigned i = 0; i < components.size(); i++)
		{
			cast = dynamic_cast<T*>(components[i]);
			if (cast != nullptr)
			{
				delete cast;
				components.erase(components.begin() + i);
				return true;//Component deleted
			}
		}
		return false;//No component of given type T was found
	}

	/*Returns nullptr if no component of given type exists*/
	template <typename T>
	T* getComponent()
	{
		T* cast;
		for (unsigned i = 0; i < components.size(); i++)
		{
			cast = dynamic_cast<T*>(components[i]);
			if (cast != nullptr)
			{
				return cast;
			}
		}
		return nullptr;
	}

	/*Returns nullptr if no components of given type exists*/
	template <typename T>
	std::vector<T*> getComponents()
	{
		std::vector<T*> _components;
		T* cast;
		for (unsigned i = 0; i < components.size(); i++)
		{
			cast = dynamic_cast<T*>(components[i]);
			if (cast != nullptr)
			{
				_components.push_back(cast);
			}
		}
		return _components;
	}
	
private:
	std::vector<Component*> components;
};
#endif