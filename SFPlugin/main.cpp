#include <Windows.h>
#include "main.h"
#include <cmath>
bool CALLBACK WndProcHandler(HWND, UINT, WPARAM, LPARAM);
HRESULT CALLBACK Reset(D3DPRESENT_PARAMETERS*);
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND, UINT, WPARAM, LPARAM);
VOID CALLBACK PluginFree();
SAMPFUNCS *SF = new SAMPFUNCS();



bool CALLBACK Present(CONST RECT* pSourceRect, CONST RECT* pDestRect, HWND hDestWindowOverride, CONST RGNDATA* pDirtyRegion)
{
	if (!SF->getGame()->isGTAMenuActive())
		if (SUCCEEDED(SF->getRender()->BeginRender()))
		{
			bool isExist = Players::isLocalPlayerExist();
			bool isInCar = Players::isLocalPlayerInCar();
			bool isDriver = Players::isLocalPlayerDriver();
			eVehicleType vehType = eVehicleType::NONE;
			if (isInCar) vehType = Vehicles::getVehicleType(Vehicles::getVehicleCVehicle(Vehicles::getVehicleInfo(VEHICLE_SELF)));
			g::hacksManager.drawHacks(crTickLocalPlayerInfo(isExist, isInCar, isDriver, vehType));
			if (g::isWindowOpen)
			{

				ImGui_ImplDX9_NewFrame();
				ImGui_ImplWin32_NewFrame();
				ImGui::NewFrame();
				{
					
					ImGui::SetNextWindowPos(ImVec2(iScrResX / 2, iScrResY / 2), ImGuiCond_Once, ImVec2(0.5F, 0.5F));
					ImGui::SetNextWindowSize(ImVec2(550.f, 450.f), ImGuiCond_::ImGuiCond_FirstUseEver);
					ImGui::Begin("hakcs", &g::isWindowOpen);
					{
						static uint currentGuiMenu = 0;
						if (ImGui::Button("Hacks"))
							currentGuiMenu = 0;
						ImGui::SameLine();
						if (ImGui::Button("Settings"))
							currentGuiMenu = 1;

						if (currentGuiMenu == 0)
							g::hacksManager.drawGui();
						else
							g::hacksManager.drawSettings();

					}
					ImGui::End();
				}
				ImGui::EndFrame();
				ImGui::Render();
				ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
				if (!g::isWindowOpen)
				{
					SF->getSAMP()->getMisc()->ToggleCursor(0, 0);
					g::hacksManager.save();
				}
			}
			SF->getRender()->EndRender();
		}
	return true;
}

bool CALLBACK incRPCHook(stRakNetHookParams* params)
{
	bool isExist = Players::isLocalPlayerExist();
	bool isInCar = Players::isLocalPlayerInCar();
	bool isDriver = Players::isLocalPlayerDriver();
	eVehicleType vehType = eVehicleType::NONE;
	if (isInCar) vehType = Vehicles::getVehicleType(Vehicles::getVehicleCVehicle(Vehicles::getVehicleInfo(VEHICLE_SELF)));
	return g::hacksManager.procIncPRC(params, crTickLocalPlayerInfo(isExist, isInCar, isDriver, vehType));
}

bool CALLBACK outRPCHook(stRakNetHookParams* params)
{
	bool isExist = Players::isLocalPlayerExist();
	bool isInCar = Players::isLocalPlayerInCar();
	bool isDriver = Players::isLocalPlayerDriver();
	eVehicleType vehType = eVehicleType::NONE;
	if (isInCar) vehType = Vehicles::getVehicleType(Vehicles::getVehicleCVehicle(Vehicles::getVehicleInfo(VEHICLE_SELF)));
	return g::hacksManager.procOutPRC(params, crTickLocalPlayerInfo(isExist, isInCar, isDriver, vehType));
}

bool CALLBACK incPacketHook(stRakNetHookParams* params)
{
	bool isExist = Players::isLocalPlayerExist();
	bool isInCar = Players::isLocalPlayerInCar();
	bool isDriver = Players::isLocalPlayerDriver();
	eVehicleType vehType = eVehicleType::NONE;
	if (isInCar) vehType = Vehicles::getVehicleType(Vehicles::getVehicleCVehicle(Vehicles::getVehicleInfo(VEHICLE_SELF)));
	return g::hacksManager.procIncPacket(params, crTickLocalPlayerInfo(isExist, isInCar, isDriver, vehType));
}

bool CALLBACK outPacketHook(stRakNetHookParams* params)
{
	bool isExist = Players::isLocalPlayerExist();
	bool isInCar = Players::isLocalPlayerInCar();
	bool isDriver = Players::isLocalPlayerDriver();
	eVehicleType vehType = eVehicleType::NONE;
	if (isInCar) vehType = Vehicles::getVehicleType(Vehicles::getVehicleCVehicle(Vehicles::getVehicleInfo(VEHICLE_SELF)));
	return g::hacksManager.procOutPacket(params, crTickLocalPlayerInfo(isExist, isInCar, isDriver, vehType));
}

void __stdcall mainloop()
{
	static bool initialized = false;
	if (!initialized)
	{
		if (GAME && GAME->GetSystemState() == eSystemState::GS_PLAYING_GAME && SF->getSAMP()->IsInitialized())
		{
			initialized = true;
			freopen("out.txt", "w", stdout);
			// imgui
			ImGui::CreateContext();
			ImGuiIO& io = ImGui::GetIO(); (void)io;
			ImGui_ImplWin32_Init(GetActiveWindow());
			ImGui_ImplDX9_Init(SF->getRender()->getD3DDevice());
			io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Arial.TTF", 16.0F, NULL, io.Fonts->GetGlyphRangesCyrillic());
			// init path var
			g::settingsPath = std::experimental::filesystem::current_path().string() + "\\SAMPFUNCS\\Hacks\\";
			Lippets::Computer::createDirs(g::settingsPath);
			SF->getGame()->registerGameDestructorCallback(PluginFree);
			SF->getRender()->registerD3DCallback(eDirect3DDeviceMethods::D3DMETHOD_PRESENT, Present);
			SF->getRender()->registerD3DCallback(eDirect3DDeviceMethods::D3DMETHOD_RESET, Reset);
			SF->getGame()->registerWndProcCallback(SFGame::MEDIUM_CB_PRIORITY, WndProcHandler);
			SF->getSAMP()->registerChatCommand("hacks", [](std::string text)
			{
				SF->getSAMP()->getInput()->DisableInput();
				SF->getSAMP()->getMisc()->ToggleCursor(2, 0);
				g::isWindowOpen ^= true;
			});

			SF->getRakNet()->registerRakNetCallback(RakNetScriptHookType::RAKHOOK_TYPE_INCOMING_PACKET, incPacketHook);
			SF->getRakNet()->registerRakNetCallback(RakNetScriptHookType::RAKHOOK_TYPE_OUTCOMING_PACKET, outPacketHook);
			SF->getRakNet()->registerRakNetCallback(RakNetScriptHookType::RAKHOOK_TYPE_INCOMING_RPC, incRPCHook);
			SF->getRakNet()->registerRakNetCallback(RakNetScriptHookType::RAKHOOK_TYPE_OUTCOMING_RPC, outRPCHook);

		}
	}
	if (initialized)
	{

		bool isExist = Players::isLocalPlayerExist();
		bool isInCar = Players::isLocalPlayerInCar();
		bool isDriver = Players::isLocalPlayerDriver();
		eVehicleType vehType = eVehicleType::NONE;
		if (isInCar) vehType = Vehicles::getVehicleType(Vehicles::getVehicleCVehicle(Vehicles::getVehicleInfo(VEHICLE_SELF)));
		g::hacksManager.procEveryTickAction(crTickLocalPlayerInfo(isExist, isInCar, isDriver, vehType));
		if (isExist)
			g::hacksManager.initHacksOnce();
	}

}

bool CALLBACK WndProcHandler(HWND hwd, UINT msg, WPARAM wParam, LPARAM lParam)
{

	bool isExist = Players::isLocalPlayerExist();
	bool isInCar = Players::isLocalPlayerInCar();
	bool isDriver = Players::isLocalPlayerDriver();
	eVehicleType vehType = eVehicleType::NONE;
	if (isInCar) vehType = Vehicles::getVehicleType(Vehicles::getVehicleCVehicle(Vehicles::getVehicleInfo(VEHICLE_SELF)));
	g::hacksManager.procKeys(wParam, msg, crTickLocalPlayerInfo(isExist, isInCar, isDriver, vehType));


	if ((wParam > 0 && wParam < 255))
	{
		switch (msg)
		{
		case WM_KEYDOWN:
		case WM_SYSKEYDOWN:
		{
			g::PressedKeys[wParam] = true;
			g::lastPressedKey = wParam;
			break;
		}
		case WM_KEYUP:
		case WM_SYSKEYUP:
		{
			g::PressedKeys[wParam] = false;
			break;
		}
		default:
			break;
		}
	}

	if (g::isWindowOpen)
		ImGui_ImplWin32_WndProcHandler(hwd, msg, wParam, lParam);
	return true;
}


VOID CALLBACK PluginFree()
{

	g::hacksManager.destroy();
}

HRESULT CALLBACK Reset(D3DPRESENT_PARAMETERS* pPresentationParameters)
{
	ImGui_ImplDX9_InvalidateDeviceObjects();
	return true;
}


BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReasonForCall, LPVOID lpReserved)
{
	if (dwReasonForCall == DLL_PROCESS_ATTACH)
		SF->initPlugin(mainloop, hModule);
	if (dwReasonForCall == DLL_PROCESS_DETACH)
		PluginFree();
	return TRUE;
}
