#pragma once
#include"Collision3D.h"
#include"Collider3D.h"
#include"DxLib.h"

class BoxCollider3D : public Collider3D
{
private:
	// �R���C�_�[�̉�]
	Vector3 m_rot;

public:
	Vector3 m_size;

	Vector3 m_normVec[3] =
	{
		Vector3(1, 0, 0),	// x
		Vector3(0, 1, 0),	// y
		Vector3(0, 0, 1),	// z
	};

	BoxCollider3D(const Vector3& size, const Vector3& offset = Vector3(0, 0, 0)) :
		Collider3D(offset),
		m_size(size){}

	// �����蔻��̃T�C�Y��ύX
	void ChangeSize(const Vector3& size) override
	{
		m_size = size;
	}

	// �Փ˔���
	virtual bool CheckCollision(const Transform3D& transform1, const Transform3D& transform2, const Collider3D* collider2) const override
	{
		// �_�u���f�B�X�p�b�`�ɂ��`�󎯕ʂ�����
		return collider2->CheckCollision(transform2, transform1, this);
	}
	virtual bool CheckCollision(const Transform3D& transform1, const Transform3D& transform2, const BoxCollider3D* collider2) const override
	{
		// ���~��
		return Collision3D::Check(transform1, this, transform2, collider2);
	}

#ifdef _DEBUG
	// �`��
	virtual void Draw(const Transform3D& transform) const override
	{
		DrawLine3D(
			transform.position + Vector3(m_size.x / 2, -m_size.y / 2, m_size.z / 2) + m_offset,
			transform.position + Vector3(-m_size.x / 2, -m_size.y / 2, m_size.z / 2) + m_offset,
			GetColor(255, 255, 0));
		DrawLine3D(
			transform.position + Vector3(m_size.x / 2, -m_size.y / 2, -m_size.z / 2) + m_offset,
			transform.position + Vector3(-m_size.x / 2, -m_size.y / 2, -m_size.z / 2) + m_offset,
			GetColor(255, 255, 0));
		DrawLine3D(
			transform.position + Vector3(m_size.x / 2, m_size.y / 2, m_size.z / 2) + m_offset,
			transform.position + Vector3(-m_size.x / 2, m_size.y / 2, m_size.z / 2) + m_offset,
			GetColor(255, 255, 0));
		DrawLine3D(
			transform.position + Vector3(m_size.x / 2, m_size.y / 2, -m_size.z / 2) + m_offset,
			transform.position + Vector3(-m_size.x / 2, m_size.y / 2, -m_size.z / 2) + m_offset,
			GetColor(255, 255, 0));


		DrawLine3D(
			transform.position + Vector3(m_size.x / 2, 0, m_size.z / 2) + m_offset,
			transform.position + Vector3(m_size.x / 2, -m_size.y / 2, m_size.z / 2) + m_offset,
			GetColor(255, 255, 0));		
		DrawLine3D(
			transform.position + Vector3(m_size.x / 2, 0, m_size.z / 2) + m_offset,
			transform.position + Vector3(m_size.x / 2, m_size.y / 2, m_size.z / 2) + m_offset,
			GetColor(255, 255, 0));
		DrawLine3D(
			transform.position + Vector3(m_size.x / 2, 0, -m_size.z / 2) + m_offset,
			transform.position + Vector3(m_size.x / 2, -m_size.y / 2, -m_size.z / 2) + m_offset,
			GetColor(255, 255, 0));		
		DrawLine3D(
			transform.position + Vector3(m_size.x / 2, 0, -m_size.z / 2) + m_offset,
			transform.position + Vector3(m_size.x / 2, m_size.y / 2, -m_size.z / 2) + m_offset,
			GetColor(255, 255, 0));
		DrawLine3D(
			transform.position + Vector3(-m_size.x / 2, 0, m_size.z / 2) + m_offset,
			transform.position + Vector3(-m_size.x / 2, -m_size.y / 2, m_size.z / 2) + m_offset,
			GetColor(255, 255, 0));		
		DrawLine3D(
			transform.position + Vector3(-m_size.x / 2, 0, m_size.z / 2) + m_offset,
			transform.position + Vector3(-m_size.x / 2, m_size.y / 2, m_size.z / 2) + m_offset,
			GetColor(255, 255, 0));
		DrawLine3D(
			transform.position + Vector3(-m_size.x / 2, 0, -m_size.z / 2) + m_offset,
			transform.position + Vector3(-m_size.x / 2, -m_size.y / 2, -m_size.z / 2) + m_offset,
			GetColor(255, 255, 0));
		DrawLine3D(
			transform.position + Vector3(-m_size.x / 2, 0, -m_size.z / 2) + m_offset,
			transform.position + Vector3(-m_size.x / 2, m_size.y / 2, -m_size.z / 2) + m_offset,
			GetColor(255, 255, 0));


		DrawLine3D(
			transform.position + Vector3(m_size.x / 2, -m_size.y / 2, m_size.z / 2) + m_offset,
			transform.position + Vector3(m_size.x / 2, -m_size.y / 2, -m_size.z / 2) + m_offset,
			GetColor(255, 255, 0));		
		DrawLine3D(
			transform.position + Vector3(-m_size.x / 2, -m_size.y / 2, m_size.z / 2) + m_offset,
			transform.position + Vector3(-m_size.x / 2, -m_size.y / 2, -m_size.z / 2) + m_offset,
			GetColor(255, 255, 0));
		DrawLine3D(
			transform.position + Vector3(m_size.x / 2, m_size.y / 2, m_size.z / 2) + m_offset,
			transform.position + Vector3(m_size.x / 2, m_size.y / 2, -m_size.z / 2) + m_offset,
			GetColor(255, 255, 0));
		DrawLine3D(
			transform.position + Vector3(-m_size.x / 2, m_size.y / 2, m_size.z / 2) + m_offset,
			transform.position + Vector3(-m_size.x / 2, m_size.y / 2, -m_size.z / 2) + m_offset,
			GetColor(255, 255, 0));
	}
#endif
};