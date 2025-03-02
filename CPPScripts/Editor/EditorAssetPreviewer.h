#pragma once
#include "../pubh.h"
#include "../PublicStruct.h"
#include "EditorEnumStruct.h"

namespace ZXEngine
{
	class Material;
	class CubeMap;
	class Texture;
	class GameObject;
	class StaticMesh;
	class MeshRenderer;
	class RenderStateSetting;
	class EditorAssetPreviewer
	{
	public:
		EditorAssetPreviewer();
		~EditorAssetPreviewer();

		bool Check();
		void Draw();
		void Reset(float size = 1.0f);
		void UpdateModelScale(float delta);
		void UpdateModelRotation(float xOffset, float yOffset);

	private:
		float yaw = 0.0f;
		float pitch = 0.0f;
		bool isLoading = false;
		const float rotSensitivity = 0.01f;
		float scale = 1.0f;
		float minScale = 0.1f;
		float maxScale = 10.0f;
		const float standardSize = 6.0f;
		float scaleSensitivity = 0.05f;
		const float standardScaleSensitivity = 0.05f;
		const unsigned int previewSize = 512;
		GameObject* cameraGO;
		StaticMesh* previewQuad;
		Material* previewQuadMaterial;
		Material* previewModelMaterial;
		MeshRenderer* materialSphere;
		Texture* loadingTexture;
		CubeMap* shadowCubeMap;
		RenderStateSetting* renderState;
		RenderStateSetting* previewQuadRenderState;
		uint32_t drawQuadCommandID = 0;
		uint32_t drawPreviewCommandID = 0;

		void RenderMaterialPreview(AssetMaterialInfo* info);
		void RenderModelPreview(AssetModelInfo* info);
		void RenderToQuad();
		Matrix4 GetModelMatrix();
	};
}