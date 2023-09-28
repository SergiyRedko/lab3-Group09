#pragma once

int qualifyPath(char** pathRef);
// Fully qualifies provided path and checks if there is an executable there.
// Returns 1 if successful, 0 otherwise.


int containsSlash(const char* string);
// Checks if given string contains a "/".
// Returns 1 if it does, 0 otherwise.