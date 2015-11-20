#ifndef GameObject_h_
#define GameObject_h_

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <memory>
#include "Transform.h"

namespace gines
{
	class GameObject
	{
	public:
		static GameObject* getGameObject(std::string gameObjectName);

		GameObject();
		GameObject(std::string gameObjectName);
		~GameObject();

		void update();
		void render();

		//------------//
		// COMPONENTS //
		//------------//

		/*Adds component of type T. If T is mono component and the object already has one instance
		of that component then no component is added.*/
		template <typename T>
		void addComponent()
		{
			//Create component
			T* newComponent = new T();
			//Check if newComponent is a mono component, if it is then check whether there already is one
			MonoComponent* mono = dynamic_cast<MonoComponent*>(newComponent);
			if (mono != nullptr) {
				//Component is mono component. Check for an existing instance of that component
				if (getComponent<T>() != nullptr) {
					//There is already component of this type, return
					//Error(GameObjectError::MonoComponentFound);
					delete newComponent;
					return;
				}
				//Error(GameObjectError::AddingMonoComponent);

				//Check if transform
				Transform* tf = dynamic_cast<Transform*>(newComponent);
				if (tf != nullptr)
				{//Set tranform
					transformComponent = tf;
				}
			}
			//Convert the new component pointer (T*) into a Component* pointer
			Component* cast = dynamic_cast<Component*>(newComponent);
			components.push_back(cast);
		}

		/*Returns true if the component was removed. False is returned if component is not found*/
		template<typename T>
		bool removeComponent()
		{
			T* cast;
			for (unsigned i = 0; i < components.size(); i++)
			{
				cast = dynamic_cast<T*>(components[i]);
				if (cast != nullptr)
				{
					//Check if transform
					Transform* tf = dynamic_cast<Transform*>(components[i]);
					if (tf != nullptr)
					{//Nullify transform pointer
						transformComponent = nullptr;
					}

					delete cast;
					components.erase(components.begin() + i);
					return true;//Component deleted
				}
			}
			//Error(GameObjectError::ComponentNotFound);
			return false;//No component of given type T was found
		}

		/*Returns nullptr if no component of given type exists*/
		template <typename T>
		T* getComponent() {
			T* cast;
			for (unsigned i = 0; i < components.size(); i++) {
				cast = dynamic_cast<T*>(components[i]);
				if (cast != nullptr) {
					return cast;
				}
			}
			//getComponentia kutsutaan MonoObjectin lis‰‰misess‰, niin se tulostaa silloinkin virheen, vaikka mit‰‰n virhett‰ ei periaatteessa ole tapahtunut.
			//Error(GameObjectError::ComponentDoesNotExist);
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
			if (_components.size() == 0) {
				Error(GameObjectError::ComponentsDoNotExist);
			}
			return _components;
		}

		std::string getName(){ return name; }
		std::string& getNameReference(){ return name; }

		//-----------------//
		// RELATED OBJECTS //
		//-----------------//
		//Parent
		GameObject* getParent();
		GameObject* createParent();
		GameObject* createParent(std::string parentName);
		void setParent(std::string parentName);
		void setParent(GameObject* parentObject);
		void unparent();
		void destroyParent();
		//Children
		GameObject* getChild(std::string childName);
		std::vector<GameObject*> getChildren();
		GameObject* createChild();
		GameObject* createChild(std::string childName);
		void addChild(std::string childName);
		void addChild(GameObject* childObject);
		void removeChild(std::string childName);
		void removeChild(GameObject* childObject);
		void destroyChild(std::string childName);
		void destroyChild(GameObject* childObject);


		//Public members
		Transform& transform();

	private:
		std::string name;
		std::vector<Component*> components;
		GameObject* parent = nullptr;
		std::vector<GameObject*> children;
		Transform* transformComponent;
	};
}
#endif