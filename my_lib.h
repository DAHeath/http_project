#ifndef MY_LIB_H
#define MY_LIB_H

/**
 * Prints the passed in message to stderr, followed by a newline character. 
 * Then, the program exits.
 */
void exitWithMessage(const char *message);

void assert_message(int condition, const char *message);

#endif
