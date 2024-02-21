#include "PostEffect.h"

PostEffect* PostEffect::GetInstance()
{
	static PostEffect instatnce;
	return &instatnce;
}

void PostEffect::Initialize()
{
	const uint32_t VertexSize = 4;
	const uint32_t IndexSize = 6;

	TextureManager::UnUsedFilePath();
	PostEffect::GetInstance()->TesttexHandle = TextureManager::LoadPngTexture("Resources/Default/uvChecker.png");
	CreateResources::CreateBufferResource(sizeof(VertexData) * VertexSize,PostEffect::GetInstance()->resource_.Vertex);
	CreateResources::CreateBufferResource(sizeof(Material), PostEffect::GetInstance()->resource_.Material);

	PostEffect::GetInstance()->resource_.BufferView = CreateResources::VertexCreateBufferView(sizeof(VertexData) * VertexSize, PostEffect::GetInstance()->resource_.Vertex.Get(), VertexSize);
	CreateResources::CreateBufferResource(sizeof(uint32_t) * IndexSize, PostEffect::GetInstance()->resource_.Index);
	PostEffect::GetInstance()->resource_.IndexBufferView = CreateResources::IndexCreateBufferView(sizeof(uint32_t) * IndexSize, PostEffect::GetInstance()->resource_.Index.Get());

	PostEffect::GetInstance()->viewProjection_.Initialize();
	PostEffect::GetInstance()->worldTransform_.Initialize();

	//レンダーテクスチャの生成
	D3D12_RESOURCE_DESC texDesc

}

void PostEffect::Update()
{
	VertexData* vertexData = nullptr;
	Material* materialData = nullptr;
	uint32_t* indexData = nullptr;
	PostEffect::GetInstance()->resource_.Vertex->Map(0, nullptr, reinterpret_cast<void**>(&vertexData));
	PostEffect::GetInstance()->resource_.Material->Map(0, nullptr, reinterpret_cast<void**>(&materialData));
	PostEffect::GetInstance()->resource_.Index->Map(0, nullptr, reinterpret_cast<void**>(&indexData));
	Vector2 pos = { 0.0f,0.0f };
	Vector2 size = TextureManager::GetTextureSize(PostEffect::GetInstance()->TesttexHandle);

	vertexData[0].position = { pos.x,pos.y + size.y,0,1 };
	vertexData[0].texcoord = {0.0f,1.0f};

	vertexData[1].position = { pos.x ,pos.y,0,1 };
	vertexData[1].texcoord = {0.0f,0.0f};

	vertexData[2].position = { pos.x + size.x,pos.y + size.y,0,1 };
	vertexData[2].texcoord = {1.0f,1.0f};

	vertexData[3].position = { pos.x + size.x,pos.y,0,1 };
	vertexData[3].texcoord = {1.0f,0.0f};

	indexData[0] = 0; indexData[1] = 1; indexData[2] = 2;
	indexData[3] = 1; indexData[4] = 3; indexData[5] = 2;

	materialData->color = {1,1,1,1};
	materialData->uvTransform = MatrixTransform::Identity();
	PostEffect::GetInstance()->viewProjection_.UpdateMatrix();
	PostEffect::GetInstance()->worldTransform_.UpdateMatrix();
}

void PostEffect::Draw()
{
	Commands commands = DirectXCommon::GetInstance()->GetCommands();

	SPSOProperty PSO = {};

	{
		PSO = GraphicsPipelineManager::GetInstance()->GetPso().Sprite2d.none;
	}

	commands.m_pList->SetGraphicsRootSignature(PSO.rootSignature.Get());
	commands.m_pList->SetPipelineState(PSO.GraphicsPipelineState.Get());

	commands.m_pList->IASetVertexBuffers(0, 1, &PostEffect::GetInstance()->resource_.BufferView);
	commands.m_pList->IASetIndexBuffer(&PostEffect::GetInstance()->resource_.IndexBufferView);

	//表示の仕方を設定
	commands.m_pList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//materialDataをgpuへ
	commands.m_pList->SetGraphicsRootConstantBufferView(0, PostEffect::GetInstance()->resource_.Material->GetGPUVirtualAddress());

	//worldTransformの行列をgpuへ
	commands.m_pList->SetGraphicsRootConstantBufferView(1, PostEffect::GetInstance()->worldTransform_.buffer_->GetGPUVirtualAddress());

	//view行列をgpu
	commands.m_pList->SetGraphicsRootConstantBufferView(2, PostEffect::GetInstance()->viewProjection_.buffer_->GetGPUVirtualAddress());

	DescriptorManager::rootParamerterCommand(3,PostEffect::GetInstance()->TesttexHandle);

	const uint32_t IndexSize = 6;

	commands.m_pList->DrawIndexedInstanced(IndexSize, 1, 0, 0, 0);
}
