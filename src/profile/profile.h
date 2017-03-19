/*
 * profile.h
 *
 *  Created on: 19 марта 2017 г.
 *      Author: walery
 */

#ifndef PROFILE_H_
#define PROFILE_H_

#include "Settings.h"



//---------- defs


struct profile_t{
	char name[128];
	char description[1024];
	char filename[128];
	struct Settings *settings;
};

// -------- vars


//// ----------- Functions

void load_profile(void);

void save_profile(void);

void new_profile(void);

void delete_profile(void);

void init_profile(void);


#endif /* PROFILE_H_ */
