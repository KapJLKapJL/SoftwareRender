#include "..\hdr\Entity.h"

face Entity::getFace()
{
	auto f = mesh->getFace(face_count++);
	return f;
}

bool Entity::eof()
{
	if (face_count == mesh->getFacesVectorSize())
	{
		// (:
		face_count = 0;
		return true;
	}
	return false;
}
