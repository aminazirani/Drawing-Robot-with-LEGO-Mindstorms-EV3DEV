/*
 *  \file  sensors.c
 *  \brief  data gathering and communication with the robot's sensors.
 *  \author  Amin, Basti, Semir and Daniel 
 *  \copyright  See the LICENSE file.
 */

#include <stdio.h>
#include <string.h>
#include "ev3.h"
#include "ev3_port.h"
#include "ev3_sensor.h"

// WIN32 /////////////////////////////////////////
#ifdef __WIN32__

#include <windows.h>

// UNIX //////////////////////////////////////////
#else

#include <unistd.h>
#define Sleep( msec ) usleep(( msec ) * 1000 )

//////////////////////////////////////////////////
#endif

//Get the value of the gyroscope. The sensor needs to be initialized before using this function.
int getGyroVal(void){
	int gyroval;
	int val;
	uint8_t sn_gyro;
	//Check if the sensor is connected or not
	if ( ev3_search_sensor( LEGO_EV3_GYRO, &sn_gyro, 0 )) {
		set_sensor_mode( sn_gyro, "LEGO_EV3_GYRO_GYRO_ANG" );
		//save the sensor value to the variable gyroval
		if ( !get_sensor_value( 0, sn_gyro, &gyroval )) {
			gyroval = 0;
		}
		//the gyroscope delivers negative values for rotation to the left. Counter this by multiplying it with -1
		gyroval = gyroval * (-1);
		//calculate the current degree based on 360 degrees maximum.
		while(gyroval < 0){
			gyroval = gyroval + 360;
		}
		while(gyroval >= 360){
			gyroval = gyroval - 360;
		}
		//return the calculated gyroscope degree
		return gyroval;
	}
	return 0;
}