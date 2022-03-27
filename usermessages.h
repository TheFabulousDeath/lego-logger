#ifndef _USERMESSAGES_H_
#define _USERMESSAGES_H_
#include <stdio.h>

void printWelcomeMessage(){
	printf("Legologger Alpha v3.1 - Gib \"HELP\" ein um eine Ansicht aller Befehle zu erhalten.\n");
}

void printMainHelp()
{
	printf("Alle g\x81ltigen Befehlte lauten:\n    ADD - F\x81gt ein Bauteil hinzu. Beispiel: ADD 412314 41\n        LF - Sucht nach einem Bauteil und gibt den Eintrag zur%cck. Beispiel LF 412314\n    LIST - Listet alle Eintr\x84ge auf.\n    CSV     - Erzeugt eine CSV Datei aus den Eintr\x84gen.\n    REMOVE - Reduziert den Betrag eines Bauteils. Beispiel: remove 412321 5\n    CA    NCEL - Macht die letzte Bauteil\x84nderung ungeschehen.\n    EXIT - F\x81hrt zur sofortigen Beendigung der Anwendung.\n    HELP - R    uft diese Ansicht auf.\n", '\x81');
}

#endif
