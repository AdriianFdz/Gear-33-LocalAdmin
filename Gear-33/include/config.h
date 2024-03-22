/*
 * config.h
 *
 *  Created on: 22 mar 2024
 *      Author: seven
 */

#ifndef CONFIG_H_
#define CONFIG_H_

typedef struct{
	char database[100];
} CONFIG;

void leerConfig (CONFIG* configuracion);
#endif /* CONFIG_H_ */
