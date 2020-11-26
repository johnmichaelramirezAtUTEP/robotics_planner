#ifndef LEGO_CONTROL_H_
#define LEGO_CONTROL_H_

void setUpControl(void);
void turnVehicleRight();
void turnVehicleLeft();
void goForward(double distance);
void goReverse(double distance);
void turnVehicleRightXDegrees(double degrees);
void turnVehicleLeftXDegrees(double degrees);
void goForwardNonBlocking(void);
void goReverseNonBlocking(void);
void stopVehicle(void);
int getRelativeEncoderTicksLeft(void);
int getRelativeEncoderTicksRight(void);
int setRelativeEncoderValues(void);


#endif
