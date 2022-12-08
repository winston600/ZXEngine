#include "Quaternion.h"
#include "../Math.h"

namespace ZXEngine
{
	Quaternion Quaternion::Euler(float x, float y, float z)
	{
		// read here: http://www.euclideanspace.com/maths/geometry/rotations/conversions/eulerToQuaternion/index.htm
		float dx = x * Math::Deg2Rad(0.5f);
		float dy = y * Math::Deg2Rad(0.5f);
		float dz = z * Math::Deg2Rad(0.5f);
		// in order of YXZ, yaw, pitch, roll in local space
		float c1 = cos(dy);
		float s1 = sin(dy);
		float c2 = cos(dz);
		float s2 = sin(dz);
		float c3 = cos(dx);
		float s3 = sin(dx);
		float c1c2 = c1 * c2;
		float s1s2 = s1 * s2;

		Quaternion q;
		q.w = c1c2 * c3 - s1s2 * s3;
		q.x = c1c2 * s3 + s1s2 * c3;
		q.y = s1 * c2 * c3 + c1 * s2 * s3;
		q.z = c1 * s2 * c3 - s1 * c2 * s3;
		return q;
	}

	Quaternion::Quaternion() 
	{
		x = 0;
		y = 0;
		z = 0;
		w = 1.0f;
	}

	Quaternion::Quaternion(float x, float y, float z, float w) 
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	float Quaternion::Normal() const
	{
		return sqrtf(NormalSquare());
	}

	float Quaternion::NormalSquare() const
	{
		return x * x + y * y + z * z + w * w;
	}

	void Quaternion::Normalize()
	{
		float sqrNorm = NormalSquare();
		if (!Math::Approximately(sqrNorm, 0.f))
		{
			float normInverse = 1.0f / sqrtf(sqrNorm);
			x *= normInverse;
			y *= normInverse;
			z *= normInverse;
			w *= normInverse;
		}
	}

	Vector3 Quaternion::GetEulerAngles() const 
	{
		// read here: http://www.euclideanspace.com/maths/geometry/rotations/conversions/quaternionToEuler/index.htm
		float test = x * y + z * w;
		float yaw, pitch, roll;
		if (test > 0.499f)
		{
			// singularity at north pole
			yaw = 2 * atan2(x, w);
			roll = Math::PI * 0.5f;
			pitch = 0;
		}
		else
		{
			if (test < -0.499f)
			{
				// singularity at south pole
				yaw = -2 * atan2(x, w);
				roll = -Math::PI * 0.5f;
				pitch = 0;
			}
			else
			{
				float sqx = x * x;
				float sqy = y * y;
				float sqz = z * z;

				yaw = atan2(2.f * y * w - 2 * x * z, 1 - 2 * sqy - 2 * sqz);
				roll = asin(2 * test);
				pitch = atan2(2 * x * w - 2 * y * z, 1 - 2 * sqx - 2 * sqz);
			}
		}

		Vector3 result;
		result.x = Math::Rad2Deg(pitch);
		result.y = Math::Rad2Deg(yaw);
		result.z = Math::Rad2Deg(roll);
		return result;
	}

	void Quaternion::SetEulerAngles(float x, float y, float z) 
	{
		Quaternion q = Quaternion::Euler(x, y ,z);
		this->x = q.x;
		this->y = q.y;
		this->z = q.z;
		this->w = q.w;
	}

	Matrix4 Quaternion::ToMatrix()
	{
		// ��һ��
		float m00 = 1 - (2 * y * y) - (2 * z * z);
		float m01 = (2 * x * y) - (2 * w * z);
		float m02 = (2 * x * z) + (2 * w * y);

		// �ڶ���
		float m10 = (2 * x * y) + (2 * w * z);
		float m11 = 1 - (2 * x * x) - (2 * z * z);
		float m12 = (2 * y * z) - (2 * w * x);

		// ������
		float m20 = (2 * x * z) - (2 * w * y);
		float m21 = (2 * y * z) + (2 * w * x);
		float m22 = 1 - (2 * x * x) - (2 * y * y);

		return Matrix4(
			m00, m01, m02, 0,
			m10, m11, m12, 0,
			m20, m21, m22, 0,
			0, 0, 0, 1);
	}

	Quaternion Quaternion::operator* (const Quaternion& q) const
	{
		float xx = w * q.x + q.w * x + y * q.z - z * q.y;
		float yy = w * q.y + q.w * y - x * q.z + z * q.x;
		float zz = w * q.z + q.w * z + x * q.y - y * q.x;
		float ww = w * q.w - (x * q.x + y * q.y + z * q.z);
		Quaternion result = Quaternion(xx, yy, zz, ww);
		result.Normalize();
		return result;
	}

	Quaternion& Quaternion::operator*= (const Quaternion& q)
	{
		// ��this�������ٳ�
		*this = *this * q;
		return *this;
	}
}