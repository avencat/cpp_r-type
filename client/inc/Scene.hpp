#ifndef SCENE_HPP_
# define SCENE_HPP_

# include <list>
# include "Object.hpp"

class Scene
{
public:
	Scene();
	virtual ~Scene();
	bool	addObject(const Object &);
	bool	deleteObject(const Object &);
	bool	updateObject(const Object &);

private:
	std::list<Object>	objects;
};

#endif /* !SCENE_HPP_ */
