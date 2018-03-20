#pragma once
#include <Windows.h>
#include <string>
#include "Definitions.h"
#include "Functions.h"

bool Breaker;
std::string PreviousCommand;

std::string ReadChatbar() {
	rlua_getglobal(rL, "game");
	rlua_getfield(rL, -1, "Players");
	rlua_getfield(rL, -1, "LocalPlayer");
	rlua_getfield(rL, -1, "PlayerGui");
	rlua_getfield(rL, -1, "Chat");
	rlua_getfield(rL, -1, "Frame");
	rlua_getfield(rL, -1, "ChatBarParentFrame");
	rlua_getfield(rL, -1, "Frame");
	rlua_getfield(rL, -1, "BoxFrame");
	rlua_getfield(rL, -1, "Frame");
	rlua_getfield(rL, -1, "ChatBar");
	rlua_getfield(rL, -1, "Text");
	return rlua_tolstring(rL, -1, NULL);
}

bool ChatFocused() {
	rlua_getglobal(rL, "game");
	rlua_getfield(rL, -1, "Players");
	rlua_getfield(rL, -1, "LocalPlayer");
	rlua_getfield(rL, -1, "PlayerGui");
	rlua_getfield(rL, -1, "Chat");
	rlua_getfield(rL, -1, "Frame");
	rlua_getfield(rL, -1, "ChatBarParentFrame");
	rlua_getfield(rL, -1, "BackgroundTransparency");
	std::string TransparencyValue = rlua_tolstring(rL, -1, NULL);
	if (TransparencyValue == "1") {
		return false;
	}
	else {
		return true;
	}
}

void Controller(bool ie) {
	if (ie == true) {
		Breaker = true;
	}
	else {
		Breaker = false;
	}
}

void Chathook() {
	for (;;) {
		if (Breaker == false) {
			break;
		}
		if (ChatFocused() == true) {
			PreventCommandSpam(ReadChatbar());
			Sleep(1000);
		}
		else {
		}
	}
}

void PreventCommandSpam(std::string s) {
	if (s == PreviousCommand) {
	}
	else if (s != PreviousCommand && GetKeyState(VK_RETURN)) { //something like that should be fine lol, untested.
		RunCommand(s);
		PreviousCommand = s;
	}
}

void RunCommand(std::string command) {

}