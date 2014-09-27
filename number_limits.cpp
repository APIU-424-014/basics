#include <iostream>
#include <string>
#include <cfloat>
#include <cstdio>
#include <limits>
#include "number_limits.h"
#include "choice.h"

using namespace std;

//to use choice
using namespace input;

namespace number_limits {

template<typename T>
void printBitsInteger(T a, bool steps) {
	int bit_count = sizeof(a) * 8;
	char bits[bit_count + 1];
	bits[bit_count] = 0; // null terminiert \0
	for (int i = 0; i < bit_count; i++) {
		T theBit = 0x1 << i; //setzt das zu testende bit
		T res = a & theBit; // Vergleich mit dem zu testenden Bit
		bool cmp = res; //integer zu bool
		if (steps) {
			cout << "  ";
			printBitsInteger<T>(a, false); //ausgeben der "Eingabe"
			cout << endl << " &";
			printBitsInteger<T>(theBit, false); //ausgeben des zu testenden Bits
			cout << endl << " =";
			printBitsInteger<T>(res, false); //ausgeben des Resultats
			cout << " = " << ((cmp) ? "true " : "false") << " = "
					<< ((cmp) ? 1 : 0) << endl << endl;
		}
		if (cmp)
			bits[bit_count - 1 - i] = '1';
		else
			bits[bit_count - 1 - i] = '0';
	}
	if (steps)
		cout << "  "; //einrücken
	cout << bits;
}

void printBitsChar(char a, bool steps) { //dummy Funktion für char, ansonsten kein Aufruf von aussen möglich
	printBitsInteger<char>(a, steps);
}
void printBitsFloat(float f) {
	//interpetiert den von float f belegten Speicherbereich als Integer Wert
	int *i = (int*) &f; //Adresse von float als int (beide 4 bytes)
	printBitsInteger(*i, false); //Wert von float als int
}

template<typename T>
void printIntegerInfo(T a, bool vorzeichen, string name) {
	cout << name << "(bytes: " << sizeof(a) << ")\n";

	//erstes Byte
	if (vorzeichen)
		a = 0x7f; //erstes Bit 0, andere 1 (erstes Bit definiert Vorzeichen)
	else
		a = 0xff; //alle Bits 1

	//restliche Bytes
	for (int i = 0; i < sizeof(a) - 1; i++) {
		//mit 1 füllen
		a = a << 8; //verschiebt alle Bits um 8 Positionen nach oben (höchste 8 bits verschwinden, tiefste 8 bits werden 0)
		a = a ^ 0xff;  //setzt die tiefsten 8 Bit auf 1 (1 xor 0 = 1)
	}
	if (vorzeichen) {
		cout << "Maximum:\t" << (long) a << endl;

		//minimum berechnen
		a = 0x80; //erstes bit 1, andere 0
		for (int i = 0; i < sizeof(a) - 1; i++) {
			//verschiebt das gesetzte Bit nach ganz oben
			a = a << 8;
		}
		cout << "Minimum:\t" << (long) a << endl;
	} else {
		cout << "Maximum:\t" << (unsigned long) a << endl;
		cout << "Minimum:\t0\n";
	}
	cout << "\n";
}

template<typename T>
void printFloatingPointInfo(T max, T min, T min_gt0, string name) {
	cout << name << " (bytes: " << sizeof(max) << ")\n";
	cout << "Maximum:\t" << max << endl;
	cout << "Minimum>0:\t" << min_gt0 << endl;
	cout << "Minimum:\t" << min << endl;
	cout << endl;
}

int run() {
	choice ch = choice();
	item signedItems[] = { item(new string("char"), CHAR), item(
			new string("short"), SHORT), item(new string("int"), INT), item(
			new string("long"), LONG) };
	int signedItemsLength = 4;
	item unsignedItems[] = { item(new string("unsigned char"), UCHAR), item(
			new string("unsigned short"), USHORT), item(
			new string("unsigned int"), UINT), item(new string("unsigned long"),
			ULONG) };
	int unsignedItemsLength = 4;
	item floatItems[] = { item(new string("float"), FLOAT), item(
			new string("double"), DOUBLE), item(new string("long double"),
			LDOUBLE) };
	int floatItemsLength = 3;
	item otherItems[] = { item(new string("Alle"), ALL), item(
			new string("Ende"), ABORT) };
	int otherItemsLength = 2;
	ch.extend(&signedItems[0], signedItemsLength);
	ch.extend(&unsignedItems[0], unsignedItemsLength);
	ch.extend(&floatItems[0], floatItemsLength);
	ch.extend(&otherItems[0], otherItemsLength);
	int auswahl;
	item *choosen;
	do {
		auswahl = ch.getChoice();
		choosen = ch.getItemByValue(auswahl);
		if (choosen) {
			cout << "== " << *choosen->name << " ==" << endl;
		} else {
			cout << "Auswahl nicht verfügbar. Bitte erneut versuchen." << endl;
		}
	} while (printLimit((number_limits::number_type) auswahl) || !choosen); //!choosen is to redo if it's a null pointer
	cout << "\nBeendet\n";
	return 0;
}

bool printLimit(number_type auswahl) {
	bool all = false;
	switch (auswahl) {
	case -1:
		return false;
	case 0:
		all = true;
	case CHAR: {
		char c = 0;
		printIntegerInfo(c, true, "char");
		if (!all)
			break;
	}
	case SHORT: {
		short s = 0;
		printIntegerInfo(s, true, "short");
		if (!all)
			break;
	}
	case INT: {
		int i = 0;
		printIntegerInfo(i, true, "int");
		if (!all)
			break;
	}
	case LONG: {
		long l = 0;
		printIntegerInfo(l, true, "long");
		if (!all)
			break;
	}
	case UCHAR: {
		unsigned char c = 0;
		printIntegerInfo(c, false, "char");
		if (!all)
			break;
	}
	case USHORT: {
		unsigned short ss = 0;
		printIntegerInfo(ss, false, "unsigned short");
		if (!all)
			break;
	}
	case UINT: {
		unsigned int si = 0;
		printIntegerInfo(si, false, "unsigned int");
		if (!all)
			break;
	}
	case ULONG: {
		unsigned long sl = 0;
		printIntegerInfo(sl, false, "unsigned long");
		if (!all)
			break;
	}
	case FLOAT: {
		float fmax = FLT_MAX; //ist gleich ((2^24)-1)*(2^104) keine Ahnung wieso.
		float fmin = -FLT_MAX;
		float fmin_gt0 = FLT_MIN;
		printFloatingPointInfo(fmax, fmin, fmin_gt0, "float");
		if (!all)
			break;
	}
	case DOUBLE: {
		double dmax = DBL_MAX;
		double dmin = -DBL_MAX;
		double dmin_gt0 = DBL_MIN;
		printFloatingPointInfo(dmax, dmin, dmin_gt0, "double");
		if (!all)
			break;
	}
	case LDOUBLE: {
		long double ldmax = LDBL_MAX;
		long double ldmin = -LDBL_MAX;
		long double ldmin_gt0 = LDBL_MIN;
		printFloatingPointInfo(ldmax, ldmin, ldmin_gt0, "long double");
		break;
	}
	default:
		return false; //Abbruch
		break;
	}
	return true;
}
}

