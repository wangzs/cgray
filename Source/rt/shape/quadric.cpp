#include "quadric.hpp"

cgray::rt::Quadric::Quadric()
	: position_(0,0,0), A(0),B(0),C(0),D(0),E(0),F(0),G(0),H(0),I(0),J(0)
{
}

cgray::rt::Quadric::Quadric(const Vector3f & pos, float a, float b, float c, float d, float e, float f, float g, float h, float i, float j)
	: position_(pos), A(a), B(b), C(c), D(d), E(e), F(f), G(g), H(h), I(i), J(j)
{
}

bool cgray::rt::Quadric::intersect(const Ray & ray, IntersectInfo & info)
{
	const Vector3f& origin = ray.origin();
	const Vector3f& direction = ray.direction();

	float Aq, Bq, Cq, t0, t1, t;

	Aq = A*direction[0]*direction[0] +
		B*direction[1]*direction[1] +
		C*direction[2]*direction[2] +
		D*direction[0]*direction[1] +
		E*direction[0]*direction[2] +
		F*direction[1]*direction[2];

	Bq = 2 * (A*origin[0]*direction[0] + B*origin[1]*direction[1] + C*origin[2]*direction[2] +
		D * (origin[0]*direction[1] + origin[1]*direction[0]) +
		E * (origin[0]*direction[2] + origin[2]*direction[0]) +
		F * (origin[1]*direction[2] + origin[2]*direction[1])) +
		G * direction[0] +
		H * direction[1] +
		I * direction[2];

	Cq = A * origin[0]*origin[0] +
		B * origin[1]*origin[1] +
		C * origin[2]*origin[2] +
		D * origin[0]*origin[1] +
		E * origin[0]*origin[2] +
		F * origin[1]*origin[2] +
		G * origin[0] +
		H * origin[1] +
		I * origin[2] +
		J;

	if (Aq == 0) { t = -Cq / Bq; }
	else
	{
		if ((Bq * Bq - 4 * Aq * Cq) < 0) return false;
		else
		{
			t0 = (-Bq - sqrt(Bq*Bq - 4 * Aq*Cq)) / (2 * Aq);
			t1 = (-Bq + sqrt(Bq*Bq - 4 * Aq*Cq)) / (2 * Aq);

			if (!(t0 < 0.001 && t1 < 0.001))
			{
				if (t0 <= 0.001)
				{
					t = t1;
				}
				else
				{
					t = t0;
				}
                     

				Vector3f norm = Vector3f((2 * A * ((origin[0] - position_[0]) + direction[0] * t) +
					2 * F * ((origin[1] - position_[1]) + direction[1] * t) +
					2 * E * ((origin[2] - position_[2]) + direction[2] * t) + G - position_[0]),
					(2 * B * ((origin[1] - position_[1]) + direction[1] * t) +
						2 * F * ((origin[0] - position_[0]) + direction[0] * t) +
						2 * D * ((origin[2] - position_[2]) + direction[2] * t) + H - position_[1]),
					(2 * C * ((origin[2] - position_[2]) + direction[2] * t) +
						2 * E * ((origin[0] - position_[0]) + direction[0] * t) +
						2 * D * ((origin[1] - position_[1]) + direction[1] * t) + I - position_[2]));

				// set intersection info
				info.hit_point = ray.origin() + ray.direction() * t;
				info.hit_shape = std::make_shared<Quadric>(*this);
				info.is_hit = true;
				info.normal = norm.normalized();
				info.ray = ray;

				return true;
			}
		}
	}
	return(false);
}

Vector3f cgray::rt::Quadric::getNormal(const Vector3f & pos) const
{
	// TODO
	return Vector3f();
}

bool cgray::rt::Quadric::getAABB(AABB & box) const
{
	// TODO
	return false;
}


