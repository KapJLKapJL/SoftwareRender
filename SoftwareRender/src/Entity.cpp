#include "..\hdr\Entity.h"

face Entity::getFace()
{
	auto f = mesh->getFace(face_count++);

	for (int i = 0; i < 3; i++)
	{
		f.v[i].coord = f.v[i].coord * resize_coef;
	}

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

void Entity::setRotation(const double& alpha, const double& beta, const double& gamma)
{
	double sin_a = sin(alpha);
	double cos_a = cos(alpha);
	double sin_b = sin(beta);
	double cos_b = cos(beta);
	double sin_g = sin(gamma);
	double cos_g = cos(gamma);

	model[0][0] = cos_b * cos_g;   model[0][1] = -sin_g * cos_a + cos_g * sin_b * sin_a;   model[0][2] = sin_g * sin_a  + cos_g * sin_b * cos_a;
	model[1][0] = cos_b * sin_g;   model[1][1] = cos_a * cos_g  + sin_b * sin_g * sin_a;   model[1][2] = -sin_a * cos_g + sin_b * sin_g * cos_a;
	model[2][0] = -sin_b;          model[2][1] = sin_a * cos_b;                            model[2][2] = cos_a * cos_b;
}
