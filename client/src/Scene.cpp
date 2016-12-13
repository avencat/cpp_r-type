#include "..\inc\Scene.hpp"

Scene::Scene()
{
}

Scene::~Scene()
{
}

bool Scene::addObject(const Object &obj)
{
	this->objects.push_back(obj);
	return (true);
}

bool Scene::deleteObject(const Object &obj)
{
	for (std::list<const Object &>::const_iterator i = objects.begin(); i != objects.end(); i++)
	{
		if ((*i).getName() == obj.getName()) {
			this->objects.erase(i);
			return (true);
		}
	}
	return (false);
}

bool Scene::updateObject(const Object &obj)
{
	return (false);
}
