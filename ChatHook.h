#pragma once
#include <Windows.h>
#include <string>
#include "Definitions.h"
#include "Functions.h"

bool Breaker;
std::string PreviousCommand;

/*
	Please give credits, thats all I ask.
	I wrote this when I was ultra shit at C++, so any noob should be able to use this...
*/

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

void Controller(bool meme) { // Control weither Chathook is on or off.
	if (meme == true) {
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
		if (ChatFocused() == true) { // Check if Chat is focused
			PreventCommandSpam(ReadChatbar());
			Sleep(1000); // Sleep for 1 second
		}
		else {
		}
	}
}

void PreventCommandSpam(std::string s) { // Prevents a command from being ran over and over again when your trying to run it once.
	if (s == PreviousCommand) {
	}
	else if (s != PreviousCommand && GetKeyState(VK_RETURN)) { // The thing where it detects if enter is pressed is by r-exterminator
		RunCommand(s);
		PreviousCommand = s;
	}
}

void RunCommand(std::string command) { 
	/* Replace this with the normal commands function that you would run through a Interface. */
}
