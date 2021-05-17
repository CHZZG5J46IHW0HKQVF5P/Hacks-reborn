#include "main.h"
SAMPFUNCS *SF = new SAMPFUNCS();



void initcrTickLocalPlayerInfo()
{
	bool isInCar = Players::isLocalPlayerInCar();
	eVehicleType vehType = eVehicleType::NONE;
	if (isInCar) vehType = Vehicles::getVehicleType(Vehicles::getVehicleCVehicle(Vehicles::getVehicleInfo(VEHICLE_SELF)));

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
					ImGui::ShowDemoWindow();

					ImGui::SetNextWindowPos(ImVec2(iScrResX / 2, iScrResY / 2), ImGuiCond_Once, ImVec2(0.5F, 0.5F));
					ImGui::SetNextWindowSize(ImVec2(550.f, 450.f), ImGuiCond_::ImGuiCond_FirstUseEver);
					ImGui::Begin("hakcs", &g::isWindowOpen);
					{
						g::keyButtonSplitter = 0;
						static uint8 currentGuiMenu = 0;
						if (ImGui::Button("Hacks"))
							currentGuiMenu = 0;
						ImGui::SameLine();
						if (ImGui::Button("Settings"))
							currentGuiMenu = 1;

						ImGui::Separator();

						if (currentGuiMenu == 0)
							HacksManager::getInstance()->drawGui();
						else
							HacksManager::getInstance()->drawSettings();
					}
					ImGui::End();
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
	return HacksManager::getInstance()->procRakNetHook(params, RakNetScriptHookType::RAKHOOK_TYPE_OUTCOMING_PACKET);
}

void CALLBACK mainloop()
{
	static bool initialized = false;
	if (!initialized)
		if (GAME && GAME->GetSystemState() == eSystemState::GS_PLAYING_GAME && SF->getSAMP()->IsInitialized())
		{
			plog::init(plog::Severity::info, "E:\\!Logs\\hacksreborn.log", 100000, 1);
			initialized = true;
			// imgui
			HacksManager hackManager();
			ImGui::CreateContext();
			ImGuiIO& io = ImGui::GetIO(); (void)io;
			ImGui_ImplWin32_Init(GetActiveWindow());
			ImGui_ImplDX9_Init(SF->getRender()->getD3DDevice());
			io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Arial.TTF", 16.0F, NULL, io.Fonts->GetGlyphRangesCyrillic());
			// init path var
			g::settingsPath = "C:\\HacksReborn\\Settings\\";//
			//std::experimental::filesystem::current_path().string() + "\\SAMPFUNCS\\Hacks\\";
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


			hacksSettings::LineOfSightFlags.bCheckBuildings = true;
			hacksSettings::LineOfSightFlags.bCheckObjects = true;
			hacksSettings::LineOfSightFlags.bCheckPeds = false;
			hacksSettings::LineOfSightFlags.bCheckVehicles = true;
			hacksSettings::LineOfSightFlags.bCheckCarTires = true;
			//*(byte*)(0x96916D) = 1;

			HacksManager::getInstance()->initHacksOnce();
		}

	if (!initialized)
		return;
	if (g::isWindowOpen)
	{

		SF->getSAMP()->getMisc()->ToggleCursor(2, 0);

		if (SF->getSAMP()->getInput()->iInputEnabled)
		{
			SF->getSAMP()->getInput()->DisableInput();
		}
	}

	initcrTickLocalPlayerInfo();
	HacksManager::getInstance()->procEveryTickAction();
}



bool CALLBACK WndProcHandler(HWND hwd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	auto keyState = Stuff::getKeyStateByMsg(msg);
	switch (wParam)
	{
	case 16:
		g::isShiftPressed = (keyState == eKeyState::PRESSED ? true : false);
		break;
	case 17:
		g::isCtrlPressed = (keyState == eKeyState::PRESSED ? true : false);
		break;
	case 18:
		g::isAltPressed = (keyState == eKeyState::PRESSED ? true : false);
		break;
	}

	//initcrTickLocalPlayerInfo();
	if (HacksManager::getInstance()->procKeys(wParam, msg) || g::isWindowOpen)
		ImGui_ImplWin32_WndProcHandler(hwd, msg, wParam, lParam);
	return true;
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
