#pragma once

void cleanSpaces(char* str);
// Cleans leading, trailing, and double spaces in provided string.

int cleanCommand(char* command);
// Cleans command string. Removes leading, trailing and double spaces.
// Checks if command ends with '&'. If so, removes it, and returns 1. Otherwise returns 0.