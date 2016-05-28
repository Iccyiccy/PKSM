#include <stdlib.h>
#include <stdio.h>
#include <3ds.h>
#include "http.h"
#include "PID.h"
#include "catch.h"

#define ENTRIES 7

void refresh(int currentEntry, PrintConsole topScreen) {	
	char *menuEntries[ENTRIES] = {"PID Checker", "Capture probability Calculator", "Wi-Fi distributions", "Code distributions", "Local distributions", "Our distributions", "News"};

	consoleSelect(&topScreen);
	printf("\x1b[2;0H");
	for (int i = 0; i < ENTRIES; i++) {
		if (i == currentEntry)
			printf("\x1b[32m%s\x1b[0m\n", menuEntries[i]);
		else 
			printf("%s\n", menuEntries[i]);
	}
}

void intro(PrintConsole topScreen, PrintConsole bottomScreen, int currentEntry){
	consoleSelect(&bottomScreen);
	printf("\nECI Tool is the official Homebrew of theFB community '\x1b[32mPokemon Event Catchers\nItalia\x1b[0m'.\n\nThis is meant to be a general purpose   application who could serve both event\ncollectors and classic players of the\ngame.\n\nYou can join us at:\n\x1b[32mfacebook.com/groups/PokemonEventCatchersItalia\x1b[0m");
	printf("\x1b[26;0HECI Tool");
	printf("\n\nDeveloped by Bernardo Giordano.");
	consoleSelect(&topScreen);
	printf("\x1b[2J");
	printf("\x1b[47;30m      Pokemon Event Catchers Italia Tool v1.3     \x1b[0m\n");

	refresh(currentEntry, topScreen);
	
	consoleSelect(&topScreen);
	printf("\x1b[29;15HPress Start to exit.");	
}

int main() {	
	gfxInitDefault();
	PrintConsole topScreen, bottomScreen;
	consoleInit(GFX_TOP, &topScreen);
	consoleInit(GFX_BOTTOM, &bottomScreen);
	
	int currentEntry = 0;
	
	consoleSelect(&topScreen);
	intro(topScreen, bottomScreen, currentEntry);
	
	while (aptMainLoop()) {
		gspWaitForVBlank();
		hidScanInput();

		u32 kDown = hidKeysDown();
		
		if (kDown & KEY_DUP) {
			if (currentEntry == 0) {
				currentEntry = ENTRIES - 1;
				refresh(currentEntry, topScreen);
			}
			else if (currentEntry > 0) {
				currentEntry--;
				refresh(currentEntry, topScreen);
			}
		}
		
		if (kDown & KEY_DDOWN) {
			if (currentEntry == ENTRIES - 1) {
				currentEntry = 0;
				refresh(currentEntry, topScreen);
			}
			else if (currentEntry < ENTRIES - 1) {
				currentEntry++;
				refresh(currentEntry, topScreen);
			}
		}
		
		if (kDown & KEY_A) {
			
			if (currentEntry == 0) {
				PID(topScreen, bottomScreen);
				consoleSelect(&bottomScreen);
				printf("\x1b[2J");
				consoleSelect(&topScreen);			
				intro(topScreen, bottomScreen, currentEntry);				
			}
			
			else if (currentEntry == 1) {
				catchrate(topScreen, bottomScreen);
				consoleSelect(&bottomScreen);
				printf("\x1b[2J");
				consoleSelect(&topScreen);
				intro(topScreen, bottomScreen, currentEntry);
			}
			
			else if (currentEntry == 2) {
				printDistro(topScreen, bottomScreen, "http://eventcatchersitalia.altervista.org/10/worldwide1.txt");
				consoleSelect(&bottomScreen);
				printf("\x1b[2J");
				consoleSelect(&topScreen);
				intro(topScreen, bottomScreen, currentEntry);
			}
			
			else if (currentEntry == 3) {
				printDistro(topScreen, bottomScreen, "http://eventcatchersitalia.altervista.org/10/worldwide2.txt");
				consoleSelect(&bottomScreen);
				printf("\x1b[2J");
				consoleSelect(&topScreen);
				intro(topScreen, bottomScreen, currentEntry);
			}
			
			else if (currentEntry == 4) {
				printDistro(topScreen, bottomScreen, "http://eventcatchersitalia.altervista.org/10/local.txt");
				consoleSelect(&bottomScreen);
				printf("\x1b[2J");
				consoleSelect(&topScreen);
				intro(topScreen, bottomScreen, currentEntry);
			}			
			
			else if (currentEntry == 5) {
				printDistro(topScreen, bottomScreen, "http://eventcatchersitalia.altervista.org/10/giveaway.txt");
				consoleSelect(&bottomScreen);
				printf("\x1b[2J");
				consoleSelect(&topScreen);
				intro(topScreen, bottomScreen, currentEntry);
			}
			
			else if (currentEntry == 6) {			
				printDistro(topScreen, bottomScreen, "http://eventcatchersitalia.altervista.org/10/info.txt");
				consoleSelect(&bottomScreen);
				printf("\x1b[2J");
				consoleSelect(&topScreen);
				intro(topScreen, bottomScreen, currentEntry);				
			}
		}
		
		if (kDown & KEY_START) 
			break; 
		
		gfxFlushBuffers();
		gfxSwapBuffers();
	}

	gfxExit();
	return 0;
}