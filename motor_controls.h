#include "ScannerConfig.h"
#include <AccelStepper.h>

extern int total_photos;
extern int current_progress;
extern bool stop_program;

void initialize_motors();
void start_motor_program(byte program);
