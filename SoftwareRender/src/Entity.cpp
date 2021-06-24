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

void Entity::setPosition(const point3D& t)
{
	model[0][3] = t.x;
	model[1][3] = t.y;
	model[2][3] = t.z;
}

void Entity::setRotationX(const double& angle)
{
	double sinus = sin(angle);
	double cosinus = cos(angle);

	model[1][1] = cosinus;
	model[1][2] = -sinus;
	model[2][1] = sinus;
	model[2][2] = cosinus;
}
