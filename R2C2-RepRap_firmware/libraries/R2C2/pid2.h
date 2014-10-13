/**********************************************************************************************
 * Arduino PID Library - Version 1.0.1
 * by Brett Beauregard <br3ttb@gmail.com> brettbeauregard.com
 *
 * Addapted by: Rui Ribeiro - racribeiro@gmail.com  
 * This Library is licensed under a GPLv3 License
 **********************************************************************************************/

#ifndef _PID2_
#define _PID2_

#include "lpc17xx.h"
#include "timer.h"

#define AUTOMATIC	1
#define MANUAL  	0
#define DIRECT      0
#define REVERSE     1

#define MAX_PID_ERROR_ELEMENTS (20000 / 100)

struct PID
{
	double dispKp;				// * we'll hold on to the tuning parameters in user-entered 
	double dispKi;				//   format for display purposes
	double dispKd;				//   
	
	double kp;                  // * (P)roportional Tuning Parameter
    double ki;                  // * (I)ntegral Tuning Parameter
    double kd;                  // * (D)erivative Tuning Parameter

	int controllerDirection;

    int16_t *myInput;           // * Pointers to the Input, Output, and Setpoint variables
    double *myOutput;           //   This creates a hard link between the variables and the 
    int16_t *mySetpoint;        //   PID, freeing the user from having to constantly tell us
                                //   what these values are.  with pointers we'll just know.
			  
	unsigned long lastTime;
	int16_t ITerm, lastInput, lastError;

	unsigned long SampleTime;
	double outMin, outMax;
	bool inAuto;
	
	unsigned int error_log_size;
	int16_t error_log[MAX_PID_ERROR_ELEMENTS];
	int16_t input_log[MAX_PID_ERROR_ELEMENTS];
	unsigned int current_pos;	
} ;


  //commonly used functions **************************************************************************
    void PID_PID(struct PID *p, int16_t*, double*, int16_t*,        // * constructor.  links the PID to the Input, Output, and 
        double, double, double, int, unsigned int, unsigned int);     //   Setpoint.  Initial tuning parameters are also set here
	
    void PID_SetMode(struct PID *p,int Mode);               // * sets PID to either Manual (0) or Auto (non-0)

    bool PID_Compute(struct PID *p);                       // * performs the PID calculation.  it should be
                                          //   called every time loop() cycles. ON/OFF and
                                          //   calculation frequency can be set using SetMode
                                          //   SetSampleTime respectively

    void PID_SetOutputLimits(struct PID *p,double, double); //clamps the output to a specific range. 0-255 by default, but
										  //it's likely the user will want to change this depending on
										  //the application
	


  //available but not commonly used functions ********************************************************
    void PID_SetTunings(struct PID *p,double, double,       // * While most users will set the tunings once in the 
                    double);         	  //   constructor, this function gives the user the option
                                          //   of changing tunings during runtime for Adaptive control
	void PID_SetControllerDirection(struct PID *p,int);	  // * Sets the Direction, or "Action" of the controller. DIRECT
										  //   means the output will increase when error is positive. REVERSE
										  //   means the opposite.  it's very unlikely that this will be needed
										  //   once it is set in the constructor.
    void PID_SetSampleTime(struct PID *p,int);              // * sets the frequency, in Milliseconds, with which 
                                          //   the PID calculation is performed.  default is 100
										  
										  
										  
  //Display functions ****************************************************************
	double PID_GetKp(struct PID *p);						  // These functions query the pid for interal values.
	double PID_GetKi(struct PID *p);						  //  they were created mainly for the pid front-end,
	double PID_GetKd(struct PID *p);						  // where it's important to know what is actually 
	int PID_GetMode(struct PID *p);						  //  inside the PID.
	int PID_GetDirection(struct PID *p);					  //	
	void PID_Initialize(struct PID *p);
	
#endif

