#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

float clamp(float value, float min, float max);

float roundToOnePoint(float value);

int inputInt(int min, int max, const char* promptMessage, const char* errorMessage);
int inputInt(int max, const char* promptMessage, const char* errorMessage);

#endif