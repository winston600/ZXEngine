#pragma once
#include "pubh.h"

namespace ZXEngine
{
	// �̶�������Mesh�����������UV
	const vec2 GlyphCoords[4] = { vec2(0, 1), vec2(0, 0), vec2(1, 1), vec2(1, 0) };
	// �̶�������Mesh�����ζ�������
	const vector<unsigned int> GlyphIndices =
	{
		1, 0, 2,
		1, 2, 3,
	};

	class TextRenderer
	{
	public:
		// ��ǰ��Ⱦ���ı�
		string text;
		// �ַ���λ��
		vec2 pos;
		// �ַ���С
		float scale;
		// �ַ���ɫ
		vec3 color;

		TextRenderer();
		~TextRenderer() {};

		void Render();
	};
}