#pragma once
#include "RDR/Enums.hpp"
#include "Natives.hpp"
#include "Menu.hpp"
#include "Helpers.hpp"
#include "Scriptglobal.hpp"
#include "NativeMemory.hpp"

void MainSubmenu();
void PlayerOptionsSubmenu();
void SkinChangerSubmenu();
void MountOptionsSubmenu();
void WeaponOptionsSubmenu();
void TeleportEntity(Actor actor, Vector3 coords);
void TeleportOptionsSubmenu();
void SelectedPlayerSubmenu();
void NetworkPlayersSubmenu();
void NetworkOptionsSubmenu();
void DebugOptionsSubmenu();