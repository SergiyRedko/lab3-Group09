#include "parser.h"

//Command to trim whitespace and ASCII control characters from buffer
//[Input] char* inputbuffer - input string to trim
//[Input] size_t bufferlen - size of input and output string buffers
//[Output] char* outputbuffer - output string after trimming 
//[Return] size_t - size of output string after trimming
size_t trimstring(char* outputbuffer, const char* inputbuffer, size_t bufferlen)
{   
    memcpy(outputbuffer, inputbuffer, bufferlen*sizeof(char));

    for(size_t ii = strlen(outputbuffer)-1; ii >=0; ii--){
        if(outputbuffer[ii] < '!') //In ASCII '!' is the first printable (non-control) character
        {
            outputbuffer[ii] = 0;
        }else{
            break;
        }    
    }

    return strlen(outputbuffer);
}


int get_args(char* parsedInput, char** arg_array){

    int length = strlen(parsedInput);
    char* token = NULL;
    int startOfToken = 0;
    int num_args = 0;

    //for(int i = 0;i < length;i++){  // Skips path
    //    if(parsedInput[i] == ' '){
    //        startOfToken = i+1;
    //        break;
    //    }
    //
    //}


    for(int i = 0; i <= length;i++){

        if(parsedInput[i] == ' ' || parsedInput[i] == '\0'){
        
        int tokenLength = i - startOfToken;

        token = (char*)malloc(tokenLength + 1);


        if(token == NULL){
            printf("Memory could not allocated for argument tokens");
            exit(1);
        }

        strncpy(token,parsedInput + startOfToken,tokenLength);
        token[tokenLength] = '\0';
        arg_array[num_args] = token;
        num_args++;

        startOfToken = i + 1;
        }


    }
        return num_args;

}

int get_num_args(char* parsedInput){}


//Command to trim the input command to just be the first word
//[Input] char* inputbuffer - input string to trim
//[Input] size_t bufferlen - size of input and output string buffers
//[Output] char* outputbuffer - output string after trimming 
//[Return] size_t - size of output string after trimming
size_t firstword(char* outputbuffer, const char* inputbuffer, size_t bufferlen)
{
    //TO DO: Implement this function
    return 0;
}

//Command to test that string only contains valid ascii characters (non-control and not extended)
//[Input] char* inputbuffer - input string to test
//[Input] size_t bufferlen - size of input buffer
//[Return] bool - true if no invalid ASCII characters present
bool isvalidascii(const char* inputbuffer, size_t bufferlen)
{
    //TO DO: Correct this function so that the second test string fails
    size_t testlen = bufferlen;
    size_t stringlength = strlen(inputbuffer);
    if(strlen(inputbuffer) < bufferlen){
        testlen = stringlength;
    }

    bool isValid = true;
    for(size_t ii = 0; ii < testlen; ii++)
    {
        isValid &= ((unsigned char) inputbuffer[ii] <= '~'); //In (lower) ASCII '~' is the last printable character
    }

    return isValid;
}

//Command to find location of pipe character in input string
//[Input] char* inputbuffer - input string to test
//[Input] size_t bufferlen - size of input buffer
//[Return] int - location in the string of the pipe character, or -1 pipe character not found
int findpipe(const char* inputbuffer, size_t bufferlen){
    //TO DO: Implement this function

    return -1;
}

//Command to test whether the input string ends with "&" and
//thus represents a command that should be run in background
//[Input] char* inputbuffer - input string to test
//[Input] size_t bufferlen - size of input buffer
//[Return] bool - true if string ends with "&"
bool runinbackground(const char* inputbuffer, size_t bufferlen){
    //TO DO: Implement this function

    return false;
}
