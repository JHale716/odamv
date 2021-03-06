#pragma once

#include "Arduino.h"
#include "config.h"
#include "reference.h"
#include "stepper.h"
#include "pressure.h"
#include <PID_v1.h>

double setpoint=0, input=0, output=0;
double kp=K_P,ki=K_I,kd=K_D;
PID pid(&input, &output, &setpoint, K_P, K_I, K_D, P_ON_M, DIRECT);

void pidSetup(){
  pid.SetMode(AUTOMATIC);
  pid.SetSampleTime(SAMPLE_TIME);
  pid.SetOutputLimits(-1000,1000);
  stepperUpdateSpeed(0);
}

double reference = 0;
void pidRun(){
  reference = getReference();
  input = getPressure()-reference;

  if(pid.Compute())
    stepperUpdateSpeed(output);
}
