#include "main.h"
SAMPFUNCS *SF = new SAMPFUNCS();


void initcrTickLocalPlayerInfo()
{

	bool isInCar = Players::isLocalPlayerInCar();
	eVehicleType vehType = eVehicleType::NONE;
	if (isInCar) vehType = Vehicles::getVehicleType(Vehicles::getVehicleCVehicle(vehicleInfoGet_(-1, 0)));

	g::pInfo->iCurrentVehicleID = Players::getLocalPlayerCarID();
	g::pInfo->isDriver = Players::isLocalPlayerDriver();
	g::pInfo->isInCar = isInCar;
	g::pInfo->isExist = Players::isLocalPlayerExist();
	g::pInfo->vehType = vehType;

	g::pInfo->nearestPlayers = Players::getNearestPlayers();
	g::pInfo->nearestVehicles = Vehicles::getNearestVehicles();
}


bool CALLBACK Present(CONST RECT* pSourceRect, CONST RECT* pDestRect, HWND hDestWindowOverride, CONST RGNDATA* pDirtyRegion)
{

	if (!SF->getGame()->isGTAMenuActive())
		if (SUCCEEDED(SF->getRender()->BeginRender()))
		{
			initcrTickLocalPlayerInfo();

			bool bImGuiNewFrameWasCalled = HacksManager::getInstance()->drawHacks();

			if (g::isWindowOpen)
			{
				if (!bImGuiNewFrameWasCalled)
				{
					ImGui_ImplDX9_NewFrame();
					ImGui_ImplWin32_NewFrame();
					ImGui::NewFrame();
				}
				{
					// ImGui::ShowDemoWindow();

					HacksManager::getInstance()->drawInterface();
					if (!g::isWindowOpen)
					{
						SF->getSAMP()->getMisc()->ToggleCursor(0, 0);
						HacksManager::getInstance()->save();
					}
					ImGui::EndFrame();
					ImGui::Render();
					ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
					goto end;
				}

			}
			if (bImGuiNewFrameWasCalled)
			{
				ImGui::EndFrame();
				ImGui::Render();
				ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
			}
		end:
			SF->getRender()->EndRender();
		}
	return true;
}

bool CALLBACK incRPCHook(stRakNetHookParams* params)
{
	return HacksManager::getInstance()->procRakNetHook(params, RakNetScriptHookType::RAKHOOK_TYPE_INCOMING_RPC);
}

bool CALLBACK outRPCHook(stRakNetHookParams* params)
{

	return HacksManager::getInstance()->procRakNetHook(params, RakNetScriptHookType::RAKHOOK_TYPE_OUTCOMING_RPC);
}

bool CALLBACK incPacketHook(stRakNetHookParams* params)
{

	return HacksManager::getInstance()->procRakNetHook(params, RakNetScriptHookType::RAKHOOK_TYPE_INCOMING_PACKET);
}

bool CALLBACK outPacketHook(stRakNetHookParams* params)
{
	if (!g::pInfo->isExist)
		return true;
	return HacksManager::getInstance()->procRakNetHook(params, RakNetScriptHookType::RAKHOOK_TYPE_OUTCOMING_PACKET);
}

void CALLBACK mainloop()
{
	static bool initialized = false;
	if (!initialized)
		if (GAME && GAME->GetSystemState() == eSystemState::GS_PLAYING_GAME && SF->getSAMP()->IsInitialized())
		{
			initialized = true;
			// imgui
			//plog::init(plog::info, "E:\\!Logs\\hacksreborn.log");
			ImGui::CreateContext();
			ImGuiIO& io = ImGui::GetIO(); (void)io;
			ImGui_ImplWin32_Init(GetActiveWindow());
			ImGui_ImplDX9_Init(SF->getRender()->getD3DDevice());
			io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Arial.TTF", 16.0F, NULL, io.Fonts->GetGlyphRangesCyrillic());
			// init path var
			g::settingsPath = "C:\\HacksReborn\\Settings\\";//
			Lippets::Computer::createDirs(g::settingsPath);

			SF->getSAMP()->registerChatCommand("hacks", [](std::string text)
			{
				SF->getSAMP()->getInput()->DisableInput();
				SF->getSAMP()->getMisc()->ToggleCursor(2, 0);
				g::isWindowOpen = !g::isWindowOpen;// true;
			});
			SF->getGame()->registerGameDestructorCallback(PluginFree);


			SF->getRender()->registerD3DCallback(eDirect3DDeviceMethods::D3DMETHOD_PRESENT, Present);
			SF->getRender()->registerD3DCallback(eDirect3DDeviceMethods::D3DMETHOD_RESET, Reset);
			SF->getGame()->registerWndProcCallback(SFGame::MEDIUM_CB_PRIORITY, WndProcHandler);
			SF->getRakNet()->registerRakNetCallback(RakNetScriptHookType::RAKHOOK_TYPE_INCOMING_PACKET, incPacketHook);
			SF->getRakNet()->registerRakNetCallback(RakNetScriptHookType::RAKHOOK_TYPE_OUTCOMING_PACKET, outPacketHook);
			SF->getRakNet()->registerRakNetCallback(RakNetScriptHookType::RAKHOOK_TYPE_INCOMING_RPC, incRPCHook);
			SF->getRakNet()->registerRakNetCallback(RakNetScriptHookType::RAKHOOK_TYPE_OUTCOMING_RPC, outRPCHook);


			g::LineOfSightFlags.bCheckBuildings = true;
			g::LineOfSightFlags.bCheckObjects = true;
			g::LineOfSightFlags.bCheckPeds = false;
			g::LineOfSightFlags.bCheckVehicles = true;
			g::LineOfSightFlags.bCheckCarTires = true;
			//*(byte*)(0x96916D) = 1;
			HacksManager::getInstance()->initHacksOnce();
			SampSnipps::setup();
		}

	if (!initialized)
		return;


	initcrTickLocalPlayerInfo();
	HacksManager::getInstance()->procEveryTickAction();
}



bool CALLBACK WndProcHandler(HWND hwd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	ImGui_ImplWin32_WndProcHandler(hwd, msg, wParam, lParam);
	return HacksManager::getInstance()->procKeys(wParam, msg);
}


VOID CALLBACK PluginFree()
{
	HacksManager::getInstance()->destroy();
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
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
