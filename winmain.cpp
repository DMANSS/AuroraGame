#include <memory>
//#include <Windows.h>
#include "DXApp.h"
#include "directxtk\Inc\SpriteBatch.h"
#include "directxtk\Inc\SpriteFont.h"
#include "directxtk\Inc\DDSTextureLoader.h"
#include "directxtk\Inc\SimpleMath.h"
#include "Sprite.h"

class TestApp : public DXApp
{
public:
	TestApp(HINSTANCE hInstance);
	~TestApp();

	bool Init() override;
	void Update(float dt) override;
	void Render(float dt) override;

private:
	std::unique_ptr<DirectX::SpriteBatch> spriteBatch;
	std::unique_ptr<DirectX::SpriteFont> spriteFont;
	//ID3D11ShaderResourceView* m_pTexture;
	Sprite* sprite;
};

TestApp::TestApp(HINSTANCE hInstance) : DXApp(hInstance)
{
	m_AppTitle = "AURORA. I'm Still Here";
}

TestApp::~TestApp()
{
	Memory::SafeDelete(sprite);
}

bool TestApp::Init()
{
	if (!DXApp::Init()) return false;

	//create spritebatch objects
	spriteBatch.reset(new DirectX::SpriteBatch(m_pImmediateContext));

	//create spritefont object
	spriteFont.reset(new DirectX::SpriteFont(m_pDevice, L"Arial.spritefont"));

	//import texture for rendering
		//HR(DirectX::CreateDDSTextureFromFile(m_pDevice, L"img1.dds", nullptr, &m_pTexture));

	sprite = new Sprite(DirectX::SimpleMath::Vector2(100, 100));
	sprite->Load(m_pDevice, L"img1.dds");

	return true;
}

void TestApp::Update(float dt)
{
	if (GetAsyncKeyState('D'))
		sprite->SetPosition(DirectX::SimpleMath::Vector2(300, 300));
}

void TestApp::Render(float dt)
{
	m_pImmediateContext->ClearRenderTargetView(m_pRenderTargetView, DirectX::Colors::CornflowerBlue);
	spriteBatch->Begin();

	//Draw sprite
	sprite->Draw(spriteBatch.get());

	//Draw sprites, fonts, etc
		//spriteBatch->Draw(m_pTexture, DirectX::SimpleMath::Vector2(100, 100));
	//draw fonts
	spriteFont->DrawString(spriteBatch.get(), L"Hello world", DirectX::SimpleMath::Vector2(300, 300));
	
	spriteBatch->End();
	HR(m_pSwapChain->Present(0, 0));
}

int WINAPI WinMain(__in HINSTANCE hInstance, __in_opt HINSTANCE hPrevInstance, __in LPSTR lpCmdLine, __in int nShowCmd)
{
	TestApp tApp(hInstance);

	if (!tApp.Init()) return 1;

	return tApp.Run();
}