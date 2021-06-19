#include "..\hdr\Entity.h"

face Entity::getFace()
{
	return mesh->getFace(face_count++);
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
