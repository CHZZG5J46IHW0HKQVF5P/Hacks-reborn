#include "main.h"
#include <variant>
SAMPFUNCS *SF = new SAMPFUNCS();



crTickLocalPlayerInfo* getCurrentTickLocalPlayerInfo()
{
	bool isInCar = Players::isLocalPlayerInCar();
	eVehicleType vehType = eVehicleType::NONE;
	if (isInCar) vehType = Vehicles::getVehicleType(Vehicles::getVehicleCVehicle(Vehicles::getVehicleInfo(VEHICLE_SELF)));
	static crTickLocalPlayerInfo info;
	info.iCurrentVehicleID = Players::getLocalPlayerCarID();
	info.isDriver = Players::isLocalPlayerDriver();
	info.isInCar = isInCar;
	info.isExist = Players::isLocalPlayerExist();
	info.vehType = vehType;
	info.nearestPlayers = Players::getNearestPlayers();
	info.nearestVehicles = Vehicles::getNearestVehicles();
	return &info;
}


bool CALLBACK Present(CONST RECT* pSourceRect, CONST RECT* pDestRect, HWND hDestWindowOverride, CONST RGNDATA* pDirtyRegion)
{

	if (!SF->getGame()->isGTAMenuActive())
		if (SUCCEEDED(SF->getRender()->BeginRender()))
		{
			bool bImGuiNewFrameWasCalled = g::hacksManager.drawHacks(getCurrentTickLocalPlayerInfo());

			if (g::isWindowOpen)
			{
				if (!bImGuiNewFrameWasCalled)
				{
					ImGui_ImplDX9_NewFrame();
					ImGui_ImplWin32_NewFrame();
					ImGui::NewFrame();
				}
				{
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
							g::hacksManager.drawGui();
						else
							g::hacksManager.drawSettings();
					}
					ImGui::End();
					if (!g::isWindowOpen)
					{
						SF->getSAMP()->getMisc()->ToggleCursor(0, 0);
						g::hacksManager.save();
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
	return g::hacksManager.procRakNetHook(params, getCurrentTickLocalPlayerInfo(), RakNetScriptHookType::RAKHOOK_TYPE_INCOMING_RPC);
}

bool CALLBACK outRPCHook(stRakNetHookParams* params)
{
	return g::hacksManager.procRakNetHook(params, getCurrentTickLocalPlayerInfo(), RakNetScriptHookType::RAKHOOK_TYPE_OUTCOMING_RPC);
}

bool CALLBACK incPacketHook(stRakNetHookParams* params)
{
	return g::hacksManager.procRakNetHook(params, getCurrentTickLocalPlayerInfo(), RakNetScriptHookType::RAKHOOK_TYPE_INCOMING_PACKET);
}

bool CALLBACK outPacketHook(stRakNetHookParams* params)
{
	return g::hacksManager.procRakNetHook(params, getCurrentTickLocalPlayerInfo(), RakNetScriptHookType::RAKHOOK_TYPE_OUTCOMING_PACKET);
}

void CALLBACK mainloop()
{
	static bool initialized = false;
	if (!initialized)
	{
		if (GAME && GAME->GetSystemState() == eSystemState::GS_PLAYING_GAME && SF->getSAMP()->IsInitialized())
		{

			initialized = true;
			g::loggerPtr = new CMLogger("E:\\!Logs\\hacksreborn.txt", 200000);
			// imgui

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

			g::hacksManager.initHacksOnce();
		}
	}
	if (!initialized)
		return;

	static CMTimer logLimCheckTimer;
	if (logLimCheckTimer.isEnded())
	{
		g::loggerPtr->clearLogFileIFlimitReached();
		logLimCheckTimer.setTimer(60000);
	}

	if (g::isWindowOpen)
	{

		SF->getSAMP()->getMisc()->ToggleCursor(2, 0);

		if (SF->getSAMP()->getInput()->iInputEnabled)
		{
			SF->getSAMP()->getInput()->DisableInput();
		}
	}

	g::hacksManager.procEveryTickAction(getCurrentTickLocalPlayerInfo());
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

	if (g::hacksManager.procKeys(wParam, msg, getCurrentTickLocalPlayerInfo()) || g::isWindowOpen)
		ImGui_ImplWin32_WndProcHandler(hwd, msg, wParam, lParam);
	return true;
}


VOID CALLBACK PluginFree()
{
	delete g::loggerPtr;
	g::hacksManager.destroy();
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
