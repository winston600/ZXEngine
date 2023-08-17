#pragma once
#include "../pubh.h"
#include "PhysZEnumStruct.h"

namespace ZXEngine
{
	namespace PhysZ
	{
		class RigidBody;
		class CollisionPrimitive
		{
		public:
			// ��ײ������Ӧ�ĸ���
			RigidBody* mRigidBody = nullptr;
			// ��ײ������ڸ����ƫ��(��������ȫ������ʹ�õ�λ���󼴿�)
			Matrix4 mOffset;
			// ��ײ�����������ı任����
			Matrix4 mTransform;

			virtual ~CollisionPrimitive();

			// ��ȡ��ײ������
			virtual ColliderType GetType() const = 0;
			// ���ɶ�Ӧ��״�ľ��ʹ�������
			virtual Matrix3 GetInertiaTensor(float mass) const = 0;
		};

		class CollisionBox : public CollisionPrimitive
		{
		public:
			// Box��3�����ϵĳ��Ȱ뾶
			Vector3 mHalfSize;

			virtual ColliderType GetType() const;
			virtual Matrix3 GetInertiaTensor(float mass) const;

			// ��ȡBoxͶӰ��ĳ�����ϵĳ��ȵ�һ��
			float GetHalfProjectedLength(const Vector3& axis) const;
		};

		// ��ײƽ��(ͨ����ʾ������һ�������ƶ���ǽ����棬�����Ǹ��壬����û�м̳�CollisionPrimitive)
		class CollisionPlane : public CollisionPrimitive
		{
		public:
			// ��ײƽ�淨��
			Vector3 mNormal;
			// ��ײƽ�浽ԭ��ľ���
			float mDistance;

			virtual ColliderType GetType() const;
			virtual Matrix3 GetInertiaTensor(float mass) const;
		};

		class CollisionSphere : public CollisionPrimitive
		{
		public:
			// ��ײ��뾶
			float mRadius;

			virtual ColliderType GetType() const;
			virtual Matrix3 GetInertiaTensor(float mass) const;
		};

		struct CollisionVolume
		{
			// ��ײ������
			ColliderType mType;
			// ��ײ��ָ��
			union
			{
				CollisionBox* mBox;
				CollisionPlane* mPlane;
				CollisionSphere* mSphere;
			};
		};
	}
}