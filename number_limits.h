
#ifndef NUMBER_LIMITS_H_
#define NUMBER_LIMITS_H_

namespace number_limits {

enum number_type {
	ABORT = -1,
	ALL,
	CHAR,
	SHORT,
	INT,
	LONG,
	UCHAR,
	USHORT,
	UINT,
	ULONG,
	FLOAT,
	DOUBLE,
	LDOUBLE
};
int run();

bool printLimit(number_type auswahl);

}

#endif /* NUMBER_LIMITS_H_ */
