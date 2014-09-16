#include <iostream>
#include <string>
#include <cfloat>
#include <cstdio>
#include <climits>
using namespace std;

template<typename T>
void printBitsInteger(T a) {
	int bit_count = sizeof(a) * 8;
	char bits[bit_count + 1];
	bits[bit_count] = 0; // null terminiert \0
	for (int i = 0; i < bit_count; i++) {
		if (a & (0x1 << i))
			bits[bit_count - 1 - i] = '1';
		else
			bits[bit_count - 1 - i] = '0';
	}
	cout << bits;
}

void printBitsFloat(float f) {
	int *i = (int*) &f; //Adresse von float als int (beide 4 bytes)
	printBitsInteger(*i); //Wert von float als int
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
		a = a << 8;
		a = a ^ 0xff;
	}
	if (vorzeichen) {
		cout << "Maximum:\t" << (long) a << endl;

		//minimum berechnen
		a = 0x80; //erstes bit 1, andere 0
		for (int i = 0; i < sizeof(a) - 1; i++) {
			//mit 0 füllen
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

int main() {
	int auswahl;
	do {
		cout
				<< "char: 1\tshort: 2\tint: 3\tlong: 4\tunsigned char: 5\tunsigned short: 6\tunsigned int: 7\tunsigned long: 8\nfloat: 9\tdouble: 10\tlong double: 11\n";
		cout << "Alle: 0\tEnde:-1\n\n";
		cout << "\nAuswahl: ";
		cin >> auswahl;
		bool all = false;
		switch (auswahl) {
		case 0:
			all = true;
		case 1: {
			char c = 0;
			printIntegerInfo(c, true, "char");
			if (!all)
				break;
		}
		case 2: {
			short s = 0;
			printIntegerInfo(s, true, "short");
			if (!all)
				break;
		}
		case 3: {
			int i = 0;
			printIntegerInfo(i, true, "int");
			if (!all)
				break;
		}
		case 4: {
			long l = 0;
			printIntegerInfo(l, true, "long");
			if (!all)
				break;
		}
		case 5: {
			unsigned char c = 0;
			printIntegerInfo(c, false, "char");
			if (!all)
				break;
		}
		case 6: {
			unsigned short ss = 0;
			printIntegerInfo(ss, false, "unsigned short");
			if (!all)
				break;
		}
		case 7: {
			unsigned int si = 0;
			printIntegerInfo(si, false, "unsigned int");
			if (!all)
				break;
		}
		case 8: {
			unsigned long sl = 0;
			printIntegerInfo(sl, false, "unsigned long");
			if (!all)
				break;
		}
		case 9: {
			float fmax = FLT_MAX;//ist gleich ((2^24)-1)*(2^104) keine Ahnung wieso.
			float fmin = -FLT_MAX;
			float fmin_gt0 = FLT_MIN;
			printFloatingPointInfo(fmax, fmin, fmin_gt0, "float");
			if (!all)
				break;
		}
		case 10: {
			double dmax = DBL_MAX;
			double dmin = -DBL_MAX;
			double dmin_gt0 = DBL_MIN;
			printFloatingPointInfo(dmax, dmin, dmin_gt0, "double");
			if (!all)
				break;
		}
		case 11: {
			long double ldmax = LDBL_MAX;
			long double ldmin = -LDBL_MAX;
			long double ldmin_gt0 = LDBL_MIN;
			printFloatingPointInfo(ldmax, ldmin, ldmin_gt0, "long double");
			if (!all)
				break;
		}
		default:
			auswahl = -1; //Abbruch
			break;
		}
	} while (auswahl >= 0);
	return 0;
}
